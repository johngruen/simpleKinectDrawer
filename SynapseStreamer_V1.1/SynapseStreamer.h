/*
SynapseStreamer MIT License
Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SynapseStreamer Version 1.1
*/

#pragma once

//SynapseStreamer is an Openframeworks interface for Synapse, you therefore need to add the Openframeworks header and OSC header files
#include "ofMain.h"
#include "ofxOsc.h"

//These are the default IP addresses and ports
#define LOCAL_HOST "127.0.0.1"
#define INCOMING_SYNAPSE_DATA_PORT 12345
#define OUTGOING_SYNAPSE_DATA_PORT 12346
#define OUTGOING_STREAMING_DATA_PORT 5000

struct Joint{
    Joint(){
        trackWorldJoint = true;
        trackBodyJoint = true;
        clear();
    }
    void clear(){
        worldX = 0;
        worldY = 0;
        worldZ = 0;
        localX = 0;
        localY = 0;
        localZ = 0;
    }
    vector< double > getWorldCoordAsVector(){
        vector< double > data(3);
        data[0] = worldX;
        data[1] = worldY;
        data[2] = worldZ;
        return data;
    }
    vector< double > getLocalCoordAsVector(){
        vector< double > data(3);
        data[0] = localX;
        data[1] = localY;
        data[2] = localZ;
        return data;
    }
    double worldX;
    double worldY;
    double worldZ;
    double localX;
    double localY;
    double localZ;
    bool trackWorldJoint;
    bool trackBodyJoint;
};
typedef struct Joint Joint;

class SynapseStreamer{

public:
    
    SynapseStreamer();
    ~SynapseStreamer();
    
    void openSynapseConnection(unsigned int receiverIncomingDataPort = INCOMING_SYNAPSE_DATA_PORT, unsigned int senderOutgoingDataPort = OUTGOING_SYNAPSE_DATA_PORT,string ipAddress = LOCAL_HOST);
    void openOutgoingConnection(unsigned int outgoingDataPort = OUTGOING_STREAMING_DATA_PORT,string ipAddress = LOCAL_HOST);
    void parseIncomingMessages();
    
    //Getters
    bool getNewMessage();
    vector< double > getHeadJoint(){ return head.getWorldCoordAsVector(); }
    vector< double > getTorsoJoint(){ return torso.getWorldCoordAsVector(); }
    vector< double > getRightShoulderJoint(){ return rightShoulder.getWorldCoordAsVector(); }
    vector< double > getLeftShoulderJoint(){ return leftShoulder.getWorldCoordAsVector(); }
    vector< double > getRightElbowJoint(){ return rightElbow.getWorldCoordAsVector(); }
    vector< double > getLeftElbowJoint(){ return leftElbow.getWorldCoordAsVector(); }
    vector< double > getRightHandJoint(){ return rightHand.getWorldCoordAsVector(); }
    vector< double > getLeftHandJoint(){ return leftHand.getWorldCoordAsVector(); }
    vector< double > getRightHipJoint(){ return rightHip.getWorldCoordAsVector(); }
    vector< double > getLeftHipJoint(){ return leftHip.getWorldCoordAsVector(); }
    vector< double > getRightKneeJoint(){ return rightKnee.getWorldCoordAsVector(); }
    vector< double > getLeftKneeJoint(){ return leftKnee.getWorldCoordAsVector(); }
    vector< double > getRightFootJoint(){ return rightFoot.getWorldCoordAsVector(); }
    vector< double > getLeftFootJoint(){ return leftFoot.getWorldCoordAsVector(); }
    
    vector< double > getHeadJointBody(){ return head.getLocalCoordAsVector(); }
    vector< double > getTorsoJointBody(){ return torso.getLocalCoordAsVector(); }
    vector< double > getRightShoulderJointBody(){ return rightShoulder.getLocalCoordAsVector(); }
    vector< double > getLeftShoulderJointBody(){ return leftShoulder.getLocalCoordAsVector(); }
    vector< double > getRightElbowJointBody(){ return rightElbow.getLocalCoordAsVector(); }
    vector< double > getLeftElbowJointBody(){ return leftElbow.getLocalCoordAsVector(); }
    vector< double > getRightHandJointBody(){ return rightHand.getLocalCoordAsVector(); }
    vector< double > getLeftHandJointBody(){ return leftHand.getLocalCoordAsVector(); }
    vector< double > getRightHipJointBody(){ return rightHip.getLocalCoordAsVector(); }
    vector< double > getLeftHipJointBody(){ return leftHip.getLocalCoordAsVector(); }
    vector< double > getRightKneeJointBody(){ return rightKnee.getLocalCoordAsVector(); }
    vector< double > getLeftKneeJointBody(){ return leftKnee.getLocalCoordAsVector(); }
    vector< double > getRightFootJointBody(){ return rightFoot.getLocalCoordAsVector(); }
    vector< double > getLeftFootJointBody(){ return leftFoot.getLocalCoordAsVector(); }

    
    double getHandDistFeature(){ return handDistFeature; }
    
    //Setters
    void trackAllJoints(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackHead(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackTorso(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackRightShoulder(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackLeftShoulder(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackRightElbow(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackLeftElbow(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackRightHand(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackLeftHand(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackRightHip(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackLeftHip(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackRightKnee(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackLeftKnee(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackRightFoot(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void trackLeftFoot(bool trackStatus,unsigned int jointPos = ALL_JOINT_POSITIONS);
    void computeHandDistFeature(bool status){ computeHandDistanceFeature = status; }
    
private:
    //Private functions
    void clear();
    void sendJointRequests();
    double euclideanDistance(vector< double > a,vector< double > b);
       
    //OSC connections and counters
    ofxOscReceiver	receiver;
    ofxOscSender sender;
    ofxOscSender streamer;
    unsigned int sendMessageCounter;
    unsigned int sendMessageCounterValue;

    //Joints
    Joint head;
    Joint torso;
    Joint rightShoulder;
    Joint leftShoulder;
    Joint rightElbow;
    Joint leftElbow;
    Joint rightHand;
    Joint leftHand;
    Joint rightHip;
    Joint leftHip;
    Joint rightKnee;
    Joint leftKnee;
    Joint rightFoot;
    Joint leftFoot;
    
    //Features
    double handDistFeature;

    bool synapseConnectionOpen;
    bool streamingConnectionOpen;
    bool streamJointPositions;
    bool computeHandDistanceFeature;
    bool newMessageReceived;
    
    enum JointPositions{ALL_JOINT_POSITIONS=0,BODY_JOINT_POSITION,WORLD_JOINT_POSITION};
		
};
