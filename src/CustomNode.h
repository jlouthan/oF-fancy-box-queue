//
//  CustomNode.h
//  tilesExperiment_3D
//
//  Created by Jennifer Louthan on 8/7/13.
//
//

#ifndef __tilesExperiment_3D__CustomNode__
#define __tilesExperiment_3D__CustomNode__

#include <iostream>

#endif /* defined(__tilesExperiment_3D__CustomNode__) */

#include "ofMain.h"

class CustomNode : public ofNode{
public:
    
    int red, green, blue;
    virtual void customDraw();

};