/**
* \file OcTree.cpp
* This file contains the declaration of all methods and attributes of the OcTree class
*/
#pragma once

#include "vector3d.h"
#include "rigidBody.h"
#include "rigidbodyContact.h"
#include <vector>


class OcTree
{
	OcTree* children_[8]; // leaf
	std::vector<RigidBody*> values_; // TODO : rigidBody or collider ?
	int minCapacity_;
	int maxDepth_;

	// Position of the Octree
	Vector3d center_;
	float w_; // width ~ x / 2
	float h_; // height ~ y / 2
	float d_; // depth ~ z / 2


public:
	// constructor
	OcTree(Vector3d center = Vector3d(), float w = 540, float h = 960, float d = 500, int minCapacity = 2, int maxDepth = 10); // TODO : default values

	// Methods
	void insertRigidBody(RigidBody* rigidBody); // TODO : rigidBody or collider ?
	bool checkBoundingVolumesOverlap();
	void checkCollisions(std::vector<RigidBodyContact>& contacts);
	// void checkBodyCollision(const PrimitiveCollider* value, std::vector<RigidbodyContact>& contacts);
	void clearOctree();
	void draw();
};