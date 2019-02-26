#pragma once

#include "ofMain.h"
#include "./box.h"

namespace ofxWidgets
{
namespace layout
{
class hBox : public ofxWidgets::layout::box
{
  public:
    typedef std::shared_ptr<hBox> pointer;
    static pointer create()
    {
        return std::make_shared<hBox>();
    }
    hBox(){
        _horizontalOffset.set("horizontalOffset", 0, 0, 1024*4);
        _horizontalOffset.addListener(this, &hBox::offsetChanged);
    }

    virtual void add(ofxWidgets::widget::pointer w)
    {
        if (_children.size() > 0)
        {
            auto pos = _children.back()->_position;
            auto width = _children.back()->_viewWidth;
            w->_position = pos + glm::vec2(width, 0);
        }
        widget::add(w);
    }
    void offsetChanged(float & value){
        recalculatePositions();
    }


    ofParameter<float> _horizontalOffset;
};
}; // namespace layout
}; // namespace ofxWidgets