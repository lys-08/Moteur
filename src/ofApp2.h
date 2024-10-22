#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ParticleSphericalCollisionGenerator.h"
#include "ParticleStraightCable.h"
#include "ParticleCable.h"
#include "particleContact.h"
#include "World.h"
#include <ofPolyline.h>
#include <ctime>

class ofApp2 : public ofBaseApp {

public:
	// Attributes
	vector<Particle*> myParticles_;
	float theta_;
	vector<ofPolyline> myLines_;
	std::clock_t previousTime_;
	float deltaTime_;
	bool isHudDisplayed_ = false;
	int type_ = 1;

	ParticleSphericalCollisionGenerator collision;
	vector<ParticleContact> contacts;

	ParticleStraightCable* collisionRod;
	ParticleCable* collisionCable;

	World world;

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

	void SpawnParticle(int type);

};