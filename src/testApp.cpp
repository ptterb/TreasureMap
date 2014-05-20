#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(7);
    
    pr.allocate(1024, 768, OF_IMAGE_COLOR);
    pr.loadImage("PR_just_island.png");
    
    eight.loadFont("Pieces of Eight.ttf", 96);
    
    drawFBO.allocate(ofGetWidth(), ofGetHeight());
    
    setupTiles();
    
    arduino.setup();
    
    loadSounds();
    
    output.setName("JollyRoger"); // Syphon for projection mapping
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Update alpha values for the last symbol drawn
    for(int i = 0; i < step; i++){
        selectedTiles[i].setAlpha(255);
    }
    
    selectedTiles[step].fadeIn();
    
    // update arduino values
    arduino.update();
    
    // Check for matches
    checkMatch();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    if (drawPr){
        ofSetColor(255, 255, 255, 150);
        pr.draw(0, 0, 1440, 562);
    }
    
    ofSetColor(255, 255, 255, 100);
    
    // Draw with offset
    selectedTiles[0].drawSymbol(20 + adjust[0].x, 20 + adjust[0].y);
    selectedTiles[1].drawSymbol(200 + adjust[1].x, 350 + adjust[1].y);
    selectedTiles[2].drawSymbol(500 + adjust[2].x, 100 + adjust[2].y);
    selectedTiles[3].drawSymbol(800 + adjust[3].x, 300 + adjust[3].y);
    selectedTiles[4].drawSymbol(1200 + adjust[4].x, 150 + adjust[4].y);
    
    drawCongrats();
    
    output.publishScreen();

    
}
//--------------------------------------------------------------
void testApp::pickSymbols(){
    
    selectedTiles.clear();
    vector<Tile>workingTiles = tiles;
    for (int i = 0; i < 5; i++) {
        int rand = ofRandom(0, workingTiles.size());
        selectedTiles.push_back(workingTiles.at(rand));
        workingTiles.erase(workingTiles.begin()+rand);
    }
    
    pickString = ofRandom(0, 3);
    
}

//--------------------------------------------------------------
void testApp::checkMatch(){
    
    int currentValue = arduino.getValue(step);
    
    // Check if value is in the right range for the current tile.
    if (step == 0){     // HACK!
        if (ofInRange(currentValue, selectedTiles[step].getResistanceSlot1().x , selectedTiles[step].getResistanceSlot1().y)) {
            nextStep();
        }
    } else if (step == 3){     // HACK!
        if (ofInRange(currentValue, selectedTiles[step].getResistanceSlot4().x , selectedTiles[step].getResistanceSlot4().y)) {
            nextStep();
        }
    } else {
        if (ofInRange(currentValue, selectedTiles[step].getResistance().x , selectedTiles[step].getResistance().y)) {
            nextStep();
        }
    }
    
    
}

void testApp::nextStep(){
    
    if (step < 4) {
        step++;
        
    } else {
        ofLogNotice() << "CONGRATS!";
        yay.play();
        showCongrats = true;
        step = 0;
        pickSymbols();
    }
}

void testApp::setupTiles(){
    
    string images [5] = {"skull","anchor","wheel","bell","spyglass"};
    
    // Add resistance ranges
    ofVec2f res [5] =
    {ofVec2f(920, 940), // skull
        ofVec2f(170, 190),  // anchor
        ofVec2f(5, 15),  // wheel
        ofVec2f(40, 50),  // bell
        ofVec2f(30, 39),  // spyglass
        };
    
    ofVec2f resSlot1 [5] =
    {ofVec2f(1010, 1020), // skull
        ofVec2f(700, 710),  // anchor
        ofVec2f(90, 100),  // wheel
        ofVec2f(320, 335),  // bell
        ofVec2f(250, 260),  // spyglass
    };
    
    ofVec2f resSlot4 [5] =
    {ofVec2f(920, 940), // skull
        ofVec2f(170, 190),  // anchor
        ofVec2f(5, 25),  // wheel
        ofVec2f(43, 55),  // bell
        ofVec2f(30, 40),  // spyglass
    };
    
    for (int i = 0; i < 5; i++) {
        Tile tile;
        tile.setup();
        tile.loadImage(images[i]);
        tile.setResistance(res[i].x, res[i].y);
        tile.setResistanceSlot1(resSlot1[i].x, resSlot1[i].y);
        tile.setResistanceSlot4(resSlot4[i].x, resSlot4[i].y);
        tiles.push_back(tile);
    }
    
    pickSymbols();
    
    adjust.push_back(ofVec2f(-30, 0));
    adjust.push_back(ofVec2f(35, -60));
    adjust.push_back(ofVec2f(65, -180));
    adjust.push_back(ofVec2f(20, -10));
    adjust.push_back(ofVec2f(40, -155));
    
    // Reset tile positions
    //    for (int i = 0; i < 5; i++) {
    //        adjust.push_back(ofVec2f(0, 0));
    //    }
}

void testApp::loadSounds(){
    
    background.loadSound("sounds/background.wav");
    background.setLoop(true);
    background.setVolume(0.5f);
    background.play();
    
    yay.loadSound("sounds/yay.wav");
        
}

void testApp::drawCongrats(){
    
    float stringX = (ofGetWidth()/2) - (eight.stringWidth(doneMessages[pickString])/2);
    
    
    if (showCongrats){
        float stringAlpha = 1.0f - ((float)congratsTimer/totalCongratsTime);
    
        ofSetColor(163, 31, 8, stringAlpha*255);
        eight.drawString(doneMessages[pickString], stringX, ofGetHeight()-100);
        
        congratsTimer++;
    
        if (congratsTimer >= totalCongratsTime){
            showCongrats = false;
            congratsTimer = 0;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case 112:
            pickSymbols();
            break;
            
        case 113:
            currentShapeDebug = 0;
            ofLogNotice() << "current shape: " << currentShapeDebug;
            break;
        case 119:
            currentShapeDebug = 1;
            ofLogNotice() << "current shape: " << currentShapeDebug;
            break;
        case 101:
            currentShapeDebug = 2;
            ofLogNotice() << "current shape: " << currentShapeDebug;
            break;
        case 114:
            currentShapeDebug = 3;
            ofLogNotice() << "current shape: " << currentShapeDebug;
            break;
        case 116:
            currentShapeDebug = 4;
            ofLogNotice() << "current shape: " << currentShapeDebug;
            break;
            
        case 358: // right
            adjust[currentShapeDebug].x += 5;
            break;
        case 359: // down
            adjust[currentShapeDebug].y += 5;
            break;
        case 356: // left
            adjust[currentShapeDebug].x -= 5;
            break;
        case 357: // up
            adjust[currentShapeDebug].y -= 5;
            break;
            
        case 32: // Space - print out adjustments
            for (int i = 0; i < adjust.size(); i++) {
                ofLogNotice() << "Offsets " << i << ": x-" << adjust[i].x << " y-" << adjust[i].y;
            }
        default:
            break;
    }
    
    ofLogNotice() << key;

}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if (button == 0){
        nextStep();
    } else {
        drawPr = !drawPr;
    }

}

