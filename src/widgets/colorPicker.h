#pragma once

#include "ofMain.h"
#include "./slider.h"
#include "../layouts/hBox.h"

namespace ofxWidgets
{
class colorPicker : public ofxWidgets::widget
{
  public:
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
    }

    colorPicker(ofParameter<ofColor> parameter) : widget(), _value(parameter)
    {
        _value.addListener(this, &colorPicker::onValueChange);
        _red.set("red", _value.get().r, 0, 255);
        _red.addListener(this, &colorPicker::onComponentChange);
        _green.set("green", _value.get().g, 0, 255);
        _green.addListener(this, &colorPicker::onComponentChange);
        _blue.set("blue", _value.get().b, 0, 255);
        _blue.addListener(this, &colorPicker::onComponentChange);

        _redSlider = ofxWidgets::intSlider::create(_red);
        _redSlider->_color = ofColor(255, 0, 0);
        _greenSlider = ofxWidgets::intSlider::create(_green);
        _greenSlider->_color = ofColor(0, 255, 0);
        _blueSlider = ofxWidgets::intSlider::create(_blue);
        _blueSlider->_color = ofColor(0, 0, 255);
    }

    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        _children.clear();
        widget::setup(width, height, hasOverlay);
        auto mainLayout = ofxWidgets::layout::hBox::create();
        auto leftLayout = ofxWidgets::layout::vBox::create();
        auto sliderLayout = ofxWidgets::layout::hBox::create();
        mainLayout->setup(_contentWidth, _contentHeight);
        leftLayout->setup(_contentWidth - height, _contentHeight);
        sliderLayout->setup(leftLayout->getContentWidth(), leftLayout->getContentHeight() / 2);
        // sliderLayout->_horizontalOffset = sliderLayout->_width/20;

        _redSlider->setup(sliderLayout->getContentWidth() / 3, sliderLayout->getContentHeight());
        sliderLayout->add(_redSlider);
        _greenSlider->setup(_redSlider->getContentWidth(), _redSlider->getContentHeight());
        sliderLayout->add(_greenSlider);
        _blueSlider->setup(_redSlider->getContentWidth(), _redSlider->getContentHeight());
        sliderLayout->add(_blueSlider);

        _redSlider->_label->_color = ofColor::white;
        _greenSlider->_label->_color = ofColor::white;
        _blueSlider->_label->_color = ofColor::white;

        leftLayout->add(sliderLayout);

        _label = ofxWidgets::label::create();
        _label->setup(leftLayout->getContentWidth(), leftLayout->getContentHeight() / 2);
        _label->_text = _value.getName();
        _label->_color = ofColor::white;
        leftLayout->add(_label);
        mainLayout->add(leftLayout);
        add(mainLayout);
    }

    virtual void update()
    {
        setNeedsToBeRedrawn(true);
        if (_needsToBeRedrawn)
        {
            widget::update();
            begin(false);
            ofSetColor(_value);
            ofDrawRectangle(_contentWidth - _contentHeight, 0, _contentHeight, _contentHeight);
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        if (button == 0)
        {
            // TODO: check if coloured square is hit and show overlay
        }
    }
    virtual void mouseDragged(int x, int y, int button)
    {
        widget::mouseDragged(x, y, button);
        if (button == 0 && _focussed)
        {
        }
    }

    void onValueChange(ofColor &value)
    {
        if (_red != value.r)
        {
            _red.setWithoutEventNotifications(value.r);
            _redSlider->setNeedsToBeRedrawn(true);
        }
        if (_green != value.g)
        {
            _green.setWithoutEventNotifications(value.g);
            _greenSlider->setNeedsToBeRedrawn(true);
        }
        if (_blue != value.b)
        {
            _blue.setWithoutEventNotifications(value.b);
            _blueSlider->setNeedsToBeRedrawn(true);
        }
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
    ofxWidgets::label::pointer _label;
};
}; // namespace ofxWidgets