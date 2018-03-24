var product = {
    gameTitle: 'Chaos;Child',
    inputScriptVersionTitle: 'English Vita 1.01',
    paths: {
        PATCH_CONTENT: 'content',
        SCRIPT_BACKUP: '%CONFIG_LOCATION%/script_backup',
        SCRIPT_DIFFS: 'scriptDiffs',
        ENSCRIPT_MPK: '%GAME_PATH%/languagebarrier/enscript.mpk',
        ORIG_GAMEEXE_PATH: '%GAME_PATH%/Game.exe',
        PATCHED_GAMEEXE_PATH: '%GAME_PATH%/GameEng.exe',
        LAUNCHERENG_PATH: '%GAME_PATH%/LauncherEng.exe'
    },
    platforms: {
        windows: {
            paths: {
                DEFAULT_INSTALL_LOCATION:
                    '%PROGRAMFILES(X86)%\\CHAOS\uFF1BCHILD',
                CONFIG_LOCATION: '%LOCALAPPDATA%/Committee of Zero/CC'
            }
        }
    },
    gameProbeFilePath: '%GAME_PATH%/USRDIR/sysse.mpk',
    gameProbeHash: 'c652ad182ae5c9c0f12d8cdac17d8ca3',
    untouchedGameExeHash: '9265520ff9e09da0781e6a9b03c1098e',
    gameExeSdWrapSize: 0x600000,
    gameExeStrippedSize: 9969152,
    // Large-address-aware flag
    gameExeLaaNeedle: '00 00 00 00 00 00 00 00 E0 00 02 01',
    gameExeLaaReplace: '00 00 00 00 00 00 00 00 E0 00 22 01',
    origScriptHashes: {
        '_map.scx': '6cd9aea8725821c17e3d2e96a9a5d2d3',
        '_startup_ps4.scx': '3cd207cb0d3ffcdb6024418eb9760269',
        '_Startup_PSV.scx': '2ff69b835f5ce6c1475283198e6ff3dd',
        '_startup_win.scx': '8d0d2b5b92c4d3b339a043efd96abe20',
        '_system.scx': '5177c29ed404abddf2a33f88c973be0e',
        '_tips.scx': '63bffc3737612cacbe5a4eb5541ef8fe',
        'anime.scx': '1483cfff8524f3f0929a7d194a53130f',
        'cc_01_01.scx': '469ea2c677d7df9e0e0ec470772ea1fb',
        'cc_01_02.scx': 'cb591355c023fa0d26f96d301fd5792f',
        'cc_01_02b.scx': '2feb6664703c1adb92b66cb166900f35',
        'cc_01_03.scx': '69893aef598c16131df1a3e7b89e7f22',
        'cc_01_04.scx': '7b0421916f58a68081b3f115cf1be974',
        'cc_01_05.scx': 'ff5c3f532f301493005bd39d4b598cd1',
        'cc_01_06.scx': '73841d6bdce0f22d0c538c08844c1f4e',
        'cc_01_07.scx': 'a094a8eb57c7dd430f2db4b878f822e5',
        'cc_01_08.scx': '65001646a0340bcc784ee78cceef9b64',
        'cc_01_08b.scx': '3b0f3f9135638dc9b889a75e43827c9c',
        'cc_01_09.scx': 'bbeaf5668d1cdbce445097139630dfc9',
        'cc_01_10.scx': '3740f9f44e77ffb7b1dd6d8236976fd4',
        'cc_01_11.scx': '1afbc4f31bb1ff446df0c064e50d0828',
        'cc_01_12.scx': 'bb717d07c1b8d6c739f45558fe0dba1c',
        'cc_01_13.scx': '43f8f1901e3fe4a411625fb6a6ce2dc0',
        'cc_01_13b.scx': '28be5c16faf6fa06e6210c7ea71f99a4',
        'cc_01_14.scx': '448408ddbfd03f05fa120fb3d267bc2a',
        'cc_01_15.scx': '24386828d26d93306c09b444cc6b8e55',
        'cc_01_16.scx': '0cf1ec4824a9e77f99a0261fd6edf712',
        'cc_01_17.scx': 'f91d70ed4c5246d2bd5d6c596c37fd51',
        'cc_02_01.scx': 'ece4022975bc93ed1bf997f2e93c617a',
        'cc_02_02.scx': '4ae728e4c2dd803c528d11c55342286d',
        'cc_02_02b.scx': 'b4f297cae66c4721877a040a53f82376',
        'cc_02_03.scx': '5d953b1c450b31e84afb7081697cbc6e',
        'cc_02_04.scx': 'c8ed56f3bc82718805c052e4da0e6aba',
        'cc_02_05.scx': '73275573514cc4deb3acff4de802ef47',
        'cc_02_06.scx': 'aef37f843bc495a453f348ac2bb22389',
        'cc_02_07.scx': '3bb739b3d8b7335cddbe302accde385a',
        'cc_02_08.scx': '690861053327280425e7d279c076b42e',
        'cc_02_09.scx': '3c2cbcabbe245a2fe41320644b4c7bb5',
        'cc_02_10.scx': '65b03fe46a9aa29c6a2034946ca97a0d',
        'cc_02_11.scx': '88d787420f47c3231477bdc820be0ccb',
        'cc_02_12.scx': 'f05dfab5f478072bd257ce625926a41a',
        'cc_02_12b.scx': 'cb065b49438a118fa54f696934f507f6',
        'cc_02_13.scx': '0fcfd7f60641c2356b438894da1ee426',
        'cc_02_14.scx': '5b0acf17cd25281888cd8b66af84041e',
        'cc_02_15.scx': '2007516146cdd7a41507e7773320bfba',
        'cc_03_01.scx': '34ea2c69dbf42f8e7723f6f3c15715ec',
        'cc_03_02.scx': 'fe6dedd0365eb1224f64218328902046',
        'cc_03_02b.scx': '578a0d8fb414180608e57329cc903b0a',
        'cc_03_03.scx': '0d18f0717753958daae4777fb8ec7df5',
        'cc_03_04.scx': '61aefd702e272bcd923abeebb6b04943',
        'cc_03_05.scx': '243c9394c71adab4c39c354693bd2b33',
        'cc_03_06.scx': '86d86f7cf0de7636fb0907958bf4e542',
        'cc_03_06b.scx': 'c20e761cd62a68f56b1b5da80f73178b',
        'cc_03_07.scx': 'fe3d971d6274e3625beab94134b6c82f',
        'cc_03_08.scx': '7cac8d737b82d9e13631bfe53d9106f9',
        'cc_03_09.scx': 'de5e738523121f956b4e23e881f6f52a',
        'cc_04_00.scx': '3940c61644fffe34b8a59001839a7f33',
        'cc_04_01.scx': 'f6ddbf0ef5d47e46d6a47933560c820c',
        'cc_04_02.scx': 'a61c0f040d72049c452013cc72725a69',
        'cc_04_02b.scx': 'b41c3e447e9924ad261fbc93b5d9ec4c',
        'cc_04_03.scx': '7a825ab56e50924181b3d14ba36eabaa',
        'cc_04_03b.scx': 'f150b93d79352ee3eb4051f80dcf457f',
        'cc_04_04.scx': '0184c5d495c0073605e1ffc78031585b',
        'cc_04_05.scx': 'cb5115f43b986e28dfa78d45a2a9c532',
        'cc_04_06.scx': '3d548bb8719ce4123bad799fa0b17fe7',
        'cc_05_01.scx': '0774834d167509654ec3d3bab223645d',
        'cc_05_02.scx': '5b2e159e3aad48000709cd91076edaac',
        'cc_05_03.scx': '9b198483c07225ce38be8cebff2845f5',
        'cc_05_04.scx': '5ac7ced9f3275da86fa13869cbcc35c1',
        'cc_05_05.scx': '0c93235a11e1180e67022e7c008facb0',
        'cc_05_06.scx': '4d4b07840151b6dc37c627b190fec1d8',
        'cc_05_07.scx': '8da5e220b228ef7ba76fe618b3e2babd',
        'cc_06_01.scx': 'b651f7dfb8d863ab182ee6b579535b7d',
        'cc_06_02.scx': '133a75916b02c6f4ae0c19949d3663b6',
        'cc_06_03.scx': 'e3d7fbb0b7bccd2c352802add1c11dbc',
        'cc_06_04.scx': 'cc79bbcb9c10ecf6c642606b0e35a2cb',
        'cc_06_05.scx': '7d1f995a869a68101b4c5e2edeecd479',
        'cc_06_06.scx': '6dfee79f408c10602f0531a8d3ee6d99',
        'cc_06_07.scx': '0951e43f21f8ce5d9c9279f355397736',
        'cc_06_08.scx': 'ba0c972f495a4afa439bb8de525897e0',
        'cc_06_09.scx': '4d2be7d8cf17cdfb5b4a12e2568304bf',
        'cc_07_01.scx': 'f539424cdac523a5426c94dbecd90dc3',
        'cc_07_02.scx': '31c9601a828e6afa2c3cefe5bde71c51',
        'cc_07_03.scx': '376b87d96835c1e709624a74b6024069',
        'cc_07_04.scx': '1abe6d83bd9316d1517b7b595fa6909f',
        'cc_07_05.scx': 'db88db1e668609441bd2af5bf272372d',
        'cc_07_06.scx': '678070b73cfda7294b93a28ba5ba9165',
        'cc_07_07.scx': 'e3d4240308eca38a198b3351e98e77b3',
        'cc_07_08.scx': '17c13d42cc940e544093a85e964c2d01',
        'cc_07_09.scx': '063c8a8018f5cfb98162ab6fd4350d72',
        'cc_07_10.scx': 'c1de7c0f9611ada432bba05bcd67b97b',
        'cc_07_11.scx': '789c651cd768a7dba4f6099d7750d1ac',
        'cc_08_01.scx': '3d6e1182a51fd7370f1e420d0460f7a3',
        'cc_08_02.scx': '815d1802584e8155468f75b1912920b6',
        'cc_08_03.scx': 'b52596771e08cea4320a34d6ec23394a',
        'cc_08_04.scx': 'eeda69c050aacbfa2a4f693312b395de',
        'cc_08_05.scx': '7475670a7a864b214e7b1c240a29836f',
        'cc_08_06.scx': '0a3c65d406eae2635cf082174840be84',
        'cc_08_07.scx': '65bed3edfb20e188355a130c7d0e08ac',
        'cc_09_01.scx': '98e537ba4aca13b993665c4f5ba46fce',
        'cc_09_02.scx': 'bf9bfa0f2bdb188a14705b55e0d79827',
        'cc_09_03.scx': '8a70999d216ed51dbdd8a93c17157dc9',
        'cc_09_04.scx': '3cb711f7b17dd4e328da5730759e5db3',
        'cc_09_05.scx': 'df73f52009c239cc3a5bed46f7bf402f',
        'cc_09_06.scx': '2c44e222bdc85ecefb2462b06fcbf54f',
        'cc_09_07.scx': 'f36cd08b5138c5bc70874085999ef98b',
        'cc_09_08.scx': '5be0bf88d012cfe7ba373193b4818b8c',
        'cc_09_09.scx': 'f9e907bc683d23a0715f27207a351041',
        'cc_09_10.scx': 'e6314415d784c111af872184e4a8efd3',
        'cc_10_01.scx': '02cac71625e57adcddd19837431eab35',
        'cc_10_02.scx': 'f8b365b27c51f99c005fa9d576b5e7f8',
        'cc_10_03.scx': '49f50b29ca416631e9f7f5ebc54a73c3',
        'cc_10_04.scx': '38b65873d3d6d0aa8008534e4fb69af6',
        'cc_10_05.scx': 'bd5ba97f63f93bfd1c914eccefd7d279',
        'cc_10_06.scx': '7d42ed400fd3bff9788af30ad8ac85d1',
        'cc_10_07.scx': 'f6cd753fdd92daeb23206c1f8cdd34f9',
        'cc_10_08.scx': '22f6fe9d4ec918f3ba340e8ae3de8c11',
        'cc_11_01.scx': 'c552daa94c3e7ccd90f6069aa19dc98d',
        'cc_11_02.scx': 'c29ee91b4d5f03aebe159ec0a62449bd',
        'cc_11_03.scx': '93d42ec701e33beaf2333d60fd9c632e',
        'cc_11_04.scx': '7bc0b5fa57998dbe60689b45a985f3d4',
        'cc_11_05.scx': 'f9abd7a558139396971191676c3f2f7a',
        'cc_11_06.scx': '66d89058fa547e43b8476c88623676c9',
        'cc_11_07.scx': '3e5124e71b08c125e652717eb82039a8',
        'cc_11_08.scx': 'a6943a957a0e30d6f3dcc3d9cbeb658a',
        'cc_11_09.scx': 'ae32888125b4d6d185afc4d26f7c1624',
        'cc_11_10.scx': 'a4f8d1c8823182a39ec12a47435b4470',
        'cc_11_11.scx': 'b91b5427c522b023c97490446ca069a6',
        'cc_11_12.scx': 'a0d0435a607be952afeba412abe71bc5',
        'cc_11_13.scx': 'de8edb4026be26ccca4eaeab9947408c',
        'cc_11_14.scx': 'e7ea6308eea48c4d0aedef6f0230cf4e',
        'cc_ah_01.scx': '9998fb1290fc4f41098cfe3d3d1ff183',
        'cc_ah_02.scx': '877eb3c7e4e55351ccdde0f355a7238f',
        'cc_ah_03.scx': '48efb37ea63e1cf2772ab0e1bc8517a5',
        'cc_ah_04.scx': '1d31c5bddf899ca0614072bb9105bdc7',
        'cc_ah_05.scx': '2871a6d3ccad07111e6815bf56885668',
        'cc_ah_06.scx': '46603468c5f386075bf0e1868f5f453d',
        'cc_ah_07.scx': '6aef97fdc54825a633e07d0d2edf68a9',
        'cc_ah_08.scx': '9ef6f54fe95b3e81b39d679f42b51fb6',
        'cc_ah_09.scx': 'ab69fb980c75040fc8394f971e989d7b',
        'cc_ah_10.scx': 'f8a10531d3a3a86a70aee7676e5c2d1b',
        'cc_ah_11.scx': '3a0fcffa0f7387243c4e7753015e9b28',
        'cc_ah_12.scx': '3e7c5e133f1d52c1c9fd648f625e6a87',
        'cc_ah_13.scx': '44c69958da897b30ceba87e020902bf8',
        'cc_ah_14.scx': 'a78b07a35da037bc06dd4bc2f60289a3',
        'cc_ah_15.scx': '0dc226ddce0008d5ab75df6fd613278c',
        'cc_ah_16.scx': '6897cfe5c1a243a54374e509dc28650f',
        'cc_ah_17.scx': 'b13b3e4e028dc53dead4eb112e297a1d',
        'cc_ah_18.scx': 'df118dee825168b0993d8df276496e35',
        'cc_ah_19.scx': '49bac9de778d1cd4ab3f0952092378e1',
        'cc_ah_20.scx': '3bc562b673d15e9e32cc118641fa89bd',
        'cc_ah_21.scx': '6e4e10166e721add9dc5eabaa35f1cc2',
        'cc_ah_22.scx': '85d04ad404e066b672254df151c87571',
        'cc_ah_24.scx': '31c31139fd4af11dd9b9c90272a4ab17',
        'cc_kh_01.scx': '694bdf53e943edddc2ed5449522613c4',
        'cc_kh_02.scx': '4c411d2eaebd1bfc6bb33bcdaaa1d5a2',
        'cc_kh_03.scx': '62240c4d4a90f364f80b9bdb75069679',
        'cc_kh_04.scx': '32cdb7793b88b18ea3a7c2d722617f02',
        'cc_kh_05.scx': '81560af2125f1cadac2281c97a000c9a',
        'cc_kh_06.scx': '0797b2c5607e5425a5553d3622a95a29',
        'cc_kh_07.scx': '51f936256b948daef3b8f6c35f63e858',
        'cc_kh_08.scx': 'c03db1e2a66c9b7a7f35206d5ebd4d4e',
        'cc_kh_09.scx': '53eb13374bc08f8d8594a9162efcfa90',
        'cc_kh_10.scx': '0957da805e4c3dd9cc81d1400dd494c5',
        'cc_kh_11.scx': 'ed1b3b3ca3b69bf025c7eb038a3bff6a',
        'cc_kh_12.scx': 'c2783cc9c1f55d02c1c73aa006191417',
        'cc_kh_13.scx': '3446a98648dffc7479b58ad3409254ec',
        'cc_kn_01.scx': 'b5bf9f1115d81ed3f5f6a46605133239',
        'cc_kn_02.scx': '0fd5434b2272f4d9ed868a2ff9b8795a',
        'cc_kn_03.scx': 'cf6f455f49578ab09cf5b10264843dd0',
        'cc_kn_04.scx': '37d8196d749f72731d32669ee1b97bca',
        'cc_kn_05.scx': '22b53f7918ac733cacde3651e249f69d',
        'cc_kn_06.scx': '005b8e903822ae9d9040e4c7a2cab022',
        'cc_kn_07.scx': '3c6a2296f949508ffef6f293070b9689',
        'cc_kn_08.scx': '3630d481c53ae8cdfdd80d2cf24bf548',
        'cc_kn_09.scx': 'af93fe8114b50ef88adddb08e4230cf9',
        'cc_kn_10.scx': 'ed60995caca71f1f06847cace9d484e6',
        'cc_kn_11.scx': '523d382abc4f00b215741a355c5dbcd7',
        'cc_kn_12.scx': 'ec056d629cfefca7680c9236ab956d2f',
        'cc_kn_13.scx': '50d12143cd0baf334c5665239ecb5e74',
        'cc_kn_14.scx': '783c323cea7fe47ac1dca55c4a805463',
        'cc_kn_15.scx': '9e85ce033297cb60ef4fbf0b3d66ecb6',
        'cc_kn_16.scx': '99a985513ae5b4c67023b82d32757093',
        'cc_kn_17.scx': '6cf45a5adf42a7dc21d5ffb3727d6267',
        'cc_kn_18.scx': 'dcc2f23abbd6a3430c799a511b1d127c',
        'cc_kn_19.scx': '326263246f0824dddeb4a34136f5220d',
        'cc_kn_20.scx': '956d941336679f1726f24fcfb8c8f889',
        'cc_kn_21.scx': 'c10e5580049aeb002836f6a250450842',
        'cc_tr_01.scx': '725d63dac78195af49820736726b741d',
        'cc_tr_02.scx': 'd900c35fbbdda74cc6389a67013ab1d5',
        'cc_tr_03.scx': '5f37bbf959c171a7ebd7e51401de5e94',
        'cc_tr_04.scx': '79c3f6d51b8b4183884f41857fec8f96',
        'cc_tr_05.scx': 'ef52df75d67ca581f41d5ca4c591fb56',
        'cc_tr_06.scx': 'b74cd832cbdd78465d4f87a95b26da85',
        'cc_tr_07.scx': '3062345504046e5e781a391b14ddaecb',
        'cc_tr_08.scx': '014ce5abdb8cc94d6d58d3aaa6ba43cc',
        'cc_tr_09.scx': '855e2162b05ce36f32945dc9f2b29bef',
        'cc_tr_10.scx': '3d51b54f2be8f8d99475dfee39ae9c96',
        'cc_tr_11.scx': '27af708e4d80ed8927797327c5025745',
        'cc_tr_12.scx': '5b609419fdbf60369ee4893385d6ed49',
        'cc_uk_01.scx': 'dc07ed1d4f22f75b82928de57e461197',
        'cc_uk_02.scx': 'b2b86c19d2d72977ad29a65554b755a0',
        'cc_uk_03.scx': '4d01a8d89b8a2d64fa979d9624fd2cc0',
        'cc_uk_04.scx': '17e241739437284558238fe495cd56d8',
        'cc_uk_05.scx': '3cd741f7a4d09b48afa317b64a3748c4',
        'cc_uk_06.scx': '397567ba2ec3a87c91d6103f0cfd54ff',
        'cc_uk_07.scx': '8d625cbd8a402820eee67a1480fd3736',
        'cc_uk_08.scx': '6ae44dcbd95bbbb6800e912202383ce6',
        'cc_uk_09.scx': '2b590e57445179efe834b7e17a1872f0',
        'cc_uk_10.scx': '033111e009e9d542b63649042007d1c0',
        'cc_uk_11.scx': '91b722fc2ff6c0847a9c5a621ef814bd',
        'clrflg.scx': 'eaf72bbc0b506765b5f5dced0aba9b4a',
        'macrosys.scx': '67f91ba11afb6c6382a4c641d3435901',
        'macrosys2.scx': '875f74622ad195cc8f1aac8bfeeb440e',
        'main00.scx': 'c14738c18078ef99f364f22335388f9f',
        'main90.scx': 'c0e4deb2df299230e531088b2692534c',
        'mstart.scx': 'd41c91ef946392de8051e8a8ca0b97db',
        'zz.scx': '5995782b63ff57d4f880f0b861a1fdd5',
        'zzz.scx': 'f418fcd326f28569178a312207f95da6'
    }
};

var state = {};

function validateOrigScripts(loc) {
    result = {success: true, found: [], notFound: [], hashMismatch: []};

    var fs = ng.fs.global();
    Object.keys(product.origScriptHashes).forEach(function(script) {
        var path = loc + '/' + script;
        try {
            if (fs.md5sum(path) != product.origScriptHashes[script]) {
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

function DoTx() {
    // TODO uninstaller / registry info
    /*
    if (ng.systemInfo.platform() == ng.systemInfo.OsFamily.Windows) {
        var regSection = ng.tx.addSection('Registration');
    }
    */

    var patchContentSection = ng.tx.addSection('Copying patch content');
    patchContentSection.copyFiles('%PATCH_CONTENT%/*', '%GAME_PATH%');

    var applyPatchesSection = ng.tx.addSection('Applying patches');
    applyPatchesSection.log(
        'Backing up original ' + product.gameTitle + ' (' +
        product.inputScriptVersionTitle + ') scripts for future updates...');
    applyPatchesSection.createDirectory('%SCRIPT_BACKUP%');
    var backupOp = applyPatchesSection.copyFiles(
        '%ORIG_SCRIPT_PATH%/*', '%SCRIPT_BACKUP%');

    applyPatchesSection.log('Building patched script archive...');
    var enscriptMpk = applyPatchesSection.buildMpk('%ENSCRIPT_MPK%');
    product.enscript.forEach(function(entry) {
        var inputPath = '%ORIG_SCRIPT_PATH%/' + entry.filename;
        var diffPath = '%SCRIPT_DIFFS%/' + entry.filename + '.vcdiff';
        if (ng.fs.global().pathIsFile(diffPath)) {
            var stream = ng.tx.diffStreamBuilder(inputPath, diffPath);
            enscriptMpk.streamOpen(stream);
            enscriptMpk.file({
                id: entry.id,
                filename: entry.filename,
                source: stream,
                size: entry.size
            });
            enscriptMpk.streamClose(stream);
        } else {
            enscriptMpk.file({
                id: entry.id,
                filename: entry.filename,
                source: inputPath,
                size: entry.size
            });
        }
    });

    applyPatchesSection.log('Patching Game.exe...');

    if (ng.fs.global().md5sum('%ORIG_GAMEEXE_PATH%') ===
        product.untouchedGameExeHash) {
        var stream = ng.tx.fileStreamBuilder('%ORIG_GAMEEXE_PATH%');
        applyPatchesSection.streamOpen(stream);
        applyPatchesSection.streamSeek(stream, product.gameExeSdWrapSize);
        var writer =
            applyPatchesSection.streamWriter(stream, '%PATCHED_GAMEEXE_PATH%');
        writer.setSize(product.gameExeStrippedSize);
        applyPatchesSection.streamClose(stream);
    } else {
        applyPatchesSection.copyFiles(
            '%ORIG_GAMEEXE_PATH%', '%PATCHED_GAMEEXE_PATH%');
    }

    applyPatchesSection.binarySearchReplace(
        '%PATCHED_GAMEEXE_PATH%', product.gameExeLaaNeedle,
        product.gameExeLaaReplace);

    if (state.shouldCreateDesktopShortcut ||
        state.shouldCreateStartMenuShortcut) {
        var shortcutsSection = ng.tx.addSection('Creating shortcuts');
        // TODO shortcuts
    }

    if (state.shouldRunLauncher) {
        ng.tx.addExecuteAfterFinish('%LAUNCHERENG_PATH%');
    }

    // And hundreds of lines of code later...
    ng.tx.run();
}

var StartPage = function() {
    nglib.PageController.call(this, 'Readme');
    this.view.addTextField('<Readme placeholder>');
};
StartPage.prototype = Object.create(nglib.PageController.prototype);
StartPage.prototype.onNext = function() {
    (new LicensePage()).push();
};

var LicensePage = function() {
    nglib.PageController.call(this, 'License');
    this.view.addTextField(
        'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Porta non pulvinar neque laoreet suspendisse interdum consectetur libero. Pretium aenean pharetra magna ac placerat vestibulum lectus. Sed nisi lacus sed viverra tellus in hac habitasse. Massa placerat duis ultricies lacus sed turpis tincidunt id. Massa massa ultricies mi quis hendrerit dolor magna eget est. Commodo quis imperdiet massa tincidunt nunc pulvinar sapien et. Quis viverra nibh cras pulvinar mattis nunc sed blandit libero. Velit laoreet id donec ultrices. Aliquam sem et tortor consequat id. Parturient montes nascetur ridiculus mus mauris vitae ultricies. Malesuada proin libero nunc consequat. Cursus vitae congue mauris rhoncus aenean vel elit scelerisque. Eget sit amet tellus cras. Augue ut lectus arcu bibendum. Elit ullamcorper dignissim cras tincidunt lobortis feugiat vivamus at. Amet mauris commodo quis imperdiet massa tincidunt nunc. Fermentum et sollicitudin ac orci phasellus egestas tellus. At urna condimentum mattis pellentesque.\n\nDui id ornare arcu odio ut sem.Cursus mattis molestie a iaculis at.Id donec ultrices tincidunt arcu non sodales neque sodales.Lectus proin nibh nisl condimentum id venenatis a condimentum vitae.Sit amet massa vitae tortor condimentum.Nulla facilisi nullam vehicula ipsum.Aliquam eleifend mi in nulla posuere sollicitudin.Sed viverra ipsum nunc aliquet bibendum enim facilisis gravida neque.Facilisis gravida neque convallis a cras semper auctor.Duis ut diam quam nulla porttitor massa id neque aliquam.Tristique senectus et netus et malesuada fames ac turpis egestas.Velit scelerisque in dictum non consectetur.Est ante in nibh mauris cursus.At in tellus integer feugiat scelerisque varius.Blandit cursus risus at ultrices mi tempus imperdiet nulla malesuada.Enim blandit volutpat maecenas volutpat.Eget duis at tellus at urna condimentum mattis pellentesque id.Quis ipsum suspendisse ultrices gravida.Lectus mauris ultrices eros in cursus.\n\nUltricies leo integer malesuada nunc vel.Pellentesque diam volutpat commodo sed egestas egestas fringilla phasellus.Metus dictum at tempor commodo ullamcorper a lacus vestibulum.Nec dui nunc mattis enim ut tellus elementum sagittis.Proin sagittis nisl rhoncus mattis rhoncus urna neque viverra.Libero nunc consequat interdum varius sit amet mattis vulputate.Sit amet massa vitae tortor condimentum lacinia quis.Ut morbi tincidunt augue interdum.Vulputate enim nulla aliquet porttitor lacus luctus accumsan tortor.Mauris pharetra et ultrices neque ornare aenean euismod elementum nisi.Nisl tincidunt eget nullam non nisi est sit amet facilisis.Mollis aliquam ut porttitor leo a diam sollicitudin tempor.');
    this.acceptedCheckBox = this.view.addCheckBox(
        'I have read and accept these terms and conditions.');
};
LicensePage.prototype = Object.create(nglib.PageController.prototype);
LicensePage.prototype.onNext = function() {
    if (!this.acceptedCheckBox.checked) {
        ng.window.messageBox(
            'You cannot proceed if you do not accept the license agreements.');
        return;
    }

    (new DirectoryPage()).push();
};

var DirectoryPage = function() {
    nglib.PageController.call(this, 'Settings');
    this.view.addLabel(
        'Choose directory where ' + product.gameTitle +
        ' (PC version) is installed, containing files like Game.exe and the USRDIR folder:');
    this.gameDirectoryPicker = this.view.addDirectoryPicker({
        title: 'Choose game directory',
        preset: ng.fs.global().expandedPath('%DEFAULT_INSTALL_LOCATION%')
    });
    this.view.addSpace(16);
    this.view.addLabel(
        'Choose directory with scripts from ' + product.gameTitle + ' (' +
        product.inputScriptVersionTitle +
        '), containing files ending in .scx:');
    this.scriptDirectoryPicker = this.view.addDirectoryPicker(
        {title: 'Choose translated scripts directory'});
    this.view.addSpace(32);
    this.desktopShortcutCb =
        this.view.addCheckBox({text: 'Create desktop shortcut', preset: true});
    this.startMenuShortcutCb = this.view.addCheckBox(
        {text: 'Create Start Menu shortcut', preset: true});
    this.launcherCb = this.view.addCheckBox(
        {text: 'Run launcher after installation', preset: true});
};
DirectoryPage.prototype = Object.create(nglib.PageController.prototype);
DirectoryPage.prototype.onNext = function() {
    ng.fs.global().setMacro('GAME_PATH', this.gameDirectoryPicker.value);
    ng.fs.global().setMacro(
        'ORIG_SCRIPT_PATH', this.scriptDirectoryPicker.value);

    if (!ng.fs.global().pathIsDirectory('%GAME_PATH%')) {
        ng.window.messageBox(
            'Game directory doesn\'t exist or isn\'t a directory');
        return;
    }
    if (!ng.fs.global().pathIsWritable('%GAME_PATH%')) {
        ng.window.messageBox('Game directory isn\'t writable');
        return;
    }
    if (!ng.fs.global().pathIsFile(product.gameProbeFilePath) ||
        ng.fs.global().md5sum(product.gameProbeFilePath) !=
            product.gameProbeHash) {
        ng.window.messageBox(
            'Could not find ' + product.gameTitle +
            ' (PC version) in specified directory');
        return;
    }

    if (!ng.fs.global().pathIsDirectory('%ORIG_SCRIPT_PATH%')) {
        ng.window.messageBox(
            'Script directory doesn\'t exist or isn\'t a directory');
        return;
    }
    if (!ng.fs.global().pathIsReadable('%ORIG_SCRIPT_PATH%')) {
        ng.window.messageBox('Script directory isn\'t readable');
        return;
    }

    var scriptValidation =
        validateOrigScripts(this.scriptDirectoryPicker.value);
    if (scriptValidation.found.length == 0) {
        ng.window.messageBox(
            'Script directory is unreadable or contains no scripts.');
        return;
    }
    if (!scriptValidation.success) {
        ng.window.modal(ng.view.DlgType.OK, function(dlg) {
            dlg.width = 300;
            var lbl = dlg.addLabel(
                'Script directory is corrupt or from a different game or from a different version of ' +
                product.gameTitle +
                '. <br><br>You need to provide <i><b>unmodified</b></i> scripts from ' +
                product.gameTitle + ' ' + product.inputScriptVersionTitle +
                '.');
            lbl.richText = true;
            var err = '';
            if (scriptValidation.notFound.length > 0) {
                err += '<b>Not found:</b><hr><p>';
                scriptValidation.notFound.forEach(function(script) {
                    err += script + '<br>';
                });
                err += '</p>';
            }
            if (scriptValidation.hashMismatch.length > 0) {
                err += '<b>Wrong data:</b><hr><p>';
                scriptValidation.hashMismatch.forEach(function(script) {
                    err += script + '<br>';
                });
                err += '</p>';
            }
            dlg.addSpace(16);
            var tf = dlg.addTextField({text: err, richText: true});
            dlg.addSpace(16);
        });
        return;
    }

    var gamePath = ng.fs.global().expandedPath('%GAME_PATH%');
    var splitter =
        Math.max(gamePath.lastIndexOf('/'), gamePath.lastIndexOf('\\'));
    var left, right;
    if (splitter == -1) {
        // shouldn't happen, but...
        left = '';
        right = gamePath;
    } else {
        left = gamePath.substr(0, splitter);
        right = gamePath.substr(splitter + 1, gamePath.length - (splitter + 1));
    }

    if (left.indexOf(';') != -1 || left.indexOf('\uFF1B') != -1) {
        ng.window.messageBox(
            'Game path contains semicolons, which causes problems with the patch, and general problems on some locales. Please install to a location not containing semicolons.');
        return;
    }

    if (right.indexOf(';') != -1 || right.indexOf('\uFF1B') != -1) {
        var shouldRename = ng.window.modal(ng.view.DlgType.YesNo, function(dlg) {
            dlg.width = 300;
            var lbl = dlg.addLabel(
                'Game directory name contains semicolons, which causes problems with the patch, and general problems on some locales.<br><br>Want to rename the directory?');
            lbl.richText = true;
        });
        if (!shouldRename) return;

        var newGamePath = gamePath.replace(/[;\uFF1B]/g, '');
        if (ng.fs.global().pathExists(newGamePath)) {
            ng.window.messageBox(
                '"' + newGamePath + '" already existed before renaming');
            return;
        }
        try {
            ng.fs.global().rename(gamePath, newGamePath);
        } catch (err) {
            ng.window.messageBox(
                'Renaming "' + gamePath + '" to "' + newGamePath + '" failed.');
            return;
        }
        ng.fs.global().setMacro('GAME_PATH', newGamePath);
    }

    state.shouldCreateDesktopShortcut = this.desktopShortcutCb.checked;
    state.shouldCreateStartMenuShortcut = this.startMenuShortcutCb.checked;
    state.shouldRunLauncher = this.launcherCb.checked;

    //(new DummyPage()).push();

    // ng.window.runTx();

    var testSection = ng.tx.tx().addSection('Test section');
    testSection.log('Log test');
    testSection.createDirectory('G:/Games/SGTL/CHAOSCHILD_2/dummyDir');
    testSection.copyFiles(
        'G:/Games/SGTL/CHAOSCHILD', 'G:/Games/SGTL/CHAOSCHILD_2');
    testSection.log('done');
    ng.tx.run();
};

var DummyPage = function() {
    nglib.PageController.call(this);
    this.view.addSpace(16);
    this.view.addLabel({
        text:
            '<center><font size=20>I clicked through the entire installer and all I got was this dummy page</font></center>',
        richText: true
    });
    this.view.addSpace(32);
    this.view.addLabel(
        'Installation directory: ' +
        ng.fs.global().expandedPath('%GAME_PATH%'));
    this.view.addLabel(
        'Script directory: ' +
        ng.fs.global().expandedPath('%ORIG_SCRIPT_PATH%'));
    this.view.addLabel(
        'Create desktop shortcut: ' +
        state.shouldCreateDesktopShortcut.toString());
    this.view.addLabel(
        'Create Start Menu shortcut: ' +
        state.shouldCreateStartMenuShortcut.toString());
    this.view.addLabel('Run launcher: ' + state.shouldRunLauncher.toString());
};
DummyPage.prototype = Object.create(nglib.PageController.prototype);

ng.fs.global().addMacros(product.paths);
switch (ng.systemInfo.platform()) {
    case ng.systemInfo.OsFamily.Windows:
        ng.fs.global().addMacros(product.platforms.windows.paths);
        break;
}

ng.window.setMessageBoxIcon(':/assets/kozue48.png');

(new StartPage()).push();