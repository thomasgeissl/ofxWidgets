#pragma once

#include "ofMain.h"
#include "../widgets/widget.h"

namespace ofxWidgets
{
namespace layout
{
class vBox : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<vBox> pointer;
    static pointer create()
    {
        return std::make_shared<vBox>();
    }
    virtual void add(ofxWidgets::widget::pointer w)
    {
        if (_children.size() > 0)
        {
            auto pos = _children.back()->_position;
            auto height = _children.back()->_height;
            w->_position = pos + glm::vec2(0, height);
        }
        widget::add(w);
    }
};
}; // namespace layout
}; // namespace ofxWidgets