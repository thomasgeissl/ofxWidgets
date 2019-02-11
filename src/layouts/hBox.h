#pragma once

#include "ofMain.h"
#include "../widgets/widget.h"

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
    virtual void add(ofxWidgets::widget::pointer w)
    {
        if(_children.size() > 0){
            auto pos = _children.back()->_position;
            auto width = _children.back()->_width;
            w->_position = pos + glm::vec2(width, 0);
        }
        widget::add(w);
    }
};
}; // namespace layout
}; // namespace ofxWidgets