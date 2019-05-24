#include "ofApp.h"

#define MAX_RADIUS (50) // when to stop the animation
#define INITIAL_TREE_SIZE (10)
#define LINE_LENGTH (20)

int Line::line_length;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    ofDisableAntiAliasing();
    Line::line_length = LINE_LENGTH;
    angle = 45.0f;
    tree_size = INITIAL_TREE_SIZE;
    max_size = 10000; // Size of ends array
    
    bAnimate = true; // Toggle animation with frame saving
    
    saveFrame = false; // Used to save animation frames
    
    // Initialize "ends" array to keep track of where lines end
    ends = new int*[max_size];
    for (int i = 0; i < max_size; i++) {
        ends[i] = new int[max_size];
        for (int j = 0; j < max_size; j++) {
            ends[i][j] = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if (saveFrame) {
        ofSaveScreen(ofToString(tree_size)+".png");
        tree_size++;
        if (tree_size > MAX_RADIUS) std::exit(1);
        saveFrame = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Clear ends array (we redraw the entire frame each time)
    // TODO: don't redraw the entire frame each time!
    for (int i = 0; i < max_size; i++) {
        for (int j = 0; j < max_size; j++) {
            ends[i][j] = 0;
        }
    }
    
    ofVec2f screen_center;
    screen_center.set(ofGetWidth()/2, ofGetHeight()/2);
    
    ofVec2f up; // Vector pointing up
    up.set(0.0f, -1.0f);
    
    list<Line> q;
    list<Line> next_q;
    
    // Enqueue the initial "plus sign"
    for (float offset = 0.0f; offset < 360.f; offset += angle * 2) {
        Line seed;
        seed.direction.x = roundf(up.getRotated(offset).x);
        seed.direction.y = roundf(up.getRotated(offset).y);
        q.push_back(seed);
    }
    
    for (int curr_level = 0; curr_level < tree_size; curr_level++) {
        vector<Line> newlyDrawn; // keep track of lines drawn in this loop
        while (!q.empty()) {
            Line currBranch = q.front();
            q.pop_front();
        
            // Check if two branches end at the same point
            if (ends[int(currBranch.start.x) + max_size / 2][int(currBranch.start.y) + max_size / 2] > 1)
                continue;
                
            currBranch.draw(screen_center);
            newlyDrawn.push_back(currBranch);
            
            queueBranches(next_q, currBranch);
        }
        for (Line l : newlyDrawn) {
            ends[int(l.end.x) + max_size / 2][int(l.end.y) + max_size / 2]++;
        }
        q = next_q;
        list<Line>().swap(next_q); // clear next_q
    }
    
    // Signal to save the frame we just drew
    if (bAnimate) saveFrame = true;
}

/*
 * Create and queue the two split branches
 * that start and the end of currBranch
 */
void ofApp::queueBranches(list<Line> &q, Line &currBranch) {
    Line left;
    Line right;
    
    left.start = currBranch.end;
    right.start = currBranch.end;

    left.direction = currBranch.direction.getRotated(-angle); // rotate left
    right.direction = currBranch.direction.getRotated(angle); // rotate right
    
    left.direction.x = roundf(left.direction.x);
    left.direction.y = roundf(left.direction.y);

    right.direction.x = roundf(right.direction.x);
    right.direction.y = roundf(right.direction.y);
    
    q.push_back(left);
    q.push_back(right);
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
    // Simple mechanism to manually control the tree size
    if (x > ofGetWidth()/2) {
        // Right half of screen
        tree_size++;
    } else {
        // Left half of screen
        tree_size--;
    }
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
