#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAntiAliasing();
    ofSetVerticalSync(true);


    _upperShape = shape::create();
    _lowerShape = shape::create();

    // # main
    _gui.setName("gui");
    _gui._backgroundColor = ofColor(64, 255);
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui.getViewWidth(), _gui.getViewHeight());
    _gui.add(mainLayout);

    // ## sidebar
    auto sideBar = ofxWidgets::widget::create();
    auto sideBarWidth = (int)(mainLayout->getViewWidth() / 5);
    sideBar->setup(sideBarWidth, mainLayout->getViewHeight());
    sideBar->setName("sideBar");
    sideBar->_backgroundColor = ofColor(24,255);

    auto sideBarLayout = ofxWidgets::layout::vBox::create();
    sideBarLayout->setup(sideBar);
    sideBarLayout->setup(mainLayout->getViewWidth() / 5, mainLayout->getViewHeight());
    sideBarLayout->setName("sideBarLayout");
    sideBarLayout->_verticalOffset = 10;


    auto sideBarHeading = ofxWidgets::label::create();
    sideBarHeading->setup(sideBarLayout->getViewWidth(), 50);
    sideBarHeading->setText("ofxWidgets Demo");
    sideBarHeading->_backgroundColor = ofColor(255, 0);
    sideBarLayout->add(sideBarHeading);

    auto sideBarSubHeading = ofxWidgets::label::create();
    sideBarSubHeading->setup(sideBarLayout->getViewWidth(), 40);
    sideBarSubHeading->setText("Settings");
    sideBarSubHeading->_backgroundColor = ofColor(255, 0);
    sideBarLayout->add(sideBarSubHeading);

    _intValue.set("int", 20, 0, 100);
    _floatValue.set("float", 0.5, 0, 1);

    auto intSlider = ofxWidgets::intSlider::create(_intValue);
    intSlider->setup(sideBarLayout->getViewWidth(), 40);
    intSlider->_color = ofColor(149,77,24);
    intSlider->_backgroundColor = ofColor(32, 255);
    sideBarLayout->add(intSlider);

    auto floatSlider = ofxWidgets::floatSlider::create(_floatValue);
    floatSlider->setup(20 * 10, 80);
    floatSlider->setup(sideBarLayout->getViewWidth(), 80);
    floatSlider->_color = ofColor(149,77,24);
    floatSlider->_backgroundColor = ofColor(32, 255);
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

    auto toggle = ofxWidgets::toggle::create(_lowerShape->_boost);
    toggle->setup(sideBarLayout->getViewWidth(), 40);
    toggle->_color = ofColor(149,77,24);
    toggle->_backgroundColor = ofColor(32, 255);
    sideBarLayout->add(toggle);

    _trigger.set("randomise");
    auto button = ofxWidgets::button::create(_trigger);
    button->setup(sideBarLayout->getViewWidth(), 20);
    button->_color = ofColor(149,77,24);
    button->_backgroundColor = ofColor(32, 255);
    sideBarLayout->add(button);

    auto colorPicker = ofxWidgets::colorPicker::create(_upperShape->_color);
    colorPicker->setup(sideBarLayout->getViewWidth(), 40);
    colorPicker->_backgroundColor = ofColor(32, 255);
    sideBarLayout->add(colorPicker);


    sideBar->add(sideBarLayout);
    mainLayout->add(sideBar);

    // ## content
    auto content = ofxWidgets::widget::create();
    content->setup(mainLayout->getViewWidth() - sideBarWidth, mainLayout->getViewHeight());
    content->setName("content");
    content->_backgroundColor = _gui._backgroundColor;

    auto contentLayout = ofxWidgets::layout::vBox::create();
    contentLayout->setup(content);
    contentLayout->setName("contentLayout");

    _upperShape->setup(contentLayout->getViewWidth(), contentLayout->getViewHeight() / 5);
    _lowerShape->setup(contentLayout->getViewWidth(), contentLayout->getViewHeight() / 5);

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
    testList->setup(contentLayout->getViewWidth(), 100);
    testList->setAlignment(ofxWidgets::widget::alignment::center);
    contentLayout->add(testList);

    auto listIndexSlider = ofxWidgets::intSlider::create(_testListIndex);
    listIndexSlider->setup(contentLayout->getViewWidth(), 10);
    contentLayout->add(listIndexSlider);


    auto sideBarSubHeadingScroll = ofxWidgets::label::create();
    sideBarSubHeadingScroll->setup(sideBarLayout->getViewWidth(), 40);
    sideBarSubHeadingScroll->setText("Scrollable");
    sideBarSubHeadingScroll->_backgroundColor = ofColor(255, 0);
    sideBarLayout->add(sideBarSubHeadingScroll);

    auto smallWidget = ofxWidgets::widget::create();
    smallWidget->setup(sideBarLayout->getViewWidth(), 80);
    auto smallWidgetLayout = ofxWidgets::layout::vBox::create();
    smallWidgetLayout->setup(smallWidget->getViewWidth(), smallWidget->getViewHeight());
    smallWidget->add(smallWidgetLayout);

    auto newIntSlider = ofxWidgets::intSlider::create(_intValue);
    newIntSlider->setup(smallWidgetLayout->getViewWidth(), 60);
    newIntSlider->_color = ofColor(149,77,24);
    newIntSlider->_backgroundColor = ofColor(32, 255);
    smallWidgetLayout->add(newIntSlider);

    auto newColorPicker = ofxWidgets::colorPicker::create(_upperShape->_color);
    newColorPicker->setup(smallWidgetLayout->getViewWidth(), 40);
    newColorPicker->_color = ofColor(149,77,24);
    newColorPicker->_backgroundColor = ofColor(32, 255);
    smallWidgetLayout->add(newColorPicker);

    sideBarLayout->add(smallWidget);
    smallWidgetLayout->_scrollPosition.y = 20;
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
            img.grabScreen(_gui._position.x, _gui._position.y , _gui.getViewWidth(), _gui.getViewHeight());
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
    _upperShape->_color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}