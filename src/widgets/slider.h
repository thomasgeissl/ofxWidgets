#pragma once

#include "ofMain.h"

namespace ofxWidgets
{

template <class T>
class slider : public ofxWidgets::widget
{
  public:
    enum style
    {
        horizontal,
        vertical,
        rotary
    };
    typedef std::shared_ptr<slider> pointer;
    static pointer create(std::string text, T value, T min, T max, int width, int height)
    {
        return std::make_shared<slider>(text, value, min, max, width, height);
    }
    static pointer create(ofParameter<T> parameter)
    {
        return std::make_shared<slider>(parameter);
    }
    slider(std::string text, T value, T min, T max, int width, int height, style s = style::horizontal) : widget(width, height), style(s)
    {
        _value.set(text, value, min, max);
        init();
    }

    slider(ofParameter<T> parameter, int width, int height, style s = style::horizontal) : widget(width, height), _value(parameter), _style(s)
    {
        init();
    }

    void init()
    {
        _type = TYPE_OFXWIDGETS_SLIDER;
        _value.addListener(this, &slider::onValueChange);
        _style = style::horizontal;

        if (_style == style::horizontal)
        {
            _label = ofxWidgets::label::create(_value.getName(), _contentWidth, _contentHeight / 2);
            _label->_position = glm::vec2(0, _contentHeight / 2);
        }
        else if (_style == style::vertical)
        {
            auto sliderWidth = _contentWidth / 10;
            _label = ofxWidgets::label::create(_value.getName(), sliderWidth * 8.5, sliderWidth);
            _label->_position = glm::vec2(sliderWidth * 1.5, (_contentHeight - sliderWidth) / 2);
        }
        else if (_style == style::rotary)
        {
        }
        _label->_color = ofColor::white;
        add(_label);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            _label->_text = _value.getName() + ": " + ofToString(_value);
            _label->setNeedsToBeRedrawn(true);
            widget::update();
            begin(false);
            if (_style == style::horizontal)
            {
                ofSetColor(brigthenColor(_color, -.5));
                ofDrawRectangle(0, 0, _contentWidth, _contentHeight / 2);
                ofSetColor(_color);
                ofDrawRectangle(0, 0, ofMap(_value, _value.getMin(), _value.getMax(), 0, _contentWidth), _contentHeight / 2);
            }
            else if (_style == style::vertical)
            {
                ofSetColor(brigthenColor(_color, -.5));
                auto sliderWidth = _contentWidth / 10;
                ofDrawRectangle(0, 0, sliderWidth, _contentHeight);
                ofSetColor(_color);
                auto height = ofMap(_value, _value.getMin(), _value.getMax(), 0, _contentHeight);
                ofDrawRectangle(0, _contentHeight - height, sliderWidth, height);
            }
            else if (_style == style::rotary)
            {
                ofPolyline line;
                line.arc(_contentWidth / 2, _contentHeight / 2, std::min(_contentWidth, _contentHeight), std::min(_contentWidth, _contentHeight), 0, 180);
                ofSetColor(ofColor::red);
                ofSetLineWidth(10);
                line.draw();
            }
            end();
        }
    }
    // TODO: arrow keys, number input
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        if (button == 0)
        {
            if (_style == style::horizontal)
            {
                _value = ofMap(x, 0, _contentWidth, _value.getMin(), _value.getMax());
            }
            else if (_style == style::vertical)
            {
                _value = ofMap(_contentHeight - y, 0, _contentHeight, _value.getMin(), _value.getMax());
            }
            else if (_style == style::rotary)
            {
                // TODO
            }
        }
    }
    virtual void mouseDragged(int x, int y, int button)
    {
        widget::mouseDragged(x, y, button);
        if (button == 0 && _focussed)
        {
            if (_style == style::horizontal)
            {
                _value = ofMap(x, 0, _contentWidth, _value.getMin(), _value.getMax());
            }
            else if (_style == style::vertical)
            {
                _value = ofMap(_contentHeight - y, 0, _contentHeight, _value.getMin(), _value.getMax());
            }
            else if (_style == style::rotary)
            {
                // TODO
            }
        }
    }

    void setStyle(style s)
    {
        _style = s;
        setup(_viewWidth, _viewHeight, _hasOverlay);
        setNeedsToBeRedrawn(true);
    }
    void setFontSize(int fontSize)
    {
        _fontSize = fontSize;
    }
    void onValueChange(T &value)
    {
        setNeedsToBeRedrawn(true);
    }

    ofParameter<T> _value;
    style _style;

    ofxWidgets::label::pointer _label;
};
typedef slider<int> intSlider;
typedef slider<float> floatSlider;
typedef slider<double> doubleSlider;
}; // namespace ofxWidgets