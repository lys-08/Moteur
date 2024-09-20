#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	previousTime = std::clock();
}

//--------------------------------------------------------------
void ofApp::update() {
	// Obtient le temps actuel en "ticks" d'horloge
	std::clock_t currentTime = std::clock();

	// Calcule le temps �coul� entre l'appel pr�c�dent � update() et l'appel actuel
	deltaTime = float(currentTime - previousTime) / CLOCKS_PER_SEC;

	previousTime = currentTime;
	for (int i = 0; i < myParticles.size(); i++) {
		// Met � jour chaque particule en int�grant son mouvement selon le temps �coul�
		myParticles[i].integrate(deltaTime);

		// Ajoute un nouveau sommet au polyline correspondant � la position actuelle de la particule
		myLines[i].addVertex(myParticles[i].getPos().getX(), myParticles[i].getPos().getY(), 0);
	}

}


//--------------------------------------------------------------
void ofApp::draw()
{

	// Sauvegarde la matrice de transformation courante (pour restaurer plus tard)
	ofPushMatrix();

	// D�place l'origine du rep�re en bas � gauche (X = 0, Y = hauteur de la fen�tre)
	ofTranslate(0, ofGetHeight(), 0);

	// Inverse l'axe Y pour avoir un rep�re avec Y croissant vers le haut (dessine en coordonn�es cart�siennes)
	ofScale(1, -1);

	// R�cup�re la position X et Y de la souris dans le rep�re normal
	mouseX = ofGetMouseX();
	mouseY = ofGetHeight() - ofGetMouseY();

	// Boucle � travers toutes les particules et lignes pour les dessiner
	for (int i = 0; i < myParticles.size(); i++) {
		// Dessine chaque particule
		myParticles[i].draw();

		// Dessine chaque ligne associ�e aux particules
		myLines[i].draw();
	}

	// Effectue une rotation dans l'axe Z
	ofRotateZDeg(-rotationAngle);

	// D�finit la couleur � blanc pour le rectangle
	ofSetColor(255);

	// Dessine un rectangle blanc dont le centre est situ� � l'origine
	ofDrawRectangle(0, -25, 75, 50);

	// Restaure la matrice de transformation � son �tat initial
	ofPopMatrix();



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	// Calcule l'angle de rotation dans le plan XY par rapport � la position actuelle de la souris
	float angleZ = atan2(y - ofGetHeight(), x);

	rotationAngle = ofRadToDeg(angleZ);
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	// Fait apparaitre une particule lors du clique gauche de la souris
	switch (button)
	{
	case 0:
		SpawnParticle();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

//--------------------------------------------------------------

/**
 * @brief Make spawn a particle
 *
 * @return nothing
*/
void ofApp::SpawnParticle()
{
	Particle newParticule(
		Vector3d(0, 0),
		Vector3d(mouseX, mouseY, 0),
		5,
		3
	);

	myParticles.push_back(newParticule);

	ofPolyline b;
	b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);
	myLines.push_back(b);
}