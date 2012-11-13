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
    
    img.loadImage(iImagePath);
    img.setAnchorPercent(0.5, 0.5);
    
    iContext->getDepthGenerator(&depth_generator);
	iContext->getUserGenerator(&user_generator);
}

icaKinectBodypart::~icaKinectBodypart(){}


void icaKinectBodypart::draw() {
    
        
    for (int i=0; i<user_generator.GetNumberOfUsers(); i++) {
        
        int id = i+1;

        xn::SkeletonCapability pUserSkel = user_generator.GetSkeletonCap();

        XnPoint3D position[2];
        XnSkeletonJointPosition jointPos[2];
        pUserSkel.GetSkeletonJointPosition(id, joints[0], jointPos[0]);
        pUserSkel.GetSkeletonJointPosition(id, joints[1], jointPos[1]);
        
        position[0] = jointPos[0].position;
        position[1] = jointPos[1].position;
        
        depth_generator.ConvertRealWorldToProjective(2, position, position);
        
        position[0].X = position[0].X*ofGetWidth()/640.0f;
        position[0].Y = position[0].Y*ofGetHeight()/480.0f;
        
        position[1].X = position[1].X*ofGetWidth()/640.0f;
        position[1].Y = position[1].Y*ofGetHeight()/480.0f;

        
        float h = ofDist(position[0].X, position[0].Y, position[1].X, position[1].Y);
        float w = h * (float)img.width / (float)img.height;
        
        float angle = atan((position[1].Y-position[0].Y)/(position[1].X-position[0].X));
        
        
        printf("%f %d %f %f %d %f %f\n", h, joints[0], position[0].X, position[0].Y, joints[1], position[1].X, position[1].Y);
        
        ofPushMatrix();
        ofTranslate( (position[0].X+position[1].X)/2, (position[0].Y+position[1].Y)/2);
        ofRotate(ofRadToDeg(angle), 0, 0, 1);
        img.draw(0, 0, 0, w, h);
        ofPopMatrix();
    }
}
