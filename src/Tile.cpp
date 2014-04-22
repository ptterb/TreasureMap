//
//  Tile.cpp
//  TreasureMap
//
//  Created by Brett Peterson on 4/17/14.
//
//

#include "Tile.h"


Tile::Tile(){
    
    tileImage.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    
    white.set(229, 201, 97);
    darkYellow.set(203, 195, 84);
    lightYellow.set(189, 158, 47);
    
    twinkleColors.push_back(white);
    twinkleColors.push_back(lightYellow);
    twinkleColors.push_back(darkYellow);
    
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
    
    if (alpha < 255){
        alpha+= 50;
    }
    
}

void Tile:: setAlpha(int value){
    alpha = value;
}



