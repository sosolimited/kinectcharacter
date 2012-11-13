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
    printf("icaKinectCharacter: %s\n", (char*)iPathname.c_str());
}

icaKinectCharacter::~icaKinectCharacter(){}

void icaKinectCharacter::loadParts(string iPathname) {
    
	
    char imageChars[256];


    partsXML.loadFile(iPathname + "parts.xml");
   
    string empty = "";
    background.loadImage("images/background.png");

	
	int numParts = partsXML.getNumTags("Part");
    
    if(numParts > 0){
        
        
        for(int i = 0; i < numParts; i++){
            
            partsXML.pushTag("Part", i);
            
            string imagePath = partsXML.getValue("Image", empty, 0);
            XnSkeletonJoint j0 = (XnSkeletonJoint) partsXML.getValue("Joint0", 1, 0);
            XnSkeletonJoint j1 = (XnSkeletonJoint) partsXML.getValue("Joint1", 1, 0);
            

            float s = partsXML.getValue("Scale", 1.0, 0);
            icaKinectBodypart *p = new icaKinectBodypart(iPathname + "images/" + imagePath, j0, j1, s, context);
           

            parts.push_back(p);
            
            partsXML.popTag();
        }
    }
    
    
    printf("icaKinectCharacter::loadParts() - %d loaded \n", (int)parts.size());

}

void icaKinectCharacter::draw()
{
    background.draw(0, 0, -1);
    for (int i=0; i<parts.size(); i++) {
        parts[i]->draw();
    }
}
