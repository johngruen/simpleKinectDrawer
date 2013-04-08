#include "ofMain.h"


class MeshBot {
    
    public:
    
    int r;
    int g;
    int b;
    int strokeWidth;
    ofMesh m;
    
    void initRGB(int r_, int g_, int b_);
    void initStrokeWidth(int w_);
    void drawMesh();
    
};