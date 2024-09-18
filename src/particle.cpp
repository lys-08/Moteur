/**
* \file Particle.cpp
* This file contains the definition of all methods and attributes of the Particle class
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
Particle::Particle(Vector3d pos, Vector3d dir, float speed)
{
	pos_ = pos;
	dir_ = dir;
	speed_ = speed;
}

/**
 * @brief Copy constructor
 *
 * @param p the particle to copy
 */
Particle::Particle(const Particle& other)
{
	pos_ = other.pos_;
	dir_ = other.dir_;
	speed_ = other.speed_;
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


Vector3d Particle::getDir() const
{
	return dir_;
}


float Particle::getSpeed() const
{
	return speed_;
}

/*bool Particle::getInvertMass() const
{
	return invertMass_;
}*/


void Particle::setDir(Vector3d dir)
{
	dir_ = dir;
}


void Particle::setSpeed(float speed)
{
	speed_ = speed;
}

/*void setInvertMass(bool invertMass)
{
	invertMass_ = invertMass;
}*/



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Move the particle according to it's position, directional and speed
 *
 * @return nothing
*/
void Particle::move()
{
	pos_ += (dir_ * speed_);
}

/**
 * @brief Draw the particle
 *
 * @return nothing
*/
void Particle::draw()
{
	ofDrawIcoSphere(pos_.v3(), 10);
}

void Particle::integrate(float temps)
{
	dir_ += (0.8 * g * temps);
	pos_ += (dir_ * temps);
}
