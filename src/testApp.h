#pragma once

#include "ofMain.h"
#include "Tile.h"

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
    void pickSymbols();
    void loadPaths();
    
        
    ofFbo drawFBO;
    
    ofImage tempImage;
    
    int objectSize = 248;
    
    vector<Tile> tiles;
    
    ofImage chosenImage;
    
    vector<Tile> selectedTiles;
    
    int step = 0;
    
    
    ofImage pr;
    bool drawPr = false;
    
    vector<ofImage> paths;
    
    int currentShapeDebug = 0;
    
    vector<ofVec2f> adjust;
    
    
        
};
