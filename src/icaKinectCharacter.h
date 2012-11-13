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
#include "ofxXmlSettings.h"
#include "ofxUserGenerator.h"
#include "icaKinectBodypart.h"


class icaKinectCharacter {
    
public:
    icaKinectCharacter(string iPathname, ofxOpenNIContext *iContext);//, ofxUserGenerator *iUser);
    ~icaKinectCharacter();
    
    void                loadParts(string iPathname);
    
    void                draw();
    
public:
    
    ofxXmlSettings                  partsXML;
    vector<icaKinectBodypart *>     parts;
    ofxUserGenerator                *user;
    ofxOpenNIContext                *context;
    
};