/**
* \file particle.cpp
* This file contains the implementation of all methods and attributes of the Particle class
*/

#include "particle.h"
#include <of3dGraphics.h>
#include <ctime>
#include <ofMain.h>




/**
 * @brief Default and evaluated constructor
 *
 * @param pos the position of the particle
 * @param dir direction of the particle
 * @param speed the speed of the particle
 */
Particle::Particle(Vector3d pos, Vector3d speed, int typeDraw, double mass)
{
	pos_ = pos;
	speed_ = speed;
	mass_ = mass;
	radius_ = 1;
	setInvertMass(mass_);
	particleTypeDraw = typeDraw;
}

/**
 * @brief Copy constructor
 *
 * @param p the particle to copy
 */
Particle::Particle(const Particle& other)
{
	pos_ = other.pos_;
	speed_ = other.speed_;
	mass_ = other.mass_;
	setInvertMass(mass_);
	particleTypeDraw = other.particleTypeDraw;
}

/**
 * @brief Dummy destructor
 */
Particle::~Particle()
{

}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

Vector3d Particle::getPos() const
{
	return pos_;
}

Vector3d Particle::getSpeed() const
{
	return speed_;
}

double Particle::getMass() const
{
	return mass_;
}

double Particle::getInvertMass() const
{
	return invertMass_;
}

Vector3d Particle::getForceAccum() const
{
	return accumForce_;
}

double Particle::getRadius() const
{
	return radius_;
}

bool Particle::getHasSpring()
{
	return hasSpring;
}

bool Particle::getHasSetSpring()
{
	return hasSetSpring;
}

ParticleSpring Particle::getSpring()
{
	if (hasSpring)
	{
		return *spring;
	}
}

ParticleSetSpring Particle::getSetSpring()
{
	if (hasSetSpring)
	{
		return *setSpring;
	}
}

void Particle::setSpeed(Vector3d speed)
{
	speed_ = speed;
}

void Particle::setInvertMass(double mass)
{
	if (mass == 0)
	{
		throw std::invalid_argument("Division by zero");
	}

	invertMass_ = 1/mass;
}

void Particle::setPos(Vector3d pos)
{
	pos_ = pos;
}

void Particle::setSpringForce(Particle* other, double k, double l0)
{
	spring = new ParticleSpring(other, k, l0);
	hasSpring = true;
}

void Particle::setSetSpringForce(Vector3d point, double k, double l0)
{
	setSpring = new ParticleSetSpring(point, k, l0);
	hasSetSpring = true;
}

void Particle::removeSpringForce()
{
	spring = nullptr;
	hasSpring = false;
}

void Particle::removeSetSpringForce()
{
	setSpring = nullptr;
	hasSetSpring = false;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Draw the particle
 *
 * @return nothing
*/
void Particle::draw()
{
	if (particleTypeDraw == 0)
	{
		ofSetColor(140, 0, 255);
	}
	else if (particleTypeDraw == 1)
	{
		ofSetColor(37, 126, 200);
	}

	ofDrawIcoSphere(pos_.v3(), 10);


	//else if (type == 2) // Basket Ball
	//{ 
	//	// Orange circle
	//	ofSetColor(255, 165, 0);  
	//	ofDrawCircle(pos_.getX(), pos_.getY(), 10);

	//	// Black lines
	//	ofSetColor(0); 
	//	ofDrawLine(pos_.getX(), pos_.getY() - 10, pos_.getX(), pos_.getY() + 10);
	//	ofDrawLine(pos_.getX() - 10, pos_.getY(), pos_.getX() + 10, pos_.getY());
	//	// lateral arches
	//	ofDrawBezier(pos_.getX() - 10, pos_.getY(),  // start
	//		pos_.getX() - 10 / 2, pos_.getY() - 10 / 2,  // first checkpoint
	//		pos_.getX() + 10 / 2, pos_.getY() - 10 / 2,  // second checkpoint
	//		pos_.getX() + 10, pos_.getY());  // end point
	//	ofDrawBezier(pos_.getX() - 10, pos_.getY(),  
	//		pos_.getX() - 10 / 2, pos_.getY() + 10 / 2,  
	//		pos_.getX() + 10 / 2, pos_.getY() + 10 / 2, 
	//		pos_.getX() + 10, pos_.getY());  
	//}
	//else if (type == 3) // Fire Ball
	//{
	//	// Concentric circles for the fireball :
	//	//	- Central yellow circle
	//	//	- Middle orange circle
	//	//	- External red circle

	//	ofSetColor(255, 255, 0);
	//	ofDrawCircle(pos_.getX(), pos_.getY(), 12 * 0.3);

	//	ofSetColor(255, 165, 0);  
	//	ofDrawCircle(pos_.getX(), pos_.getY(), 12 * 0.6);

	//	ofSetColor(255, 69, 0);
	//	ofDrawCircle(pos_.getX(), pos_.getY(), 12);

	//	// Flames
	//	ofSetColor(255, 140, 0); 
	//	for (int i = 0; i < 8; i++) 
	//	{
	//		float randomAngle = ofRandom(TWO_PI);
	//		float flameLength = ofRandom(5, 10);  
	//		ofDrawLine(pos_.getX(), pos_.getY(),
	//			pos_.getX() + cos(randomAngle) * (12 + flameLength),
	//			pos_.getY() + sin(randomAngle) * (12 + flameLength));
	//	}
	//}
	//else if (type == 4) // Canon Ball
	//{
	//	ofSetColor(200); 
	//	ofDrawCircle(pos_.getX(), pos_.getY(), 15);

	//	// Shadow
	//	ofSetColor(235); 
	//	ofDrawCircle(pos_.getX() - 2, pos_.getY() + 10 * 0.3, 15 * 0.8);
	//}
}


/**
 * @brief Euler integration
 * 
 * @param time
 * @return nothing
*/
void Particle::integrate(float time)
{
	speed_ += (accumForce_* time);
	pos_ += (speed_ * time);
}

/**
 * @brief add a strength to the accumulator
 *
 * @param strength the strength to add to accumForce
 * @return nothing
*/
void Particle::addForce(const Vector3d& strength)
{
	accumForce_ += strength;
}

/**
 * @brief Clear accumForce
 *
 * @return nothing
*/
void Particle::clearAccumForce()
{
	accumForce_ = Vector3d(0, 0, 0, 0);
}