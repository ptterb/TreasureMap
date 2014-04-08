#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(7);
    
    white.set(255, 255, 255);
    darkYellow.set(191, 162, 17);
    lightYellow.set(255, 255, 157);
    
    twinkleColors.push_back(white);
    twinkleColors.push_back(lightYellow);
    twinkleColors.push_back(darkYellow);
    
    drawFBO.allocate(ofGetWidth(), ofGetHeight());
    
    // Allocate all images
    skull.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    anchor.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    wheel.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    cannon.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    bell.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    spyglass.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    bone.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    compass.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    key.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    hourglass.allocate(objectSize, objectSize, OF_IMAGE_COLOR_ALPHA);
    
    // Load all images
    skull.loadImage(path+"skull.png");
    anchor.loadImage(path+"anchor.png");
    wheel.loadImage(path+"wheel.png");
    cannon.loadImage(path+"cannon.png");
    bell.loadImage(path+"bell.png");
    spyglass.loadImage(path+"spyglass.png");
    bone.loadImage(path+"bone.png");
    compass.loadImage(path+"compass.png");
    key.loadImage(path+"key.png");
    hourglass.loadImage(path+"hourglass.png");
    
    // Load all images into vector
    tiles.push_back(skull);
    tiles.push_back(anchor);
    tiles.push_back(wheel);
    tiles.push_back(cannon);
    tiles.push_back(bell);
    tiles.push_back(spyglass);
    tiles.push_back(bone);
    tiles.push_back(compass);
    tiles.push_back(key);
    tiles.push_back(hourglass);
    
    pickSymbols();

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    if (step >= 0) {
        drawSymbol(20,20, selectedTiles[0]);
    }

    if (step >= 1){
        drawSymbol(300,100, selectedTiles[1]);
    }
    
    if (step >= 2){
        drawSymbol(100,450, selectedTiles[2]);
    }
    
    if (step >= 3){
        drawSymbol(800,500, selectedTiles[3]);
    }

    if (step >= 4){
        drawSymbol(600,150, selectedTiles[4]);
    }
    
    
    
}
//--------------------------------------------------------------
void testApp::pickSymbols(){
    
    selectedTiles.clear();
    vector<ofImage>workingTiles = tiles;
    for (int i = 0; i < 5; i++) {
        int rand = ofRandom(0, workingTiles.size());
        selectedTiles.push_back(workingTiles.at(rand));
        workingTiles.erase(workingTiles.begin()+rand);
    }
    
}

//--------------------------------------------------------------
void testApp::drawSymbol(int x, int y, ofImage positionedImage){
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    int randSeed = (int) ofRandom(0, 5);
    
    for (int x = randSeed; x < objectSize; x+=5){
        for (int y = randSeed; y < objectSize; y+=5) {
            if (positionedImage.getColor(x, y).a == 255) {
                int twinkleSize = ofRandom(0, 5);
                ofSetColor(twinkleColors.at(ofRandom(0, twinkleColors.size())));
                ofEllipse(x, y, twinkleSize, twinkleSize);
            }
        }
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    pickSymbols();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if (step < 4) {
        step++;
        
    } else {
        step = 0;
        pickSymbols();
    }
    
    ofLogNotice() << step;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
