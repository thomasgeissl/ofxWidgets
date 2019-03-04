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
        init();
    }
    panel(ofParameterGroup parameters, int width, int height) : widget(width, height), _layout(ofxWidgets::layout::vBox::create(width, height))
    {
        // _layout = ofxWidgets::layout::vBox::createAndAddTo(std::make_shared<ofxWidgets::panel>(this));
        _layout = ofxWidgets::layout::vBox::create(_viewWidth, _viewHeight);
        add(_layout);
        for (auto &parameter : parameters)
        {
            auto type = parameter->type();
            if (type == "11ofParameterIvE")
            {
                // TODO: height
                _layout->add(ofxWidgets::button::create(parameter->cast<void>(), _layout->getViewWidth(), 50));
            }
            else if (type == "11ofParameterIbE")
            {
                _layout->add(ofxWidgets::toggle::create(parameter->cast<bool>(), _layout->getViewWidth(), 100));
            }
            else if (type == "11ofParameterIiE")
            {
                _layout->add(ofxWidgets::intSlider::create(parameter->cast<int>(), _layout->getViewWidth(), 100));
            }
            else if (type == "11ofParameterIfE")
            {
                _layout->add(ofxWidgets::floatSlider::create(parameter->cast<float>(), _layout->getViewWidth(), 100));
            }
            else
            {
                ofLogWarning("ofxWidgets") << "trying to add parameter to panel, but " << type << " is not (yet) supported";
            }
        }
        init();
    }
    void init()
    {
        _type = TYPE_OFXWIDGETS_PANEL;
    }

    virtual void add(ofxWidgets::widget::pointer w)
    {
        _layout->add(w);
    }

  protected:
    ofxWidgets::layout::vBox::pointer _layout;
};
}; // namespace ofxWidgets