#pragma once

#include "ofMain.h"

/*
 * Line object
 * -----------
 * Struct object representing one drawn line
 * of the tree
 */
struct Line {
    int level = 0;
    static int line_length;
    ofVec2f start;
    ofVec2f direction;
    ofVec2f end;
    
    void draw(ofVec2f center, int color = 0x000000) {
        end = start + direction;
        ofSetHexColor(color);
        
        ofDrawLine(start * line_length + center, end * line_length + center);
    }
    
    bool operator == (const Line &comp) {
        return (this->start == comp.start && this->end == comp.end);
    }
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
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
 
        void queueBranches(list<Line> &q, Line &now);
    
        int tree_size;
        int max_size;
        float angle;
        int **ends;
        bool saveFrame;
        bool bAnimate;
};
