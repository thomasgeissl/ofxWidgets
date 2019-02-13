#pragma once

#include "ofMain.h"
#include "./base.h"

namespace ofxWidgets
{
namespace layout
{
class box : public ofxWidgets::layout::base
{
  public:
    typedef std::shared_ptr<box> pointer;
    static pointer create()
    {
        return std::make_shared<box>();
    }
};
}; // namespace layout
}; // namespace ofxWidgets