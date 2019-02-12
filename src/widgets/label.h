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
    label() : widget() {
        _fontSize = 32;
        _ttf.load(ofToDataPath("Roboto-Light.ttf"), _fontSize);
        _text.addListener(this, &label::onTextChange);
        _fontSize.addListener(this, &label::onFontSizeChange);
    }
    label(ofParameter<std::string> parameter) : _text(parameter){
        label();
    }


    virtual void update()
    {
        widget::update();
        if(_needsToBeRedrawn){
            begin();
            ofFill();
            ofSetColor(_color);
            _ttf.drawString(_text, 0, 36);
            _fbo.end();
        }
    }
    void setText(std::string text){
        _text = text;
        setNeedsToBeRedrawn(true);
    }
    void setFontSize(int fontSize){
        _fontSize = fontSize;
    }
    void onTextChange(std::string & value){
        setNeedsToBeRedrawn(true);
    }
    void onFontSizeChange(int & value){
        _ttf.load(ofToDataPath("Roboto-Light.ttf"), _fontSize);
        setNeedsToBeRedrawn(true);
    }

    ofTrueTypeFont _ttf;
    ofParameter<std::string> _text;
    ofParameter<int> _fontSize;
};
}; // namespace ofxWidgets