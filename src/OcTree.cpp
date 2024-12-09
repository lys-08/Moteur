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

bool OcTree::isRigidBodyInBoundary(RigidBody& body, const ofBoxPrimitive& boundary) {
	// We check if the center of mass of the rigid body is inside the boundary
    glm::vec3 centerOfMass = body.getMassCenter()->getPos().v3();
    if (isPointInsideBox(centerOfMass, boundary)) {
        return true;
    }

	// We check if the bounding sphere of the rigid body intersects the boundary
    float boundingRadius = body.getBoundingRadius();
    return doesSphereIntersectBox(centerOfMass, boundingRadius, boundary);
}

void OcTree::buildTree(const std::vector<RigidBody*>& rigidBodies, const ofBoxPrimitive& boundary) {
    // Create a vector to hold rigid bodies that are within the current boundary
    std::vector<RigidBody*> containedBodies;

    // Iterate through all rigid bodies and check if they are inside the current boundary
    for (RigidBody* body : rigidBodies) {
        if (isRigidBodyInBoundary(*body, boundary)) {
            containedBodies.push_back(body); // Add rigid body to the contained list
        }
    }

    // Check if the number of contained rigid bodies exceeds the capacity
    if (containedBodies.size() > capacity_) {
        // If the OcTree node is not yet divided, subdivide it
        if (!divided_) {
            subdivide(boundary); // Split the current boundary into smaller regions
        }

        // Recursively build the tree for each child node
        for (int i = 0; i < 8; ++i) {
            if (children[i] != nullptr) {
                children[i]->buildTree(containedBodies, children[i]->boundary_); // Pass the child's boundary
            }
        }
    }
    else {
        // If the number of rigid bodies is within capacity, store them in the current node
        rigidBodies_.clear(); // Clear the current list to avoid duplicates
        for (RigidBody* body : containedBodies) {
            if (body) { // Ensure the pointer is not null
                rigidBodies_.push_back(*body); // Copy the object from the pointer
            }
        }

        // Mark this node as a leaf (not divided)
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
            ofBoxPrimitive(halfWidth, halfHeight, halfDepth),
            capacity_);
        children[i]->boundary_ = ofBoxPrimitive(halfWidth, halfHeight, halfDepth); // Assign the sub-boundary
    }

    divided_ = true;
}

void OcTree::checkCollisions() {
	// If the OcTree is subdivided, we check collisions for the 8 childrens
    if (divided_) {
        for (int i = 0; i < 8; ++i) {
            if (children[i] != nullptr) {
                children[i]->checkCollisions(); // Appel récursif sur les subdivisions
            }
        }
    }
    else {
		// If we're on a leaf, we check collisions between the rigid bodies
        for (size_t i = 0; i < rigidBodies_.size(); ++i) {
            for (size_t j = i + 1; j < rigidBodies_.size(); ++j) {
                if (checkBoundingVolumesOverlap(rigidBodies_[i], rigidBodies_[j])) {
                    // TODO RESOLUTION COLLISION FUNCTION
                    std::cout << "Collision detected between RigidBody " << i
                        << " and RigidBody " << j << std::endl;
                }
            }
        }
    }
}

bool OcTree::checkBoundingVolumesOverlap(RigidBody& body1, RigidBody& body2) {
    Vector3d center1 = body1.getMassCenter()->getPos();
    Vector3d center2 = body2.getMassCenter()->getPos();

    float dx = center1.getX() - center2.getX();
    float dy = center1.getY() - center2.getY();
    float dz = center1.getZ() - center2.getZ();

    float distanceSquared = dx * dx + dy * dy + dz * dz;

	// We calculate the combined radius of the two bounding spheres
    float combinedRadius = body1.getBoundingRadius() + body2.getBoundingRadius();

	// If the distance between the two centers is less than the sum of the radius, the bounding spheres intersect
    return distanceSquared <= (combinedRadius * combinedRadius);
}

bool OcTree::isPointInsideBox(const glm::vec3& point, const ofBoxPrimitive& box)
{
	// We get the boundaries of the box
    glm::vec3 min = box.getPosition() - glm::vec3(box.getWidth() / 2, box.getHeight() / 2, box.getDepth() / 2);
    glm::vec3 max = box.getPosition() + glm::vec3(box.getWidth() / 2, box.getHeight() / 2, box.getDepth() / 2);

	// We verify if the point is inside the box by checking the x, y and z coordinates of the point
    return (point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y &&
        point.z >= min.z && point.z <= max.z);
}

bool OcTree::doesSphereIntersectBox(const glm::vec3& center, float radius, const ofBoxPrimitive& box) {
	// We get the boundaries of the box
    glm::vec3 min = box.getPosition() - glm::vec3(box.getWidth() / 2, box.getHeight() / 2, box.getDepth() / 2);
    glm::vec3 max = box.getPosition() + glm::vec3(box.getWidth() / 2, box.getHeight() / 2, box.getDepth() / 2);

	// We calculate the closest point to the sphere
    glm::vec3 closestPoint(
        glm::clamp(center.x, min.x, max.x), 
        glm::clamp(center.y, min.y, max.y),
        glm::clamp(center.z, min.z, max.z));

	// We calculate the distance between the center of the sphere and the closest point
    float distanceSquared = glm::distance2(center, closestPoint);

	// We check if the distance is less than the radius of the sphere
    return distanceSquared <= radius * radius;
}


