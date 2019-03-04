#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class label : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<label> pointer;
    static pointer create(std::string text, ofxWidgets::widget::pointer w)
    {
        return create(text, w->getViewWidth(), w->getViewHeight());
    }
    static pointer create(ofParameter<std::string> text, ofxWidgets::widget::pointer w)
    {
        return create(text, w->getViewWidth(), w->getViewHeight());
    }
    static pointer create(std::string text, int width, int height)
    {
        return std::make_shared<label>(text, width, height);
    }
    static pointer create(ofParameter<std::string> parameter, int width, int height)
    {
        return std::make_shared<label>(parameter, width, height);
    }
    label(std::string text, int width, int height) : widget(width, height)
    {
        _value.set(text, text); // parameter name, value
        init();
    }
    label(ofParameter<std::string> parameter, int width, int height) : widget(width, height), _value(parameter)
    {
        init();
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_LABEL;
        ofTrueTypeFont::setGlobalDpi(72);
        _fontSize = _contentHeight * .8;
        _value.addListener(this, &label::onValueChange);
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            widget::update();
            begin(false);
            ofFill();
            ofSetColor(_color);
            auto boundingBox = _ttf.getStringBoundingBox(_value, 0, 0);
            auto width = boundingBox.getWidth();
            if (_alignment == alignment::left)
            {
                _ttf.drawString(_value, 0, _fontSize);
            }
            else if (_alignment == alignment::center)
            {
                _ttf.drawString(_value, _contentWidth / 2 - width / 2, _fontSize);
            }
            else
            {
                _ttf.drawString(_value, _contentWidth - width, _fontSize);
            }
            end();
        }
    }
    void onValueChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }

    void setValue(std::string value)
    {
        _value = value;
    }
    ofParameter<std::string> &getValue()
    {
        return _value;
    }

  protected:
    ofParameter<std::string> _value;
};
}; // namespace ofxWidgets