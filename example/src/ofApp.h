#pragma once

#include "ofMain.h"
#include "ofxWidgets.h"
#include "shape.h"

class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  shape::pointer _upperShape;
  shape::pointer _lowerShape;
  ofxWidgets::gui _gui;
  ofParameter<float> _value;
  ofParameter<void> _trigger;

  ofParameter<int> _intValue;
  ofParameter<float> _floatValue;
  ofParameter<int> _intDropDownValue;
  ofParameter<int> _testListIndex;

  void onTrigger();
};
