#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
template <class T>
class dropDown : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<dropDown> pointer;
    static pointer create()
    {
        return std::make_shared<dropDown>();
    }
    static pointer create(ofParameter<T> value, std::vector<T> options)
    {
        return std::make_shared<dropDown>(value, options);
    }
    dropDown() : widget() {
    }

    dropDown(ofParameter<T> value, std::vector<T> options) : widget(), _value(value), _options(options){
    }


    virtual void update()
    {
        _needsToBeRedrawn = true;
        widget::update();
        if(_needsToBeRedrawn){
            begin();
            ofFill();
            end();
        }
        // TODO: draw overlay
    }

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
    std::vector<T> _options;
    ofParameter<int> _fontSize;
};
typedef dropDown<int> intDropDown;
typedef dropDown<float> floatDropDown;
typedef dropDown<std::string> stringDropDown;
}; // namespace ofxWidgets