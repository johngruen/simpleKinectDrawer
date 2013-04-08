#pragma once

#include "ofMain.h"
#include "SynapseStreamer.h"
#include "MeshBot.h"

// listen on port 12345



class testApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        SynapseStreamer synapseStreamer;
    
        //receivers for OSC data from synapse
        vector<double> leftHand;
        vector<double> rightHand;
    
        //test is is Active
        bool isActive;
    
        //easing for hand positions
        float ease;
        ofVec3f easedLeft;
        ofVec3f easedRight;
    
        //final, mapped positions for hands
        void convertToMappedPoints();
        ofVec2f mappedEasedLeft;
        ofVec2f mappedEasedRight;
    
        //handPicker
        void handPoint(ofVec2f pos, int r, int g, int b);
        void handPointPulse(int min, int max);
        void pulseSizeCycle();
        float pulseSize;
        float pulseSizeInc;
        
        //keycontrols
        void winSettings();
        bool showWinSettings;
        int maxX;
        int minX;
        int maxY;
        int minY;
    
    
        //colorpicker
        void colorPicker();
        bool showColorPicker;
    
        //alphaPicker
        void alphaPicker();
        bool ShowAlphaPicker;
    
        //controls
    
        bool showControls;
        bool alreadyOff;
        void toggleControls();
        void controls();
    
        //settings
    
        ofColor drawColor;
        int drawStroke;
        int selectionTimer;
        bool pushMesh = false;
        bool alreadyPushed = false;
        bool clearMesh = false;
        int omq = 20;
        ofMesh mesh;
        ofMesh oldMesh [20];
        int oldType [20];
        bool fillType;
        ofColor oldColor[20];
        int oldStroke[20];
        void drawMeshes();
        void pushMeshes();
        void clearMeshes();
    
    
        //setmeshType
        

    

        
};
