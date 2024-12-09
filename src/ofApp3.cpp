#include "ofApp3.h"
#include "box.h"
#include "Cone.h"
#include "SimpleForce.h"
#include "../solve.h"
// Tests
#include "../tests/test_vector3d.h"
#include "../tests/test_matrix3.h"
#include "../tests/test_matrix4.h"
#include "../tests/test_quaternion.h"


//--------------------------------------------------------------
void ofApp3::setup()
{
	previousTime_ = std::clock();

	std::vector<Vector3d> object1 = {
		{0, 0, 0},
		{1, 4, 0},
		{4, 1, 0},
		{1.5, 1.5, 1.5}
	};

	std::vector<Vector3d> object2 = {
		{1, 0, 0},
		{4, 3, 0},
		{5, -1, 0},
		{3.5, 1, 1.5}
	};

	// Appeler la fonction pour vérifier s'il existe un plan séparateur
	bool result = FourierMotzkin::has_separating_plane(object1, object1);

	if (result)
	{
		std::cout << "Il existe un plan séparateur entre les deux objets." << std::endl;
	}
	else
	{
		std::cout << "Les deux objets sont en collision." << std::endl;
	}

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

	int x = ofGetWidth() - 320;
	int y = 20;

	ofDrawBitmapString(deltaTimeText, x, y);
	ofSetColor(255, 0, 0);
	ofDrawBitmapString("Force: (10,0,0) except for q: (10,10,0)", x, y + 20);
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("b: Box, c: Cone, p: Pave\nz: Box + depth, q: Box + diverse force", x, y + 40);
	ofDrawBitmapString("1: Applied at massCenter - 20 (z)\n", x, y + 80);
	ofDrawBitmapString("2: Applied at massCenter - 20 (y)\n", x, y + 100);
	ofDrawBitmapString("3: Applied at massCenter - 20 (x)\n", x, y + 120);

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
		physics.objects_[i]->draw();
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
	case 't':
		Test_vector3d testVector3d;
		testVector3d.tests_all();

		Test_matrix3 test_matrix3;
		test_matrix3.tests_all();

		Test_matrix4 test_matrix4;
		test_matrix4.tests_all();

		Test_quaternion test_quaternion;
		test_quaternion.tests_all();
		break;
	case 'b':
		rigidBodyType_ = 1;
		break;
	case 'c':
		rigidBodyType_ = 2;
		break;
	case 'p':
		rigidBodyType_ = 3;
		break;
	case 'z':
		rigidBodyType_ = 4;
		break;
	case 'q':
		rigidBodyType_ = 5;
		break;
	case '1':
		simpleForceType_ = 1;
		break;
	case '2':
		simpleForceType_ = 2;
		break;
	case '3':
		simpleForceType_ = 3;
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
		SpawnRigidBody(rigidBodyType_);
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
	if (type == 1) //Box
	{
		RigidBody* newObject = new Box(20,Vector3d(0,0,0,1),Vector3d(mouseX_,mouseY_,0,0),Quaternion().identity(), 50, 50, 50);
		SimpleForce newForce = SimpleForce(Vector3d(10, 0, 0,0), simpleForceType_);
		physics.addRigidBody(newObject);
		physics.addSimpleForce(newForce);
	}
	else if (type == 2) //Cone
	{
		RigidBody* newObject = new Cone(30, Vector3d(0, 0, 0, 1), Vector3d(mouseX_, mouseY_, 0, 0), Quaternion().identity(), 30,50);
		SimpleForce newForce = SimpleForce(Vector3d(10, 0, 0, 0), simpleForceType_);
		physics.addRigidBody(newObject);
		physics.addSimpleForce(newForce);
	}
	else if (type == 3) //Pave
	{
		RigidBody* newObject = new Box(20, Vector3d(0, 0, 0, 1), Vector3d(mouseX_, mouseY_, 0, 0), Quaternion().identity(), 100, 50, 50);
		SimpleForce newForce = SimpleForce(Vector3d(10, 0, 0, 0), simpleForceType_);
		physics.addRigidBody(newObject);
		physics.addSimpleForce(newForce);
	}
	else if (type == 4) //Box + Depth
	{
		RigidBody* newObject = new Box(20, Vector3d(0, 0, 0, 1), Vector3d(mouseX_, mouseY_, -200, 0), Quaternion().identity(), 50, 50, 50);
		SimpleForce newForce = SimpleForce(Vector3d(10, 0, 0, 0), simpleForceType_);
		physics.addRigidBody(newObject);
		physics.addSimpleForce(newForce);
	}
	else if (type == 5) //Box
	{
		RigidBody* newObject = new Box(20, Vector3d(0, 0, 0, 1), Vector3d(mouseX_, mouseY_, 0, 0), Quaternion().identity(), 50, 50, 50);
		SimpleForce newForce = SimpleForce(Vector3d(10, 10, 0, 0), simpleForceType_);
		physics.addRigidBody(newObject);
		physics.addSimpleForce(newForce);
	}
}