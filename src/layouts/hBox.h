#pragma once

#include "ofMain.h"

namespace ofxWidgets
{
namespace layout
{
class hBox : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<hBox> pointer;
    static pointer create()
    {
        return std::make_shared<hBox>();
    }
    void setup(float width, float height)
    {
        widget::setup(width, height);
        _backgroundColor = ofColor::blue;
    }
};
}; // namespace layout
}; // namespace ofxWidgets