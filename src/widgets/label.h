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
        init();
    }
    label(ofParameter<std::string> parameter) : widget(), _text(parameter)
    {
        init();
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_LABEL;
        ofTrueTypeFont::setGlobalDpi(72);
        _fontSize = 32;
        _text.addListener(this, &label::onTextChange);
    }
    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        _children.clear();
        widget::setup(width, height, hasOverlay);
        // TODO: calculate font size based on height and width
        _fontSize = height * .8;
    }

    virtual void update()
    {
        if (_needsToBeRedrawn)
        {
            widget::update();
            begin(false);
            ofFill();
            ofSetColor(_color);
            auto boundingBox = _ttf.getStringBoundingBox(_text, 0, 0);
            auto width = boundingBox.getWidth();
            if (_alignment == alignment::left)
            {
                _ttf.drawString(_text, 0, _fontSize);
            }
            else if (_alignment == alignment::center)
            {
                _ttf.drawString(_text, _contentWidth / 2 - width / 2, _fontSize);
            }
            else
            {
                _ttf.drawString(_text, _contentWidth - width, _fontSize);
            }
            end();
        }
    }
    void setText(std::string text)
    {
        _text = text;
    }
    void onTextChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }

    ofParameter<std::string> _text;
};
}; // namespace ofxWidgets