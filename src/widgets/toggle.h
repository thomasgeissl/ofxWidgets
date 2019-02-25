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
    toggle() : widget(), _checkedText("on"), _unCheckedText("off")
    {
        _value.addListener(this, &toggle::onValueChange);
    }
    toggle(ofParameter<bool> parameter) : widget(), _value(parameter), _checkedText("on"), _unCheckedText("off")
    {
        _value.addListener(this, &toggle::onValueChange);
    }

    virtual void setup(int width, int height, bool hasOverlay = true){
        widget::setup(width, height, hasOverlay);
        _label = ofxWidgets::label::create();
        _label->_text = _value.getName();
        _label->setup(_width, height/2);
        _label->_position = glm::vec2(0, height/2);
        _label->_color = ofColor::white;
        add(_label);
    }
    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            if(_value){
                _label->_text = _value.getName() + ": "+_checkedText;
            }else{
                _label->_text = _value.getName() + ": "+_unCheckedText;
            }
            _label->setNeedsToBeRedrawn(true);
            widget::update();
            begin(false);
            float offset = _height * 0.05;
            float height = _height - 2 * offset;
            height /= 2;
            float width = _width/2 - 2 * offset;
            float x = offset;
            float y = offset;
            if (_value)
            {
                ofSetColor(_color);
                ofDrawRectangle(_width/2 + x , y, width, height);
            }
            else
            {
                ofSetColor(brigthenColor(_color, -.5));
                ofDrawRectangle(x, y, width, height);
            }
            _label->draw();
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

    ofParameter<bool> _value;
    ofxWidgets::label::pointer _label;

    std::string _checkedText;
    std::string _unCheckedText;
};
}; // namespace ofxWidgets