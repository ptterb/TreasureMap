//
//  Tile.h
//  TreasureMap
//
//  Created by Brett Peterson on 4/17/14.
//
//

#include "ofMain.h"

#ifndef __TreasureMap__Tile__
#define __TreasureMap__Tile__

#include <iostream>

#endif /* defined(__TreasureMap__Tile__) */

class Tile {
   
    string path = "tiles/";
    int objectSize = 248;
    int tileX;
    int tileY;
    
    int minRes;
    int maxRes;
    
public:
    Tile();
    void loadImage(string name);
    void drawSymbol();
    void drawSymbol(int x, int y);
    void fadeIn();
    void setAlpha(int value);
    void setResistance(int _min, int _max);
    ofVec2f getResistance();
    ofImage tileImage;
    
    vector<ofColor> twinkleColors;
    ofColor white;
    ofColor lightYellow;
    ofColor darkYellow;
    
    int alpha = 0;
    int frameRateFlicker = 7;
    
    ofSoundPlayer chimes3;
};

