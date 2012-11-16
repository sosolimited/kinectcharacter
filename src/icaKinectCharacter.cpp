//
//  icaKinectCharacter.cpp
//  kinectcharacter
//
//  Created by Eric Gunther on 10/31/12.
//
//

#include "icaKinectCharacter.h"


icaKinectCharacter::icaKinectCharacter(string iPathname, ofxOpenNIContext *iContext)
{
       //user = iUser;
    context = iContext;
    loadParts(iPathname);
    name = iPathname;
    printf("icaKinectCharacter: %s\n", (char*)iPathname.c_str());
}

icaKinectCharacter::~icaKinectCharacter(){}

void icaKinectCharacter::loadParts(string iPathname) {
    
    char imageChars[256];

    partsXML.loadFile(iPathname + "parts.xml");
   
    string empty = "";
    background.loadImage(iPathname + "images/background.png");

	
	int numParts = partsXML.getNumTags("Part");
    int bgLayer = 0;
    
    if(numParts > 0){
        
        
        for(int i = 0; i < numParts; i++){
            
            partsXML.pushTag("Part", i);
            
        
            string imagePath = partsXML.getValue("Image", empty, 0);
            XnSkeletonJoint j0 = (XnSkeletonJoint) partsXML.getValue("Joint0", 1, 0);
            XnSkeletonJoint j1 = (XnSkeletonJoint) partsXML.getValue("Joint1", 1, 0);
            XnSkeletonJoint j2 = (XnSkeletonJoint) partsXML.getValue("Joint2", j1, 0);
            int l = partsXML.getValue("Layer", bgLayer, 0);
            if (l == bgLayer) bgLayer--;
            else printf("LAYER %d", l);

            float s = partsXML.getValue("Scale", 1.1, 0);
            icaKinectBodypart *p = new icaKinectBodypart(iPathname + "images/" + imagePath, j0, j1, j2, l, s, context);
           

            parts.push_back(p);
            
            partsXML.popTag();
        }
    }
    
    
    
    
    printf("icaKinectCharacter::loadParts() - %d loaded \n", (int)parts.size());

}

void icaKinectCharacter::draw()
{
    //glEnable(GL_DEPTH);
    //glEnable(GL_DEPTH_TEST);
    //ofEnableAlphaBlending();
    //glDepthMask(GL_FALSE);
    
    background.draw(0, 0, bgLayer);
    for (int i=0; i<parts.size(); i++) {
        parts[i]->draw();
    }
}
