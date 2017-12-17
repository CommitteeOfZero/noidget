var page = ng.window.createPage('Page 1');
page.addLabel('<b>Should be plain</b>');
var lbl = page.addLabel({text: '<b>Should also be plain</b>'});
page.addLabel({text: '<b>Should be rich</b>', richText: true});
page.onNext = function() {
    ng.window.messageBox('onNext()');
};
ng.window.pushPage(page);