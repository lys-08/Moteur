/**
* \file OcTree.cpp
* This file contains the implementation of all methods and attributes of the OcTree class
*/

#include "OcTree.h"

OcTree::OcTree(ofBoxPrimitive boundary, int capacity)
{

	boundary_ = boundary;
	this->capacity_ = capacity;
	divided_ = false;

	// Initialize children to nullptr
	for (int i = 0; i < 8; i++) {
		children[i] = nullptr;
	}

}

void OcTree::initialize(const std::vector<RigidBody*>& rigidBodies) {
	buildTree(rigidBodies, boundary_); // We start the recursion with the initial boundary
}

bool OcTree::isRigidBodyInBoundary(const RigidBody& body, const ofBoxPrimitive& boundary) {
	// We verify if the center of mass of the rigid body is inside the boundary
    Vector3d centerOfMass = body.getMassCenter()->getPos();
    if (boundary.inside(centerOfMass.v3())) {
        return true;
    }

	// We verify if the bounding sphere of the rigid body intersects the boundary
    float boundingRadius = body.getBoundingRadius();
    ofVec3f sphereMin(centerOfMass.getX() - boundingRadius,
        centerOfMass.getY() - boundingRadius,
        centerOfMass.getZ() - boundingRadius);
    ofVec3f sphereMax(centerOfMass.getX() + boundingRadius,
        centerOfMass.getY() + boundingRadius,
        centerOfMass.getZ() + boundingRadius);
    
    return boundary.intersects(ofBoxPrimitive((sphereMin + sphereMax) / 2,
        sphereMax.x - sphereMin.x,
        sphereMax.y - sphereMin.y,
        sphereMax.z - sphereMin.z));
}

void OcTree::buildTree(const std::vector<RigidBody*>& rigidBodies, const ofBoxPrimitive& boundary) {
	// We count the number of rigid bodies in the boundary
    std::vector<RigidBody*> containedBodies;
    for (RigidBody* body : rigidBodies) {
		if (isRigidBodyInBoundary(*body, boundary)) { // We use the current boundary passed as parameter
            containedBodies.push_back(body);
        }
    }

	// We subdivide if the capacity is exceeded
    if (containedBodies.size() > capacity_) {
        if (!divided_) { // Passing the current boundary as parameter
            subdivide(boundary);
        }

		// We continue the recursion with the childrens
        for (int i = 0; i < 8; ++i) {
            if (children[i] != nullptr) {
                children[i]->buildTree(containedBodies, children[i]->boundary_); // Passe le boundary de l'enfant
            }
        }
    }
    else {
        
        rigidBodies_ = containedBodies;
        divided_ = false;
    }
}

void OcTree::subdivide(const ofBoxPrimitive& parentBoundary) {
    // We obtain the dimensions of the parrent boundary
    ofVec3f center = parentBoundary.getPosition();
    float halfWidth = parentBoundary.getWidth() / 2;
    float halfHeight = parentBoundary.getHeight() / 2;
    float halfDepth = parentBoundary.getDepth() / 2;

    // We create the 8 sub-cubes
    for (int i = 0; i < 8; ++i) {
        ofVec3f offset(
            (i & 1 ? 1 : -1) * halfWidth / 2,
            (i & 2 ? 1 : -1) * halfHeight / 2,
            (i & 4 ? 1 : -1) * halfDepth / 2);

        children[i] = new OcTree(
            ofBoxPrimitive(center + offset, halfWidth, halfHeight, halfDepth),
            capacity_);
        children[i]->boundary_ = ofBoxPrimitive(center + offset, halfWidth, halfHeight, halfDepth); // Assign the sub-boundary
    }

    divided_ = true;
}
