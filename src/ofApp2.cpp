#include "ofApp2.h"
#include "../tests/test_vector3d.h"

//--------------------------------------------------------------
void ofApp2::setup()
{
	previousTime_ = std::clock();
}

//--------------------------------------------------------------
void ofApp2::update()
{
	std::clock_t currentTime = std::clock();

	deltaTime_ = float(currentTime - previousTime_) / CLOCKS_PER_SEC;
	previousTime_ = currentTime;

	if (world.particles_.size() == 0)
	{
		return;
	}
	world.particles_[0]->setSpeed((Vector3d(mouseX,mouseY,0) - world.particles_[0]->getPos())/deltaTime_);
	world.update(deltaTime_);
}

//--------------------------------------------------------------
void ofApp2::draw()
{
	ofSetColor(255, 255, 255);
	ofDrawLine(glm::vec2(2000, 950), glm::vec2(0, 950));
	for (int i = 0; i < world.particles_.size(); i++)
	{
		world.particles_[i]->draw();
	}

	if (hasStarted)
	{
		int originalBlobSize = world.originalBlob.size();
		ofSetColor(255, 0, 0);
		ofDrawBitmapString("Taille du blob original : " + ofToString(originalBlobSize-1), ofGetWidth() - 300, 20);
	}
}

//--------------------------------------------------------------
void ofApp2::keyPressed(int key)
{
	switch (key)
	{
	case '1':
		if (hasStarted)
		{
			world.attachNewParticle();
		}
		else
		{
			world.start(mouseX, mouseY);
			hasStarted = true;
		}
		break;
	case '2':
		world.separateBlob();
		break;
	case '3':
		world.reformBlob();
		break;
	}

}

//--------------------------------------------------------------
void ofApp2::keyReleased(int key)
{
	// No action on key release
}

//--------------------------------------------------------------
void ofApp2::mouseMoved(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

//--------------------------------------------------------------
void ofApp2::mouseDragged(int x, int y, int button)
{
	// No action on mouse drag
}

//--------------------------------------------------------------
void ofApp2::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp2::mouseReleased(int x, int y, int button)
{
	// No action on mouse release
}

//--------------------------------------------------------------
void ofApp2::mouseEntered(int x, int y)
{
	// No action when mouse enters the window
}

//--------------------------------------------------------------
void ofApp2::mouseExited(int x, int y)
{
	// No action when mouse exits the window
}

//--------------------------------------------------------------
void ofApp2::windowResized(int w, int h)
{
	// No action on window resize
}

//--------------------------------------------------------------
void ofApp2::gotMessage(ofMessage msg)
{
	// No action when a message is received
}

//--------------------------------------------------------------
void ofApp2::dragEvent(ofDragInfo dragInfo)
{
	// No action on drag event
}