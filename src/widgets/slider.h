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
    static pointer create(std::string text, T value, T min, T max, int width, int height, style s = style::horizontal)
    {
        return std::make_shared<slider>(text, value, min, max, width, height, s);
    }
    static pointer create(ofParameter<T> parameter, int width, int height, style s = style::horizontal)
    {
        return std::make_shared<slider>(parameter, width, height, s);
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
            _label = ofxWidgets::label::create(_value.getName(), _contentWidth, _contentHeight / 4);
            _label->_position = glm::vec2(0, _contentHeight / 4 * 3);
            _label->setAlignment(ofxWidgets::widget::alignment::center);
        }
        add(_label);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            _label->setValue(_value.getName() + ": " + ofToString(_value));
            widget::update();
            begin(false);
            if (_style == style::horizontal)
            {
                ofSetColor(_secondaryColor);
                ofDrawRectangle(0, 0, _contentWidth, _contentHeight / 2);
                ofSetColor(_color);
                ofDrawRectangle(0, 0, ofMap(_value, _value.getMin(), _value.getMax(), 0, _contentWidth), _contentHeight / 2);
            }
            else if (_style == style::vertical)
            {
                ofSetColor(_secondaryColor);
                auto sliderWidth = _contentWidth / 10;
                ofDrawRectangle(0, 0, sliderWidth, _contentHeight);
                ofSetColor(_color);
                auto height = ofMap(_value, _value.getMin(), _value.getMax(), 0, _contentHeight);
                ofDrawRectangle(0, _contentHeight - height, sliderWidth, height);
            }
            else if (_style == style::rotary)
            {
                ofSetColor(_secondaryColor);
                glm::vec2 center(_contentWidth / 2, _contentHeight / 4 * 3 / 2);
                auto radius = _contentHeight / 4 * 3 / 2;
                ofDrawCircle(center.x, center.y, radius);

                ofPolyline line;
                float mapped = ofMap(_value, _value.getMin(), _value.getMax(), 0 + 90, 359.99 + 90);
                if (mapped > 360)
                {
                    mapped -= 360;
                }

                line.arc(center.x, center.y, radius * 0.9, radius * 0.9, 90, mapped);
                ofSetLineWidth(5);
                ofSetColor(_color);
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
                if (y < _contentHeight / 4 * 3)
                {
                    glm::vec2 a(x, y);
                    glm::vec2 b(_contentWidth/2, _contentHeight/4*3/2 + 1);
                    glm::vec2 origin(_contentWidth/2, _contentHeight/4*3/2);
                    glm::vec2 da = glm::normalize(a - origin);
                    glm::vec2 db = glm::normalize(b - origin);
                    auto angle = glm::acos(glm::dot(da, db)) * 180 / 3.14;//glm::pi;
                    if(x > _contentWidth/2){
                        angle = 360 - angle;
                    }
                    _value = ofMap(angle, 0, 359.99, _value.getMin(), _value.getMax());
                }
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
                if (y < _contentHeight / 4 * 3)
                {
                    _value = ofMap(_contentHeight / 4 * 3 - y, 0, _contentHeight / 4 * 3, _value.getMin(), _value.getMax(), true);
                }
            }
        }
    }

    void setStyle(style s)
    {
        _style = s;
        setup(_viewWidth, _viewHeight, _hasOverlay);
        init();
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

    void setValue(T value)
    {
        _value = value;
    }
    ofParameter<T> &getValue()
    {
        return _value;
    }

  protected:
    ofParameter<T> _value;
    style _style;

    ofxWidgets::label::pointer _label;
};
typedef slider<int> intSlider;
typedef slider<float> floatSlider;
typedef slider<double> doubleSlider;
}; // namespace ofxWidgets