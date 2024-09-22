/**
* \file Particle.cpp
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
void Particle::draw(int type)
{
	if (type == 1) {
		ofDrawIcoSphere(pos_.v3(), 10);
	}
	else if (type == 2) {
		// Dessine le cercle orange pour la balle de basket
		ofSetColor(255, 165, 0);  // Orange
		ofDrawCircle(pos_.getX(), pos_.getY(), 10);

		// Dessine les lignes noires sur la balle
		ofSetColor(0);  // Noir

		// Ligne verticale
		ofDrawLine(pos_.getX(), pos_.getY() - 10, pos_.getX(), pos_.getY() + 10);

		// Ligne horizontale
		ofDrawLine(pos_.getX() - 10, pos_.getY(), pos_.getX() + 10, pos_.getY());

		// Deux courbes pour les arcs latéraux
		ofDrawBezier(pos_.getX() - 10, pos_.getY(),  // Point de départ
			pos_.getX() - 10 / 2, pos_.getY() - 10 / 2,  // Premier point de contrôle
			pos_.getX() + 10 / 2, pos_.getY() - 10 / 2,  // Deuxième point de contrôle
			pos_.getX() + 10, pos_.getY());  // Point d'arrivée

		ofDrawBezier(pos_.getX() - 10, pos_.getY(),  // Point de départ
			pos_.getX() - 10 / 2, pos_.getY() + 10 / 2,  // Premier point de contrôle
			pos_.getX() + 10 / 2, pos_.getY() + 10 / 2,  // Deuxième point de contrôle
			pos_.getX() + 10, pos_.getY());  // Point d'arrivée
	}
	else if (type == 3) {
		
		// Dessin des cercles concentriques pour la boule de feu

		// Couche centrale jaune
		ofSetColor(255, 255, 0);  // Jaune
		ofDrawCircle(pos_.getX(), pos_.getY(), 12 * 0.3);

		// Couche intermédiaire orange
		ofSetColor(255, 165, 0);  // Orange
		ofDrawCircle(pos_.getX(), pos_.getY(), 12 * 0.6);

		// Couche extérieure rouge
		ofSetColor(255, 69, 0);  // Rouge
		ofDrawCircle(pos_.getX(), pos_.getY(), 12);

		// Optionnel : ajout de quelques flammes
		ofSetColor(255, 140, 0);  // Flammes orange
		for (int i = 0; i < 8; i++) {
			float randomAngle = ofRandom(TWO_PI);
			float flameLength = ofRandom(5, 10);  // Longueur aléatoire des flammes
			ofDrawLine(pos_.getX(), pos_.getY(),
				pos_.getX() + cos(randomAngle) * (12 + flameLength),
				pos_.getY() + sin(randomAngle) * (12 + flameLength));
		}
	}
	else if (type == 4) {
		// Canonball --------------------------------------------------------------
		ofSetColor(200);  // Gris foncé pour le boulet de canon
		ofDrawCircle(pos_.getX(), pos_.getY(), 15);

		// Optionnel : ajouter des détails comme une légère ombre
		ofSetColor(235);  // Ombre plus foncée
		ofDrawCircle(pos_.getX() - 2, pos_.getY() + 10 * 0.3, 15 * 0.8);
	}
}


/**
 * @brief 
 * 
 * @param time
 * @return nothing
*/
void Particle::integrate(float time)
{
	speed_ += (mass_ * g * time);
	pos_ += (speed_ * time);
}
