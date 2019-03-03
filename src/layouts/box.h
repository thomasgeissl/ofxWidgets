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
  static pointer create(int width, int height)
  {
    return std::make_shared<box>(width, height);
  }
  box(int width, int height) : base(width, height)
  {
  }
};
}; // namespace layout
}; // namespace ofxWidgets