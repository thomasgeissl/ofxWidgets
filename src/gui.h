#pragma once

#include "ofMain.h"
#include "./widgets/widget.h"

namespace ofxWidgets
{
class gui : public widget
{
  public:
    typedef std::shared_ptr<gui> pointer;
    static pointer create()
    {
        return std::make_shared<gui>();
    }
    gui(bool registerEventListeners = true, bool registerDrawEventListener = true){
        if(registerEventListeners){
            ofAddListener(ofEvents().setup, this, &gui::onSetup, OF_EVENT_ORDER_BEFORE_APP);
            ofAddListener(ofEvents().update, this, &gui::onUpdate);
            ofAddListener(ofEvents().keyPressed, this, &gui::onKeyPressed);
            ofAddListener(ofEvents().keyReleased, this, &gui::onKeyReleased);
            ofAddListener(ofEvents().mouseMoved, this, &gui::onMouseMoved);
            ofAddListener(ofEvents().mouseDragged, this, &gui::onMouseDragged);
            ofAddListener(ofEvents().mousePressed, this, &gui::onMousePressed);
            ofAddListener(ofEvents().mouseReleased, this, &gui::onMouseReleased);
            ofAddListener(ofEvents().mouseEntered, this, &gui::onMouseEntered);
            ofAddListener(ofEvents().mouseExited, this, &gui::onMouseExited);
            ofAddListener(ofEvents().windowResized, this, &gui::onWindowResized);
        }
        if(registerDrawEventListener){
            ofAddListener(ofEvents().draw, this, &gui::onDraw, OF_EVENT_ORDER_BEFORE_APP);
        }
    }

    ~gui(){
        ofRemoveListener(ofEvents().setup, this, &gui::onSetup);
        ofRemoveListener(ofEvents().update, this, &gui::onUpdate);
        ofRemoveListener(ofEvents().draw, this, &gui::onDraw);
        ofRemoveListener(ofEvents().keyPressed, this, &gui::onKeyPressed);
        ofRemoveListener(ofEvents().keyReleased, this, &gui::onKeyReleased);
        ofRemoveListener(ofEvents().mouseMoved, this, &gui::onMouseMoved);
        ofRemoveListener(ofEvents().mouseDragged, this, &gui::onMouseDragged);
        ofRemoveListener(ofEvents().mousePressed, this, &gui::onMousePressed);
        ofRemoveListener(ofEvents().mouseReleased, this, &gui::onMouseReleased);
        ofRemoveListener(ofEvents().mouseEntered, this, &gui::onMouseEntered);
        ofRemoveListener(ofEvents().mouseExited, this, &gui::onMouseExited);
        ofRemoveListener(ofEvents().windowResized, this, &gui::onWindowResized);
    }

    void setup(){
        widget::setup(ofGetWidth(), ofGetHeight());
    }

	void onSetup(ofEventArgs &e){
		setup();
	}
	void onUpdate(ofEventArgs &e){
		update();
	}
	void onDraw(ofEventArgs &e){
		draw();
        drawOverlay(_position);
	}
    void onKeyPressed(ofKeyEventArgs & event) {
        keyPressed(event.key);
    }
    void onKeyReleased(ofKeyEventArgs & event) {
        keyReleased(event.key);
    }
    void onMouseMoved(ofMouseEventArgs & event){
        mouseMoved(event.x, event.y);
    }
    void onMouseDragged(ofMouseEventArgs & event){
        mouseDragged(event.x, event.y, event.button);
    }
    void onMousePressed(ofMouseEventArgs & event){
        mousePressed(event.x, event.y, event.button);
    }
    void onMouseReleased(ofMouseEventArgs & event){
        mouseReleased(event.x, event.y, event.button);
    }
    void onMouseEntered(ofMouseEventArgs & event){
        mouseEntered(event.x, event.y);
    }
    void onMouseExited(ofMouseEventArgs & event){
        mouseExited(event.x, event.y);
    }
    void onWindowResized(ofResizeEventArgs & event){
        resized(event.width, event.height);
    }
};
}; // namespace ofxWidgets