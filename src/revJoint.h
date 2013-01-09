// created by René Christen and found on the openFrameworks Forum
// http://forum.openframeworks.cc/index.php?topic=3411.0
// http://renechristen.net/
//
// thank you !!!
//

#pragma once
//based on Todd Vanderlin's ofxBox2dJoint class

class revJoint {
	
public:
	
	b2World * world;
	b2Joint * joint;
	bool alive;
	b2RevoluteJointDef jd;
	
	revJoint() {
		world = NULL;
		alive = false;
	}
	
	void setWorld(b2World * w) {
		if(w == NULL) {
			ofLog(OF_LOG_NOTICE, "- box2d world needed -");
			return;
		}
		world = w;
		alive = true;
	}
	
	void destroyJoint() {
		world->DestroyJoint(joint);
		joint = NULL;
	}
	
	void addJoint(b2Body * a, b2Body * b, float stiffness=3.0f, float damping=0.6f, int Xoffset=0, int Yoffset=0 ) {
		
		if(world == NULL) {
			ofLog(OF_LOG_NOTICE, "- no joint added - box2d world needed -");
			return;
		}
        
		b2Vec2 anchor = a->GetWorldCenter();
		jd.Initialize(a, b, anchor);
		//need to override anchor set in Initialize() if you don't want the anchor to be in b2Body a's center
		//(due to reasons I can't figure out!)
		
		jd.collideConnected = false;
		jd.lowerAngle = -PI/8;
		jd.upperAngle = PI/8;
		jd.enableLimit = true;
		jd.maxMotorTorque = 1000.0;
		jd.motorSpeed = PI*2;
		jd.enableMotor = false;
		
		joint = world->CreateJoint(&jd);
	}
	
	void draw(int alpha=200) {
		
		if(!alive) return;
		
		ofEnableAlphaBlending();
		ofSetColor(255, 0, 255, alpha);
		
		b2Vec2 p1 = joint->GetAnchorA();
		b2Vec2 p2 = joint->GetAnchorB();
		
		p1 *= OFX_BOX2D_SCALE;
		p2 *= OFX_BOX2D_SCALE;
		ofLine(p1.x, p1.y, p2.x, p2.y);
		ofDisableAlphaBlending();
	}
};
