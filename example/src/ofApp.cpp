#include "ofApp.h"

void ofApp::setup()
{
    _gui.setName("gui");
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui._width, _gui._height);

    auto sideBar = ofxWidgets::widget::create();
    sideBar->setup(mainLayout->_width / 5, mainLayout->_height);
    sideBar->setName("sideBar");
    sideBar->_backgroundColor = ofColor(16, 16, 16);

    auto sideBarLayout = ofxWidgets::layout::vBox::create();
    sideBarLayout->setup(sideBar);
    sideBarLayout->setName("sideBarLayout");

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

    mainLayout->add(sideBar);

    auto content = ofxWidgets::widget::create();
    content->setup(mainLayout->_width / 5 * 4, mainLayout->_height);
    content->setName("content");
    auto contentLayout = ofxWidgets::layout::vBox::create();
    contentLayout->setup(content);
    contentLayout->setName("contentLayout");

    _upperCircle = circle::create();
    _upperCircle->setup(contentLayout->_width, contentLayout->_height / 3);
    _lowerCircle = circle::create();
    _lowerCircle->setup(contentLayout->_width, contentLayout->_height / 3);

    _value.set("value", 0.5, 0, 1);
    auto slider = ofxWidgets::floatSlider::create(_value);
    slider->setup(sideBarLayout->_width, 50);
    sideBarLayout->add(slider);

    _trigger.set("trigger");
    auto button = ofxWidgets::button::create(_trigger);
    button->setup(sideBarLayout->_width, 50);
    button->setName("button");
    sideBarLayout->add(button);

    auto toggle = ofxWidgets::toggle::create(_lowerCircle->_boost);
    toggle->setup(sideBarLayout->_width, 50);
    toggle->setName("toggle");
    sideBarLayout->add(toggle);

    sideBar->add(sideBarLayout);

    contentLayout->add(_upperCircle);
    contentLayout->add(_lowerCircle);
    contentLayout->add(button);
    contentLayout->add(toggle);

    _intValue.set("int", 20, 0, 100);
    _floatValue.set("float", 0.5, 0, 1);

    auto intSlider = ofxWidgets::intSlider::create(_intValue);
    intSlider->setup(sideBarLayout->_width, 50);
    auto floatSlider = ofxWidgets::floatSlider::create(_floatValue);
    floatSlider->setup(sideBarLayout->_width, 50);
    floatSlider->setStyle(ofxWidgets::floatSlider::style::vertical);

    contentLayout->add(intSlider);
    contentLayout->add(floatSlider);

    content->add(contentLayout);

    mainLayout->add(content);
    _gui.add(mainLayout);

    _trigger.addListener(this, &ofApp::onTrigger);
}

void ofApp::update()
{
    ofSetWindowTitle(ofToString((int)(ofGetFrameRate())));
}

void ofApp::draw()
{
}

void ofApp::keyPressed(int key)
{
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::mouseDragged(int x, int y, int button)
{
}

void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::windowResized(int w, int h)
{
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::onTrigger()
{
    _upperCircle->_color = ofColor(ofRandom(255));
}