#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    previousTime = std::clock();
}

//--------------------------------------------------------------
void ofApp::update() {
    // Get the current time in clock ticks
    std::clock_t currentTime = std::clock();

    // Calculate the elapsed time between the last update() call and the current one
    deltaTime = float(currentTime - previousTime) / CLOCKS_PER_SEC;

    previousTime = currentTime;

    for (int i = 0; i < myParticles.size(); i++) {
        // Update each particle by integrating its movement based on the elapsed time
        myParticles[i].integrate(deltaTime);

        // Add a new vertex to the polyline based on the particle's current position
        myLines[i].addVertex(myParticles[i].getPos().getX(), myParticles[i].getPos().getY(), 0);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Save the current transformation matrix
    ofPushMatrix();

    // Move the origin to the bottom-left corner of the window
    ofTranslate(0, ofGetHeight(), 0);

    // Flip the Y axis to make positive Y go upwards
    ofScale(1, -1);

    // Get the mouse position in the transformed coordinate system
    mouseX = ofGetMouseX();
    mouseY = ofGetHeight() - ofGetMouseY();

    for (int i = 0; i < myParticles.size(); i++) {
        myParticles[i].draw();

        myLines[i].draw();
    }

    ofRotateZDeg(-rotationAngle);
    ofSetColor(255);
    ofDrawRectangle(0, -25, 75, 50);

    // Restore the transformation matrix to its original state
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // No action on key press
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
    float angleZ = atan2(y - ofGetHeight(), x);

    rotationAngle = ofRadToDeg(angleZ);
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
        SpawnParticle();
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

    // Add the current particle position as the first vertex of the line
    b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);

    myLines.push_back(b);
}
