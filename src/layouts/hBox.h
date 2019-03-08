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
				auto y = 0;
        auto x = 0;
        if (_children.size() > 0)
        {
            x += _horizontalOffset;
            x += _children.back()->_position.x;
            x += _children.back()->_viewWidth;
            if (w->getContentHeight() < _contentHeight)
            {
                x = (_contentHeight - w->getContentHeight()) / 2;
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
        _horizontalOffset = value;
    }
		int getRemainingWidth(){
			if(_children.size() > 0){
				return _contentWidth - _children.back()->_position.x - _children.back()->getContentWidth() - _horizontalOffset;
			}
			return _contentWidth;
		}

  protected:
    ofParameter<float> _horizontalOffset;
};
}; // namespace layout
}; // namespace ofxWidgets