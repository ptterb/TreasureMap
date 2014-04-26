#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(7);
    
    pr.allocate(1024, 768, OF_IMAGE_COLOR);
    pr.loadImage("PR_just_island.png");
    
    drawFBO.allocate(ofGetWidth(), ofGetHeight());
    
    setupTiles();
    // NOT USING PATHS YET
    //loadPaths();
    
    arduino.setup();
    
    loadSounds();
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
        pr.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    selectedTiles[0].drawSymbol(20 + adjust[0].x, 20 + adjust[0].y);
//    paths[0].draw(20, 268);
    selectedTiles[1].drawSymbol(200 + adjust[1].x, 350 + adjust[1].y);
    selectedTiles[2].drawSymbol(500 + adjust[2].x, 100 + adjust[2].y);
    selectedTiles[3].drawSymbol(800 + adjust[3].x, 300 + adjust[3].y);
    selectedTiles[4].drawSymbol(1200 + adjust[4].x, 150 + adjust[4].y);
    
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
    
}

//--------------------------------------------------------------
void testApp::loadPaths(){
    
    string pathImages[5] = {"path1.png", "path1.png", "path1.png", "path1.png", "path1.png"};
    
    for (int i = 0; i < 5; i++) {
        ofImage path;
        path.loadImage("paths/" + pathImages[i]);
        paths.push_back(path);
    }
    
}

//--------------------------------------------------------------
void testApp::checkMatch(){
    
    int currentValue = arduino.getValue(step);
    
    // Check if value is in the right range for the current tile.
    
    if (ofInRange(currentValue, selectedTiles[step].getResistance().x , selectedTiles[step].getResistance().y)) {
        nextStep();
    }
    
}

void testApp::nextStep(){
    
    if (step < 4) {
        step++;
        
    } else {
        ofLogNotice() << "CONGRATS!";
        yay.play();
        step = 0;
        pickSymbols();
    }
    
    ofLogNotice() << step;
    
}

void testApp::setupTiles(){
    
    string images [10] = {"skull","anchor","wheel","cannon","bell","spyglass", "bone", "compass", "key","hourglass"};
    
    ofVec2f res [10] =
    {ofVec2f(100, 120), // skull
        ofVec2f(100, 120),  // anchor
        ofVec2f(100, 120),  // wheel
        ofVec2f(100, 120),  // cannon
        ofVec2f(100, 120),  // bell
        ofVec2f(100, 120),  // spyglass
        ofVec2f(100, 120),  // bone
        ofVec2f(100, 120),  // compass
        ofVec2f(100, 120),  // key
        ofVec2f(100, 120)}; // hourglass
    
    for (int i = 0; i < 10; i++) {
        Tile tile;
        tile.loadImage(images[i]);
        tile.setResistance(res[i].x, res[i].y);
        tiles.push_back(tile);
    }
    
    pickSymbols();
    
    /* Offsets for placement
     [notice ] Offsets 0: x-170 y-0
     [notice ] Offsets 1: x-135 y--95
     [notice ] Offsets 2: x-80 y--45
     [notice ] Offsets 3: x-0 y--50
     [notice ] Offsets 4: x--225 y--105
     */
    adjust.push_back(ofVec2f(170, 0));
    adjust.push_back(ofVec2f(135, -95));
    adjust.push_back(ofVec2f(80, -45));
    adjust.push_back(ofVec2f(0, -50));
    adjust.push_back(ofVec2f(-225, -105));
    
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

