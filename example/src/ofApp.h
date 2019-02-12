#pragma once

#include "ofMain.h"
#include "ofxWidgets.h"
#include "circle.h"

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

  circle::pointer _upperCircle;
  circle::pointer _lowerCircle;
  ofxWidgets::gui _gui;
  ofParameter<float> _value;
  ofParameter<void> _trigger;

  ofParameter<int> _intValue;
  ofParameter<float> _floatValue;

  void onTrigger();
};
