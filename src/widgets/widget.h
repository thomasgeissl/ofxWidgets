#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
class widget
{
  public:
    enum alignment
    {
        left,
        center,
        right,
        top,
        bottom
    };
    static ofColor brigthenColor(ofColor color, float amount)
    {
        auto brightness = color.getBrightness();
        ofColor brightenedColor = color;
        brightenedColor.setBrightness(brightness * (1 + amount));
        return brightenedColor;
    }
    typedef std::shared_ptr<widget> pointer;
    static pointer create()
    {
        return std::make_shared<widget>();
    }
    widget()
    {
        _pressed.addListener(this, &widget::onPressedChange);
        _pressed.set("pressed", false);
        _hovered.set("hovered", false);

        _alignment = alignment::left;
        _verticalAlignment = alignment::top;
        _color.addListener(this, &widget::onColorChange);
        _backgroundColor.addListener(this, &widget::onColorChange);
        _borderColor.addListener(this, &widget::onColorChange);
        _fontSize.addListener(this, &widget::onFontSizeChange);

        _color.set("color", ofColor::lightGrey);
        _backgroundColor.set("backgroundColor", ofColor(255, 0));

        _fontSize = 32;

        // border
        _borderColor.set("borderColor", ofColor(255, 0));
        _borderWidth.set("borderWidth", 0, 0, 100);

        ofTrueTypeFontSettings settings("Roboto-Light.ttf", _fontSize);
        settings.contours = false;
        settings.antialiased = true;
        settings.simplifyAmt = 0;
        _ttf.load(settings);
    }

    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        _children.clear();
        _needsToBeRedrawn = true;
        _width = width;
        _height = height;
        _hasOverlay = hasOverlay;
        _fbo.allocate(_width, _height, GL_RGBA);
        if (hasOverlay)
        {
            setupOverlay();
        }
    }

    virtual void setup(pointer other, bool hasOverlay = true)
    {
        setup(other->_width, other->_height, hasOverlay);
    }
    virtual void setupOverlay()
    {
        _overlay = ofxWidgets::widget::create();
        _overlay->setup(_width, _height, false);
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
        if (_overlay != nullptr)
        {
            _overlay->update();
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

        if (_overlay != nullptr && _overlay->_needsToBeRedrawn)
        {
            needsToBeRedrawn = true;
        }
        if (!_needsToBeRedrawn && !needsToBeRedrawn)
        {
            return;
        }

        begin();
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
        // updateOverlay();
        ofNoFill();
        ofSetColor(_borderColor);
        ofSetLineWidth(_borderWidth);
        ofDrawRectangle(0, 0, _width, _height);

        end();
        setNeedsToBeRedrawn();
    }
    virtual void updateOverlay()
    {
    }
    void draw()
    {
        _fbo.draw(_position);
        setNeedsToBeRedrawn(false);
    }
    void draw(glm::vec2 position)
    {
        _fbo.draw(position);
    }
    void drawOverlay(glm::vec2 position)
    {
        if (_overlay != nullptr && _overlayVisible)
        {
            _overlay->draw(position + _position + _overlay->_position);
        }
        for (auto &child : _children)
        {
            child->drawOverlay(position + _position);
        }
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
        if (!_hovered)
        {
            for (auto &child : _children)
            {
                child->mouseExited(x - child->_position.x, y - child->_position.y);
            }
            mouseEntered(x, y);
        }
        else
        {
            auto w = getWidgetAtPosition(x, y);
            if (w != nullptr)
            {
                return;
                w->mouseMoved(x - w->_position.x, y - w->_position.y);
            }
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
        else
        {
            _pressed = true;
        }
    }
    virtual void mouseReleased(int x, int y, int button)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseReleased(x - w->_position.x, y - w->_position.y, button);
        }
        else
        {
            _pressed = false;
        }
    }
    virtual void mouseEntered(int x, int y)
    {
        auto w = getWidgetAtPosition(x, y);
        if (w != nullptr)
        {
            w->mouseEntered(x - w->_position.x, y - w->_position.y);
        }
        else
        {
            _hovered = true;
            setNeedsToBeRedrawn(true);
        }
    }
    virtual void mouseExited(int x, int y)
    {
        _hovered = false;
        _pressed = false;
        setNeedsToBeRedrawn(true);
        for (auto &child : _children)
        {
            child->mouseExited(x - child->_position.x, y - child->_position.y);
        }
    }
    virtual void resized(int w, int h)
    {
        auto xFactor = (float)(w) / _width;
        auto yFactor = (float)(h) / _height;
        _width = w;
        _height = h;
        _fbo.allocate(_width, _height, GL_RGBA);
        setNeedsToBeRedrawn(true);

        for (auto &child : _children)
        {
            child->resized((float)(child->_width) * xFactor, (float)(child->_height) * yFactor);
            child->_position *= glm::vec2(xFactor, yFactor);
        }
    }

    virtual void add(pointer w)
    {
        _children.push_back(std::move(w));
    }

    virtual void setFontSize(int fontSize)
    {
        _fontSize = fontSize;
    }
    virtual void setAlignment(alignment a)
    {
        _alignment = a;
    }
    void setVerticalAlignment(alignment a)
    {
        _verticalAlignment = a;
    }
    void setNeedsToBeRedrawn(bool value = true)
    {
        _needsToBeRedrawn = value;
    }

    void begin(bool clear = true)
    {
        ofPushMatrix();
        ofPushStyle();
        _fbo.begin();
        if (clear)
        {
            // ofClear(255, 0);
            ofClear(_backgroundColor);
        }
    }
    void end()
    {
        _fbo.end();
        ofPopStyle();
        ofPopMatrix();
    }

    pointer getWidgetAtPosition(float x, float y)
    {
        pointer w = nullptr;
        if (_overlay != nullptr && _overlayVisible &&
            x > _overlay->_position.x &&
            x < _overlay->_position.x + _overlay->_width &&
            y > _overlay->_position.y &&
            y < _overlay->_position.y + _overlay->_height)
        {
            return _overlay;
        }
        // if(_overlay != nullptr){
        //     ofLogNotice() << _overlayVisible <<": "<<x <<" "<<y << " "<<_overlay->_position;
        // }
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
    void onFontSizeChange(int &value)
    {
        ofTrueTypeFontSettings settings("Roboto-Light.ttf", _fontSize);
        settings.contours = false;
        settings.antialiased = true;
        settings.simplifyAmt = 0;
        _ttf.load(settings);
        setNeedsToBeRedrawn(true);
    }
    void onPressedChange(bool &value)
    {
        setNeedsToBeRedrawn(true);
    }

    bool _needsToBeRedrawn;
    bool _hasOverlay;
    ofFbo _fbo;
    glm::vec2 _position;
    std::vector<pointer> _children;
    pointer _overlay;

    bool _overlayVisible = false;

    std::string _name;
    int _width;
    int _height;
    ofParameter<bool> _focussed;
    ofParameter<bool> _hovered;
    ofParameter<bool> _pressed;

    ofTrueTypeFont _ttf;

    // style
    ofParameterGroup _parameters;
    ofParameter<ofColor> _color;
    ofParameter<ofColor> _backgroundColor;
    ofParameter<int> _fontSize;
    alignment _alignment;
    alignment _verticalAlignment;

    ofParameter<ofColor> _borderColor;
    ofParameter<float> _borderWidth;


    static ofParameter<bool> _debug;
};
}; // namespace ofxWidgets