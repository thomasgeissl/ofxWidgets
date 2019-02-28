#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
template <class T>
class dropDown : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<dropDown> pointer;
    typedef std::pair<T, std::string> option;
    class overlay : public ofxWidgets::widget
    {
      public:
        typedef std::shared_ptr<overlay> pointer;
        static pointer create(ofParameter<T> value, std::vector<option> options)
        {
            return std::make_shared<overlay>(value, options);
        }
        overlay(ofParameter<T> value, std::vector<option> options) : _value(value), _options(options)
        {
            setFontSize(24);
        }
        void update()
        {
            widget::update();
            begin();
            auto y = 0;
            for (auto &opt : _options)
            {
                ofSetColor(ofColor::lightGrey);
                ofDrawRectangle(0, y, _contentWidth, 18);
                ofSetColor(ofColor::black);
                _ttf.drawString(opt.second, 0, y + 20);
                y += 20;
            }
            end();
        }
        ofParameter<T> _value;
        std::vector<option> _options;
    };
    static option createOption(T value, std::string text)
    {
        return std::make_pair(value, text);
    }
    static pointer create()
    {
        return std::make_shared<dropDown>();
    }
    static pointer create(ofParameter<T> value, std::vector<option> options)
    {
        return std::make_shared<dropDown>(value, options);
    }
    dropDown() : widget()
    {
        init();
    }

    dropDown(ofParameter<T> value, std::vector<option> options) : widget(), _value(value), _options(options)
    {
        init();
    }
    void init()
    {
    }

    virtual void setupOverlay()
    {
        _overlay = overlay::create(_value, _options);
        auto height = _options.size() * 20;
        _overlay->setup(_contentWidth, height, false);
    }
    virtual void update()
    {
        widget::update();
        if (_needsToBeRedrawn)
        {
            begin();
            ofFill();
            ofSetColor(ofColor::purple);
            ofDrawRectangle(0, 0, _contentWidth, _contentHeight);
            end();
        }

        widget::updateOverlay();
        if (_overlay != nullptr)
        {
            _overlay->update();
        }
    }

    void onValueChange(T &value)
    {
        setNeedsToBeRedrawn(true);
    }

    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        _overlayVisible = !_overlayVisible;
    }

    ofParameter<T> _value;
    std::vector<option> _options;
    int _currentIndex;
};
typedef dropDown<int> intDropDown;
typedef dropDown<float> floatDropDown;
typedef dropDown<std::string> stringDropDown;
}; // namespace ofxWidgets