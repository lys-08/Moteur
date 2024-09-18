#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	Particle p(Vector3d(500, -500), Vector3d(1, 1), 20);
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (auto& particle : myParticles)
	{
		particle.move();
	}


	box.setWidth(300);
	box.setPosition(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::draw()
{

	ofTranslate(0, ofGetHeight(), 0);
	ofPushMatrix();

	ofRotateZDeg(rotationAngle);
	ofSetColor(255);
	ofDrawRectangle(0, -25, 75, 50);

	ofPopMatrix();

	for (auto& particle : myParticles)
	{
		particle.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	float angleZ = atan2(y - ofGetHeight(), x);

	rotationAngle = ofRadToDeg(angleZ);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	switch (button)
	{
	case 0:
		SpawnParticle();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

//--------------------------------------------------------------

/**
 * @brief Make spawn a particle
 *
 * @return nothing
*/
void ofApp::SpawnParticle()
{
	Particle newParticule(
		Vector3d(0, 0),
		Vector3d(ofGetMouseX(), ofGetMouseY(), 0),
		5
	);

	myParticles.push_back(newParticule);
}