//
//  TreasureArduino.cpp
//  TreasureMap
//
//  Created by Brett Peterson on 4/26/14.
//
//

#include "TreasureArduino.h"


void TreasureArduino::setup(){
    
    arduino.connect("/dev/tty.usbmodem1411", 57600);
    
    for (int i = 0; i < 5; i++) {
        values.push_back(0);
    }
}

void TreasureArduino::update(){
    
    // Set up the Arduino
    if (arduino.isInitialized() && bSetup == false) {
        setupArduino();
    }
    
    updateArduino();
}

void TreasureArduino::setupArduino(){
    
    // Set A0 to analog read TODO: change to read all inputs
    arduino.sendAnalogPinReporting(0, ARD_ANALOG);
    
    ofLogNotice() << "Arduino set up";
    bSetup = true;
}

void TreasureArduino::updateArduino(){
    
    arduino.update();
    
    // Grab values and compare to last checked val. Only update if it's significantly different
    for (int i = 0; i< values.size(); i++) {
        
        int readNow = arduino.getAnalog(i);
        
        if (!ofInRange(readNow, values[i] - fudge, values[i] + fudge)){
            values[i]= readNow;
            ofLogNotice() << "PIN " << i << ": " << values[i];
        }
    }
    
}

int TreasureArduino::getValue(int tilePlace){
    return values[tilePlace];
}
