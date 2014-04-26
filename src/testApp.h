#pragma once

#include "ofMain.h"
#include "Tile.h"
#include "TreasureArduino.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
    void pickSymbols();
    void loadPaths();
    void checkMatch();
    void nextStep();
    void setupTiles();
    void loadSounds();
    
        
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
    
    TreasureArduino arduino;
    
    // --- Sounds --- //
    
    ofSoundPlayer background;
    ofSoundPlayer yay;
    
    
    
        
};
