#pragma once

#include "ofMain.h"
#include "./widget.h"

namespace ofxWidgets
{
class list : public ofxWidgets::widget
{
  public:
    class listItem : public ofxWidgets::widget
    {
      public:
        typedef std::shared_ptr<listItem> pointer;
        static pointer create(std::string value)
        {
            return std::make_shared<listItem>(value);
        }
        listItem(std::string value) : _value(value)
        {
            _selected.set("selected", false);
        }
        virtual void setup(int width, int height, bool hasOverlay = true)
        {
            widget::setup(width, height, hasOverlay);
            _label = ofxWidgets::label::create(_value);
            _label->setup(_width, _height);
            add(_label);
        }
        virtual void setAlignment(alignment a)
        {
            _label->setAlignment(a);
        }
        ofParameter<std::string> _value;
        ofParameter<bool> _selected;

        ofxWidgets::label::pointer _label;
    };
    static pointer create()
    {
        return std::make_shared<list>();
    }
    static pointer create(ofParameter<int> index, std::vector<std::string> values)
    {
        return std::make_shared<list>(index, values);
    }
    list(ofParameter<int> index, std::vector<std::string> values) : widget(), _currentIndex(index)
    {
        for (auto value : values)
        {
            auto listItem = listItem::create(value);
            listItem->_backgroundColor = ofColor::black;
            listItem->_color = ofColor::lightGrey;
            _listItems.push_back(listItem);
        }
    }
    list() : widget()
    {
    }
    virtual void setup(int width, int height, bool hasOverlay = true)
    {
        _children.clear();
        widget::setup(width, height, hasOverlay);
        auto layout = ofxWidgets::layout::vBox::create();
        layout->_verticalOffset = 2;
        layout->setup(width, height);
        for (auto listItem : _listItems)
        {
            listItem->setup(layout->_width, (layout->_height - _listItems.size() * 2) / _listItems.size());
            layout->add(listItem);
        }
        add(layout);
    }
    virtual void mousePressed(int x, int y, int button)
    {
        widget::mousePressed(x, y, button);
        auto counter = 0;
        auto isAnItemPressed = false;
        auto pressedItem = -1;
        for(auto & item : _listItems){
            if(item->_pressed){
                isAnItemPressed = true;
                pressedItem = counter;
            }
            counter++;
        }
        counter = 0;
        if(isAnItemPressed){
            _currentIndex = pressedItem;
            ofLogNotice() << "index changed " << _currentIndex;
            for(auto & item : _listItems){
                item->_selected = counter == pressedItem;
            }
            counter++;
        }
    }

    virtual void setAlignment(alignment a)
    {
        widget::setAlignment(a);
        for (auto &item : _listItems)
        {
            item->setAlignment(a);
        }
    }

    ofParameter<int> _currentIndex;
    std::vector<listItem::pointer> _listItems;
};
}; // namespace ofxWidgets