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
        _color.set("color", ofColor::lightGrey);
        _backgroundColor.set("backgroundColor", ofColor(255,0));

        _color.addListener(this, &widget::onColorChange);
        _backgroundColor.addListener(this, &widget::onColorChange);
        _borderColor.addListener(this, &widget::onColorChange);
        _fontSize.addListener(this, &widget::onFontSizeChange);

        _fontSize = 32;
        _focussed = false;

        ofTrueTypeFontSettings settings("Roboto-Light.ttf", _fontSize);
        settings.addRanges(ofAlphabet::Latin);
        settings.contours = false;
        settings.antialiased = true;
        settings.simplifyAmt = 0;
        _ttf.load(settings);
    }

    virtual void setup(float width, float height, bool hasOverlay = true)
    {
        _needsToBeRedrawn = true;
        _width = width;
        _height = height;
        _fbo.allocate(_width, _height, GL_RGBA);
        if(hasOverlay){
            setupOverlay();
        }
    }

    virtual void setup(pointer other, bool hasOverlay = true)
    {
        _needsToBeRedrawn = true;
        _width = other->_width;
        _height = other->_height;
        _fbo.allocate(_width, _height, GL_RGBA);
        if(hasOverlay){
            setupOverlay();
        }
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
        if(_overlay != nullptr){
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
        if(_overlay != nullptr && _overlayVisible){
            _overlay->draw(position + _position + _overlay->_position);
        }
        for(auto & child : _children){
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

    void setFontSize(int fontSize)
    {
        _fontSize = fontSize;
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
            // ofClear(255, 0);
            ofClear(_backgroundColor);
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
        if(_overlay != nullptr && _overlayVisible &&
            x > _overlay->_position.x && 
            x < _overlay->_position.x + _overlay->_width &&
            y > _overlay->_position.y &&
            y < _overlay->_position.y + _overlay->_height
        ){
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
        settings.addRanges(ofAlphabet::Latin);
        settings.contours = false;
        settings.antialiased = true;
        settings.simplifyAmt = 0;
        _ttf.load(settings);
        setNeedsToBeRedrawn(true);
    }

    bool _needsToBeRedrawn;
    ofFbo _fbo;
    glm::vec2 _position;
    std::vector<pointer> _children;
    pointer _overlay;

    bool _overlayVisible = false;

    std::string _name;
    float _width;
    float _height;
    bool _focussed;

    ofTrueTypeFont _ttf;

    // style
    ofParameterGroup _parameters;
    ofParameter<ofColor> _color;
    ofParameter<ofColor> _backgroundColor;
    ofParameter<ofColor> _borderColor;
    ofParameter<int> _fontSize;
    // alignment (left, center, right)
    // verticalAlignment (top, center, bottom)

    int _borderWidth;
};
}; // namespace ofxWidgets