#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ParticleSphericalCollisionGenerator.h"
#include "ParticleStraightCable.h"
#include "ParticleCable.h"
#include "particleContact.h"
#include "World.h"
#include "particleSetSpring.h"
#include <ofPolyline.h>
#include <ctime>

class ofApp2 : public ofBaseApp {

public:
	// Attributes
	std::clock_t previousTime_;
	float deltaTime_;

	World world;

	float mouseX_;
	float mouseY_;
	bool hasStarted = false;


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

};