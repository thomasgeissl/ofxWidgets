#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class widget
{
  public:
    typedef std::shared_ptr<widget> pointer;
    static pointer create()
    {
        return std::make_shared<widget>();
    }

    virtual void setup(float width, float height)
    {
        _needsToBeRedrawn = true;
        _width = width;
        _height = height;
        _fbo.allocate(_width, _height, GL_RGBA);
        _fbo.begin();
        ofClear(255, 0);
        _fbo.end();
        _position = glm::vec2(0, 0);
    }

    virtual void setup(pointer other){
        _needsToBeRedrawn = true;
        _width = other->_width;
        _height = other->_height;
        _fbo.allocate(_width, _height, GL_RGBA);
        _fbo.begin();
        ofClear(255, 0);
        _fbo.end();
        _position = glm::vec2(0, 0);
    }

    void setName(std::string name)
    {
        _name = name;
    }
    virtual void update()
    {
        // update all children
        for (auto & child : _children)
        {
            if (child != nullptr)
            {
                child->update();
            }
            else
            {
                //remove child
            }
        }

        // check if needs to be redrawn
        // auto needsToBeRedrawn = false;
        // for (auto & child : _children)
        // {
        //     if(child->_needsToBeRedrawn){
        //         needsToBeRedrawn = true;
        //     }
        // }
        // if(!needsToBeRedrawn){
        //     return;
        // }

        _fbo.begin();
        ofClear(255, 0);
        // draw the background
        ofSetColor(_backgroundColor);
        ofDrawRectangle(0, 0, _width, _height);

        for (auto & child : _children)
        {
            if (child != nullptr)
            {
                child->draw();
            }
            else
            {
                //remove child
            }
        }
        _fbo.end();
        setNeedsToBeRedrawn();
    }
    void draw()
    {
        _fbo.draw(_position);
        setNeedsToBeRedrawn(false);
    }
    virtual void keyPressed(int key) {
        auto w = getFocussedWidget();
        if(w != nullptr){
            w->keyPressed(key);
        }
    }
    virtual void keyReleased(int key) {
        auto w = getFocussedWidget();
        if(w != nullptr){
            w->keyReleased(key);
        }
    }
    virtual void mouseMoved(int x, int y) {
        auto w = getWidgetAtPosition(x, y);
        if(w != nullptr){
            w->mouseMoved(x, y);
        }
    }
    virtual void mouseDragged(int x, int y, int button) {
        auto w = getWidgetAtPosition(x, y);
        if(w != nullptr){
            w->mouseDragged(x, y, button);
        }
    }
    virtual void mousePressed(int x, int y, int button) {
        auto focussedWidget = getFocussedWidget();
        if(focussedWidget != nullptr){
            focussedWidget->_focussed = false;
        }
        auto w = getWidgetAtPosition(x, y);
        if(w != nullptr){
            w->_focussed = true;
            w->mousePressed(x, y, button);
        }
    }
    virtual void mouseReleased(int x, int y, int button) {
        auto w = getWidgetAtPosition(x, y);
        if(w != nullptr){
            w->mouseReleased(x, y, button);
        }
    }
    virtual void mouseEntered(int x, int y) {
        auto w = getWidgetAtPosition(x, y);
        if(w != nullptr){
            w->mouseEntered(x, y);
        }
    }
    virtual void mouseExited(int x, int y) {
        auto w = getWidgetAtPosition(x, y);
        if(w != nullptr){
            w->mouseExited(x, y);
        }
    }
    virtual void resized(int w, int h) {
    }

    virtual void add(pointer w)
    {
        _children.push_back(std::move(w));
    }

    void setNeedsToBeRedrawn(bool value = true){
        _needsToBeRedrawn = value;
    }

    pointer getWidgetAtPosition(float x, float y){
        pointer w = nullptr;
        for(auto & child : _children){
            if((x > child->_position.x && x < child->_position.x + child->_width) &&
            (y > child->_position.y && y < child->_position.y + child->_height)){
                w = child;
            }
        }
        return w;
    }
    pointer getFocussedWidget(){
        pointer w = nullptr;
        for(auto & child : _children){
            if(child->_focussed){
                w = child;
            }
        }
        return w;
    }

    bool _needsToBeRedrawn;
    ofFbo _fbo;
    glm::vec2 _position;
    std::vector<pointer> _children;

    std::string _name;
    float _width;
    float _height;
    bool _focussed;

    // style
    ofColor _backgroundColor;
    ofColor _borderColor;
    int _borderWidth;
};
}; // namespace ofxWidgets