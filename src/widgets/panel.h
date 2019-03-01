#pragma once

#include "ofMain.h"
#include "./widget.h"
#include "./button.h"
#include "./toggle.h"
#include "./slider.h"
#include "./colorPicker.h"

namespace ofxWidgets
{
class panel : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<panel> pointer;
    static pointer create()
    {
        return std::make_shared<panel>();
    }
    static pointer create(ofParameterGroup parameters)
    {
        return std::make_shared<panel>(parameters);
    }
    panel() : widget()
    {
    }
    panel(ofParameterGroup parameters) : widget(), _layout(ofxWidgets::layout::vBox::create())
    {
        for (auto &parameter : parameters)
        {
            auto type = parameter->type();
            if (type == "11ofParameterIvE")
            {
                auto widget = ofxWidgets::button::create(parameter->cast<void>());
                _layout->add(widget);
            }
            else if (type == "11ofParameterIbE")
            {
                auto widget = ofxWidgets::toggle::create(parameter->cast<bool>());
                _layout->add(widget);
            }
            else if (type == "11ofParameterIiE")
            {
                auto widget = ofxWidgets::intSlider::create(parameter->cast<int>());
                _layout->add(widget);
            }
            else if (type == "11ofParameterIfE")
            {
                auto widget = ofxWidgets::floatSlider::create(parameter->cast<float>());
                _layout->add(widget);
            }
            else
            {
                ofLogWarning("ofxWidgets") << "trying to add parameter to panel, but " << type << " is not (yet) supported";
            }
        }
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_PANEL;
    }
    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        widget::setup(width, height, hasOverlay);
        _layout->setup(_viewWidth, _viewHeight, hasOverlay);
        for (auto &child : _layout->_children)
        {
            child->setup(_layout->getViewWidth(), _layout->getViewHeight() / _layout->_children.size(), hasOverlay);
        }
        add(_layout);
    }

    virtual void add(ofxWidgets::widget::pointer w)
    {
        _layout->add(w);
    }

    ofxWidgets::layout::vBox::pointer _layout;
};
}; // namespace ofxWidgets