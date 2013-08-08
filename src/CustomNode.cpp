//
//  CustomNode.cpp
//  tilesExperiment_3D
//
//  Created by Jennifer Louthan on 8/7/13.
//
//

#include "CustomNode.h"

void CustomNode::customDraw(){
    ofFill();
    ofSetColor(red, green, blue);
    ofBox(5);
    ofNoFill();
    ofSetHexColor(0x000000);
    ofBox(5);
}
