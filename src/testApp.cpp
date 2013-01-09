//--------------------------------------------------------------
//
//      BBDO WINTER 2012 INSTALLATION
//
//      Created by Mathias Appelblad, Sermad Buni, Jason Walters, and Michael Enerva
//      Developed by Jason Walters
//      Artwork by Michael Enerva
//
//      All artwork is property of BBDO and can not be used
//      for commercial use.  Thank you!
//
//      Last revision by Jason Walters on January 9th, 2013
//      Compatible with openFrameworks 0073, written on a Mac.
//
//
//      HOW TO USE
//      * define your display resolution in main.cpp
//
//      * when running - press spacebar to access GUI
//                     - press / to toggle fullscreen
//                     - use GUI POSITION(s) to adjust objects on screen
//
//--------------------------------------------------------------

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetVerticalSync(true); // helps with display jerkiness. but could case potential issues with Kinect & FPS ???
    // Github issue: https://github.com/openframeworks/openFrameworks/issues/1292
    // OF Forum:  http://forum.openframeworks.cc/index.php/topic,9919.msg45469.html#msg45469
    
    ofBackground(255, 255, 255);    //sets the background to white
    ofSetLogLevel(OF_LOG_VERBOSE);  //sets the log level to verbose
    ofToggleFullscreen();
    
    setupGUI();         // gui setup
    setupKinect();      // kinect setup
    setupBox2d();       // box2d setup
    setupAvatar();      // avatar setup
    setupSnow();        // snow setup
    setupSmoke();       // smoke setup
    setupClouds();      // clouds setup
    setupComicWords();  // comicwords setup
    setupSounds();      // sounds setup
    setupMusic();       // music setup
    setupBackground();  // background setup
    
    font.loadFont("fonts/HouseHoliday-Sans.otf", 60);
}

//--------------------------------------------------------------
void testApp::setupBackground() {
    bgImage.loadImage("body/world.png");
}

//--------------------------------------------------------------
void testApp::setupGUI() {
    gui.setup();
    
    gui.addTitle("KINECT");
    gui.addContent("threshCam", grayImage);
    gui.addSlider("nearThresh", nearThreshold, 0, 255);
    gui.addSlider("farThresh", farThreshold, 0, 255);
    gui.addTitle("");  // creates a blank space
    gui.addToggle("openCVThresh", bThreshWithOpenCV);
    gui.addToggle("depthNearWhite", depthWhite);
    gui.addTitle("");  // creates a blank space
    gui.addSlider("camera tilt", angle, -30, 30);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("MUSIC");
    gui.addSlider("music volume", musicVol, 0.0, 0.75);
    
    gui.addTitle("LAYERS").setNewColumn(true);
    gui.addToggle("0 background", bgOn);
    gui.addToggle("1 snow", snowOn);
    gui.addToggle("2 smoke", smokeOn);
    gui.addToggle("3 clouds", cloudsOn);
    gui.addToggle("4 contours", contoursOn);
    gui.addToggle("5 snowman", avatarOn);
    gui.addToggle("6 comic bubbles", comicOn);
    gui.addToggle("7 sounds", soundsOn);
    gui.addToggle("8 joints", jointsOn);
    
    gui.addTitle("POSITION WORLD").setNewColumn(true);
    gui.addSlider("world x", xWorld, -2560, 2560);
    gui.addSlider("world y", yWorld, -1440, 1440);
    gui.addSlider("world z", zWorld, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("POSITION OBJECTS").setNewColumn(true);
    gui.addSlider("snowman x", avatarXpos, -2560, 2560);
    gui.addSlider("snowman y", avatarYpos, -1440, 1440);
    gui.addSlider("snowman z", avatarZpos, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    gui.addSlider("contour x", contourXpos, -2560, 2560);
    gui.addSlider("contour y", contourYpos, -1440, 1440);
    gui.addSlider("contour z", contourZpos, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    gui.addSlider("snow x", snowXpos, -2560, 2560);
    gui.addSlider("snow y", snowYpos, -1440, 1440);
    gui.addSlider("snow z", snowZpos, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    gui.addSlider("smoke x", smokeXpos, -2560, 2560);
    gui.addSlider("smoke y", smokeYpos, -1440, 1440);
    gui.addSlider("smoke z", smokeZpos, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    gui.addSlider("clouds x", cloudsXpos, -2560, 2560);
    gui.addSlider("clouds y", cloudsYpos, -1440, 1440);
    gui.addSlider("clouds z", cloudsZpos, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    gui.addSlider("comic x", comicXpos, -2560, 2560);
    gui.addSlider("comic y", comicYpos, -1440, 1440);
    gui.addSlider("comic z", comicZpos, -1000, 1000);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("SNOW").setNewColumn(true);
    gui.addSlider("snow amount", snowAmt, 1, 200);
    gui.addSlider("snow frequency", snowFreq, 1, 200);
    gui.addSlider("snow max size", snowMaxSize, 1, 50);
    gui.addSlider("snow speed", snowSpeed, 0, 2);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("SMOKE");
    gui.addSlider("smoke amount", smokeAmt, 1, 200);
    gui.addSlider("smoke frequency", smokeFreq, 1, 200);
    gui.addSlider("smoke max size", smokeMaxSize, 1, 50);
    gui.addSlider("smoke speed", smokeSpeed, 0, 2);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("CLOUDS");
    gui.addSlider("clouds amount", cloudsAmt, 1, 1);
    gui.addSlider("clouds frequency", cloudsFreq, 1, 10);
    gui.addSlider("clouds size", cloudsMaxSize, 1, 8);
    gui.addSlider("clouds speed", cloudsSpeed, 0, 2);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("COMIC BUBBLES");
    gui.addSlider("comic fade", comicFade, 1, 20);
    gui.addTitle("");  // creates a blank space
    
    gui.addTitle("SNOWMAN");
    gui.addSlider("reverse gravity", avatarGravity, 0, 1000);
    gui.addTitle("");  // creates a blank space
    
    gui.loadFromXML();  // loads file "/bin/data/_settings.xml"
}

//--------------------------------------------------------------
void testApp::setupKinect() {
    kinect.setRegistration(true);   // enable depth->video image calibration
    
	kinect.init();
	kinect.open();
	
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
    
	kinect.setCameraTiltAngle(angle);
    kinect.enableDepthNearValueWhite(depthWhite);
}

//--------------------------------------------------------------
void testApp::setupBox2d() {
    
    // register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
    
    // AVATAR
    box2d.init();
    box2d.setGravity(0, -300);    // strong reverse gravity to keep avatar upright
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
    box2d.setIterations(8, 10);
    
    // SNOW
    box2dSnow.init();
    box2dSnow.setGravity(0, 1);    // slight gravity for the snowflakes
	box2dSnow.setFPS(60.0);
    box2dSnow.setIterations(8, 10);
    
    // SMOKE
    box2dSmoke.init();
    box2dSmoke.setGravity(0, -2);  // slight reverse gravity for the smoke
	box2dSmoke.setFPS(60.0);
    box2dSmoke.setIterations(8, 10);
    
    // CLOUDS
    box2dClouds.init();
    box2dClouds.setGravity(0.5, 0);  // slight pull-to-right for the clouds
	box2dClouds.setFPS(60.0);
    box2dClouds.setIterations(8, 10);
}

//--------------------------------------------------------------
void testApp::setupSounds() {
	// load the sounds into an array
	for (int i=0; i<N_SOUNDS; i++) {
		sound[i].loadSound("sfx/"+ofToString(i)+".mp3");
		sound[i].setMultiPlay(false);
		sound[i].setLoop(false);
	}
}

//--------------------------------------------------------------
void testApp::setupMusic() {
    music.loadSound("music/sleighbells.wav");
    music.setLoop(true);
    music.play();
    music.setVolume(musicVol);
}

//--------------------------------------------------------------
void testApp::setupComicWords() {
    
	// load the 4 comic bubble images into an array
	for (int i=0; i<N_IMAGES; i++) {
		comic[i].loadImage("comic/"+ofToString(i)+".png");
	}
}

//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) {
		
		// if we collide with the ground we do not
		// want to play a sound. this is how you do that
		if(e.a->GetType() == b2Shape::e_polygon && e.b->GetType() == b2Shape::e_polygon) {
			
			SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
			SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
			
			if(aData) {
				aData->bHit = true;
                if (soundsOn) {
                    sound[aData->soundID].play();
                    sound[aData->soundID].setVolume(0.75f);
                    
                    headHit = true;  // change avatar head to head-hit
                    comicSelector = true;
                    
                    scorePlus = true;
                }
                
			}
			
			if(bData) {
				bData->bHit = true;
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
		
		SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
		SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
		
		if(aData) {
			aData->bHit = false;
            
            headHit = false;  // change avatar head to head-hit
            comicSelector = false;
            scorePlus = false;
		}
		
		if(bData) {
			bData->bHit = false;
		}
	}
}

//--------------------------------------------------------------
void testApp::setupSnow() {
    
    // snowflake texture
    iSnow.loadImage("snowflake/snowflake.png");
}

//--------------------------------------------------------------
void testApp::setupSmoke() {
    // smoke texture
    iSmoke.loadImage("smoke/smoke.png");
}

//--------------------------------------------------------------
void testApp::setupClouds() {
    // cloud texture
    iClouds.loadImage("clouds/clouds.png");
}

//--------------------------------------------------------------
void testApp::setupAvatar() {
    // snowman body parts textures
    iHead.loadImage("body/body1.png");
    iBody.loadImage("body/body2.png");
    iBase.loadImage("body/body3.png");
    iLArm.loadImage("body/leftarm.png");
    iRArm.loadImage("body/rightarm.png");
    
    // head texture when hit
    iHeadHit.loadImage("body/body1_hit.png");
    
    // setup box2d objects
    for (int i=0; i<1; i++) {
        // Head
        ofxBox2dRect rHead;
        rHead.setPhysics(3.0, 0.53, 0.1);
        rHead.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2-420, 151,197);
        b2Filter filter0;
        filter0.categoryBits = 0x0002;
        filter0.maskBits = 0x0004;
        filter0.groupIndex = -2;
        rHead.setFilterData(filter0);
        rHead.setData(new SoundData());
        SoundData * sd1 = (SoundData*)rHead.getData();
        sd1 = (SoundData*)rHead.getData();
        sd1->soundID = ofRandom(0, N_SOUNDS);
        sd1->bHit	= false;
        rectHead.push_back(rHead);
        
        // Body
        ofxBox2dRect rBody;
        rBody.setPhysics(3.0, 0.53, 0.1);
        rBody.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2-100, 178,169);
        b2Filter filter1;
        filter1.categoryBits = 0x0002;
        filter1.maskBits = 0x0004;
        filter1.groupIndex = -2;
        rBody.setFilterData(filter1);
        rBody.setData(new SoundData());
        SoundData * sd2 = (SoundData*)rBody.getData();
        sd2->soundID = ofRandom(0, N_SOUNDS);
        sd2->bHit	= false;
        rectBody.push_back(rBody);
        
        // Base
        ofxBox2dRect rBase;
        rBase.setPhysics(3.0, 0.53, 0.1);
        rBase.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2+220, 251, 231);
        rectBase.push_back(rBase);
        
        // Left Arm
        ofxBox2dRect rLArm;
        rLArm.setPhysics(3.0, 0.53, 0.1);
        rLArm.setup(box2d.getWorld(), ofGetWidth()/2-320, ofGetHeight()/2-100, 59,216);
        rectLArm.push_back(rLArm);
        
        // Right Arm
        ofxBox2dRect rRArm;
        rRArm.setPhysics(3.0, 0.53, 0.1);
        rRArm.setup(box2d.getWorld(), ofGetWidth()/2+320, ofGetHeight()/2-100, 43,217);
        rectRArm.push_back(rRArm);
        
        // Suspension node - bottom left
        ofxBox2dRect bLeft;
        bLeft.setPhysics(0, 0, 0);
        bLeft.setup(box2d.getWorld(), ofGetWidth()/2-50, ofGetHeight(), 20, 20);
        bottomLeft.push_back(bLeft);
        
        // Suspension node - bottom right
        ofxBox2dRect bRight;
        bRight.setPhysics(0, 0, 0);
        bRight.setup(box2d.getWorld(), ofGetWidth()/2+50, ofGetHeight(), 20, 20);
        bottomRight.push_back(bRight);
    }
    
    // Hinge Joints
    revjointAvatar.setWorld(box2d.getWorld());
    revjointAvatar.addJoint(rectHead[0].body, rectBody[0].body);
    revjointAvatar.addJoint(rectBase[0].body, rectBody[0].body);
    revjointAvatar.addJoint(rectLArm[0].body, rectBody[0].body);
    revjointAvatar.addJoint(rectRArm[0].body, rectBody[0].body);
    
    // Suspension Joint - bottom left to base
    ofxBox2dJoint joint1;
    joint1.setup(box2d.getWorld(), rectBase[0].body, bottomLeft[0].body);
    joint1.setLength(300);
    joints.push_back(joint1);
    
    ofxBox2dJoint joint2;
    joint2.setup(box2d.getWorld(), rectBase[0].body, bottomRight[0].body);
    joint2.setLength(300);
    joints.push_back(joint2);
}

//--------------------------------------------------------------
void testApp::update() {
    updateGUI();        // gui update
    updateKinect();     // kinect update
    updateContours();   // contours update
    updateBox2d();      // box2d update
    updateSnow();       // snow update
    updateSmoke();      // smoke update
    updateClouds();     // clouds update
    updateScore();      // score update
}

//--------------------------------------------------------------
void testApp::updateKinect() {
    kinect.update();
    kinect.setCameraTiltAngle(angle);
    kinect.enableDepthNearValueWhite(depthWhite);
    
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        grayImage.mirror(false, true);
        
		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		} else {
			
			// or we do it ourselves - show people how they can work with the pixels
			unsigned char * pix = grayImage.getPixels();
			
			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}
		}
		
		// update the cv images
		grayImage.flagImageChanged();
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
	}
}

//--------------------------------------------------------------
void testApp::updateBox2d() {
    box2d.update();
    box2d.setGravity(0, -avatarGravity);
    
    box2dSnow.update();
    float xGrav1 = 40 * sin(ofSignedNoise(ofGetElapsedTimeMillis()*0.2));
    box2dSnow.setGravity(xGrav1, snowSpeed);
    
    box2dSmoke.update();
    float yGrav1 = 20 * sin(ofSignedNoise(ofGetElapsedTimeMillis()*0.2));
    box2dSmoke.setGravity(yGrav1, -smokeSpeed);
    
    box2dClouds.update();
    float xGrav2 = 40 * sin(ofSignedNoise(ofGetElapsedTimeMillis()*0.2));
    box2dClouds.setGravity(cloudsSpeed, 0);
}

//--------------------------------------------------------------
void testApp::updateContours() {
    // IDEO example - thank you for sharing!!!
    triangle.clear();
    
    for (int i = 0; i < contourFinder.nBlobs; i++) {
        triangle.triangulate(contourFinder.blobs[i], max( 3.0f, (float)contourFinder.blobs[i].pts.size()/12));
	}
    
    for (int i = body.size() - 1; i >= 0; i--) {
        box2d.world->DestroyBody(body[i].body);
    }
    
    body.clear();
    
	// triangulate contour in order to add to box2d
	ofxTriangleData* tData;
	for (int i=triangle.triangles.size()-1; i>=0; i--) {
		
		tData = &triangle.triangles[i];
		
		ofxBox2dPolygon poly;
		
		ofPoint t1,t2,t3;
		
		t1.x=ofMap(tData->a.x, 0, grayImage.width, 0, ofGetWidth());
		t1.y=ofMap(tData->a.y, 0, grayImage.height, 0, ofGetHeight());
		t2.x = ofMap(tData->b.x, 0, grayImage.width, 0, ofGetWidth());
		t2.y=ofMap(tData->b.y, 0, grayImage.height, 0, ofGetHeight());
		
		t3.x = ofMap(tData->c.x, 0, grayImage.width, 0, ofGetWidth());
		t3.y = ofMap(tData->c.y, 0, grayImage.height, 0, ofGetHeight());
		
		poly.addVertex(t1.x,t1.y);
		poly.addVertex(t2.x,t2.y);
		poly.addVertex(t3.x,t3.y);
        
        poly.create(box2d.world);
		
        b2Filter filter;
        filter.categoryBits = 0x0004;
        filter.maskBits = 0x0002;
        filter.groupIndex = 1;
        poly.setFilterData(filter);
        
        body.push_back(poly);
	}
}

//--------------------------------------------------------------
void testApp::updateGUI() {
    // nothing currently need here...
}

//--------------------------------------------------------------
void testApp::updateSnow() {
    // setup box2d objects
    if (snowOn) {
        float ranSize = ofRandom(snowMaxSize);
        
        if((int)ofRandom(0, snowFreq) == 0) {
            ofxBox2dRect sFlake;
            sFlake.setPhysics(1, 0.5, 0.9);
            sFlake.setup(box2dSnow.getWorld(), ofRandomWidth(), 0, ranSize, ranSize);
            b2Filter filter20;
            filter20.categoryBits = 0x0002;
            filter20.maskBits = 0x0004;
            filter20.groupIndex = -2;
            sFlake.setFilterData(filter20);
            snowFlakes.push_back(sFlake);
        }
        //KILL snokwFlakes if greater than snowAmt
        if (snowFlakes.size()>snowAmt){
            snowFlakes.erase(snowFlakes.begin());
            snowFlakes[0].destroy();
        }
    }
    else {
        if (snowFlakes.size()>0){
            snowFlakes.erase(snowFlakes.begin());
            snowFlakes[0].destroy();
        }
    }
}

//--------------------------------------------------------------
void testApp::updateSmoke() {
    if (smokeOn) {
        float ranSize = ofRandom(smokeMaxSize);
        
        if((int)ofRandom(0, smokeFreq) == 0) {
            ofxBox2dRect sSmoke;
            sSmoke.setPhysics(1, 0.5, 0.9);
            sSmoke.fixture;
            sSmoke.setup(box2dSmoke.getWorld(), 740, 820, ranSize, ranSize);
            smoke.push_back(sSmoke);
        }
        //KILL smoke if greater than smokeAmt
        if (smoke.size()>smokeAmt){
            smoke.erase(smoke.begin());
            smoke[0].destroy();
        }
    }
    else {
        if (smoke.size()>0){
            smoke.erase(smoke.begin());
            smoke[0].destroy();
        }
    }
}

//--------------------------------------------------------------
void testApp::updateClouds() {
    if (cloudsOn) {
        float cloudsSize = ofMap(cloudsMaxSize, 1, 10, 10, 1);
        
        if (clouds.size() < cloudsAmt) {
            if((int)ofRandom(0, cloudsFreq) == 0) {
                ofxBox2dRect cClouds;
                cClouds.setPhysics(1, 0.5, 0.9);
                cClouds.setup(box2dClouds.getWorld(), -200, ofRandom(60, 240), 615/cloudsSize, 313/cloudsSize);
                clouds.push_back(cClouds);
            }
        }
        //KILL clouds if off-screen
        for (int i = 0; i < clouds.size(); i++) {
            if (clouds[i].getPosition().x > ofGetWidth()+300){
                clouds.erase(clouds.begin());
                clouds[0].destroy();
            }
        }
        
        if ((int)clouds[0].getPosition().x == ofGetWidth()/2) {
            ofxBox2dRect cClouds2;
            cClouds2.setPhysics(1, 0.5, 0.9);
            cClouds2.setup(box2dClouds.getWorld(), -200, ofRandom(60,240), 615/cloudsSize, 313/cloudsSize);
            clouds2.push_back(cClouds2);
        }
        
        //KILL clouds if off-screen
        for (int i = 0; i < clouds2.size(); i++) {
            if (clouds2[i].getPosition().x > ofGetWidth()+300){
                clouds2.erase(clouds2.begin());
                clouds2[0].destroy();
            }
        }
    }
    else {
        if (clouds.size()>0){
            clouds.erase(clouds.begin());
            clouds[0].destroy();
        }
        if (clouds2.size()>0){
            clouds2.erase(clouds2.begin());
            clouds2[0].destroy();
        }
    }
}

//--------------------------------------------------------------
void testApp::updateScore() {
    
    frame += (ofGetFrameNum() * 0) + 1;
    frame100 += (ofGetFrameNum() * 0) + 1;
    
    if (frame > 12) {
        frame = 0;
    }
    
    if (frame100 > 50) {
        frame100 = 0;
    }
    
    if (scoreCount < 1) {
        combo *= 1;
    }
    if (scoreCount > 1) {
        combo *= 2;
    }
    
    if (combo > 100) {
        combo = 2;
    }
    
    if (frame == 10) {
        if (scorePlus) {
            combo = combo * 2;
            totalScore = totalScore + combo;
            scorePlus = false;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    
    //draw layers
    drawBackground();   // draw background
    drawSnow();         // draw snowflakes
    drawSmoke();        // draw chimney smoke
    drawClouds();       // draw clouds
    
    ofPushMatrix();
    ofTranslate(xWorld, yWorld, zWorld);
    drawContours();     // draw user's contours
    drawAvatar();       // draw snowman
    drawComicWords();   // draw comicWords
    ofPopMatrix();
    
    drawMusic();        // draw music
    drawScore();        // draw score
    
    // ofPopMatrix();
    
    gui.draw();         // draw gui
}

//--------------------------------------------------------------
void testApp::drawMusic() {
    music.setVolume(musicVol);
}

//--------------------------------------------------------------
void testApp::drawBackground() {
    if (bgOn) {
        ofSetColor(255, 255, 255);
        bgImage.draw(0, 0, ofGetWidth(), ofGetHeight()); // draw background world
    }
}

//--------------------------------------------------------------
void testApp::drawContours(){
    if (contoursOn) {
        ofPushMatrix();
        ofTranslate(contourXpos, contourYpos, contourZpos);
        int numBlobs = contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, true);
        
        //reset score to zero if there are no blobs...after 10 frames.
        if (numBlobs <= 0) {
            if (frame100 > 49) {
                scoreCount = 0;
                combo = 2;
            }
        }
        
        for(int i=0;i<6;i++){
            if(numBlobs > 0){
                for(int j=0;j<numBlobs;j++){
                    
                    // lets get out the contour data
                    int length_of_contour = contourFinder.blobs[j].pts.size();
                    
                    // clear the old contours
                    contourRough.clear();
                    contourRough.assign(length_of_contour, ofPoint());
                    contourSmooth.clear();
                    contourSmooth.assign(length_of_contour, ofPoint());
                    
                    // lets make a copy for ourselves
                    for(int k = 0; k < length_of_contour; k++){
                        contourRough[k] = contourFinder.blobs[j].pts[k];
                    }
                    
                    contourSimp.simplify(contourRough, contourSmooth, 0.005*i);
                    
                    ofPushMatrix();
                    ofSetLineWidth(0.25);
                    ofEnableAlphaBlending();
                    ofSetColor(255,255,255,45);
                    ofBeginShape();
                    for(int i = 0; i < contourSmooth.size(); i++){
                        float xC = ofMap(contourSmooth[i].x, 0, 640, 0, ofGetWidth());
                        float yC = ofMap(contourSmooth[i].y, 0, 480, 0, ofGetHeight());
                        
                        ofVertex(xC,yC);
                    }
                    ofEndShape(true);
                    ofDisableAlphaBlending();
                    ofPopMatrix();
                    
                    ofPushMatrix();
                    ofSetLineWidth(12);
                    ofEnableAlphaBlending();
                    ofSetColor(74,255,255,45);
                    
                    ofNoFill();
                    ofBeginShape();
                    for(int i = 0; i < contourSmooth.size(); i++){
                        float xC = ofMap(contourSmooth[i].x, 0, 640, 0, ofGetWidth());
                        float yC = ofMap(contourSmooth[i].y, 0, 480, 0, ofGetHeight());
                        
                        ofVertex(xC,yC);
                    }
                    ofEndShape(true);
                    ofFill();
                    ofDisableAlphaBlending();
                    ofPopMatrix();
                }
            }
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::drawAvatar() {
    
    // avatar suspension joints
    if (jointsOn) {
        ofSetColor(0,100,255,76);
        ofSetLineWidth(2);
        for (int i = 0; i < joints.size(); i++) {
            joints[i].draw();
        }
    }
    
    // avatar body parts
    if (avatarOn) {
        ofPushMatrix();
        ofTranslate(avatarXpos, avatarYpos, avatarZpos);
        ofEnableAlphaBlending();
        
        // left arm texture - maps left arm image to box2d shape
        ofPushMatrix();
        ofSetColor(0, 0, 0);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofTranslate(rectLArm[0].getPosition().x, rectLArm[0].getPosition().y-40, 0);
        ofRotate(rectLArm[0].getRotation()+60);
        iLArm.draw(-rectLArm[0].getWidth()+70, -rectLArm[0].getHeight(), rectLArm[0].getWidth()*2, rectLArm[0].getHeight()*2);
        ofPopMatrix();
        
        // right arm texture - maps right arm image to box2d shape
        ofPushMatrix();
        ofSetColor(0, 0, 0);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofTranslate(rectRArm[0].getPosition().x, rectRArm[0].getPosition().y-40, 0);
        ofRotate(rectRArm[0].getRotation()-60);
        iRArm.draw(-rectRArm[0].getWidth()-70, -rectRArm[0].getHeight(), rectRArm[0].getWidth()*2, rectRArm[0].getHeight()*2);
        ofPopMatrix();
        
        // base texture - maps base image to box2d shape
        ofPushMatrix();
        ofSetColor(255, 255, 255);
        ofTranslate(rectBase[0].getPosition().x, rectBase[0].getPosition().y, 0);
        ofRotate(rectBase[0].getRotation());
        iBase.draw(-rectBase[0].getWidth(), -rectBase[0].getHeight(), rectBase[0].getWidth()*2, rectBase[0].getHeight()*2);
        ofPopMatrix();
        
        // body texture - maps body image to box2d shape
        ofPushMatrix();
        ofSetColor(255, 255, 255);
        ofTranslate(rectBody[0].getPosition().x, rectBody[0].getPosition().y, 0);
        ofRotate(rectBody[0].getRotation());
        iBody.draw(-rectBody[0].getWidth(), -rectBody[0].getHeight(), rectBody[0].getWidth()*2, rectBody[0].getHeight()*2);
        ofPopMatrix();
        
        // head texture - maps head image to box2d shape
        if (headHit) {
            ofPushMatrix();
            ofSetColor(255, 255, 255);
            ofTranslate(rectHead[0].getPosition().x, rectHead[0].getPosition().y, 0);
            ofRotate(rectHead[0].getRotation());
            iHeadHit.draw(-rectHead[0].getWidth(), -rectHead[0].getHeight(), rectHead[0].getWidth()*2, rectHead[0].getHeight()*2);
            ofPopMatrix();
        } else {
            ofPushMatrix();
            ofSetColor(255, 255, 255);
            ofTranslate(rectHead[0].getPosition().x, rectHead[0].getPosition().y, 0);
            ofRotate(rectHead[0].getRotation());
            iHead.draw(-rectHead[0].getWidth(), -rectHead[0].getHeight(), rectHead[0].getWidth()*2, rectHead[0].getHeight()*2);
            ofPopMatrix();
        }
        
        ofDisableAlphaBlending();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::drawSnow() {
    if (snowOn) {
        ofPushMatrix();
        ofTranslate(snowXpos, snowYpos, snowZpos);
        for (int i = 0; i < snowFlakes.size(); i++) {
            // base texture - maps base image to box2d shape
            ofPushMatrix();
            ofEnableAlphaBlending();
            ofSetColor(255, 255, 255);
            ofTranslate(snowFlakes[i].getPosition().x, snowFlakes[i].getPosition().y, 0);
            ofRotate(snowFlakes[i].getRotation());
            iSnow.draw(-snowFlakes[i].getWidth(), -snowFlakes[i].getHeight(), snowFlakes[i].getWidth()*2, snowFlakes[i].getHeight()*2);
            ofDisableAlphaBlending();
            ofPopMatrix();
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::drawSmoke() {
    if (smokeOn) {
        ofPushMatrix();
        ofTranslate(smokeXpos, smokeYpos, smokeZpos);
        for (int i = 0; i < smoke.size(); i++) {
            // base texture - maps base image to box2d shape
            ofPushMatrix();
            ofEnableAlphaBlending();
            ofSetColor(255, 255, 255, 75);
            ofTranslate(smoke[i].getPosition().x, smoke[i].getPosition().y, 0);
            ofRotate(smoke[i].getRotation());
            iSmoke.draw(-smoke[i].getWidth(), -smoke[i].getHeight(), smoke[i].getWidth()*2, smoke[i].getHeight()*2);
            ofDisableAlphaBlending();
            ofPopMatrix();
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::drawClouds() {
    
    if (cloudsOn) {
        ofPushMatrix();
        ofTranslate(cloudsXpos, cloudsYpos, cloudsZpos);
        for (int i = 0; i < clouds.size(); i++) {
            ofPushMatrix();
            ofEnableAlphaBlending();
            ofSetColor(255, 255, 255, 75);
            ofTranslate(clouds[i].getPosition().x, clouds[i].getPosition().y, 0);
            iClouds.draw(-clouds[i].getWidth(), -clouds[i].getHeight(), clouds[i].getWidth()*2, clouds[i].getHeight()*2);
            ofDisableAlphaBlending();
            ofPopMatrix();
        }
        for (int i = 0; i < clouds2.size(); i++) {
            ofPushMatrix();
            ofEnableAlphaBlending();
            ofSetColor(255, 255, 255, 75);
            ofTranslate(clouds2[i].getPosition().x, clouds2[i].getPosition().y, 0);
            iClouds.draw(-clouds2[i].getWidth(), -clouds2[i].getHeight(), clouds2[i].getWidth()*2, clouds2[i].getHeight()*2);
            ofDisableAlphaBlending();
            ofPopMatrix();
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::drawComicWords() {
    
    if (comicOn) {
        if (comicSelector) {
            drawMethod = (int)ofRandom(0, 30);
            comicSelector = false;
        }
        
        ofPushMatrix();
        ofTranslate(comicXpos, comicYpos, comicZpos);
        ofSetColor(255, 255, 255, comicAlpha);
        ofEnableAlphaBlending();
        //graphic modes
        switch (drawMethod) {
            case 0:
                comic0 = true;
                comic1 = false;
                comic2 = false;
                comic3 = false;
                break;
            case 1:
                comic1 = true;
                comic0 = false;
                comic2 = false;
                comic3 = false;
                break;
            case 2:
                comic2 = true;
                comic1 = false;
                comic0 = false;
                comic3 = false;
                break;
            case 3:
                comic3 = true;
                comic1 = false;
                comic2 = false;
                comic0 = false;
                break;
        }
        
        if (comic0) {
            
            ofSetColor(255, 255, 255, comicA0);
            comic[0].draw(rectHead[0].getPosition().x + 200, rectHead[0].getPosition().y + 100);
            comicA0-=comicFade;
            if (comicA0 <= 0) {
                comicA0 = 0;
                comic0 = false;
            }
        }
        else {
            comicA0 = 255;
        }
        
        if (comic1) {
            ofSetColor(255, 255, 255, comicA1);
            comic[1].draw(rectHead[0].getPosition().x - 400, rectHead[0].getPosition().y - 100);
            comicA1-=comicFade;
            if (comicA1 <= 0) {
                comicA1 = 0;
                comic1 = false;
            }
        }
        else {
            comicA1 = 255;
        }
        
        if (comic2) {
            ofSetColor(255, 255, 255, comicA2);
            comic[2].draw(rectHead[0].getPosition().x + 200, rectHead[0].getPosition().y - 100);
            comicA2-=comicFade;
            if (comicA2 <= 0) {
                comicA2 = 0;
                comic2 = false;
            }
        }
        else {
            comicA2 = 255;
        }
        
        if (comic3) {
            ofSetColor(255, 255, 255, comicA3);
            comic[3].draw(rectHead[0].getPosition().x - 400, rectHead[0].getPosition().y + 100);
            comicA3-=comicFade;
            if (comicA3 <= 0) {
                comicA3 = 0;
                comic3 = false;
            }
        }
        else {
            comicA3 = 255;
        }
        
        ofDisableAlphaBlending();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::drawScore() {
    
    if (!scoreHide) {   // display score when not in GUI
        ofSetColor(0, 0, 0);
        font.drawString("TOTAL SCORE " + ofToString(totalScore), 100,100);
        
        ofSetColor(255, 0, 0);
        font.drawString("COMBO " + ofToString(combo), 270,160);
    }
}

//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0);
	kinect.close();
    gui.saveToXML(); // saves "/bin/data/_settings.xml"
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
        case ' ':
            gui.toggleDraw();
            scoreHide = !scoreHide; // show score in game, hide in gui
            break;
        case '/':
            ofToggleFullscreen();
            break;
		case 't':
			bThreshWithOpenCV = !bThreshWithOpenCV;
			break;
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
			
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
            
        case '[': gui.prevPage(); break;
        case ']': gui.nextPage(); break;
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}
