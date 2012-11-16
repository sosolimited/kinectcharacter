//
//  icaKinectBodypart.cpp
//  kinectcharacter
//
//  Created by Lauren McCarthy on 11/07/12.
//
//

#include "icaKinectBodypart.h"

icaKinectBodypart::icaKinectBodypart(string iImagePath, XnSkeletonJoint iJoint0, XnSkeletonJoint iJoint1, XnSkeletonJoint iJoint2, int iLayer, float iScale, ofxOpenNIContext* iContext)
{
 
    joints[0] = iJoint0;
    joints[1] = iJoint1;
    joints[2] = iJoint2;
    
    isHead = (joints[0] == 1) ? true : false;
    scale = (isHead) ? 2*iScale: iScale;
    layer = iLayer;
    
    
    printf("layer %d joints %d %d %d", layer, joints[0], joints[1], joints[2]);
    
    img.loadImage(iImagePath);
    img.setAnchorPercent(0.5, 0.5);
    
    iContext->getDepthGenerator(&depth_generator);
	iContext->getUserGenerator(&user_generator);
}

icaKinectBodypart::~icaKinectBodypart(){}


void icaKinectBodypart::draw() {	
    
    glEnable(GL_DEPTH);
    
    for (int i=0; i<user_generator.GetNumberOfUsers(); i++) {
        
        int id = i+1;
        
        // check user being tracked
        if(!user_generator.GetSkeletonCap().IsTracking(id)) {
            printf("Not tracking this user: %d\n", id);
            return;
        }

        xn::SkeletonCapability pUserSkel = user_generator.GetSkeletonCap();

        
        // doing an average of joints 1 and 2 here for situations like torso where there is no midpoint joint
        XnPoint3D position[3];
        XnSkeletonJointPosition jointPos[3];
        pUserSkel.GetSkeletonJointPosition(id, joints[0], jointPos[0]);
        pUserSkel.GetSkeletonJointPosition(id, joints[1], jointPos[1]);
        pUserSkel.GetSkeletonJointPosition(id, joints[2], jointPos[2]);
        
        position[0] = jointPos[0].position;
        position[1] = jointPos[1].position;
        position[2] = jointPos[2].position;
        
        // check accurate enough
        if(jointPos[0].fConfidence < 0.3f || jointPos[1].fConfidence < 0.3f || jointPos[2].fConfidence < 0.3f) {
            return;
        }
        
        depth_generator.ConvertRealWorldToProjective(3, position, position);
        
        position[0].X = position[0].X*ofGetWidth()/640.0f;
        position[0].Y = position[0].Y*ofGetHeight()/480.0f;
        
        position[1].X = (position[1].X+position[2].X)*ofGetWidth()/(2.0*640.0f);
        position[1].Y = (position[1].Y+position[2].Y)*ofGetHeight()/(2.0*480.0f);
        
        XnPoint3D midPosition;
        midPosition.X = (position[0].X+position[1].X)/2;
        midPosition.Y = (position[0].Y+position[1].Y)/2;

        
        float angle = M_PI/2 + atan((position[1].Y-midPosition.Y)/(position[1].X-midPosition.X));
        if (position[1].X > position[0].X) angle -= M_PI;
        printf("%f %d %f %f %d %f %f\n", ofRadToDeg(angle), joints[0], position[0].X, position[0].Y, joints[1], position[1].X, position[1].Y);
        
        
        ofPushMatrix();

        float h = scale * abs(ofDist(position[0].X, position[0].Y, position[1].X, position[1].Y));
        float w = h * (float)img.width / (float)img.height;
        
        
        ofTranslate( midPosition.X, midPosition.Y );
        ofRotate(ofRadToDeg(angle), 0, 0, 1);
        img.draw(0, 0, layer, w, h);
        
        ofPopMatrix();
    }
}
