#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void drawSymbol(int x, int y, ofImage positionedImage);
    void pickSymbols();
    
    
        // Tiles
        ofImage skull;
        ofImage anchor;
        ofImage wheel;
        ofImage cannon;
        ofImage bell;
        ofImage spyglass;
        ofImage bone;
        ofImage compass;
        ofImage key;
        ofImage hourglass;
        
        string path = "tiles/";
    
    ofFbo drawFBO;
    
    ofImage tempImage;
    
    int objectSize = 248;
    
    vector<ofColor> twinkleColors;
    ofColor white;
    ofColor lightYellow;
    ofColor darkYellow;
    
    vector<ofImage> tiles;
    
    ofImage chosenImage;
    
    vector<ofImage> selectedTiles;
    
    int step = 0;
    
    
    
        
};
