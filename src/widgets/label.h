#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class label : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<label> pointer;
    static pointer create()
    {
        return std::make_shared<label>();
    }
    static pointer create(ofParameter<std::string> parameter)
    {
        return std::make_shared<label>(parameter);
    }
    label() : widget()
    {
        _fontSize = 32;
        _text.addListener(this, &label::onTextChange);
    }
    label(ofParameter<std::string> parameter) : widget(), _text(parameter)
    {
        _fontSize = 32;
        _text.addListener(this, &label::onTextChange);
    }

    virtual void update()
    {
        // widget::update();
        if (_needsToBeRedrawn)
        {
            begin();
            ofFill();
            ofSetColor(_color);
            ofSetLineWidth(3);
            _ttf.drawString(_text, 0, 36);
            end();
        }
    }
    void setText(std::string text)
    {
        _text = text;
        setNeedsToBeRedrawn(true);
    }
    void onTextChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }

    ofParameter<std::string> _text;
};
}; // namespace ofxWidgets