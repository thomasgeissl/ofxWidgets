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
    static pointer create(std::string text, ofColor value, int width, int height)
    {
        return std::make_shared<colorPicker>(text, value, width, height);
    }
    static pointer create(ofParameter<ofColor> parameter, int width, int height)
    {
        return std::make_shared<colorPicker>(parameter, width, height);
    }
    colorPicker(std::string text, ofColor value, int width, int height) : widget(width, height)
    {
        // _value.set("color", ofColor::black);
        _value.set(text, value);
        init();
    }

    colorPicker(ofParameter<ofColor> parameter, int width, int height) : widget(width, height), _value(parameter)
    {
        init();
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_COLORPICKER;
        auto mainLayout = ofxWidgets::layout::hBox::create(_contentWidth, _contentHeight);
        auto leftLayout = ofxWidgets::layout::vBox::create(_contentWidth - _contentHeight, _contentHeight);
        auto sliderLayout = ofxWidgets::layout::hBox::create(leftLayout->getContentWidth(), leftLayout->getContentHeight() / 2);

        _value.addListener(this, &colorPicker::onValueChange);
        _red.set("red", _value.get().r, 0, 255);
        _red.addListener(this, &colorPicker::onComponentChange);
        _green.set("green", _value.get().g, 0, 255);
        _green.addListener(this, &colorPicker::onComponentChange);
        _blue.set("blue", _value.get().b, 0, 255);
        _blue.addListener(this, &colorPicker::onComponentChange);

        _redSlider = ofxWidgets::intSlider::create(_red, sliderLayout->getContentWidth() / 3, sliderLayout->getContentHeight());
        _greenSlider = ofxWidgets::intSlider::create(_green, _redSlider->getContentWidth(), _redSlider->getContentHeight());
        _blueSlider = ofxWidgets::intSlider::create(_blue, _redSlider->getContentWidth(), _redSlider->getContentHeight());

        _redSlider->_color = ofColor(255, 0, 0);
        _greenSlider->_color = ofColor(0, 255, 0);
        _blueSlider->_color = ofColor(0, 0, 255);

        // sliderLayout->_horizontalOffset = sliderLayout->_width/20;

        sliderLayout->add(_redSlider);
        sliderLayout->add(_greenSlider);
        sliderLayout->add(_blueSlider);

        leftLayout->add(sliderLayout);

        _label = ofxWidgets::label::create(_value.getName(), leftLayout->getContentWidth(), leftLayout->getContentHeight() / 2);
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