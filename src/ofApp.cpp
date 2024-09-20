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
    // Save the current transformation matrix
    ofPushMatrix();

    // Move the origin to the bottom-left corner of the window
    ofTranslate(0, ofGetHeight(), 0);

    // Flip the Y axis to make positive Y go upwards
    ofScale(1, -1);

    // Get the mouse position in the transformed coordinate system
    mouseX_ = ofGetMouseX();
    mouseY_ = ofGetHeight() - ofGetMouseY();

    for (int i = 0; i < myParticles_.size(); i++) 
    {
        myParticles_[i].draw();
        myLines_[i].draw();
    }

    ofRotateZDeg(-theta_);
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
    double theta = atan2(y - ofGetHeight(), x);
    theta_ = ofRadToDeg(theta);
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
        Vector3d(mouseX_, mouseY_, 0),      
        50                                                        
    );

    myParticles_.push_back(newParticule);
    ofPolyline b;

    // Add the current particle position as the first vertex of the line
    b.addVertex(newParticule.getPos().getX(), newParticule.getPos().getY(), 0);

    myLines_.push_back(b);
}
