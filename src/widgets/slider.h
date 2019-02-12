#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
template <class T>
class slider : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<slider> pointer;
    static pointer create()
    {
        return std::make_shared<slider>();
    }
    static pointer create(ofParameter<T> parameter)
    {
        return std::make_shared<slider>(parameter);
    }
    slider() : widget() {
        _value.set("value", 0, 0, 100);
        _value.addListener(this, &slider::onValueChange);
    }

    slider(ofParameter<T> parameter) : widget(), _value(parameter){
        _value.addListener(this, &slider::onValueChange);
    }


    virtual void update()
    {
        _needsToBeRedrawn = true;
        widget::update();
        if(_needsToBeRedrawn){
            begin();
            ofFill();
            ofSetColor(ofColor::green);
            ofDrawRectangle(0, 0, ofMap(_value, _value.getMin(), _value.getMax(), 0, _width), _height);
            // ofDrawRectangle(0, 0, 100, _height);
            end();
        }
    }
    // TODO: arrow keys, number input
    virtual void mouseDragged(int x, int y, int button) {
        widget::mouseDragged(x, y, button);
        // TODO: calculate position and value
    }

    // TODO: horizontal, vertical, rotary
    // void setStyle(){}
    void setFontSize(int fontSize){
        _fontSize = fontSize;
    }
    void onValueChange(T & value){
        setNeedsToBeRedrawn(true);
    }
    void onFontSizeChange(int & value){
        _ttf.load(ofToDataPath("Roboto-Light.ttf"), _fontSize);
        setNeedsToBeRedrawn(true);
    }

    ofTrueTypeFont _ttf;
    ofParameter<T> _value;
    ofParameter<int> _fontSize;
};
typedef slider<int> intSlider;
typedef slider<float> floatSlider;
typedef slider<double> doubleSlider;
}; // namespace ofxWidgets