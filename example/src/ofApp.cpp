#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAntiAliasing();
    ofSetVerticalSync(true);

    _panelVoidParameter.set("trigger");
    _panelBoolParameter.set("activate", false);
    _panelIntParameter.set("int value", 0, 0, 100);
    _panelFloatParameter.set("float value", 0, 0, 1);
    _panelParameters.add(_panelVoidParameter);
    _panelParameters.add(_panelBoolParameter);
    _panelParameters.add(_panelIntParameter);
    _panelParameters.add(_panelFloatParameter);

    _upperShape = shape::create();

    // # main
    _gui.setName("gui");
    _gui.setup(ofGetWidth(), ofGetHeight());
    auto mainLayout = ofxWidgets::layout::hBox::create();
    mainLayout->setup(_gui.getViewWidth(), _gui.getViewHeight());
    _gui.add(mainLayout);

    // ## sidebar
    auto sideBar = ofxWidgets::widget::create();
    auto sideBarWidth = (int)(mainLayout->getViewWidth() / 5);
    sideBar->setup(sideBarWidth, mainLayout->getViewHeight());
    sideBar->setName("sideBar");

    auto sideBarLayout = ofxWidgets::layout::vBox::create();
    sideBarLayout->setup(sideBar);
    sideBarLayout->setup(mainLayout->getViewWidth() / 5, mainLayout->getViewHeight());
    sideBarLayout->setName("sideBarLayout");
    sideBarLayout->_verticalOffset = 10;


    auto sideBarHeading = ofxWidgets::label::create("ofxWidgets Demo", sideBarLayout->getViewWidth(), 50);
    sideBarLayout->add(sideBarHeading);

    auto sideBarSubHeading = ofxWidgets::label::create("Settings", sideBarLayout->getViewWidth(), 40);
    sideBarLayout->add(sideBarSubHeading);

    _intValue.set("int", 20, 0, 100);
    _floatValue.set("float", 0.5, 0, 1);

    auto intSlider = ofxWidgets::intSlider::create(_intValue, sideBarLayout->getViewWidth(), 40);
    sideBarLayout->add(intSlider);

    auto floatSlider = ofxWidgets::floatSlider::create(_floatValue, sideBarLayout->getViewWidth(), 80);
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

    auto toggle = ofxWidgets::toggle::create(_upperShape->_boost, sideBarLayout->getViewWidth(), 40);
    sideBarLayout->add(toggle);

    _trigger.set("randomise");
    auto button = ofxWidgets::button::create(_trigger, sideBarLayout->getViewWidth(), 20);
    sideBarLayout->add(button);

    auto colorPicker = ofxWidgets::colorPicker::create(_upperShape->_fillColor, sideBarLayout->getViewWidth(), 40);
    sideBarLayout->add(colorPicker);


    sideBar->add(sideBarLayout);
    mainLayout->add(sideBar);

    // ## content
    auto content = ofxWidgets::widget::create(mainLayout->getViewWidth() - sideBarWidth, mainLayout->getViewHeight());
    content->setName("content");

    auto contentLayout = ofxWidgets::layout::vBox::create();
    contentLayout->setup(content);
    contentLayout->setName("contentLayout");

    _upperShape->setup(contentLayout->getViewWidth(), contentLayout->getViewHeight() / 5);

    contentLayout->add(_upperShape);

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
    sideBarLayout->add(sideBarSubHeadingScroll);

    auto smallWidget = ofxWidgets::widget::create();
    smallWidget->setup(sideBarLayout->getViewWidth(), 80);
    auto smallWidgetLayout = ofxWidgets::layout::vBox::create();
    smallWidgetLayout->setup(smallWidget->getViewWidth(), smallWidget->getViewHeight());
    smallWidget->add(smallWidgetLayout);

    auto newIntSlider = ofxWidgets::intSlider::create(_intValue, smallWidgetLayout->getViewWidth(), 60);
    smallWidgetLayout->add(newIntSlider);

    auto newColorPicker = ofxWidgets::colorPicker::create(_upperShape->_fillColor, smallWidgetLayout->getViewWidth(), 40);
    smallWidgetLayout->add(newColorPicker);

    sideBarLayout->add(smallWidget);
    smallWidgetLayout->_scrollPosition.y = 20;

    // auto sideBarSubHeadingPanel = ofxWidgets::label::create();
    // sideBarSubHeadingPanel->setup(sideBarLayout->getViewWidth(), 40);
    // sideBarSubHeadingPanel->setText("Panel");
    // sideBarLayout->add(sideBarSubHeadingPanel);

    // auto panel = ofxWidgets::panel::create(_panelParameters);
    // panel->setup(sideBarLayout->getViewWidth(), 200);
    // sideBarLayout->add(panel);

    ofJson theme;
    ofFile file("themes/default.json");
    file >> theme;
    _gui.setTheme(theme);
    sideBar->_backgroundColor = ofColor(24, 255);
    content->_backgroundColor = ofColor(48, 255);
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
    _upperShape->_fillColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}