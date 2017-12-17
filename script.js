var page = ng.window.createPage('Page 1');
page.addLabel('Hello World');
page.onNext = function() {
    ng.window.messageBox('onNext()');
};
ng.window.pushPage(page);