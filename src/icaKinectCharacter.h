//
//  icaKinectCharacter.h
//  kinectcharacter
//
//  Created by Eric Gunther on 10/31/12.
//
//
#pragma once
#include "ofxTrackedUser.h"
#include "ofImage.h"

class icaKinectBodypart {
public:
    icaKinectBodypart(string iImagePath, XnSkeletonJoint iJoint1, XnSkeletonJoint iJoint2);
    ~icaKinectBodypart();
    void draw();
    
public:
    XnSkeletonJoint     joints[2];
    ofImage             img;

};

class icaKinectCharacter {
    
public:
    icaKinectCharacter(string iPathname);
    ~icaKinectCharacter();
    
    void                draw();
    
public:
    
    vector<icaKinectBodypart>   parts;
    
};