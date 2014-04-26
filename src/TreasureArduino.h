//
//  TreasureArduino.h
//  TreasureMap
//
//  Created by Brett Peterson on 4/26/14.
//
//

#ifndef __TreasureMap__TreasureArduino__
#define __TreasureMap__TreasureArduino__

#include <iostream>
#include "ofMain.h"

class TreasureArduino{
    
    ofArduino arduino;
    bool bSetup = false;
    
    vector<int> values;
    int fudge = 5;
    
    
public:
    
    void setup();
    void update();
    void setupArduino();
    void updateArduino();
    int getValue(int tilePlace);
    
    
};
#endif /* defined(__TreasureMap__TreasureArduino__) */
