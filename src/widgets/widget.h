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
    widget()
    {
        _color.addListener(this, &widget::onColorChange);
        _backgroundColor.addListener(this, &widget::onColorChange);
        _borderColor.addListener(this, &widget::onColorChange);
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

    virtual void setup(pointer other)
    {
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
        for (auto &child : _children)
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
        auto needsToBeRedrawn = false;
        for (auto &child : _children)
        {
            if (child->_needsToBeRedrawn)
            {
                needsToBeRedrawn = true;
            }
        }
        if (!_needsToBeRedrawn && !needsToBeRedrawn)
        {
            return;
        }

        begin();
        // draw the background
        ofSetColor(_backgroundColor);
        ofDrawRectangle(0, 0, _width, _height);

        // draw each child
        for (auto &child : _children)
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
        end();
        setNeedsToBeRedrawn();
    }
    void draw()
    {
        _fbo.draw(_position);
        setNeedsToBeRedrawn(false);
    }
    virtual void keyPressed(int key)
    {
        auto w = getFocussedWidget();
        if (w != nullptr)
        {
            w->keyPressed(key);
        }
    }
    virtual void keyReleased(int key)
    {
        auto w = getFocussedWidget();
        if (w != nullptr)
        {
            w->keyReleased(key);
        }
    }
    virtual void mouseMoved(int x, int y)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseMoved(x - w->_position.x, y - w->_position.y);
        }
    }
    virtual void mouseDragged(int x, int y, int button)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseDragged(x - w->_position.x, y - w->_position.y, button);
        }
    }
    virtual void mousePressed(int x, int y, int button)
    {
        auto focussedWidget = getFocussedWidget();
        if (focussedWidget != nullptr)
        {
            focussedWidget->setFocus(false);
        }
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->setFocus(true);
            w->mousePressed(x - w->_position.x, y - w->_position.y, button);
        }
    }
    virtual void mouseReleased(int x, int y, int button)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseReleased(x - w->_position.x, y - w->_position.y, button);
        }
    }
    virtual void mouseEntered(int x, int y)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseEntered(x - w->_position.x, y - w->_position.y);
        }
    }
    virtual void mouseExited(int x, int y)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseExited(x - w->_position.x, y - w->_position.y);
        }
    }
    virtual void resized(int w, int h)
    {
        float xFactor = w / _width;
        float yFactor = h / _height;
        _width = w;
        _height = h;
        _fbo.allocate(_width, _height, GL_RGBA);
        setNeedsToBeRedrawn(true);

        for (auto &child : _children)
        {
            child->resized(child->_width * xFactor, child->_height * yFactor);
            child->_position *= glm::vec2(xFactor, yFactor);
        }
    }

    virtual void add(pointer w)
    {
        _children.push_back(std::move(w));
    }

    void setNeedsToBeRedrawn(bool value = true)
    {
        _needsToBeRedrawn = value;
    }

    void begin(bool clear = true)
    {
        ofPushMatrix();
        _fbo.begin();
        if (clear)
        {
            ofClear(255, 0);
        }
    }
    void end()
    {
        _fbo.end();
        ofPopMatrix();
    }

    pointer getWidgetAtPosition(float x, float y)
    {
        pointer w = nullptr;
        for (auto &child : _children)
        {
            if ((x > child->_position.x && x < child->_position.x + child->_width) &&
                (y > child->_position.y && y < child->_position.y + child->_height))
            {
                w = child;
            }
        }
        return w;
    }
    pointer getFocussedWidget()
    {
        pointer w = nullptr;
        for (auto &child : _children)
        {
            if (child->_focussed)
            {
                w = child;
            }
        }
        return w;
    }

    void setFocus(bool value = true)
    {
        _focussed = value;
        if (!value)
        {
            for (auto &child : _children)
            {
                child->setFocus(value);
            }
        }
    }

    // listeners
    void onColorChange(ofColor &color)
    {
        setNeedsToBeRedrawn(true);
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
    ofParameterGroup _parameters;
    ofParameter<ofColor> _color;
    ofParameter<ofColor> _backgroundColor;
    ofParameter<ofColor> _borderColor;

    int _borderWidth;
};
}; // namespace ofxWidgets