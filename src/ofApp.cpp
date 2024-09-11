#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	box.set(500);
	Particle p(Vector3d(500, 500), Vector3d(1, 1), 20);
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (auto& particle : myParticles)
	{
		particle.move();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	
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
		Vector3d(500, 500),
		Vector3d(ofRandom(-2, 2), ofRandom(-2, 2)),
		20
	);

	myParticles.push_back(newParticule);
}

// TEST COMMENTAIRE