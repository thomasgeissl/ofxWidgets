#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAntiAliasing();
    ofSetVerticalSync(true);

    // setting up some parameters, which will then be passed to the ui widgets
    _intValue.set("int", 20, 0, 100);
    _floatValue.set("float", 0.5, 0, 1);
    _trigger.set("randomise");
    _trigger.addListener(this, &ofApp::onTrigger);

    _panelVoidParameter.set("trigger");
    _panelBoolParameter.set("activate", false);
    _panelIntParameter.set("int value", 0, 0, 100);
    _panelFloatParameter.set("float value", 0, 0, 1);
    _panelParameters.add(_panelVoidParameter);
    _panelParameters.add(_panelBoolParameter);
    _panelParameters.add(_panelIntParameter);
    _panelParameters.add(_panelFloatParameter);

    // # structure
    // ## main
    _gui.setName("gui");
    auto mainLayout = ofxWidgets::layout::hBox::create(_gui.getViewWidth(), _gui.getViewHeight());
    _gui.add(mainLayout);

    // ## content
    auto content = ofxWidgets::widget::create(mainLayout->getViewWidth() / 3 * 2, mainLayout->getViewHeight());
    auto contentLayout = ofxWidgets::layout::vBox::createAndAddTo(content);
    contentLayout->setName("contentLayout");

    _upperShape = shape::create(contentLayout->getViewWidth(), contentLayout->getViewHeight() / 2);
    contentLayout->add(_upperShape);
    contentLayout->add(ofxWidgets::panel::create(_panelParameters, contentLayout->getViewWidth(), contentLayout->getViewHeight() / 2));

    // ## sidebar
    auto sideBar = ofxWidgets::widget::create(_gui.getViewWidth() / 3, _gui.getViewHeight());
    auto sideBarLayout = ofxWidgets::layout::tab::createAndAddTo(sideBar);

    auto sliderLayout = ofxWidgets::layout::vBox::create(sideBarLayout->getViewWidth(), sideBarLayout->getViewHeight()-20);
    sliderLayout->setOffset(10);
    sliderLayout->add(ofxWidgets::label::create("ofxWidgets Demo", sliderLayout->getViewWidth(), 50));

    sliderLayout->add(ofxWidgets::label::create("Sliders", sliderLayout->getViewWidth(), 35));
    sliderLayout->add(ofxWidgets::intSlider::create(_intValue, sliderLayout->getViewWidth(), 20));
    auto verticalSliderWidget = ofxWidgets::widget::create(sliderLayout->getViewWidth(), 60);
    auto verticalSliderWidgetLayout = ofxWidgets::layout::hBox::createAndAddTo(verticalSliderWidget);
    verticalSliderWidgetLayout->setOffset(5);
    for (auto i = 0; i < 4; i++)
    {
        verticalSliderWidgetLayout->add(ofxWidgets::floatSlider::create(ofToString(i), 0, 0, 1, 20, verticalSliderWidgetLayout->getViewHeight(), ofxWidgets::floatSlider::style::vertical));
    }
    // sideBarLayout->add(ofxWidgets::floatSlider::create(_floatValue, sideBarLayout->getViewWidth(), 80, ofxWidgets::floatSlider::style::rotary));
    verticalSliderWidgetLayout->add(ofxWidgets::floatSlider::create(_floatValue, verticalSliderWidgetLayout->getRemainingWidth(), verticalSliderWidgetLayout->getViewHeight(), ofxWidgets::floatSlider::style::rotary));
    sliderLayout->add(verticalSliderWidget);
    sliderLayout->add(ofxWidgets::labeledIntSlider::create(ofxWidgets::intSlider::create(_intValue, sliderLayout->getViewWidth(), 10), ofxWidgets::labeledIntSlider::position::TOP, sliderLayout->getViewWidth(), 40));
    sliderLayout->add(ofxWidgets::labeledIntSlider::create(ofxWidgets::intSlider::create(_intValue, sliderLayout->getViewWidth() / 2, 20, ofxWidgets::intSlider::style::vertical), ofxWidgets::labeledIntSlider::position::RIGHT, sliderLayout->getViewWidth(), 20));
    sliderLayout->add(ofxWidgets::labeledIntSlider::create(ofxWidgets::intSlider::create(_intValue, sliderLayout->getViewWidth() / 2, 20, ofxWidgets::intSlider::style::vertical), ofxWidgets::labeledIntSlider::position::LEFT, sliderLayout->getViewWidth(), 20));
    sliderLayout->add(ofxWidgets::labeledIntSlider::create(ofxWidgets::intSlider::create(_intValue, sliderLayout->getViewWidth(), 10), ofxWidgets::labeledIntSlider::position::BOTTOM, sliderLayout->getViewWidth(), 40));

    auto buttonToggleColorPickerLayout = ofxWidgets::layout::vBox::create(sideBarLayout->getViewWidth(), sideBarLayout->getViewHeight()-20);
    buttonToggleColorPickerLayout->add(ofxWidgets::label::create("Button, toggle, colorpicker", buttonToggleColorPickerLayout->getViewWidth(), 35));
    buttonToggleColorPickerLayout->add(ofxWidgets::toggle::create(_upperShape->_boost, buttonToggleColorPickerLayout->getViewWidth(), 20));
    buttonToggleColorPickerLayout->add(ofxWidgets::labeledToggle::create(ofxWidgets::toggle::create(_upperShape->_boost, buttonToggleColorPickerLayout->getViewWidth(), 20), ofxWidgets::labeledToggle::position::BOTTOM, sliderLayout->getViewWidth(), 40));
    buttonToggleColorPickerLayout->add(ofxWidgets::button::create(_trigger, buttonToggleColorPickerLayout->getViewWidth(), 20));
    buttonToggleColorPickerLayout->add(ofxWidgets::colorPicker::create(_upperShape->_fillColor, buttonToggleColorPickerLayout->getViewWidth(), 40));

    buttonToggleColorPickerLayout->add(ofxWidgets::label::create("Scrollable", buttonToggleColorPickerLayout->getViewWidth(), 35));
    auto scrollableWidget = ofxWidgets::widget::create(buttonToggleColorPickerLayout->getViewWidth(), 80);
    auto scrollableWidgetLayout = ofxWidgets::layout::vBox::createAndAddTo(scrollableWidget);
    scrollableWidgetLayout->setOffset(10);
    scrollableWidgetLayout->add(ofxWidgets::intSlider::create(_intValue, scrollableWidgetLayout->getViewWidth(), 40));
    scrollableWidgetLayout->add(ofxWidgets::intSlider::create(_intValue, scrollableWidgetLayout->getViewWidth(), 40));
    scrollableWidgetLayout->add(ofxWidgets::colorPicker::create(_upperShape->_fillColor, scrollableWidgetLayout->getViewWidth(), 20));
    scrollableWidgetLayout->_scrollPosition.y = 20;
    buttonToggleColorPickerLayout->add(scrollableWidget);


    sideBarLayout->add("Sliders", sliderLayout);
    sideBarLayout->add("B.T.C.", buttonToggleColorPickerLayout);
    sideBarLayout->setIndex(0);
    mainLayout->add(sideBar);
    mainLayout->add(content);

    // # style
    ofFile file("themes/default.json");
    ofJson theme;
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
    switch (key)
    {
    case 's':
    {
        ofImage img;
        img.grabScreen(_gui._position.x, _gui._position.y, _gui.getViewWidth(), _gui.getViewHeight());
        img.save("screenshot.png");
        break;
    }
    default:
    {
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