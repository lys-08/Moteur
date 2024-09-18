#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	box.set(500);
	previousTime = std::clock();
	//Particle p(Vector3d(500, 500), Vector3d(1, 1), 20);
}

//--------------------------------------------------------------
void ofApp::update()
{
	std::clock_t currentTime = std::clock();
	deltaTime = float(currentTime - previousTime) / CLOCKS_PER_SEC;
	previousTime = currentTime;
		
	for (int i=0;i<myParticles.size();i++)
	{
		myParticles[i].integrate(deltaTime);
		//myParticles[i].move();
		myLines[i].addVertex(myParticles[i].getPos().getX(), myParticles[i].getPos().getY(), 0);
	}


	box.setWidth(300);
	box.setPosition(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//ofTranslate(0, ofGetHeight(), 0);
	//ofPushMatrix();

	//ofRotateZDeg(rotationAngle);
	//ofSetColor(255);
	//ofDrawRectangle(0, -25, 75, 50);

	//ofPopMatrix();

	for (int i = 0; i < myParticles.size(); i++)
	{
		myParticles[i].draw();
		myLines[i].draw();
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
		printf("hey");
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
		Vector3d(0, ofGetHeight()),
		Vector3d(50, -50, 0),
		5
	);

	myParticles.push_back(newParticule);

	ofPolyline b;
	b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
	myLines.push_back(b);
}