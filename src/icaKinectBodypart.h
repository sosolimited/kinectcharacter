//
//  icaKinectBodypart.h
//  kinectcharacter
//
//  Created by Lauren McCarthy on 11/07/12.
//
//
#pragma once
#include "ofxTrackedUser.h"
#include "ofImage.h"
#include "ofxUserGenerator.h"

class icaKinectBodypart {
public:
    icaKinectBodypart(string iImagePath, XnSkeletonJoint iJoint0, XnSkeletonJoint iJoint1, XnSkeletonJoint iJoint2, int iLayer, float iScale, ofxOpenNIContext* iContext);
    ~icaKinectBodypart();
    void draw();
    
public:
    string              name;
    ofImage             img;
	xn::UserGenerator	user_generator;
	xn::DepthGenerator  depth_generator;
    
    XnSkeletonJoint     joints[3];
    bool                isHead;
    float               scale;
    int                 layer;

};

