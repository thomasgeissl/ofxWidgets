#include "ofApp.h"

void ofApp::setup(){
    // _gui = ofxWidgets::widget::create();
    // _gui->setup(ofGetWidth(), ofGetHeight());
    // _gui->setName("gui");
    // auto layout = ofxWidgets::layout::hBox::create();
    // layout->setup(_gui->_width-100, _gui->_height);
    // layout->setName("layout");
    // auto leftWidget = ofxWidgets::widget::create();
    // leftWidget->setup(ofGetWidth()/2, ofGetHeight());
    // leftWidget->setName("left");
    // auto rightWidget = ofxWidgets::widget::create();
    // rightWidget->setName("right");
    // rightWidget->setup(ofGetWidth()/2, ofGetHeight());
    // layout->add(leftWidget);
    // _gui->add(layout);
    _gui.setName("gui");
    auto testWidget = ofxWidgets::test::create();
    testWidget->setup(_gui._width, _gui._height);
    testWidget->setName("testWidget");
    _gui.add(testWidget);
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