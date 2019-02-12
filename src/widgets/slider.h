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
    static pointer create()
    {
        return std::make_shared<slider>();
    }
    static pointer create(ofParameter<T> parameter)
    {
        return std::make_shared<slider>(parameter);
    }
    slider() : widget()
    {
        _value.set("value", 0, 0, 100);
        _value.addListener(this, &slider::onValueChange);
        _style = style::horizontal;
        _color = ofColor::darkGrey;
    }

    slider(ofParameter<T> parameter) : widget(), _value(parameter)
    {
        _value.addListener(this, &slider::onValueChange);
        _style = style::horizontal;
        _color = ofColor::darkGrey;
    }

    virtual void update()
    {
        _needsToBeRedrawn = true;
        widget::update();
        if (_needsToBeRedrawn)
        {
            begin();
            ofFill();
            ofSetColor(_color);
            if (_style == style::horizontal)
            {
                ofDrawRectangle(0, 0, ofMap(_value, _value.getMin(), _value.getMax(), 0, _width), _height);
            }
            else if (_style == style::vertical)
            {
                auto height = ofMap(_value, _value.getMin(), _value.getMax(), 0, _height);
                ofDrawRectangle(0, _height - height, _width, height);
            }
            else if (_style == style::rotary)
            {
                // TODO
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
                _value = ofMap(x, 0, _width, _value.getMin(), _value.getMax());
            }
            else if (_style == style::vertical)
            {
                _value = ofMap(_height - y, 0, _height, _value.getMin(), _value.getMax());
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
        if (button == 0)
        {
            if (_style == style::horizontal)
            {
                _value = ofMap(x, 0, _width, _value.getMin(), _value.getMax());
            }
            else if (_style == style::vertical)
            {
                _value = ofMap(_height - y, 0, _height, _value.getMin(), _value.getMax());
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
    void onFontSizeChange(int &value)
    {
        _ttf.load(ofToDataPath("Roboto-Light.ttf"), _fontSize);
        setNeedsToBeRedrawn(true);
    }

    ofTrueTypeFont _ttf;
    ofParameter<T> _value;
    ofParameter<int> _fontSize;
    style _style;
};
typedef slider<int> intSlider;
typedef slider<float> floatSlider;
typedef slider<double> doubleSlider;
}; // namespace ofxWidgets