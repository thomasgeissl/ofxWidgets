#pragma once

#include "ofMain.h"
#include "./box.h"

namespace ofxWidgets
{
namespace layout
{
class panel : public ofxWidgets::layout::base
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
    panel()
    {
    }
    panel(ofParameterGroup parameters)
    {
    }
    virtual void setup(int width, int height, bool hasOverlay = true)
    {
    }

    virtual void add(ofxWidgets::widget::pointer w)
    {
        _layout->add(w);
    }

    ofxWidgets::layout::vBox::pointer _layout;
};
}; // namespace layout
}; // namespace ofxWidgets