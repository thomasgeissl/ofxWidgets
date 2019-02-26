#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class button : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<button> pointer;
    static pointer create()
    {
        return std::make_shared<button>();
    }
    static pointer create(ofParameter<void> parameter)
    {
        return std::make_shared<button>(parameter);
    }
    button() : widget()
    {
        _color = ofColor::lightGrey;
        setFontSize(16);
    }
    button(ofParameter<void> parameter) : _trigger(parameter)
    {
        _color = ofColor::lightGrey;
        setFontSize(16);
        _label = ofxWidgets::label::create();
        _label->_text = parameter.getName();
        _label->setAlignment(ofxWidgets::widget::alignment::center);
    }
    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        _children.clear();
        widget::setup(width, height, hasOverlay);
        _label->setup(_width, _height);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            // widget::update();
            _label->update();
            begin();
            if (_pressed)
            {
                ofSetColor(_color);
            }
            else
            {
                ofSetColor(brigthenColor(_color, -0.5));
            }
            ofDrawRectangle(0, 0, _width, _height);
            _label->draw();

            if (_hovered)
            {
                ofNoFill();
                ofSetColor(brigthenColor(_color, -0.25));
                ofSetLineWidth(1);
                ofDrawRectangle(0, 0, _width, _height);
            }
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        _trigger.trigger();
    }

    ofParameter<void> _trigger;
    ofxWidgets::label::pointer _label;
};
}; // namespace ofxWidgets