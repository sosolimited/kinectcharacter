//
//  icaKinectCharacter.cpp
//  kinectcharacter
//
//  Created by Eric Gunther on 10/31/12.
//
//

#include "icaKinectCharacter.h"

icaKinectBodypart::icaKinectBodypart(string iImagePath, XnSkeletonJoint iJoint1, XnSkeletonJoint iJoint2)
{
    joints[0] = iJoint1;
    joints[1] = iJoint2;
    
    img.loadImage(iImagePath);
}

icaKinectBodypart::~icaKinectBodypart(){}

void icaKinectBodypart::draw() {
    img.draw(0, 0, 0, 100, 100);
}




icaKinectCharacter::icaKinectCharacter(string iPathname)
{
    // walk thru xml, build parts
}

icaKinectCharacter::~icaKinectCharacter(){}

void icaKinectCharacter::draw()
{
    for (int i=0; i<parts.size(); i++) {
        parts[i].draw();
    }
}
