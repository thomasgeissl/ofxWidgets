#pragma once

#include "ofMain.h"
#include "ofxWidgets.h"

class shape : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<shape> pointer;
    static pointer create(ofxWidgets::widget::pointer w)
    {
        return create(w->getContentWidth(), w->getContentHeight());
    }
    static pointer create(int width, int height)
    {
        return std::make_shared<shape>(width, height);
    }
    shape(int width, int height) : widget(width, height)
    {
        _fillColor = ofColor::purple;
        _boost.set("boost", false);
        _shapePosition.set("position", glm::vec2(0, 0), glm::vec2(-1, -1), glm::vec2(1, 1));
    }

    void update()
    {
        widget::update();
        begin();
        ofSetColor(_fillColor);
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
    ofParameter<ofColor> _fillColor;
};