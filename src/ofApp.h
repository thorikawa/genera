#pragma once

#include "ofMain.h"

#define NUM_NODES 100
#define NUM_LINES 6

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
    void initDirections();
    void initLine(int l, bool doCalcSatellitesPosition = false);
    void init(bool doCalcSatellitesPosition = false);
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofVec3f startPoints[NUM_LINES];
    ofVec3f forwards[NUM_LINES];
    ofPolyline line[NUM_LINES];
    ofQuaternion quaternions[NUM_LINES * NUM_NODES];
    ofNode nodes[NUM_LINES * NUM_NODES];
    ofNode children[NUM_LINES * NUM_NODES];
    ofPolyline lines[NUM_LINES * NUM_NODES];
    ofSpherePrimitive spheres[NUM_LINES * NUM_NODES];

    float startTime;
        ofEasyCam cam;
};
