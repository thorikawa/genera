#include "ofApp.h"

#define NUM_NODES 100
#define DISTANCE 10.0
#define FPS 60

ofNode nodes[NUM_NODES];
ofNode children[NUM_NODES];
ofPolyline lines[NUM_NODES];
ofSpherePrimitive spheres[NUM_NODES];

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(FPS);

    startTime = ofGetElapsedTimef();

    float x = 0.0, y = 0.0, z = 0.0;
    ofVec3f forward(1.0, 0, 0);
    for (int i = 0; i < NUM_NODES; i++) {
        float theta = ofRandom(PI);
        float phi = ofRandom(TWO_PI);

        float px = sin(theta) * cos(phi);
        float py = sin(theta) * sin(phi);
        float pz = cos(theta);
        x += px;
        y += py;
        z += pz;

        nodes[i].setPosition(x, y, z);
        children[i].setPosition(40, 0, 0);
        children[i].setParent(nodes[i]);
        
        ofVec3f dir(px, py, pz);
        ofQuaternion q;
        q.makeRotate(forward, dir);
        
        quaternions.push_back(q);
    }
}

ofImage myImage;

//--------------------------------------------------------------
void ofApp::update(){

    uint64_t num = ofGetFrameNum();
    float dt = (float)num / FPS;
    
    line.clear();

    ofVec3f forward = DISTANCE * ofVec3f(1, 1, 1).normalize();
//    forward.normalize();
    ofQuaternion identity(0, ofVec3f(1, 0, 0));
    
    ofQuaternion prevQuaternion(0, ofVec3f(0, 0, 1));
    float x = -200.0, y = -200.0, z = 0.0;
    
    ofQuaternion q(0, ofVec3f(1, 0, 0));
    for (int i = 0; i<NUM_NODES; i++) {
        float t = cos(dt * 0.5) / 2.0 + 0.5;
        ofQuaternion q;
        q.slerp(t, identity, quaternions[i]);
        
        
        ofVec3f v = q * forward;
        float px = v[0];
        float py = v[1];
        float pz = v[2];
        x += px;
        y += py;
        z += pz;
        
        nodes[i].setPosition(x, y, z);
        nodes[i].pan(3.0 + i / 30.0);
        line.addVertex(nodes[i].getGlobalPosition());
        if (line.size() > 1050){
            line.getVertices().erase(line.getVertices().begin());
        }
        lines[i].addVertex(children[i].getGlobalPosition());
        if (lines[i].size() > 1050){
            lines[i].getVertices().erase(lines[i].getVertices().begin());
        }

        spheres[i].setRadius(4.0);
        spheres[i].setResolution(8);

        forward = v;
    }
    
//    myImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
//    char filename[256];
//    sprintf(filename, "i%05llu.jpg", num);
//    myImage.saveImage(filename, OF_IMAGE_QUALITY_HIGH);

}

//--------------------------------------------------------------
void ofApp::draw(){
    uint64_t num = ofGetFrameNum();
    float dt = (float)num / FPS;

    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofEnableDepthTest();
    cam.begin();
    ofSetLineWidth(1.0);
    for (int i = 0; i<NUM_NODES; i++) {
        float t = cos(dt * 0.6 + i * TWO_PI / NUM_NODES) / 2.0 + 0.5;
        int color3 = (int)(t * 255);

        ofSetColor(color3, color3, color3, 180);
        ofVec3f v = children[i].getGlobalPosition();
        spheres[i].setPosition(v);
        spheres[i].draw();
        lines[i].draw();
    }

    ofSetColor(ofColor::white);
    ofSetLineWidth(3.0);
    line.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
