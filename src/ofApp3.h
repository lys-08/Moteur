#pragma once

#include "ofMain.h"
#include "rigidBody.h"
#include "physics.h"
#include <ofPolyline.h>
#include <ctime>

class ofApp3 : public ofBaseApp {

public:
	// Attributes
	Physics physics;
	float theta_;
	std::clock_t previousTime_;
	float deltaTime_;
	int rigidBodyType_ = 1;
	int simpleForceType_ = 1;

	float mouseX_;
	float mouseY_;


	// Methods
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void SpawnRigidBody(int type);

};
