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
    static pointer createAndAddTo(ofxWidgets::widget::pointer w)
    {
        auto layout = create(w->getViewWidth(), w->getViewHeight());
        w->add(layout);
        return layout;
    }
    static pointer create(ofxWidgets::widget::pointer w)
    {
        return create(w->getViewWidth(), w->getViewHeight());
    }
    static pointer create(int width, int height)
    {
        return std::make_shared<hBox>(width, height);
    }
    hBox(int width, int height) : box(width, height)
    {
        _horizontalOffset.set("horizontalOffset", 0, 0, 1024 * 4);
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
    void offsetChanged(float &value)
    {
        recalculatePositions();
    }

    void setOffset(float value)
    {
        _horizontalOffset = value;
    }

  protected:
    ofParameter<float> _horizontalOffset;
};
}; // namespace layout
}; // namespace ofxWidgets