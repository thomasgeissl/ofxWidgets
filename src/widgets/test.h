#pragma once

#include "ofMain.h"
#include "./widget.h"

namespace ofxWidgets
{
class test : public widget
{
  public:
    typedef std::shared_ptr<test> pointer;
    static pointer create()
    {
        return std::make_shared<test>();
    }

    void update()
    {
        widget::update();

        _fbo.begin();
        ofClear(255,0);
        ofSetColor(ofColor::purple);
        ofDrawCircle(_width/2 + std::sin(ofGetElapsedTimeMillis())*20, _height/2 + std::cos(ofGetElapsedTimeMillis())*20, 100);
        _fbo.end();
        setNeedsToBeRedrawn();
    }
};
}; // namespace ofxWidgets