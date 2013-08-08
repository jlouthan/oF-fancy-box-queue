#include "testApp.h"

//--------------------------------------------------------------

double timeStep = 0.01;
double theTime;
double bigTileX = 4;
double bigTileY = 0;
double bigTileZ = 12;

double rotationStep = ofRadToDeg(-M_PI/(8*20));
double zStep = -6*M_PI/3;
ofVec3f firstNodePosition;
ofVec3f lastNodePosition;


void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0xaaaaaa);
    easyCam.setDistance(22);

    ofSetLineWidth(3);
    
    ofSetVerticalSync(true);
    
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	glEnable(GL_DEPTH_TEST);
	
	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	ofEnableNormalizedTexCoords();
    
    //create a bunch of custom nodes
    for(double z = 0; z > -36*M_PI; z +=zStep){
        double x = -10;
        double y = tileLayoutFunction(z);
        double blueValue = fmod(-floor(z*2),255);

        CustomNode* node = new CustomNode();
        node->setPosition(x, y, z);
        node->red = 0;
        node->green = 60;
        node->blue = blueValue;
        customNodes.push_back(node);
        
    }
    firstNodePosition = customNodes[0]->getPosition();
    lastNodePosition = customNodes[customNodes.size()-1]->getPosition();
    
    
    light.enable();
    light.setPosition(0, 0, 150);
    light.setDirectional();
    ofFloatColor ambient_color(1.0, 0.0, 0.0,1.0);
    ofFloatColor diffuse_color(1.0, 1.0, 1.0);
    ofFloatColor specular_color(0.0, 1.0, 0.0);
    light.setAmbientColor(ambient_color);
    light.setDiffuseColor(diffuse_color);
    light.setSpecularColor(specular_color);

    easyCam.disableMouseInput();
    
    

}

//--------------------------------------------------------------
void testApp::update(){
    
    if(animating){
        ofVec3f startingPosition = firstNodePosition;
        double x = startingPosition.x + (bigTileX-startingPosition.x)*theTime;
        double y = startingPosition.y + (bigTileY-startingPosition.y)*theTime;
        double z = startingPosition.z + (bigTileZ-startingPosition.z)*theTime;
        ofVec3f animatingNodePosition = ofVec3f(x,y,z);
        
        if(animatingNodePosition.x<=bigTileX){
            animatingNode->setPosition(animatingNodePosition);
            animatingNode->rotate(rotationStep, 0, 1, 0);
            
            //animate all nodes along the function too
            for(int i=1; i<customNodes.size(); i++){
                ofVec3f currentPosition = customNodes[i]->getPosition();
                double newX = currentPosition.x;
                double newZ = currentPosition.z - zStep/100;
                double newY = tileLayoutFunction(newZ);
                customNodes[i]->setPosition(ofVec3f(newX, newY, newZ));
            }
        
            theTime+=timeStep;
        }
        else{
            animating = false;
            customNodes[0]->setPosition(lastNodePosition);
            customNodes[customNodes.size()-1] = customNodes[0];
            for(int i=0;i<customNodes.size()-1;i++){
                customNodes[i] = customNodes[i+1];
            }
            cout << theTime;
        }
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    easyCam.begin();

    for(int i = animating ? 1 : 0; i<customNodes.size(); ++i){
            customNodes[i]->draw();
    }
    
    if(animatingNode)
        animatingNode->draw();
        
    easyCam.end();
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);

}

double testApp::tileLayoutFunction(double zValue){
    return 15*sin(zValue/12);
//    return 25*sin(zValue/5);
//    return pow(1.05, -zValue) - 4;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
    if(!animating)
    {
        animatingNode = new CustomNode();
        animatingNode->setPosition(customNodes[0]->getPosition());
        animatingNode->red = customNodes[0]->red;
        animatingNode->green = customNodes[0]->green;
        animatingNode->blue = customNodes[0]->blue;

        animating = true;
        theTime = 0;
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