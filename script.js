var page = ng.window.createPage('Page 1');

page.addLabel('Label 1');
page.addLabel('Label 2');

var lipsum = '<ul>' +
    '   <li>Morbi in sem quis dui placerat ornare. Pellentesque odio nisi, euismod in, pharetra a, ultricies in, diam. Sed arcu. Cras consequat.</li>' +
    '   <li>Praesent dapibus, neque id cursus faucibus, tortor neque egestas augue, eu vulputate magna eros eu erat. Aliquam erat volutpat. Nam dui mi, tincidunt quis, accumsan porttitor, facilisis luctus, metus.</li>' +
    '   <li>Phasellus ultrices nulla quis nibh. Quisque a lectus. Donec consectetuer ligula vulputate sem tristique cursus. Nam nulla quam, gravida non, commodo a, sodales sit amet, nisi.</li>' +
    '   <li>Pellentesque fermentum dolor. Aliquam quam lectus, facilisis auctor, ultrices ut, elementum vulputate, nunc.</li>' +
    '</ul>';

var tf = page.addTextField(lipsum);
page.addSpace(50);
page.addLabel(
    'Praesent dapibus, neque id cursus faucibus, tortor neque egestas augue, eu vulputate magna eros eu erat. Aliquam erat volutpat. Nam dui mi, tincidunt quis, accumsan porttitor, facilisis luctus, metus.');
page.addCheckBox(
    'Praesent dapibus, neque id cursus faucibus, tortor neque egestas augue, eu vulputate magna eros eu erat. Aliquam erat volutpat. Nam dui mi, tincidunt quis, accumsan porttitor, facilisis luctus, metus.');

var cb = page.addCheckBox({
    text: 'Foo bar baz quux',
    preset: true,
    onChange: function(newState) {
        ng.window.messageBox('New state: ' + newState);
    }
});

page.onNext = function() {
    var page2 = ng.window.createPage('Page 2');
    page2.addRadioGroup({
        text: 'Horizontal',
        options: [
            {name: '480p', text: '854x480'}, {name: '576p', text: '1024x576'},
            {name: '720p', text: '1280x720'},
            {name: '1080p', text: '1920x1080'}, {
                name: '4k',
                text:
                    '3840x2160dapibus, neque id cursus faucibus, tortor neque '
            }
        ],
        preset: '1080p'
    });
    page2.addRadioGroup({
        text: 'Vertical',
        vertical: true,
        options: [
            {name: 'opt1', text: 'Option 1'}, {name: 'opt2', text: 'Option 2'}
        ],
        onChange: function(sel) {
            ng.window.messageBox('Now selected: ' + sel);
        }
    });
    try {
        page2.addRadioGroup('foo');
    } catch (err) {
        print(err);
    }
    ng.window.pushPage(page2);
};

ng.window.pushPage(page);
// ng.window.playBgm('qrc:/bgm.mp3');