#pragma once

#include "ofMain.h"
#include "ofxWidgets.h"

class circle : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<circle> pointer;
    static pointer create()
    {
        return std::make_shared<circle>();
    }
    circle(){
        _color = ofColor::purple;
    }

    void update()
    {
        widget::update();

        _fbo.begin();
        ofClear(255,0);
        ofSetColor(_color);
        if(_boost){
            ofDrawCircle(_width/2 + std::sin(ofGetElapsedTimef()), _height/2 + std::cos(ofGetElapsedTimef()), 100);
        }else{
            ofDrawCircle(_width/2 + std::sin(ofGetElapsedTimef())*20, _height/2 + std::cos(ofGetElapsedTimef())*20, 100);
        }

        if(_focussed){
            ofSetColor(ofColor::red);
            ofDrawCircle(_width/2 + std::sin(ofGetElapsedTimef())*20, _height/2 + std::cos(ofGetElapsedTimef())*20, 10);
        }
        _fbo.end();
        setNeedsToBeRedrawn();
    }
    ofParameter<bool> _boost;
};