#include "ofApp.h"

void ofApp::setup(){
    _gui.setName("gui");
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui._width, _gui._height);

    auto sideBar = ofxWidgets::widget::create();
    sideBar->setup(mainLayout->_width/5, mainLayout->_height);
    sideBar->_backgroundColor = ofColor(16, 16, 16);
    
    auto sideBarLayout = ofxWidgets::layout::vBox::create();
    sideBarLayout->setup(sideBar);

    auto sideBarHeading = ofxWidgets::label::create();
    sideBarHeading->setup(sideBarLayout->_width, 50);
    sideBarHeading->setText("Sidebar");
    sideBarHeading->_color = ofColor::white;
    sideBarHeading->_backgroundColor = ofColor::green;
    sideBarLayout->add(sideBarHeading);
    
    auto sideBarSubHeading = ofxWidgets::label::create();
    sideBarSubHeading->setup(sideBarLayout->_width, 50);
    sideBarSubHeading->setText("Settings");
    sideBarSubHeading->_color = ofColor::white;
    sideBarSubHeading->setFontSize(16);
    sideBarLayout->add(sideBarSubHeading);
    
    _value.set("value", 0.5, 0, 1);
    auto slider = ofxWidgets::floatSlider::create(_value);
    slider->setup(sideBarLayout->_width, 50);
    sideBarLayout->add(slider);

    _trigger.set("trigger");
    auto button = ofxWidgets::button::create(_trigger);
    button->setup(sideBarLayout->_width, 50);
    sideBarLayout->add(button);

    sideBar->add(sideBarLayout);
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
    ofSetWindowTitle(ofToString((int)(ofGetFrameRate())));
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