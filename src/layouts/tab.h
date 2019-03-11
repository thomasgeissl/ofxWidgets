#pragma once

#include "ofMain.h"
#include "../widgets/widget.h"

namespace ofxWidgets
{
namespace layout
{
class tab : public ofxWidgets::layout::base
{
public:
  enum style
  {
    barTop,
    barBottom
  };
  typedef std::shared_ptr<tab> pointer;
  class tabBar : public ofxWidgets::widget
  {
  public:
    typedef std::shared_ptr<tabBar> pointer;
    static pointer create(ofParameter<int> index, int width, int height)
    {
      return std::make_shared<tabBar>(index, width, height);
    }
    tabBar(ofParameter<int> index, int width, int height) : widget(width, height), _index(index)
    {
      _index.set("index", -1, -1, -1);
    }
    virtual void update()
    {
      begin();
      ofSetColor(ofColor::green);
      ofDrawRectangle(0, 0, _contentWidth, _contentHeight);
      end();
    }
    void add(std::string name)
    {
    }
    ofParameter<int> &getIndex()
    {
      return _index;
    }

  protected:
    ofParameter<int> _index;
  };
  static pointer create(int width, int height)
  {
    return std::make_shared<tab>(width, height);
  }
  static pointer createAndAddTo(ofxWidgets::widget::pointer w)
  {
    auto layout = create(w->getViewWidth(), w->getViewHeight());
    w->add(layout);
    return layout;
  }
  tab(int width, int height) : base(width, height), _style(style::barTop)
  {
    _tabBar = tabBar::create(_index, width, 20);
    _index.addListener(this, &tab::onIndexChange);
  }
  virtual void update()
  {
    _tabBar->update();
    if (_index >= 0 && _children.size() > 0)
    {
      ofLogNotice() << "updating " << _index;
      _children[_index]->update();
    }
    begin();
    _tabBar->draw();
    if (_index >= 0 && _children.size() > 0)
    {
      _children[_index]->draw();
    }
    end();
  }
  virtual void add(std::string name, ofxWidgets::widget::pointer w)
  {
    _index.set("index", 0, 0, _index.getMax() + 1);
    _tabBar->add(name);
    if (_style == style::barTop)
    {
      w->setPosition(0, _tabBar->getViewHeight());
    }
    else
    {
      w->setPosition(0, _viewHeight - _tabBar->getViewHeight());
    }

    widget::add(w);
  }
  void setIndex(int index)
  {
    _index = index;
  }

  void onIndexChange(int &value)
  {
    for(auto & child : _children){
      child->setPosition(-_viewWidth, -_viewHeight);
    }
    if(_index >= 0 && _index < _children.size()){
      _children[_index]->setPosition(0, 20);
    }
  }

protected:
  ofParameter<int> _index;
  tabBar::pointer _tabBar;
  style _style;
};
}; // namespace layout
}; // namespace ofxWidgets