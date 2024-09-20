/**
* \file Particle.cpp
* This file contains the implementation of all methods and attributes of the Particle class
*/

#include "particle.h"
#include <of3dGraphics.h>
#include <ctime>




/**
 * @brief Default and evaluated constructor
 *
 * @param pos the position of the particle
 * @param dir direction of the particle
 * @param speed the speed of the particle
 */
Particle::Particle(Vector3d pos, Vector3d speed, double mass)
{
	pos_ = pos;
	speed_ = speed;
	mass_ = mass;
	setInvertMass(mass_);
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

double Particle::getInvertMass() const
{
	return invertMass_;
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
	ofDrawIcoSphere(pos_.v3(), 10);
}


/**
 * @brief 
 * 
 * @param time
 * @return nothing
*/
void Particle::integrate(double time)
{
	speed_ += (mass_ * g * time);
	pos_ += (speed_ * time);
}
