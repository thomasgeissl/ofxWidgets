#include "ofApp.h"

void ofApp::setup()
{
    _upperShape = shape::create();
    _lowerShape = shape::create();

    // # main
    _gui.setName("gui");
    _gui._backgroundColor = ofColor(64, 255);
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui._width, _gui._height);
    _gui.add(mainLayout);

    // ## sidebar
    auto sideBar = ofxWidgets::widget::create();
    auto sideBarWidth = (int)(mainLayout->_width / 5);
    sideBar->setup(sideBarWidth, mainLayout->_height);
    sideBar->setName("sideBar");
    sideBar->_backgroundColor = ofColor(24,255);

    auto sideBarLayout = ofxWidgets::layout::vBox::create();
    sideBarLayout->setup(sideBar);
    sideBarLayout->setup(mainLayout->_width / 5, mainLayout->_height);
    sideBarLayout->setName("sideBarLayout");
    sideBarLayout->_verticalOffset = 10;


    auto sideBarHeading = ofxWidgets::label::create();
    sideBarHeading->setup(sideBarLayout->_width, 50);
    sideBarHeading->setText("ofxWidgets Demo");
    sideBarHeading->_backgroundColor = ofColor(255, 0);
    sideBarLayout->add(sideBarHeading);

    auto sideBarSubHeading = ofxWidgets::label::create();
    sideBarSubHeading->setup(sideBarLayout->_width, 40);
    sideBarSubHeading->setText("Settings");
    sideBarSubHeading->_backgroundColor = ofColor(255, 0);
    sideBarLayout->add(sideBarSubHeading);

    _intValue.set("int", 20, 0, 100);
    _floatValue.set("float", 0.5, 0, 1);

    auto intSlider = ofxWidgets::intSlider::create(_intValue);
    intSlider->setup(sideBarLayout->_width, 40);
    intSlider->_color = ofColor(149,77,24);
    sideBarLayout->add(intSlider);

    auto floatSlider = ofxWidgets::floatSlider::create(_floatValue);
    floatSlider->setup(20 * 10, 80);
    floatSlider->_color = ofColor(149,77,24);
    floatSlider->setStyle(ofxWidgets::floatSlider::style::vertical);
    sideBarLayout->add(floatSlider);

    // std::vector<ofxWidgets::intDropDown::option> options;
    // options.push_back(ofxWidgets::intDropDown::createOption(0, "none"));
    // options.push_back(ofxWidgets::intDropDown::createOption(1, "small"));
    // options.push_back(ofxWidgets::intDropDown::createOption(2, "medium"));
    // options.push_back(ofxWidgets::intDropDown::createOption(3, "large"));
    // auto intDropDown = ofxWidgets::intDropDown::create(_intDropDownValue, options);
    // intDropDown->setup(sideBarLayout->_width, 50);
    // sideBarLayout->add(intDropDown);

    _trigger.set("trigger");
    auto button = ofxWidgets::button::create(_trigger);
    button->setup(sideBarLayout->_width, 20);
    button->_color = ofColor(149,77,24);
    sideBarLayout->add(button);

    auto toggle = ofxWidgets::toggle::create(_lowerShape->_boost);
    toggle->setup(sideBarLayout->_width, 40);
    toggle->_color = ofColor(149,77,24);
    sideBarLayout->add(toggle);

    auto colorPicker = ofxWidgets::colorPicker::create(_upperShape->_color);
    colorPicker->setup(sideBarLayout->_width, 40);
    sideBarLayout->add(colorPicker);


    sideBar->add(sideBarLayout);
    mainLayout->add(sideBar);

    // ## content
    auto content = ofxWidgets::widget::create();
    content->setup(mainLayout->_width - sideBarWidth, mainLayout->_height);
    content->setName("content");
    content->_backgroundColor = _gui._backgroundColor;

    auto contentLayout = ofxWidgets::layout::vBox::create();
    contentLayout->setup(content);
    contentLayout->setName("contentLayout");

    _upperShape->setup(contentLayout->_width, contentLayout->_height / 5);
    _lowerShape->setup(contentLayout->_width, contentLayout->_height / 5);

    contentLayout->add(_upperShape);
    contentLayout->add(_lowerShape);

    content->add(contentLayout);
    mainLayout->add(content);

    _trigger.addListener(this, &ofApp::onTrigger);


    std::vector<std::string> testListItems;
    testListItems.push_back("first list item");
    testListItems.push_back("second list item");
    testListItems.push_back("third list item");
    _testListIndex.set("testListIndex", 0, 0, testListItems.size());
    auto testList = ofxWidgets::list::create(_testListIndex, testListItems);
    testList->setup(contentLayout->_width, 100);
    testList->setAlignment(ofxWidgets::widget::alignment::center);
    contentLayout->add(testList);

    auto listIndexSlider = ofxWidgets::intSlider::create(_testListIndex);
    listIndexSlider->setup(contentLayout->_width, 10);
    contentLayout->add(listIndexSlider);
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
    switch(key){
        case 's':{
            ofImage img;
            img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
            img.save("screenshot.png");
            break;
        }
        default: {
            break;
        }
    }
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
    _upperShape->_color = ofColor(ofRandom(100, 255));
}