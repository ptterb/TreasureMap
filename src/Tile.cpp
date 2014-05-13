//
//  Tile.cpp
//  TreasureMap
//
//  Created by Brett Peterson on 4/17/14.
//
//

#include "Tile.h"


Tile::Tile(){}

void Tile::setup(){
    
    
    tileImage.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    
    white.set(229, 201, 97);
    darkYellow.set(203, 195, 84);
    lightYellow.set(189, 158, 47);
    
    twinkleColors.push_back(white);
    twinkleColors.push_back(lightYellow);
    twinkleColors.push_back(darkYellow);
    
    chimes3.loadSound("sounds/chimes-short3.mp3");
}

void Tile::loadImage(string name){
    tileImage.loadImage(path + name + ".png");
}

void Tile::drawSymbol(int x, int y){
    
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    int randSeed = (int) ofRandom(0, 5);
    
    for (int x = randSeed; x < objectSize; x+=5){
        for (int y = randSeed; y < objectSize; y+=5) {
            if (tileImage.getColor(x, y).a == 255) {
                int twinkleSize = ofRandom(0, 5);
                ofSetColor(twinkleColors.at(ofRandom(0, twinkleColors.size())), alpha);
                ofEllipse(x, y, twinkleSize, twinkleSize);
                ofSetColor(255,255,255);
            }
        }
    }
    ofPopMatrix();
}

void Tile::fadeIn(){
    
    if (alpha == 0) {
        chimes3.play();
    }
    
    if (alpha < 255){
        alpha+= 50;
    }
    
    
}

void Tile:: setAlpha(int value){
    alpha = value;
}

void Tile::setResistance(int _min, int _max){
    minRes = _min;
    maxRes = _max;
}

void Tile::setResistanceSlot1(int _min, int _max){
    minResSlot1 = _min;
    maxResSlot1 = _max;
}

void Tile::setResistanceSlot4(int _min, int _max){
    minResSlot4 = _min;
    maxResSlot4 = _max;
}

ofVec2f Tile::getResistance(){
    return ofVec2f(minRes, maxRes);
}

// HACK!! Resistance values for slot 1 were consistent, but different than slot 2 and 3
ofVec2f Tile::getResistanceSlot1(){
    return ofVec2f(minResSlot1, maxResSlot1);
}

ofVec2f Tile::getResistanceSlot4(){
    return ofVec2f(minResSlot4, maxResSlot4);
}



