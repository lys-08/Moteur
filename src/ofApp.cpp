#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    previousTime_ = std::clock();
}

//--------------------------------------------------------------
void ofApp::update() {
    // Get the current time in clock ticks
    std::clock_t currentTime = std::clock();

    // Calculate the elapsed time between the last update() call and the current one
    deltaTime_ = float(currentTime - previousTime_) / CLOCKS_PER_SEC;

    previousTime_ = currentTime;

    for (int i = 0; i < myParticles_.size(); i++) {
        // Update each particle by integrating its movement based on the elapsed time
        myParticles_[i].integrate(deltaTime_);

        // Add a new vertex to the polyline based on the particle's current position
        myLines_[i].addVertex(myParticles_[i].getPos().getX(), myParticles_[i].getPos().getY(), 0);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{

	if (!isHudDisplayed)
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
		ofDrawCircle(85, 85, 10); // 1

		// Basketball -------------------------------------------------------------
		float posX = 85;     // Position X de la balle
		float posY = 155;    // Position Y de la balle
		float ballRadius = 10;  // Rayon de la balle de basket

		// Dessine le cercle orange pour la balle de basket
		ofSetColor(255, 165, 0);  // Orange
		ofDrawCircle(posX, posY, ballRadius);

		// Dessine les lignes noires sur la balle
		ofSetColor(0);  // Noir

		// Ligne verticale
		ofDrawLine(posX, posY - ballRadius, posX, posY + ballRadius);

		// Ligne horizontale
		ofDrawLine(posX - ballRadius, posY, posX + ballRadius, posY);

		// Deux courbes pour les arcs latéraux
		ofDrawBezier(posX - ballRadius, posY,  // Point de départ
			posX - ballRadius / 2, posY - ballRadius / 2,  // Premier point de contrôle
			posX + ballRadius / 2, posY - ballRadius / 2,  // Deuxième point de contrôle
			posX + ballRadius, posY);  // Point d'arrivée

		ofDrawBezier(posX - ballRadius, posY,  // Point de départ
			posX - ballRadius / 2, posY + ballRadius / 2,  // Premier point de contrôle
			posX + ballRadius / 2, posY + ballRadius / 2,  // Deuxième point de contrôle
			posX + ballRadius, posY);  // Point d'arrivée

		// Fireball ---------------------------------------------------------------
		float maxRadius = 12;  // Rayon maximal de la boule de feu
		float centerX = 85;    // Position X fixe
		float centerY = 230;   // Position Y fixe

		// Dessin des cercles concentriques pour la boule de feu

		// Couche centrale jaune
		ofSetColor(255, 255, 0);  // Jaune
		ofDrawCircle(centerX, centerY, maxRadius * 0.3);

		// Couche intermédiaire orange
		ofSetColor(255, 165, 0);  // Orange
		ofDrawCircle(centerX, centerY, maxRadius * 0.6);

		// Couche extérieure rouge
		ofSetColor(255, 69, 0);  // Rouge
		ofDrawCircle(centerX, centerY, maxRadius);

		// Optionnel : ajout de quelques flammes
		ofSetColor(255, 140, 0);  // Flammes orange
		for (int i = 0; i < 8; i++) {
			float randomAngle = ofRandom(TWO_PI);
			float flameLength = ofRandom(5, 10);  // Longueur aléatoire des flammes
			ofDrawLine(centerX, centerY,
				centerX + cos(randomAngle) * (maxRadius + flameLength),
				centerY + sin(randomAngle) * (maxRadius + flameLength));
		}
		
		

		// Canonball --------------------------------------------------------------
		ofSetColor(200);  // Gris foncé pour le boulet de canon
		ofDrawCircle(85, 305, 15);

		// Optionnel : ajouter des détails comme une légère ombre
		ofSetColor(235);  // Ombre plus foncée
		ofDrawCircle(87 - 15 * 0.3, 300 + 15 * 0.3, 15 * 0.8);

		
	}

	ofPushMatrix();
	ofTranslate(0, ofGetHeight(), 0);
	ofScale(1, -1);
	mouseX_ = ofGetMouseX();
	mouseY_ = ofGetHeight() - ofGetMouseY();
	for (int i = 0; i < myParticles_.size(); i++)
	{
		myParticles_[i].draw(type);
		myLines_[i].draw();
	}
	ofRotateZDeg(-rotationAngle);
	ofSetColor(255);
	ofDrawRectangle(0, - 25, 75, 50);
	ofPopMatrix();



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	// On le réécrit sous forme d'un swicth case
	switch (key)
	{
	case '1':
		type = 1;
		break;
	case '2':
		type = 2;
		break;
	case '3':
		type = 3;
		break;
	case '4':
		type = 4;
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
    double theta_ = atan2(y - ofGetHeight(), x);
    rotationAngle = ofRadToDeg(theta_);
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
		SpawnParticle(type);
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

	printf("Spawning a particle of type : %d\n", type);

	if (type == 1)
	{
		printf("mouseX: %f, mouseY: %f\n", mouseX, mouseY);
		Particle newParticule(
			Vector3d(0, 0),
			Vector3d(mouseX_, mouseY_, 0),
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
			Vector3d(0, 0),
			Vector3d(mouseX_, mouseY_, 0),
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
			Vector3d(0, 0),
			Vector3d(mouseX_, mouseY_, 0),
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
			Vector3d(0, 0),
			Vector3d(mouseX_, mouseY_, 0),
			100
		);

		myParticles_.push_back(newParticule);

		ofPolyline b;
		b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
		myLines_.push_back(b);
	}

	
}