#pragma once

#include "ofMain.h"
#include "particle.h"
#include <ofPolyline.h>
#include <ctime>

class ofApp : public ofBaseApp {

public:
	// Attributes
	vector<Particle> myParticles_;
	float theta_;
	vector<ofPolyline> myLines_;
	std::clock_t previousTime_;
	float deltaTime_;
	bool isHudDisplayed_ = false;
	int type_ = 1;

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
