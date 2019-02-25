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
    }

    slider(ofParameter<T> parameter) : widget(), _value(parameter)
    {
        _value.addListener(this, &slider::onValueChange);
        _style = style::horizontal;
    }
    virtual void setup(int width, int height, bool hasOverlay = true){
        widget::setup(width, height, hasOverlay);

        _label = ofxWidgets::label::create();
        if(_style == style::horizontal){
            _label->setup(_width, height/2);
            _label->_position = glm::vec2(0, height/2);
        }else if(_style == style::vertical){
            auto sliderWidth = _width/10;
            _label->setup(sliderWidth*9, sliderWidth);
            _label->_position = glm::vec2(sliderWidth, (_height-sliderWidth)/2);
        }
        _label->_color = ofColor::white;
        add(_label);
        setNeedsToBeRedrawn(true);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            widget::update();
            _label->_text = _value.getName() + ": " + ofToString(_value);
            _label->setNeedsToBeRedrawn(true);
            begin(false);
            ofFill();
            if (_style == style::horizontal)
            {
                ofSetColor(brigthenColor(_color, -.5));
                ofDrawRectangle(0, 0, _width, _height/2);
                ofSetColor(_color);
                ofDrawRectangle(0, 0, ofMap(_value, _value.getMin(), _value.getMax(), 0, _width), _height/2);
            }
            else if (_style == style::vertical)
            {
                ofSetColor(brigthenColor(_color, -.5));
                auto sliderWidth = _width/10;
                ofDrawRectangle(0, 0, sliderWidth, _height);
                ofSetColor(_color);
                auto height = ofMap(_value, _value.getMin(), _value.getMax(), 0, _height);
                ofDrawRectangle(0, _height - height, sliderWidth, height);
            }
            else if (_style == style::rotary)
            {
                // TODO
            }
            _label->draw();
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
        if (button == 0 && _focussed)
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
        setup(_width, _height, _hasOverlay);
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

    ofTrueTypeFont _ttf;
    ofParameter<T> _value;
    ofParameter<int> _fontSize;
    style _style;

    ofxWidgets::label::pointer _label;
};
typedef slider<int> intSlider;
typedef slider<float> floatSlider;
typedef slider<double> doubleSlider;
}; // namespace ofxWidgets