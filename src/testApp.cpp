#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(7);
    
    pr.allocate(1024, 768, OF_IMAGE_COLOR);
    pr.loadImage("PR.png");
    
    drawFBO.allocate(ofGetWidth(), ofGetHeight());
    
    string images [10] = {"skull","anchor","wheel","cannon","bell","spyglass", "bone", "compass", "key","hourglass"};
    
    for (int i = 0; i < 10; i++) {
        Tile tile;
        tile.loadImage(images[i]);
        tiles.push_back(tile);
    }
    
    pickSymbols();

}

//--------------------------------------------------------------
void testApp::update(){
    
    // Update alpha values for the last symbol drawn
    for(int i = 0; i < step; i++){
        selectedTiles[i].setAlpha(255);
    }
    
    selectedTiles[step].fadeIn();
    
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    if (drawPr){
        pr.draw(0, 0);
    }
    
    selectedTiles[0].drawSymbol(20, 20);
    paths[0].draw(20, 268);
    selectedTiles[1].drawSymbol(200, 350);
    selectedTiles[2].drawSymbol(500, 100);
    selectedTiles[3].drawSymbol(800, 300);
    selectedTiles[4].drawSymbol(1200, 150);
    
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
        path.loadImage("paths/" + pathImages[i] + ".png");
        paths.push_back(path);
    }
    
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
    
    if (button == 0){
        if (step < 4) {
            step++;
            
        } else {
            ofLogNotice() << "CONGRATS!";
            step = 0;
            pickSymbols();
        }
        
        ofLogNotice() << step;
    } else {
        drawPr = !drawPr;
    }

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
