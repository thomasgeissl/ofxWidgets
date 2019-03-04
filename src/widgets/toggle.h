#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class toggle : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<toggle> pointer;
    static pointer create(std::string text, bool value, int width, int height)
    {
        return std::make_shared<toggle>(text, value, width, height);
    }
    static pointer create(ofParameter<bool> parameter, int width, int height)
    {
        return std::make_shared<toggle>(parameter, width, height);
    }
    toggle(std::string text, bool value, int width, int height) : widget(width, height)
    {
        _value.set(text, value);
        init();
    }
    toggle(ofParameter<bool> parameter, int width, int height) : widget(width, height), _value(parameter)
    {
        init();
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_TOGGLE;
        _value.addListener(this, &toggle::onValueChange);
        _checkedText.addListener(this, &toggle::onCheckedTextChange);
        _checkedText.set("checkedText", "on");
        _unCheckedText.addListener(this, &toggle::onUnCheckedTextChange);
        _unCheckedText.set("uncheckedText", "off");

        _label = ofxWidgets::label::create(_value.getName(), _contentWidth, _contentHeight / 2);
        _label->_position = glm::vec2(0, _contentHeight / 2);
        add(_label);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            if (_value)
            {
                _label->setValue(_value.getName() + ": " + _checkedText.get());
            }
            else
            {
                _label->setValue(_value.getName() + ": " + _unCheckedText.get());
            }
            // update and draw all children
            widget::update();
            // draw a new layer onto the the fbo, but dont clear it
            begin(false);
            float offset = _contentHeight * 0.05;
            float height = _contentHeight - 2 * offset;
            height /= 2;
            float width = _contentWidth / 2 - 2 * offset;
            float x = offset;
            float y = offset;
            if (_value)
            {
                ofSetColor(_color);
                ofDrawRectangle(_contentWidth / 2 + x, y, width, height);
            }
            else
            {
                ofSetColor(_secondaryColor);
                ofDrawRectangle(x, y, width, height);
            }
            ofNoFill();
            ofSetLineWidth(1);
            ofDrawRectangle(x, y, _contentWidth - 2 * offset, height);
            ofFill();
            // _label->draw();
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        _value = !_value;
    }
    void onValueChange(bool &value)
    {
        setNeedsToBeRedrawn(true);
    }
    void onCheckedTextChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }
    void onUnCheckedTextChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }

    void setValue(bool value)
    {
        _value = value;
    }
    ofParameter<bool> &getValue()
    {
        return _value;
    }
    void setCheckedText(std::string value){
        _checkedText = value;
    }
    void setUnCheckedText(std::string value){
        _unCheckedText = value;
    }

  protected:
    ofParameter<bool> _value;
    ofParameter<std::string> _checkedText;
    ofParameter<std::string> _unCheckedText;
    ofxWidgets::label::pointer _label;
};
}; // namespace ofxWidgets