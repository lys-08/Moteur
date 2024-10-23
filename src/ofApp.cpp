#include "ofApp.h"
#include "../tests/test_vector3d.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	previousTime_ = std::clock();
}

//--------------------------------------------------------------
void ofApp::update() {
	std::clock_t currentTime = std::clock();

	// Calculate the elapsed time between the last update() call and the current one
	deltaTime_ = float(currentTime - previousTime_) / CLOCKS_PER_SEC;
	previousTime_ = currentTime;

	for (int i = 0; i < myParticles_.size(); i++) 
	{
		// Update each particle by integrating its movement based on the elapsed time
		myParticles_[i].integrate(deltaTime_);

		// Add a new vertex to the polyline based on the particle's current position
		myLines_[i].addVertex(myParticles_[i].getPos().getX(), myParticles_[i].getPos().getY(), 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//Display difference between frames
	ofSetColor(0, 255, 0);

	std::string deltaTimeText = "Delta Time: " + ofToString(deltaTime_, 5);

	int x = ofGetWidth() - 200;
	int y = 20;

	ofDrawBitmapString(deltaTimeText, x, y);

	ofSetColor(0, 0, 0);

	if (!isHudDisplayed_)
	{
		// Display the HUD
		ofSetColor(255);
		ofDrawRectangle(50, 50, 65, 65);
		ofDrawRectangle(50, 125, 65, 65);
		ofDrawRectangle(50, 200, 65, 65);
		ofDrawRectangle(50, 275, 65, 65);

		ofSetColor(0);
		ofDrawRectangle(60, 60, 45, 45);
		ofDrawRectangle(60, 135, 45, 45);
		ofDrawRectangle(60, 210, 45, 45);
		ofDrawRectangle(60, 285, 45, 45);

		ofSetColor(255);

		ofDrawBitmapString("1", 65, 100);
		ofDrawBitmapString("2", 65, 175);
		ofDrawBitmapString("3", 65, 250);
		ofDrawBitmapString("4", 65, 325);

		// Ping Pong Ball ---------------------------------------------------------
		ofSetColor(255);  // White
		ofDrawCircle(85, 85, 10);

		// Basketball -------------------------------------------------------------
		float posX = 85;
		float posY = 155;
		float ballRadius = 10;

		// Orange circle
		ofSetColor(255, 165, 0); 
		ofDrawCircle(posX, posY, ballRadius);

		// Black lines
		ofSetColor(0); 
		ofDrawLine(posX, posY - ballRadius, posX, posY + ballRadius); // vertical line
		ofDrawLine(posX - ballRadius, posY, posX + ballRadius, posY); // horizontal line

		// lateral arches
		ofDrawBezier(posX - ballRadius, posY,  // start
			posX - ballRadius / 2, posY - ballRadius / 2,  // first checkpoint
			posX + ballRadius / 2, posY - ballRadius / 2,  // second checkpoint
			posX + ballRadius, posY);  // end point
		ofDrawBezier(posX - ballRadius, posY, 
			posX - ballRadius / 2, posY + ballRadius / 2, 
			posX + ballRadius / 2, posY + ballRadius / 2,
			posX + ballRadius, posY);

		// Fireball ---------------------------------------------------------------
		float maxRadius = 12; 
		float centerX = 85;
		float centerY = 230;

		// Concentric circles for the fireball :
		//	- Central yellow circle
		//	- Middle orange circle
		//	- External red circle

		ofSetColor(255, 255, 0);
		ofDrawCircle(centerX, centerY, maxRadius * 0.3);

		ofSetColor(255, 165, 0);  
		ofDrawCircle(centerX, centerY, maxRadius * 0.6);

		ofSetColor(255, 69, 0); 
		ofDrawCircle(centerX, centerY, maxRadius);

		// Flames
		ofSetColor(255, 140, 0);
		for (int i = 0; i < 8; i++) {
			float randomAngle = ofRandom(TWO_PI);
			float flameLength = ofRandom(5, 10);
			ofDrawLine(centerX, centerY,
				centerX + cos(randomAngle) * (maxRadius + flameLength),
				centerY + sin(randomAngle) * (maxRadius + flameLength));
		}



		// Canonball --------------------------------------------------------------
		ofSetColor(200);  
		ofDrawCircle(85, 305, 15);

		// Shadow
		ofSetColor(235);
		ofDrawCircle(87 - 15 * 0.3, 300 + 15 * 0.3, 15 * 0.8);
	}


	// Save the current transformation matrix
	ofPushMatrix();
	ofTranslate(0, ofGetHeight(), 0); // Origine at the botton left
	ofScale(1, -1); // Positive x axis to the right and y axis to the top

	// Get the mouse position in our transformed coordinate system
	mouseX_ = ofGetMouseX();
	mouseY_ = ofGetHeight() - ofGetMouseY();

	// Drawing our particles
	for (int i = 0; i < myParticles_.size(); i++)
	{
		myParticles_[i].draw();
		myLines_[i].draw();
	}
	ofRotateZDeg(-theta_);

	// Canon
	ofSetColor(255);
	ofDrawRectangle(0, -25, 75, 50);
	
	// Restore the transformation matrix to it's original state
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	myLines_.clear();
	myParticles_.clear();

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
void ofApp::keyReleased(int key)
{
	// No action on key release
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	// Calculate the rotation angle in the XY plane based on the mouse's current position
	double theta = atan2(y - ofGetHeight(), x);
	theta_ = ofRadToDeg(theta);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	// No action on mouse drag
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	switch (button)
	{
	case 0:
		SpawnParticle(type_);
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	// No action on mouse release
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
	// No action when mouse enters the window
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
	// No action when mouse exits the window
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	// No action on window resize
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
	// No action when a message is received
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	// No action on drag event
}

//--------------------------------------------------------------
/**
 * @brief Spawns a particle
 *
 * @return nothing
*/
void ofApp::SpawnParticle(int type)
{
	if (type == 1)
	{
		Particle newParticule(
			Vector3d(0, 0, 0, 1),
			Vector3d(mouseX_, mouseY_, 0, 0),
			3
		);

		myParticles_.push_back(newParticule);

		ofPolyline b;
		b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
		myLines_.push_back(b);
	}
	else if (type == 2)
	{
		Particle newParticule(
			Vector3d(0, 0, 0, 1),
			Vector3d(mouseX_, mouseY_, 0, 1),
			10
		);

		myParticles_.push_back(newParticule);

		ofPolyline b;
		b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
		myLines_.push_back(b);
	}
	else if (type == 3)
	{
		Particle newParticule(
			Vector3d(0, 0, 0, 1),
			Vector3d(mouseX_, mouseY_, 0, 0),
			30
		);

		myParticles_.push_back(newParticule);

		ofPolyline b;
		b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
		myLines_.push_back(b);
	}
	else if (type == 4)
	{
		Particle newParticule(
			Vector3d(0, 0, 0, 1),
			Vector3d(mouseX_, mouseY_, 0, 0),
			100
		);

		myParticles_.push_back(newParticule);

		ofPolyline b;
		b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
		myLines_.push_back(b);
	}

}