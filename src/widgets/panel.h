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
    static pointer create(int width, int height)
    {
        return std::make_shared<panel>(width, height);
    }
    static pointer create(ofParameterGroup parameters, int width, int height)
    {
        return std::make_shared<panel>(parameters, width, height);
    }
    panel(int width, int height) : widget(width, height)
    {
    }
    panel(ofParameterGroup parameters, int width, int height) : widget(width, height), _layout(ofxWidgets::layout::vBox::create(width, height))
    {
        for (auto &parameter : parameters)
        {
            auto type = parameter->type();
            if (type == "11ofParameterIvE")
            {
                // auto widget = ofxWidgets::button::create(parameter->cast<void>());
                // _layout->add(widget);
            }
            else if (type == "11ofParameterIbE")
            {
                // auto widget = ofxWidgets::toggle::create(parameter->cast<bool>());
                // _layout->add(widget);
            }
            else if (type == "11ofParameterIiE")
            {
                // auto widget = ofxWidgets::intSlider::create(parameter->cast<int>());
                // _layout->add(widget);
            }
            else if (type == "11ofParameterIfE")
            {
                // auto widget = ofxWidgets::floatSlider::create(parameter->cast<float>());
                // _layout->add(widget);
            }
            else
            {
                ofLogWarning("ofxWidgets") << "trying to add parameter to panel, but " << type << " is not (yet) supported";
            }
        }
        add(_layout);
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_PANEL;
    }

    virtual void add(ofxWidgets::widget::pointer w)
    {
        _layout->add(w);
    }

    ofxWidgets::layout::vBox::pointer _layout;
};
}; // namespace ofxWidgets