
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
  static pointer createAndAddTo(ofxWidgets::widget::pointer w){
    auto layout = std::make_shared<base>(w->getViewWidth(), w->getViewHeight());
    w->add(layout);
    return layout;
  }
  static pointer create(ofxWidgets::widget::pointer w){
    return std::make_shared<base>(w->getViewWidth(), w->getViewHeight());
  }
  static pointer create(int width, int height)
  {
    return std::make_shared<base>(width, height);
  }
  base(int width, int height) : widget(width, height)
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
