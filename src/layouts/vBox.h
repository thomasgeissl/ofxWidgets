#pragma once

#include "ofMain.h"
#include "./box.h"

namespace ofxWidgets
{
namespace layout
{
class vBox : public ofxWidgets::layout::box
{
  public:
    typedef std::shared_ptr<vBox> pointer;
    static pointer create(int width, int height)
    {
        return std::make_shared<vBox>(width, height);
    }
    vBox(int width, int height) : box(width, height)
    {
        _verticalOffset.set("verticalOffset", 0, 0, 1024 * 4);
        _verticalOffset.addListener(this, &vBox::offsetChanged);
    }
    virtual void add(ofxWidgets::widget::pointer w)
    {
        if (_children.size() > 0)
        {
            auto pos = _children.back()->_position;
            auto height = _children.back()->_viewHeight + _verticalOffset;
            w->_position = pos + glm::vec2(0, height);
        }
        widget::add(w);
    }
    void offsetChanged(float &value)
    {
        recalculatePositions();
    }

    ofParameter<float> _verticalOffset;
};
}; // namespace layout
}; // namespace ofxWidgets