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

	world.update(deltaTime_);

	/*collision.particles = myParticles_;*/

	//std::cout << collision.particles.size() << std::endl;

	/*for (int i = 0; i < myParticles_.size(); i++)
	{
		myParticles_[i]->integrate(deltaTime_);
	}*/
	/*collision.addContact(contacts, deltaTime_);
	for (int j = 0; j < contacts.size(); j++)
	{
		contacts[j].solve();
	}
	contacts.clear();*/
}

//--------------------------------------------------------------
void ofApp2::draw()
{
	for (int i = 0; i < world.particles_.size(); i++)
	{
		world.particles_[i]->draw(1);
	}
}

//--------------------------------------------------------------
void ofApp2::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp2::keyReleased(int key)
{
	// No action on key release
}

//--------------------------------------------------------------
void ofApp2::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp2::mouseDragged(int x, int y, int button)
{
	// No action on mouse drag
}

//--------------------------------------------------------------
void ofApp2::mousePressed(int x, int y, int button)
{
	switch (button)
	{
	case 0:
		SpawnParticle(1);
		break;
	default:
		break;
	}
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

//--------------------------------------------------------------
/**
 * @brief Spawns a particle
 *
 * @return nothing
*/
void ofApp2::SpawnParticle(int type)
{
	if (type == 1)
	{

		Particle* newParticule = new Particle(
			Vector3d(ofGetMouseX(), ofGetMouseY()),
			Vector3d(0, 0, 0),
			3
		);
		myParticles_.push_back(newParticule);
		world.addParticle(newParticule);
	}

}