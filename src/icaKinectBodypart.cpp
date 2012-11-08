//
//  icaKinectBodypart.cpp
//  kinectcharacter
//
//  Created by Lauren McCarthy on 11/07/12.
//
//

#include "icaKinectBodypart.h"

icaKinectBodypart::icaKinectBodypart(string iImagePath, XnSkeletonJoint iJoint0, XnSkeletonJoint iJoint1, ofxOpenNIContext* iContext)
{
 
    joints[0] = iJoint0;
    joints[1] = iJoint1;
    
    printf("joints %d %d", joints[0], joints[1]);
    
    img.loadImage("images/"+iImagePath);
    img.setAnchorPercent(0.5, 0.5);
    
    iContext->getDepthGenerator(&depth_generator);
	iContext->getUserGenerator(&user_generator);
}

icaKinectBodypart::~icaKinectBodypart(){}


void icaKinectBodypart::draw() {
    
        
    for (int i=0; i<user_generator.GetNumberOfUsers(); i++) {
        
        int id = i+1;

        xn::SkeletonCapability pUserSkel = user_generator.GetSkeletonCap();
        
        //XnSkeletonJointOrientation jointOri;
        //pUserSkel.GetSkeletonJointOrientation(id ,(XnSkeletonJoint)0, jointOri);
        
        XnPoint3D position[2];
        XnSkeletonJointPosition a, b;
        pUserSkel.GetSkeletonJointPosition(id, joints[1], a);
        pUserSkel.GetSkeletonJointPosition(id, joints[0], b);
        
        position[0] = a.position;
        position[1] = b.position;
        
        depth_generator.ConvertRealWorldToProjective(2, position, position);
        
        float h = ofDist(position[0].X, position[0].Y, position[1].X, position[1].Y);
        float w = h * (float)img.width / (float)img.height;
        
        
        printf("%f %d %f %f %d %f %f\n", h, joints[0], position[0].X, position[0].Y, joints[1], position[1].X, position[1].Y);
        
        //img.draw((position[0].X+position[1].X)/2, (position[0].Y+position[1].Y)/2, 0, w, h);
        img.draw((position[0].X+position[1].X)/2, (position[1].Y+position[1].Y)/2, 0, w, h);
    }
}
