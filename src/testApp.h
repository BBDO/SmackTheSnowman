#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"      // kinect
#include "ofxKinect.h"      // kinect

#include "ofxBox2d.h"               // box2d
#include "ofxTriangle.h"            // box2d
#include "ofxCvContourSimplify.h"   // box2d
#include "revJoint.h"

#include "ofxSimpleGuiToo.h" // GUI
#include "ofxXmlSettings.h"  // GUI

#define WIDTH 640
#define HEIGHT 480
#define N_SOUNDS 1
#define N_IMAGES 4

class SoundData {
public:
	int	 soundID;
	bool bHit;
};

class testApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
    // SYSTEM
    void setDrawMethod(int method);
    int drawMethod;
    
    // GUI
    void    setupGUI();
    void    updateGUI();
    ofxSimpleGuiToo gui;
    
    // WORLD
    int xWorld; // controls world x position
    int yWorld; // controls world y position
    int zWorld; // controls world z position
    
    // KINECT
    void setupKinect();
    void updateKinect();
    void drawKinect();
	ofxKinect kinect;
    
    void updateContours();
    void drawContours();
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	ofxCvContourFinder contourFinder;
	bool bThreshWithOpenCV;
    bool contoursOn;
    bool depthWhite;
	int nearThreshold;
	int farThreshold;
	int angle;
    int contourXpos, contourYpos, contourZpos;
    
    // BOX2D
    void setupBox2d();
    void updateBox2d();
    ofxBox2d box2d;
    ofxBox2d box2dSnow;
    ofxBox2d box2dSmoke;
    ofxBox2d box2dClouds;
    vector<ofxBox2dJoint> joints;
    vector<ofxBox2dPolygon> body;
    ofxTriangle triangle;
    ofxCvContourSimplify contourSimp;   // Contour simplification for the body
    vector<ofPoint> contourRough;       // Contour simplification for the body
    vector<ofPoint> contourSmooth;      // Contour simplification for the body
    
    // SNOWMAN
    void setupAvatar();
    void drawAvatar();
    vector <ofxBox2dRect> rectHead, rectBody, rectBase, rectLArm, rectRArm; // Avatar body parts
    vector <ofxBox2dRect> bottomLeft, bottomRight;  // Avatar suspension
    revJoint revjointAvatar;
    ofImage iHead, iBody, iBase, iLArm, iRArm;
    ofImage iHeadHit;
    SoundData * sd1;
    bool headHit;
    bool avatarOn;
    bool jointsOn;
    int avatarGravity;
    float vol;
    int avatarXpos, avatarYpos, avatarZpos;
    
    // SNOW
    void setupSnow();
    void updateSnow();
    void drawSnow();
    vector <ofxBox2dRect> snowFlakes;
    ofImage iSnow;
    bool snowOn;
    int snowXpos, snowYpos, snowZpos;
    int snowAmt;
    int snowFreq;
    int snowMaxSize;
    float snowSpeed;
    
    // SMOKE
    void setupSmoke();
    void updateSmoke();
    void drawSmoke();
    vector <ofxBox2dRect> smoke;
    ofImage iSmoke;
    bool smokeOn;
    int smokeXpos, smokeYpos, smokeZpos;
    int smokeAmt;
    int smokeFreq;
    int smokeMaxSize;
    float smokeSpeed;
    
    // CLOUDS
    void setupClouds();
    void updateClouds();
    void drawClouds();
    vector <ofxBox2dRect> clouds, clouds2;
    ofImage iClouds;
    bool cloudsOn;
    int cloudsXpos, cloudsYpos, cloudsZpos;
    int cloudsAmt;
    int cloudsFreq;
    int cloudsMaxSize;
    float cloudsSpeed;
    
    // SOUNDS
    void setupSounds();
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
	ofSoundPlayer  sound[N_SOUNDS];
    bool soundsOn;
    float sfxVol;
    
    // MUSIC
    void setupMusic();
    void drawMusic();
    ofSoundPlayer music;
    bool musicOn;
    float musicVol;
    
    // COMICWORDS
    void setupComicWords();
    void drawComicWords();
    ofImage comic[N_IMAGES];
    bool comicSelector;
    bool comicOn;
    bool comic0;
    bool comic1;
    bool comic2;
    bool comic3;
    int comicXpos, comicYpos, comicZpos;
    int comicFade;
    float comicA0, comicA1, comicA2, comicA3;
    float comicAlpha;
    
    // BACKGROUND
    void setupBackground();
    void drawBackground();
    ofImage bgImage;
    bool bgOn;
    
    // SCORE
    void updateScore();
    void drawScore();
    ofTrueTypeFont font;
    bool comboOn;
    bool scoreHide;
    bool scorePlus;
    int frame;
    int frame100;
    float scoreCount;
    float combo;
    float totalScore;
    float comboScore;
};
