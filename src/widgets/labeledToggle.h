#pragma once

#include "ofMain.h"
#include "./widget.h"
#include "./toggle.h"
#include "./label.h"

namespace ofxWidgets
{

class labeledToggle : public ofxWidgets::widget
{
  public:
    enum position
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };
    typedef std::shared_ptr<labeledToggle> pointer;
    static pointer create(ofxWidgets::toggle::pointer toggle, position p, int width, int height)
    {
        return std::make_shared<labeledToggle>(toggle, p, width, height);
    }

    labeledToggle(ofxWidgets::toggle::pointer toggle, position p, int width, int height) : widget(width, height), _toggle(toggle)
    {
        auto labelWidth = _contentWidth;
        auto labelHeight = _contentHeight;
        if (p == position::TOP)
        {
            labelHeight = _contentHeight - toggle->getViewHeight();
            _label = ofxWidgets::label::create("", labelWidth, labelHeight);
            _toggle->_position.y = _label->getViewHeight();
        }
        else if (p == position::LEFT)
        {
					auto offset = 10;
            labelWidth = _contentWidth - toggle->getViewWidth();
            _label = ofxWidgets::label::create("", labelWidth - offset, labelHeight);
						_label->setAlignment(ofxWidgets::widget::alignment::right);
            _toggle->_position.x = _label->getViewWidth() + offset;
        }
        else if (p == position::BOTTOM)
        {
            labelHeight = _contentHeight - toggle->getViewHeight();
            _label = ofxWidgets::label::create("", labelWidth, labelHeight);
            _label->_position.y = _toggle->getViewHeight();
        }
        else if (p == position::RIGHT)
        {
					auto offset = 10;
            labelWidth = _contentWidth - toggle->getViewWidth();
            _label = ofxWidgets::label::create("", labelWidth - offset, labelHeight);
            _label->_position.x = _toggle->getViewWidth() + offset;
        }
        add(_toggle);
        add(_label);
        init();
    }

    void init()
    {
        _type = TYPE_OFXWIDGETS_TOGGLE;
        _checkedText.addListener(this, &labeledToggle::onCheckedTextChange);
        _checkedText.set("checkedText", "on");
        _unCheckedText.addListener(this, &labeledToggle::onUnCheckedTextChange);
        _unCheckedText.set("uncheckedText", "off");
        _toggle->getValue().addListener(this, &labeledToggle::onValueChange);
				bool value = _toggle->getValue();
				onValueChange(value);
    }

    void onValueChange(bool &value)
    {
						if (value)
            {
                _label->setValue(_toggle->getValue().getName() + ": " + _checkedText.get());
            }
            else
            {
                _label->setValue(_toggle->getValue().getName() + ": " + _unCheckedText.get());
            }
    }
    void onCheckedTextChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }
    void onUnCheckedTextChange(std::string &value)
    {
        setNeedsToBeRedrawn(true);
    }
    ofxWidgets::toggle::pointer getToggle()
    {
        return _toggle;
    }
    ofxWidgets::label::pointer getLabel()
    {
        return _label;
    }

    void setCheckedText(std::string value){
        _checkedText = value;
    }
    void setUnCheckedText(std::string value){
        _unCheckedText = value;
    }

  protected:
    ofxWidgets::toggle::pointer _toggle;
    ofxWidgets::label::pointer _label;
    ofParameter<std::string> _checkedText;
    ofParameter<std::string> _unCheckedText;
};
}; // namespace ofxWidgets