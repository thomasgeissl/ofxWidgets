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
    button() : widget() {
    }
    button(ofParameter<void> parameter) : _trigger(parameter){
        button();
    }


    virtual void update()
    {
        widget::update();
        if(_needsToBeRedrawn){
            begin();
            ofSetColor(ofColor::red);
            ofDrawRectangle(0,0, 50, 50);
            end();
        }
    }
    virtual void mousePressed(int x, int y, int button) {
        widget::mousePressed(x, y, button);
        _trigger.trigger();
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
    ofParameter<void> _trigger;
};
}; // namespace ofxWidgets