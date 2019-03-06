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
        return std::make_shared<vBox>(width, height);
    }
    vBox(int width, int height) : box(width, height)
    {
        _verticalOffset.set("verticalOffset", 0, 0, 1024 * 4);
        _verticalOffset.addListener(this, &vBox::offsetChanged);
    }
    virtual void add(ofxWidgets::widget::pointer w)
    {
        auto y = 0;
        auto x = 0;
        if (_children.size() > 0)
        {
            y += _verticalOffset;
            y += _children.back()->_position.y;
            y += _children.back()->_viewHeight;
            if (w->getContentWidth() < _contentWidth)
            {
                x = (_contentWidth - w->getContentWidth()) / 2;
            }
        }
        w->_position.x = x;
        w->_position.y = y;
        widget::add(w);
    }
    void offsetChanged(float &value)
    {
        recalculatePositions();
    }

    void setOffset(float value)
    {
        _verticalOffset = value;
    }

  protected:
    ofParameter<float> _verticalOffset;
};
}; // namespace layout
}; // namespace ofxWidgets