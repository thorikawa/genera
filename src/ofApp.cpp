#include "ofApp.h"

#define NUM_NODES 3000
#define DISTANCE 1.0

//--------------------------------------------------------------
void ofApp::setup(){
    startTime = ofGetElapsedTimef();

    float x = 0.0, y = 0.0, z = 0.0;
    ofVec3f forward(1.0, 0, 0);
    for (int i = 0; i<NUM_NODES; i++) {
        float theta = ofRandom(PI);
        float phi = ofRandom(TWO_PI);

        float px = sin(theta) * cos(phi);
        float py = sin(theta) * sin(phi);
        float pz = cos(theta);
        x += px;
        y += py;
        z += pz;

        ofVec3f dir(px, py, pz);
        ofQuaternion q;
        q.makeRotate(forward, dir);
        ofVec3f check = q * forward;
        
        ofLogNotice() << dir << " " << check;
        
        quaternions.push_back(q);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float dt = ofGetElapsedTimef() - startTime;

    ofVec3f forward = DISTANCE * ofVec3f(1.0, 0, 0);
    ofQuaternion identity(0, ofVec3f(1, 0, 0));

    cam.begin();
    ofQuaternion prevQuaternion(0, ofVec3f(0, 0, 1));
    float x = -400.0, y = 0.0, z = 0.0;
    ofNode prevNode;

    prevNode.setPosition(x, y, z);
//    prevNode.draw();

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
        
        auto n = ofNode();
        n.setPosition(x, y, z);

//        n.draw();

//        ofLogNotice() << v;
        
        if (i < 3) {
//            ofLogNotice() << i << " " << dt << " " << q << x << " " << y << " " << z;
        }

        ofDrawLine(n.getX(), n.getY(), n.getZ(), prevNode.getX(), prevNode.getY(), prevNode.getZ());

        prevNode = n;
        prevQuaternion = q;
        forward = v;
    }
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
