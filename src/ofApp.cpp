#include "ofApp.h"

#define DISTANCE 3.0
#define FPS 60
#define RADIUS 100
#define TRAJECTORY_POINTS 15

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(FPS);

    startTime = ofGetElapsedTimef();
    init(true);
}

void ofApp::initDirections() {
    printf("init directions\n");
    for (int l = 0; l < NUM_LINES; l++) {
        forwards[l] = ofVec3f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)).normalize();
    }
}
void ofApp::initLine(int l, bool doCalcSatellitesPosition) {
    if (doCalcSatellitesPosition) {
        startPoints[l] = ofVec3f(ofRandom(-300.0, 300.0), ofRandom(-100.0, 100.0), ofRandom(-100.0, 100.0));
    }
    
    for (int n = 0; n < NUM_NODES; n++) {
        int i = NUM_NODES * l + n;
        
        float theta = ofRandom(PI);
        float phi = ofRandom(TWO_PI);
        
        float px = sin(theta) * cos(phi);
        float py = sin(theta) * sin(phi);
        float pz = cos(theta);
        //        px = ABS(px);
        //            py = ABS(py);
        //        pz = ABS(pz);

        if (doCalcSatellitesPosition) {
            children[i].setPosition(ofRandom(RADIUS), 0, 0);
        }
        children[i].setParent(nodes[i]);
        ofVec3f dir(px, py, pz);
        quaternions[i].makeRotate(forwards[l], dir);
    }
}

void ofApp::init(bool doCalcSatellitesPosition) {
    printf("init\n");

    if (doCalcSatellitesPosition) {
        initDirections();
    }

    for (int l = 0; l < NUM_LINES; l++) {
        initLine(l, doCalcSatellitesPosition);
    }
}

ofImage myImage;

//--------------------------------------------------------------
void ofApp::update(){

    uint64_t num = ofGetFrameNum();
    float dt = (float)num / FPS;

    ofQuaternion identity(0, ofVec3f(1, 0, 0));

    for (int l = 0; l < NUM_LINES; l++) {
        float t = cos(dt * 0.5 + l) / 2.0 + 0.5;
        if (t < 0.00001) {
            initLine(l);
        }

        ofVec3f forward = DISTANCE * forwards[l];
        ofVec3f start = startPoints[l];
        float x = start[0];
        float y = start[1];
        float z = start[2];

        line[l].clear();
        for (int n = 0; n < NUM_NODES; n++) {
            int i = NUM_NODES * l + n;

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
            nodes[i].pan(1.0 + i / 30.0);
//            nodes[i].tilt(ofRandom(3.0));

            line[l].addVertex(nodes[i].getGlobalPosition());

            lines[i].addVertex(children[i].getGlobalPosition());
            if (lines[i].size() > TRAJECTORY_POINTS){
                lines[i].getVertices().erase(lines[i].getVertices().begin());
            }

            spheres[i].setRadius(4.0);
            spheres[i].setResolution(8);

            forward = v;
        }
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
    for (int l = 0; l < NUM_LINES; l++) {
        for (int n = 0; n < NUM_NODES; n++) {
            int i = NUM_NODES * l + n;

            float t = cos(dt * 0.6 + i * TWO_PI / NUM_NODES) / 2.0 + 0.5;
            int color3 = (int)(t * 255);

            ofSetColor(color3, color3, color3, 100);
            ofVec3f v = children[i].getGlobalPosition();
            spheres[i].setPosition(v);
            spheres[i].draw();

            ofSetLineWidth(1.0);
            lines[i].draw();
        }
        
        ofSetColor(ofColor::white);
        ofSetLineWidth(3.0);
        line[l].draw();
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
