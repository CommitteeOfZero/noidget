// TODO remove, this is a mockup!



// window.installer will be provided by the native runtime
window.installer = {
    platform: 'windows'
};
window.pages = {};
window.state = {};

function logLocation(installLocation) {
    return product.platforms[installer.platform].logLocation.replace(
        '$installLocation', installLocation);
}

function backupScriptLocation(installLocation) {
    return product.platforms[installer.platform].backupScriptLocation.replace(
        '$installLocation', installLocation);
}

function tryReadInstallLog(installLocation) {
    var log = installer.logging.tryRead(logLocation(installLocation));
    if (log.success) {
        state.discovery.patchInstalled = true;
        state.discovery.patchIntVersion = log.patchIntVersion;
        state.discovery.patchDisplayVersion = log.patchDisplayVersion;
        if (log.installType == 'gameAndPatch') {
            state.discovery.gameInstallType = 'withPatch';
        }
    }
};

function discoverExistingInstallation(view) {
    state.discovery = {};
    if (installer.platform == 'windows') {
        var reg = installer.win32.readRegKey(
            product.platforms.windows.patchUninstallRegKey +
            '\\InstallLocation');
        if (!reg.success) {
            reg = installer.win32.readRegKey(
                product.platforms.windows.discUninstallRegKey +
                '\\InstallLocation');
            if (reg.success) {
                state.discovery.gameInstallType = 'disc';
            }
        }
        state.discovery.installLocation = reg.value;
        state.discovery.gameInstalled = true;
        tryReadInstallLog(reg.value);
    }
};

function validateNewInstallDir(location) {
    return installer.path.validDir(location) &&
        (!installer.fs.exists(location) || installer.fs.isEmptyDir(location));
};

function validateExistingInstallation(location) {
    // TODO implement
    // TODO rewrite game path (semicolons) on Windows
    return true;
};

function validateVitaScripts(loc) {
    result = {
        success: true,
        locationReadable: true,
        found: [],
        notFound: [],
        hashMismatch: []
    };

    try {
        installer.fs.listDir(loc);
    } catch (err) {
        result.success = false;
        result.locationReadable = false;
    }

    Object.keys(product.origScripts).forEach(function(script) {
        var path = installer.path.combine(loc, script);
        try {
            if (installer.fs.sha256(path) != product.origScripts[script]) {
                result.success = false;
                result.hashMismatch.push(script);
            }
            result.found.push(script);
        } catch (err) {
            result.success = false;
            result.notFound.push(script);
        }
    });
    return result;
}

var readmeText = installer.loadString('README.txt');
var licenseText = installer.loadString('LICENSE.txt');
var product = installer.loadJSON('product.json');

pages.Readme = function(view) {
    this.view = view;
    view.title = 'Readme';
    view.addTextField({text: readmeText});
};
pages.Readme.prototype.onNext = function() {
    installer.window.pushPage(pages.LicenseAgreement);
};

pages.LicenseAgreement = function(view) {
    this.view = view;
    view.title = 'License agreement';
    view.addTextField({text: licenseText});
    this.agreeCheckBox = view.addCheckBox(
        {label: {text: 'I have read and accept these terms.'}, default: false});
};

function continueFromVitaScripts(view) {
    state.shortcuts = {};
    if (installer.platform != 'mac') {
        installer.window.pushPage(pages.Shortcuts);
    } else {
        installer.window.pushPage(pages.AboutToInstall);
    }
};

// This is for loading from backup and displaying the script page only if no
// backup is found
function prepareVitaScripts(view) {
    state.vitaScripts = {};
    var loc = backupScriptLocation(state.installLocation);
    var validation = validateVitaScripts(loc);
    if (validation.success) {
        state.vitaScripts.location = loc;
        state.vitaScripts.createBackup = false;
        continueFromVitaScripts(view);
    } else {
        installer.window.pushPage(pages.VitaScripts);
    }
};

function prepareModeSelection(view) {
    discoverExistingInstallation(view);
    if (installer.platform == 'mac' && state.discovery.gameInstalled) {
        // TODO check requirements
        state.installLocation = state.discovery.installLocation;
        state.mode = 'patchOnly';
        prepareVitaScripts(view);
    } else {
        installer.window.pushPage(pages.ModeSelect);
    }
};

pages.LicenseAgreement.prototype.onNext = function() {
    if (this.agreeCheckBox.checked) {
        prepareModeSelection(view);
    } else {
        installer.window.messageBox(
            'You need to accept the license agreement to continue installation.');
    }
};

pages.ModeSelect = function(view) {
    this.view = view;
    view.title = 'Mode selection';

    this.installLocation = installer.path.expand(
        product.platforms[installer.platform].defaultInstallLocation);
    if (state.discovery.gameInstalled) {
        this.installLocation = state.discovery.installLocation;
    }

    view.addLabel({text: 'We have detected the following on your system:'});

    var gameText = '<b>Game:</b> ';
    if (state.discovery.gameInstalled) {
        gameText += 'installed';
        if (state.discovery.gameInstallType == 'disc') {
            gameText += ' (from disc)';
        } else if (state.discovery.gameInstallType == 'withPatch') {
            gameText += ' (with patch)';
        }
    } else {
        gameText += 'not installed';
    }
    view.addLabel({text: gameText, richText: true});

    if (state.discovery.gameInstalled) {
        var patchText = '<b>Patch:</b> ';
        if (state.discovery.patchInstalled) {
            patchText += 'installed (Version ' +
                state.discovery.patchDisplayVersion + ')';
        } else {
            patchText += 'not installed';
        }
        view.addLabel({text: patchText, richText: true});
    }

    this.modeGroup = view.addRadioGroup();
    modeGroup.add(
        {id: 'dmm', label: {text: 'Install patch and game from DMM download'}});
    modeGroup.add(
        {id: 'disc', label: {text: 'Install patch and game from discs'}});
    if (installer.platform != 'windows') {
        modeGroup.add({
            id: 'copy',
            label: {text: 'Install patch and copy game from bare folder'}
        });
    }
    if (installer.platform != 'mac') {
        // we do not allow installation in nonstandard folders on macOS
        // existing installations are autodetected *only*, so on macOS this
        // screen is just for new installs
        modeGroup.add({
            id: 'patchOnly',
            label: {text: 'Game is installed, install/update patch only'}
        });
        var o = this;
        this.installLocationPicker = view.addDirectoryPicker({
            label:
                {text: '<b>Game installation directory:</b>', richText: true},
            prompt: 'Parent of game installation directory',
            onPick: function(value) {
                // TODO figure out how to achieve this correctly
                o.installLocation =
                    installer.path.expand(installer.path.combine(
                        value,
                        installer.path.lastPart(
                            product.platforms[installer.platform]
                                .defaultInstallLocation)));
                o.installLocationPicker.value = o.installLocation;
            }
        });
        installLocationPicker.value = installLocation;
    }

    if (state.discovery.gameInstalled) {
        modeGroup.select('patchOnly');
    }

    // TODO space left
};

pages.ModeSelect.onNext = function() {
    state.installLocation = installLocation;
    state.mode = modeGroup.selection;

    if (state.discovery.patchInstalled &&
        !installer.path.equals(
            state.installLocation, state.discovery.installLocation)) {
        if (!view.confirm(
                'You have chosen a different installation directory than the detected previous installation. If you continue, you will no longer be able to reach your old installation (or its uninstaller) through shortcuts, and it will no longer be detected by (future update) installers. Are you sure?'))
            return;
    }

    if (state.mode != 'patchOnly' &&
        !validateNewInstallDir(state.installLocation)) {
        installer.window.messageBox(
            'Please specify a valid path to an empty or nonexistent folder for new game installation.');
        return;
    }

    if (state.mode == 'patchOnly' &&
        !validateExistingInstallation(state.installLocation)) {
        installer.window.messageBox(
            'The path you entered either does not exist, is not readable or does not contain a game installation we can detect.');
        return;
    }

    // TODO ensure this works for not-yet-existing directories too
    if (!installer.fs.isWritable(state.installLocation)) {
        installer.window.messageBox('The path you specified is not writable.');
        return;
    }

    prepareVitaScripts(view);
};

pages.VitaScripts = function(view) {
    this.view = view;
    view.title = 'Vita scripts';
    if (state.discovery.patchInstalled && state.mode == 'patchOnly') {
        // TODO error details maybe
        // TODO scenario: state.discovery.patchInstalled is true, but user picks
        // a different directory
        view.addLabel('No valid backup found in this installation.');
    }

    // TODO move these strings to product.json or something
    view.addLabel(
        'Select the folder containing unmodified, decrypted scripts from CHAOS;CHILD English Vita version 1.01.');

    this.scriptLocationPicker = view.addDirectoryPicker({
        label: {text: '<b>English script directory:</b>', richText: true},
        prompt: 'English script directory'
    });
};

pages.VitaScripts.prototype.onNext = function() {
    var loc = this.scriptLocationPicker.value;
    var validation = validateVitaScripts(loc);

    if (validation.success) {
        state.vitaScripts.location = loc;
        state.vitaScripts.createBackup = true;
        continueFromVitaScripts(view);
        return;
    }

    if (!validation.locationReadable) {
        installer.window.messageBox(
            'The path you entered either does not exist or is not readable.');
        return;
    }

    if (validation.found.empty()) {
        installer.window.messageBox(
            'The path you entered does not contain any scripts or is not readable by the installer.');
        return;
    }

    if (validation.notFound.empty()) {
        installer.window.messageBox(
            'The scripts in the folder you selected are not unmodified CHAOS;CHILD English Vita version 1.01 scripts.');
        return;
    }

    installer.window.modal(function(dlg) {
        dlg.dialogType = 'ok';
        dlg.addLabel(
            'The scripts in the folder you selected are corrupt or not unmodified CHAOS;CHILD English Vita version 1.01 scripts.');
        dlg.addLabel('Not found:');
        var notFoundText = '';
        validation.notFound.forEach(function(script) {
            notFoundText += script + '\n';
        });
        dlg.addTextField({text: notFoundText});
        dlg.addLabel('Hash mismatch (file present, wrong data):');
        var hashMismatchText = '';
        validation.hashMismatch.forEach(function(script) {
            hashMismatchText += script + '\n';
        });
        dlg.addTextField({text: hashMismatchText});
    });
};

pages.Shortcuts = function(view) {
    this.view = view;
    view.title = 'Shortcuts';

    var o = this;

    this.desktopCheckBox = view.addCheckBox({
        label: {text: 'Create/replace desktop shortcut'},
        default: true,
        onChange: function(value) {
            if (o.hasOwnProperty('desktopJapaneseCheckBox')) {
                o.desktopJapaneseCheckBox.enabled = value;
            }
        }
    });
    if (state.mode != 'patchOnly') {
        view.addRow(function(row) {
            row.addHorzSpacer(24);
            o.desktopJapaneseCheckBox = row.addCheckBox({
                label: {text: 'Also create shortcut for Japanese version'},
                default: false
            });
        })
    }
    this.startMenuCheckBox = view.addCheckBox({
        label: {text: 'Create/replace start menu shortcuts'},
        default: true,
        onChange: function(value) {
            if (o.hasOwnProperty('startMenuJapaneseCheckBox')) {
                o.startMenuJapaneseCheckBox.enabled = value;
            }
        }
    });
    if (state.mode != 'patchOnly') {
        view.addRow(function(row) {
            row.addHorzSpacer(24);
            o.startMenuJapaneseCheckBox = row.addCheckBox({
                label: {text: 'Also create shortcut for Japanese version'},
                default: false
            });
        })
    }
};
pages.Shortcuts.prototype.onNext = function() {
    state.shortcuts.desktop = this.desktopCheckBox.checked;
    state.shortcuts.desktopJapanese =
        (this.hasOwnProperty('desktopJapaneseCheckBox') &&
         this.desktopJapaneseCheckBox.checked);
    state.shortcuts.startMenu = this.startMenuCheckBox.checked;
    state.shortcuts.startMenuJapanese =
        (this.hasOwnProperty('startMenuJapaneseCheckBox') &&
         this.startMenuJapaneseCheckBox.checked);

    installer.window.pushPage(pages.AboutToInstall);
};