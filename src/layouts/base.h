
#pragma once

#include "ofMain.h"
#include "../widgets/widget.h"

namespace ofxWidgets
{
namespace layout
{
class base : public ofxWidgets::widget
{
public:
  typedef std::shared_ptr<base> pointer;
  static pointer create()
  {
    return std::make_shared<base>();
  }
  base() : widget()
  {
    init();
  }
  void init(){
    _type = TYPE_OFXWIDGETS_LAYOUT;
  }
  virtual void recalculatePositions()
  {
  }
};
}; // namespace layout
}; // namespace ofxWidgets
