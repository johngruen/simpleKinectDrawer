#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableSmoothing();
    synapseStreamer.openSynapseConnection();
    synapseStreamer.trackAllJoints(false);          
    synapseStreamer.trackLeftHand(true);           
    synapseStreamer.trackRightHand(true);
    isActive = false;
    ofSetFrameRate(30);
    ease = .5;
    
    
    easedLeft.x = 1024/2;
    easedLeft.y = 768/2;
    easedRight.x = 1024/2;
    easedRight.y = 768/2;
    mappedEasedLeft = easedLeft;
    mappedEasedRight = easedRight;
    
    //set hand stuff
    pulseSize = 7.5;
    pulseSizeInc = .25;
    
    //set up for window mapping
    showWinSettings = false;
    maxX = 626;
    maxY = -600;
    minX = -800;
    minY = 810;
    
    //setup for color picker
    drawColor = ofColor(255);
    drawStroke = 1;
    selectionTimer = 0;
    pushMesh = false;
    alreadyPushed = false;
    clearMesh = false;
    fillType = false;
    
    //setup for controls
    showControls = false;
    alreadyOff = false;
    
    ofSetCurveResolution(20);
}

//--------------------------------------------------------------
void testApp::update(){
    ofBackground(0);
    //Update SynapseStreamer to check for any new data
    
    synapseStreamer.parseIncomingMessages();
    
    //You should only get the data from synapseStreamer if new data has arrived
    
    if( synapseStreamer.getNewMessage() ){
        
        leftHand = synapseStreamer.getLeftHandJointBody();
        rightHand = synapseStreamer.getRightHandJointBody();
        ofSetColor(0);
        
        //Add your own code here to actually do something with the data
        //ofLogNotice() << leftHand[1];
        isActive = true;
    }

}


//--------------------------------------------------------------
void testApp::draw(){
    convertToMappedPoints();
    
    //cycle pulse size
    pulseSizeCycle();
    
    drawMeshes();
    
    //controls
    winSettings();
    toggleControls();
    controls();
    
    //left hand
    handPoint(mappedEasedLeft,0,255,255);
    //right hand
    handPoint(mappedEasedRight,255,0,255);
       

    
    
    pushMeshes();
    clearMeshes();





    
}

void testApp::controls() {
    if(showControls) {
        int regX = 934;
        int regY = 10;
        int side = 80;
        ofEnableAlphaBlending();
        ofSetColor(40,200);
        ofRect(924,0,100,768);
        
        //INCREASE STROKEWEIGHT
        ofSetColor(255,0,255,20);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > regY && mappedEasedRight.x < regX+side && mappedEasedRight.y < regY + side ) {
            ofSetColor(255,0,255,200);
            selectionTimer++;
            if (selectionTimer % 8 == 0) drawStroke ++;
        } 
        ofRect(regX,regY,side,side);
        ofSetColor(255);
        ofDrawBitmapString("stroke +",regX + 10, regY+side/2);
        
        //DECREASE STROKE WEIGHT
        ofSetColor(255,0,255,20);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > regY + 90 && mappedEasedRight.x < regX+side && mappedEasedRight.y < regY + side + 90 ) {
            ofSetColor(255,0,255,200);
            selectionTimer++;
            if (selectionTimer % 8 == 0 && drawStroke > 1) drawStroke --;
        } 
        ofRect(regX,regY+90,side,side);
        ofSetColor(255);
        ofDrawBitmapString("stroke -",regX + 10, 90+regY+side/2);
        
        //
        ofColor rainbow;
        
        for (int i = 0; i < 255; i ++){
            rainbow.setHsb(i,255,255);
            ofSetColor(rainbow);
            ofRect(regX, 190+i,side,1);
        }
        
        ofSetColor(0,100);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > 190 && mappedEasedRight.x < regX+side && mappedEasedRight.y < 190+255 ) {
            ofSetColor(0,0);
            selectionTimer++;
            if (selectionTimer % 8 == 0) drawColor.setHsb(mappedEasedRight.y-190,255,255);
        }
        ofRect(regX,190,side,255);
        
        //WHITE COLOR
        ofSetColor(255,200);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > 455 && mappedEasedRight.x < regX+side && mappedEasedRight.y < 455+side/2 ) {
            ofSetColor(255);
            selectionTimer++;
            if (selectionTimer % 8 == 0) drawColor = ofColor(255);
        }
        ofRect(regX,455,side,side/2);
        
        //typeToggle
        ofSetColor(255,0,255,20);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > 500 && mappedEasedRight.x < regX+side && mappedEasedRight.y < 500+ side ) {
            ofSetColor(255,0,255,200);
            selectionTimer++;
            if (selectionTimer % 8 == 0) {
                if (fillType == 0) fillType = 1;
                else if (fillType == 1) fillType = 0;
            };
        } 
        ofRect(regX,500,side,side);
        ofSetColor(255);
        ofDrawBitmapString("toggle \nfill",regX + 10, 500+side/2);
        
        //PUSHMESH
        ofSetColor(255,0,255,20);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > 590 && mappedEasedRight.x < regX+side && mappedEasedRight.y < 590 + side ) {
            ofSetColor(255,0,255,200);
            selectionTimer++;
            if (selectionTimer % 8 == 0) pushMesh = true;
        } else {
            pushMesh = false;
            alreadyPushed = false;
        }
        ofRect(regX,590,side,side);
        ofSetColor(255);
        ofDrawBitmapString("new \nlayer",regX + 10, 590+side/2);
        
        //ClearMesh
        ofSetColor(255,0,255,20);
        if(mappedEasedRight.x > regX && mappedEasedRight.y > 680 && mappedEasedRight.x < regX+side && mappedEasedRight.y < 680 + side ) {
            ofSetColor(255,0,255,200);
            selectionTimer++;
            if (selectionTimer % 20 == 0) clearMesh = true;
        } else {
            clearMesh = false;
        }
        ofRect(regX,680,side,side);
        ofSetColor(255);
        ofDrawBitmapString("clear",regX + 10, 680+side/2);

        
        
        ofDisableAlphaBlending();
    }
}

void testApp::pushMeshes(){
    if(pushMesh == true && alreadyPushed == false) {

        alreadyPushed = true;
        oldStroke[0] = drawStroke;
        oldColor[0] = drawColor;
        oldMesh[0] = mesh;
        mesh.clear();
        for(int i = omq-1; i >= 1; i--) {
            oldStroke[i] = oldStroke[i-1];
            oldColor[i] = oldColor[i-1];
            oldMesh[i].clear();
            oldMesh[i] = oldMesh[i-1];
            ofLogNotice() << oldStroke[i];
        }


    }
}

void testApp::drawMeshes(){
    for(int i = omq-1; i >= 0; i--){
        ofSetColor(oldColor[i]);
        ofSetLineWidth(oldStroke[i]);
        oldMesh[i].draw();
    }
    
    mesh.addVertex(mappedEasedLeft);
    if (fillType == 0) mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    else mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    ofSetColor(drawColor);
    ofSetLineWidth(drawStroke);
    mesh.draw();
    
}
void testApp::clearMeshes() {
    if(clearMesh) {
        for(int i = 0; i < omq; i++){
            oldMesh[i].clear();
        }
        mesh.clear();
    }
}

void testApp::toggleControls() {
    if (alreadyOff == false && mappedEasedRight.x > 1024) {
        alreadyOff = true;
        if (showControls) showControls = false;
        else showControls = true;
    }
    if (mappedEasedRight.x < 1024) alreadyOff = false;
}



//----------------------------------------------------------
void testApp::convertToMappedPoints(){
    if(isActive) {
        isActive = false;
        easedLeft.x += (leftHand[0] - easedLeft.x)*ease;
        easedLeft.y += (leftHand[1] - easedLeft.y)*ease;
        easedRight.x += (rightHand[0] - easedRight.x)*ease;
        easedRight.y += (rightHand[1] - easedRight.y)*ease;
        mappedEasedLeft.x = ofMap(easedLeft.x,minX,maxX,0,1024);
        mappedEasedLeft.y = ofMap(easedLeft.y,minY,maxY,0,1024);
        mappedEasedRight.x = ofMap(easedRight.x,minX,maxX,0,1024);
        mappedEasedRight.y = ofMap(easedRight.y,minY,maxY,0,1024);
        
    }
}

void testApp::handPoint(ofVec2f pos, int r, int g, int b) {
    ofEnableAlphaBlending();
    ofSetColor(r,g,b,150);
    ofEllipse(pos.x,pos.y,pulseSize,pulseSize);
    ofDisableAlphaBlending();
}

void testApp::pulseSizeCycle() {
    if (pulseSize < 5 || pulseSize > 10 ) pulseSizeInc = -pulseSizeInc;
    pulseSize+=pulseSizeInc;
}


//-----------------------------------------------------------
void testApp::winSettings() {
    if (showWinSettings) {
    ofSetColor(50,100);
    ofRect(0,0,1024,110);
    ofSetColor(255);
    string posString =  "use WASD and Arrows to modify \n"
                        "kinect hand mapping \n"
                        "press r to reset default \n"
                        "maxX: " + ofToString(maxX,2) +"\n"+
                        "minX: " + ofToString(minX,2) +"\n"+
                        "maxY: " + ofToString(maxY,2) +"\n"+
                        "minY: " + ofToString(minY,2) +"\n";
    ofDrawBitmapString(posString,10,20);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key) {
        case 357:
            maxY--;
            break;
        case 358:
            maxX++;
            break;
        case 359:
            maxY++;
            break;
        case 356:
            maxX--;
            break;
        case 119:
            minY++;
            break;
        case 100:
            minX--;
            break;
        case 115:
            minY--;
            break;
        case 97:
            minX--;
            break;
        case 32:
            if (showWinSettings) {
                showWinSettings = false;
            } else showWinSettings = true;
            ofLogNotice() << showWinSettings;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
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
