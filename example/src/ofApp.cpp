#include "ofApp.h"

void ofApp::setup(){
    _gui.setName("gui");
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui._width, _gui._height);
    _gui.add(mainLayout);
    auto leftWidget = ofxWidgets::test::create();
    leftWidget->setup(mainLayout->_width/2, mainLayout->_height);
    auto rightWidget = ofxWidgets::test::create();
    rightWidget->setup(mainLayout->_width/2, mainLayout->_height);
    mainLayout->add(leftWidget);
    mainLayout->add(rightWidget);
    // testWidget->setup(_gui._width, _gui._height);
    // testWidget->setName("testWidget");
    // _gui.add(testWidget);
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