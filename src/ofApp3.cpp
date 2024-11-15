#include "ofApp3.h"
#include "../tests/test_vector3d.h"

//--------------------------------------------------------------
void ofApp3::setup()
{
	previousTime_ = std::clock();
}

//--------------------------------------------------------------
void ofApp3::update() {
	std::clock_t currentTime = std::clock();

	// Calculate the elapsed time between the last update() call and the current one
	deltaTime_ = float(currentTime - previousTime_) / CLOCKS_PER_SEC;
	previousTime_ = currentTime;

	physics.update(deltaTime_);
}

//--------------------------------------------------------------
void ofApp3::draw()
{
	//Display difference between frames
	ofSetColor(0, 255, 0);

	std::string deltaTimeText = "Delta Time: " + ofToString(deltaTime_, 5);

	int x = ofGetWidth() - 200;
	int y = 20;

	ofDrawBitmapString(deltaTimeText, x, y);

	ofSetColor(0, 0, 0);
	// Save the current transformation matrix
	ofPushMatrix();
	ofTranslate(0, ofGetHeight(), 0); // Origine at the botton left
	ofScale(1, -1); // Positive x axis to the right and y axis to the top

	// Get the mouse position in our transformed coordinate system
	mouseX_ = ofGetMouseX();
	mouseY_ = ofGetHeight() - ofGetMouseY();

	// Drawing our particles
	for (int i = 0; i < physics.objects_.size(); i++)
	{
		physics.objects_[i]->getMassCenter().draw();
	}
	ofRotateZDeg(-theta_);

	// Canon
	ofSetColor(255);
	ofDrawRectangle(0, -25, 75, 50);

	// Restore the transformation matrix to it's original state
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp3::keyPressed(int key)
{
	switch (key)
	{
	case '1':
		type_ = 1;
		break;
	case '2':
		type_ = 2;
		break;
	case '3':
		type_ = 3;
		break;
	case '4':
		type_ = 4;
		break;
	case 't':
		Test_vector3d testVector3d;
		testVector3d.tests_all();
		break;
	}
}

//--------------------------------------------------------------
void ofApp3::keyReleased(int key)
{
	// No action on key release
}

//--------------------------------------------------------------
void ofApp3::mouseMoved(int x, int y)
{
	// Calculate the rotation angle in the XY plane based on the mouse's current position
	double theta = atan2(y - ofGetHeight(), x);
	theta_ = ofRadToDeg(theta);
}

//--------------------------------------------------------------
void ofApp3::mouseDragged(int x, int y, int button)
{
	// No action on mouse drag
}

//--------------------------------------------------------------
void ofApp3::mousePressed(int x, int y, int button)
{
	switch (button)
	{
	case 0:
		SpawnRigidBody(type_);
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp3::mouseReleased(int x, int y, int button)
{
	// No action on mouse release
}

//--------------------------------------------------------------
void ofApp3::mouseEntered(int x, int y)
{
	// No action when mouse enters the window
}

//--------------------------------------------------------------
void ofApp3::mouseExited(int x, int y)
{
	// No action when mouse exits the window
}

//--------------------------------------------------------------
void ofApp3::windowResized(int w, int h)
{
	// No action on window resize
}

//--------------------------------------------------------------
void ofApp3::gotMessage(ofMessage msg)
{
	// No action when a message is received
}

//--------------------------------------------------------------
void ofApp3::dragEvent(ofDragInfo dragInfo)
{
	// No action on drag event
}

//--------------------------------------------------------------
/**
 * @brief Spawns a particle
 *
 * @return nothing
*/
void ofApp3::SpawnRigidBody(int type)
{
	RigidBody newObject(10,Vector3d(500,500,0,1),Vector3d(0,0,0,0),Quaternion(),20,20,20);
	physics.addRigidBody(&newObject);
	//std::cout << "added rigid body" << std::endl;
}