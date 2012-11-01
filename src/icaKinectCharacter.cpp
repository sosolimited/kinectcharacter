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
    
    image.loadImage(iImagePath);
}

icaKinectBodypart::~icaKinectBodypart(){}

icaKinectCharacter::icaKinectCharacter(string iPathname)
{
    
}

icaKinectCharacter::~icaKinectCharacter(){}

void icaKinectCharacter::draw()
{
    
}
