#pragma once

#include "ofMain.h"
#include "ofxWidgets.h"

class shape : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<shape> pointer;
    static pointer create()
    {
        return std::make_shared<shape>();
    }
    shape()
    {
        _color = ofColor::purple;
        _boost.set("boost", false);
        _shapePosition.set("position", glm::vec2(0, 0), glm::vec2(-1, -1), glm::vec2(1, 1));
    }

    void update()
    {
        widget::update();
        begin(false);
        ofSetColor(_color);
        if (_boost)
        {
            ofDrawCircle(_contentWidth / 2 + std::sin(ofGetElapsedTimef() * 10) * 20, _contentHeight / 2 + std::cos(ofGetElapsedTimef() * 10) * 20, 50);
        }
        else
        {
            ofDrawCircle(_contentWidth / 2 + std::sin(ofGetElapsedTimef()) * 20, _contentHeight / 2 + std::cos(ofGetElapsedTimef()) * 20, 50);
        }

        if (_focussed)
        {
            ofSetColor(ofColor::red);
            ofDrawCircle(_contentWidth / 2 + std::sin(ofGetElapsedTimef()) * 20, _contentHeight / 2 + std::cos(ofGetElapsedTimef()) * 20, 10);
        }
        end();
        setNeedsToBeRedrawn();
    }
    ofParameter<glm::vec2> _shapePosition;
    ofParameter<bool> _boost;
};