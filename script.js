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

page.addLabel('Label 3');

var cb = page.addCheckBox({
    text: 'Foo bar baz quux',
    preset: true,
    onChange: function(newState) {
        ng.window.messageBox('New state: ' + newState);
    }
});

page.onNext = function() {
    tf.richText = true;
    ng.window.messageBox('onNext()');
};

ng.window.pushPage(page);