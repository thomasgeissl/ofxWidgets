#pragma once

#include "ofMain.h"
#include "./slider.h"

namespace ofxWidgets
{

template <class T>
class labeledSlider : public ofxWidgets::widget
{
  public:
    enum position
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };
    typedef std::shared_ptr<labeledSlider> pointer;
    static pointer create(typename ofxWidgets::slider<T>::pointer s, position p, int width, int height)
    {
        return std::make_shared<labeledSlider>(s, p, width, height);
    }

    labeledSlider(typename ofxWidgets::slider<T>::pointer s, position p, int width, int height) : widget(width, height), _slider(s)
    {
        auto labelWidth = _contentWidth;
        auto labelHeight = _contentHeight;
        if (p == position::TOP)
        {
            labelHeight = _contentHeight - s->getViewHeight();
            _label = ofxWidgets::label::create("", labelWidth, labelHeight);
            _slider->_position.y = _label->getViewHeight();
        }
        else if (p == position::LEFT)
        {
					auto offset = 10;
            labelWidth = _contentWidth - s->getViewWidth();
            _label = ofxWidgets::label::create("", labelWidth - offset, labelHeight);
						_label->setAlignment(ofxWidgets::widget::alignment::right);
            _slider->_position.x = _label->getViewWidth() + offset;
        }
        else if (p == position::BOTTOM)
        {
            labelHeight = _contentHeight - s->getViewHeight();
            _label = ofxWidgets::label::create("", labelWidth, labelHeight);
            _label->_position.y = _slider->getViewHeight();
        }
        else if (p == position::RIGHT)
        {
					auto offset = 10;
            labelWidth = _contentWidth - s->getViewWidth();
            _label = ofxWidgets::label::create("", labelWidth - offset, labelHeight);
            _label->_position.x = _slider->getViewWidth() + offset;
        }
        add(_slider);
        add(_label);
        init();
    }

    void init()
    {
        _type = TYPE_OFXWIDGETS_SLIDER;
        _slider->getValue().addListener(this, &labeledSlider::onValueChange);
				auto text = _slider->getValue().getName();
				text += ": ";
				text += ofToString(_slider->getValue());
        _label->setValue(text);
    }

    void onValueChange(T &value)
    {
        auto text = _slider->getValue().getName();
				text += ": ";
				text += ofToString(_slider->getValue());
        _label->setValue(text);
    }

    typename ofxWidgets::slider<T>::pointer getSlider()
    {
        return _slider;
    }
    typename ofxWidgets::label::pointer getLabel()
    {
        return _label;
    }

  protected:
    typename ofxWidgets::slider<T>::pointer _slider;
    ofxWidgets::label::pointer _label;
};
typedef labeledSlider<int> labeledIntSlider;
typedef labeledSlider<float> labeledFloatSlider;
typedef labeledSlider<double> labeledDoubleSlider;
}; // namespace ofxWidgets