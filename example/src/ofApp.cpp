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
    auto content = ofxWidgets::widget::create(mainLayout->getViewWidth()/5*4, mainLayout->getViewHeight());
    auto contentLayout = ofxWidgets::layout::vBox::createAndAddTo(content);
    contentLayout->setName("contentLayout");

    _upperShape = shape::create(contentLayout->getViewWidth(), contentLayout->getViewHeight()/2);
    contentLayout->add(_upperShape);
    contentLayout->add(ofxWidgets::panel::create(_panelParameters, contentLayout->getViewWidth(), contentLayout->getViewHeight()/2));


    // ## sidebar
    auto sideBar = ofxWidgets::widget::create(_gui.getViewWidth() /5, _gui.getViewHeight());
    auto sideBarLayout = ofxWidgets::layout::vBox::createAndAddTo(sideBar);
    sideBarLayout->_verticalOffset = 10;
    sideBarLayout->add(ofxWidgets::label::create("ofxWidgets Demo", sideBarLayout->getViewWidth(), 50));
    sideBarLayout->add(ofxWidgets::label::create("Settings", sideBarLayout->getViewWidth(), 40));
    sideBarLayout->add(ofxWidgets::intSlider::create(_intValue, sideBarLayout->getViewWidth(), 40));
    sideBarLayout->add(ofxWidgets::floatSlider::create(_floatValue, sideBarLayout->getViewWidth(), 80, ofxWidgets::floatSlider::style::vertical));
    sideBarLayout->add(ofxWidgets::floatSlider::create(_floatValue, sideBarLayout->getViewWidth(), 80, ofxWidgets::floatSlider::style::rotary));
    sideBarLayout->add(ofxWidgets::toggle::create(_upperShape->_boost, sideBarLayout->getViewWidth(), 40));
    sideBarLayout->add(ofxWidgets::button::create(_trigger, sideBarLayout->getViewWidth(), 20));
    sideBarLayout->add(ofxWidgets::colorPicker::create(_upperShape->_fillColor, sideBarLayout->getViewWidth(), 40));
    sideBarLayout->add(ofxWidgets::label::create("Scrollable", sideBarLayout->getViewWidth(), 40));
    auto scrollableWidget = ofxWidgets::widget::create(sideBarLayout->getViewWidth(), 80);
    auto scrollableWidgetLayout = ofxWidgets::layout::vBox::createAndAddTo(scrollableWidget);
    scrollableWidgetLayout->add(ofxWidgets::intSlider::create(_intValue, scrollableWidgetLayout->getViewWidth(), 60));
    scrollableWidgetLayout->add(ofxWidgets::colorPicker::create(_upperShape->_fillColor, scrollableWidgetLayout->getViewWidth(), 40));
    scrollableWidgetLayout->_scrollPosition.y = 20;
    sideBarLayout->add(scrollableWidget);

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