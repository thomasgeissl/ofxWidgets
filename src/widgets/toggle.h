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
    toggle() : widget() {
        _value.addListener(this, &toggle::onValueChange);
    }
    toggle(ofParameter<bool> parameter) : _value(parameter){
        _value.addListener(this, &toggle::onValueChange);
    }


    virtual void update()
    {
        widget::update();
        // _needsToBeRedrawn = true;
        if(_needsToBeRedrawn){
            begin();
            if(_value){
                ofSetColor(ofColor::green);
                ofDrawRectangle(0,0, _width, _height);
            }else{
                ofSetColor(ofColor::red);
                ofDrawRectangle(0,0, _width, _height);
            }
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button) {
        widget::mousePressed(x, y, button);
        _value = !_value;
        // TODO: highlight
    }
    virtual void mouseReleased(int x, int y, int button) {
        widget::mouseReleased(x, y, button);
        // TODO: unhighlight
    }

    void setText(std::string text){
        _text = text;
        setNeedsToBeRedrawn(true);
    }
    void setFontSize(int fontSize){
        _fontSize = fontSize;
    }
    void onValueChange(bool & value){
        setNeedsToBeRedrawn(true);
    }
    void onFontSizeChange(int & value){
        _ttf.load(ofToDataPath("Roboto-Light.ttf"), _fontSize);
        setNeedsToBeRedrawn(true);
    }

    ofTrueTypeFont _ttf;
    ofParameter<std::string> _text;
    ofParameter<int> _fontSize;
    ofParameter<bool> _value;
};
}; // namespace ofxWidgets