#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class button : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<button> pointer;
    static pointer create(std::string text, int width, int height)
    {
        return std::make_shared<button>(text, width, height);
    }
    static pointer create(ofParameter<void> parameter, int width, int height)
    {
        return std::make_shared<button>(parameter, width, height);
    }
    button(std::string text, int width, int height) : widget(width, height)
    {
        _value.setName("text");
        init();
    }
    button(ofParameter<void> parameter, int width, int height) : widget(width, height), _value(parameter)
    {
        init();
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_BUTTON;
        _label = ofxWidgets::label::create(_value.getName(), _contentWidth, _contentHeight);
        _label->setAlignment(ofxWidgets::widget::alignment::center);
        add(_label);
    }
    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        widget::setup(width, height, hasOverlay);
        _label->setup(_contentWidth, _contentHeight);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            // update and draw all children
            widget::update();
            // clear fbo and draw onto it
            begin();
            if (_pressed)
            {
                ofSetColor(_color);
            }
            else
            {
                ofSetColor(_secondaryColor);
            }
            ofDrawRectangle(0, 0, _contentWidth, _contentHeight);
            _label->draw();

            if (_hovered)
            {
                ofNoFill();
                ofSetColor(_color);
                ofSetLineWidth(1);
                ofDrawRectangle(0, 0, _contentWidth, _contentHeight);
            }
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        _value.trigger();
    }

    void trigger(){
        _value.trigger();
    }
    void setValue(){
        _value.trigger();
    }
    ofParameter<void> & getValue(){
        return _value;
    }
  protected:
    ofParameter<void> _value;
    ofxWidgets::label::pointer _label;
};
}; // namespace ofxWidgets