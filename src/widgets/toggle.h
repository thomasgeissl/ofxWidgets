#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class toggle : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<toggle> pointer;
    static pointer create()
    {
        return std::make_shared<toggle>();
    }
    static pointer create(ofParameter<bool> parameter)
    {
        return std::make_shared<toggle>(parameter);
    }
    toggle() : widget()
    {
        _value.addListener(this, &toggle::onValueChange);
        _color = ofColor::darkGrey;
        _inactiveColor = ofColor::lightGrey;
    }
    toggle(ofParameter<bool> parameter) : _value(parameter)
    {
        _value.addListener(this, &toggle::onValueChange);
        _color = ofColor::darkGrey;
        _inactiveColor = ofColor::lightGrey;
    }

    virtual void update()
    {
        widget::update();
        if (_needsToBeRedrawn)
        {
            begin();
            if (_value)
            {
                ofSetColor(_color);
                ofDrawRectangle(0, 0, _width, _height);
            }
            else
            {
                ofSetColor(_inactiveColor);
                ofDrawRectangle(0, 0, _width, _height);
            }
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        _value = !_value;
        // TODO: highlight
    }
    virtual void mouseReleased(int x, int y, int button)
    {
        widget::mouseReleased(x, y, button);
        // TODO: unhighlight
    }

    void onValueChange(bool &value)
    {
        setNeedsToBeRedrawn(true);
    }

    ofParameter<bool> _value;
    ofParameter<ofColor> _inactiveColor;
};
}; // namespace ofxWidgets