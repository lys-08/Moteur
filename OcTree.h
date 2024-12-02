/**
* \file OcTree.cpp
* This file contains the implementation of all methods and attributes of the OcTree class
*/

#include "../apps/myApps/Moteur/src/rigidBody.h"
#include <vector>
#include "ofMain.h"

#pragma once
class OcTree
{

public:
	// constructor
	OcTree(ofBoxPrimitive boundary, int capacity);

	// Methods
	
	void subdivide();
	std::vector<RigidBody*> query(const ofBoxPrimitive& range);
	void draw();
	bool isRigidBodyInBoundary(const RigidBody& body, const ofBoxPrimitive& boundary);
	void buildTree(const std::vector<RigidBody*>& rigidBodies, const ofBoxPrimitive& boundary);
	void initialize(const std::vector<RigidBody*>& rigidBodies);
	void subdivide(const ofBoxPrimitive& parentBoundary);

private:

	std::vector<RigidBody> rigidBodies_; // List of rigid bodies in the OcTree

	ofBoxPrimitive boundary_; // Starting boundary of the OcTree

	int capacity_; // Maximum number of rigid bodies tolerated in a sub-division square of the OcTree

	bool divided_; // Indicate if the 3D cell is sub-divised or not

	OcTree* children[8];// 8 children of the OcTree (dividing a cube in 3D gives 8 sub-cubes)




};

