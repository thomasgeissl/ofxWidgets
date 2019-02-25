#pragma once

#include "ofMain.h"
#include "./slider.h"
#include "../layouts/hBox.h"

namespace ofxWidgets
{
class colorPicker : public ofxWidgets::widget
{
  public:
    enum style
    {
    };
    typedef std::shared_ptr<colorPicker> pointer;
    static pointer create()
    {
        return std::make_shared<colorPicker>();
    }
    static pointer create(ofParameter<ofColor> parameter)
    {
        return std::make_shared<colorPicker>(parameter);
    }
    colorPicker() : widget()
    {
        _value.set("value", ofColor::black);
        _value.addListener(this, &colorPicker::onValueChange);
        _red.addListener(this, &colorPicker::onComponentChange);
        _red.set("red", 0, 0, 255);
        _green.addListener(this, &colorPicker::onComponentChange);
        _green.set("green", 0, 0, 255);
        _blue.addListener(this, &colorPicker::onComponentChange);
        _blue.set("blue", 0, 0, 255);
        _redSlider = ofxWidgets::intSlider::create(_red);
        _redSlider->_color = ofColor(255, 0, 0);
        _greenSlider = ofxWidgets::intSlider::create(_green);
        _greenSlider->_color = ofColor(0, 255, 0);
        _blueSlider = ofxWidgets::intSlider::create(_blue);
        _blueSlider->_color = ofColor(0, 0, 255);
        // _style = style::horizontal;
        // _color = ofColor::darkGrey;
        // _backgroundColor = ofColor::lightGrey;
    }

    colorPicker(ofParameter<ofColor> parameter) : widget(), _value(parameter)
    {
        _value.addListener(this, &colorPicker::onValueChange);
        _red.addListener(this, &colorPicker::onComponentChange);
        _red.set("red", 0, 0, 255);
        _green.addListener(this, &colorPicker::onComponentChange);
        _green.set("green", 0, 0, 255);
        _blue.addListener(this, &colorPicker::onComponentChange);
        _blue.set("blue", 0, 0, 255);

        _redSlider = ofxWidgets::intSlider::create(_red);
        _redSlider->_color = ofColor(255, 0, 0);
        _greenSlider = ofxWidgets::intSlider::create(_green);
        _greenSlider->_color = ofColor(0, 255, 0);
        _blueSlider = ofxWidgets::intSlider::create(_blue);
        _blueSlider->_color = ofColor(0, 0, 255);
        // _style = style::horizontal;
        // _color = ofColor::darkGrey;
        // _backgroundColor = ofColor::lightGrey;
    }

    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        widget::setup(width, height, hasOverlay);
        _children.clear();
        auto mainLayout = ofxWidgets::layout::hBox::create();
        auto leftLayout = ofxWidgets::layout::vBox::create();
        auto sliderLayout = ofxWidgets::layout::hBox::create();
        mainLayout->setup(_width, _height);
        leftLayout->setup(_width - height, _height);
        sliderLayout->setup(leftLayout->_width, leftLayout->_height / 2);

        _redSlider->setup(sliderLayout->_width / 3, sliderLayout->_height);
        sliderLayout->add(_redSlider);
        _greenSlider->setup(_redSlider->_width, _redSlider->_height);
        sliderLayout->add(_greenSlider);
        _blueSlider->setup(_redSlider->_width, _redSlider->_height);
        sliderLayout->add(_blueSlider);

        leftLayout->add(sliderLayout);
        mainLayout->add(leftLayout);
        add(mainLayout);
    }

    virtual void update()
    {
        setNeedsToBeRedrawn(true);
        widget::update();
        if (_needsToBeRedrawn)
        {
            begin(false);
            ofFill();
            ofSetColor(_value);
            ofDrawRectangle(_width - _height, 0, _height, _height);
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        if (button == 0)
        {
        }
    }
    virtual void mouseDragged(int x, int y, int button)
    {
        widget::mouseDragged(x, y, button);
        if (button == 0 && _focussed)
        {
        }
    }

    void setStyle(style s)
    {
        _style = s;
        setNeedsToBeRedrawn(true);
    }
    void setFontSize(int fontSize)
    {
        _fontSize = fontSize;
    }
    void onValueChange(ofColor &value)
    {
        setNeedsToBeRedrawn(true);
    }
    void onComponentChange(int &value)
    {
        _value = ofColor(_red, _green, _blue);
    }

    ofParameter<ofColor> _value;
    ofxWidgets::intSlider::pointer _redSlider;
    ofxWidgets::intSlider::pointer _greenSlider;
    ofxWidgets::intSlider::pointer _blueSlider;
    ofParameter<int> _red;
    ofParameter<int> _green;
    ofParameter<int> _blue;
    style _style;
};
}; // namespace ofxWidgets