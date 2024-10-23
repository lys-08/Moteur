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
	world.particles_[0]->clearAccumForce();

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
	ofSetColor(255, 255, 255);
	ofDrawLine(glm::vec2(2000, 950), glm::vec2(0, 950));
	for (int i = 0; i < world.particles_.size(); i++)
	{
		world.particles_[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp2::keyPressed(int key)
{
	switch (key)
	{
	case '1':
		world.start(mouseX, mouseY);
		break;
	case '2':
		type_ = 2;
		//SpawnParticle(2);
		break;
	case '3':
		//type_ = 3;
		world.separateBlob();
		break;
	case '4':
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
	world.attachNewParticle();
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
			Vector3d(ofGetMouseX(), ofGetMouseY(), 0, 1),
			Vector3d(200, 0, 0),
			1,
			10
		);


		
		//world.addParticle(newParticule);
		//newParticule->setSpeed(Vector3d(150, 0, 0));
	}
	if (type == 2)
	{
		world.particles_[0]->setPos(Vector3d(300, 300, 0));

	}
	if (type == 3)
	{
		Particle* newParticule1 = new Particle(
			Vector3d(500, 500),
			Vector3d(0, 0, 0),
			0,
			3
		);

		Particle* newParticule2 = new Particle(
			Vector3d(200, 500),
			Vector3d(10, 0, 0),
			1,
			3
		);

		Particle* particles[2] = { newParticule1, newParticule2 };
		collisionCable = new ParticleCable(particles, 300, 0.7);
		world.addContactGenerator(collisionCable);
		world.addParticle(newParticule1);
		world.addParticle(newParticule2);
	}

}