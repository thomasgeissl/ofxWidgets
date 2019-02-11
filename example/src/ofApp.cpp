#include "ofApp.h"

void ofApp::setup(){
    _gui.setName("gui");
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui._width, _gui._height);

    auto sideBar = ofxWidgets::widget::create();
    sideBar->setup(mainLayout->_width/5, mainLayout->_height);
    sideBar->_backgroundColor = ofColor::red;
    mainLayout->add(sideBar);

    auto content = ofxWidgets::widget::create();
    content->setup(mainLayout->_width/5*4, mainLayout->_height);
    auto contentLayout = ofxWidgets::layout::vBox::create();
    contentLayout->setup(content);

    auto topWidget = ofxWidgets::test::create();
    topWidget->setup(contentLayout->_width, contentLayout->_height/2);
    auto bottomWidget = ofxWidgets::test::create();
    bottomWidget->setup(contentLayout->_width, contentLayout->_height/2);

    contentLayout->add(topWidget);
    contentLayout->add(bottomWidget);
    content->add(contentLayout);

    mainLayout->add(content);
    _gui.add(mainLayout);
}

void ofApp::update(){
}

void ofApp::draw(){
}

void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y){
}

void ofApp::mouseDragged(int x, int y, int button){
}

void ofApp::mousePressed(int x, int y, int button){
}

void ofApp::mouseReleased(int x, int y, int button){
}

void ofApp::windowResized(int w, int h){
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){ 
}