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
    }
    button(ofParameter<void> parameter) : _trigger(parameter)
    {
        _color = ofColor::lightGrey;
    }

    virtual void update()
    {
        widget::update();
        if (_needsToBeRedrawn)
        {
            begin();
            ofSetColor(_color);
            ofDrawRectangle(0, 0, _width, _height);
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        _trigger.trigger();
        // TODO: highlight
    }
    virtual void mouseReleased(int x, int y, int button)
    {
        widget::mouseReleased(x, y, button);
        // TODO: unhighlight
    }

    ofParameter<void> _trigger;
};
}; // namespace ofxWidgets