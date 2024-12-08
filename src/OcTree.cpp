/**
* \file OcTree.cpp
* This file contains the implementation of all methods and attributes of the OcTree class
*/

#include "OcTree.h"

/**
 * @brief "Default" and evaluated constructor
 */
OcTree::OcTree(Vector3d center, float w, float h, float d, int minCapacity, int maxDepth)
{
    center_ = center;
	minCapacity_ = minCapacity;
	maxDepth_ = maxDepth;

	if (w == 0.0f) w_ = 960;
	else w_ = w / 2.0;

	if (h == 0.0f) h_ = 540;
	else h_ = h / 2.0;

	if (d == 0.0f) d_ = 500;
	else d_ = d / 2.0;
}

/**
 * @brief Insert a rigidBody in the list to add it in the octree
 */
void OcTree::insertRigidBody(RigidBody* rigidBody)
{
    /* If the number of RigidBody stocked is less than minimum capacity or if the max depth
	 * of the octree is reached, we directly add the rigidBody to the list of value
     */
    if (values_.size() < minCapacity_ || maxDepth_ == 0) {
        values_.push_back(rigidBody);
        return;
    }


	// we get the position of the rigidBody to add and the radius of it's bounding box
	Vector3d rbCenter = rigidBody->getMassCenter()->getPos();
	Vector3d rbRadius = rigidBody->calculateBoundingRadius();

	/* if the distance between the center of the rigidBody and the half size of the axe (for 
	 * each one, then the collider is overlaping the octree and we add it directly to the 
	 * list of rigidBody
	 */
	float offsetX, offsetY, offsetZ;
	offsetX = rbCenter.getX() - center_.getX();
	if (abs(offsetX) < w_) {
		values_.push_back(rigidBody);
		return;
	}

	offsetY = rbCenter.getY() - center_.getY();
	if (abs(offsetY) < h_) {
		values_.push_back(rigidBody);
		return;
	}

	offsetZ = rbCenter.getZ() - center_.getZ();
	if (abs(offsetZ) < d_) {
		values_.push_back(rigidBody);
		return;
	}


	// If the rigidBody is entirely in a leaf, we add it to this list
	// the childIndex depend on the offset value (vary between 0 and 7 => 8 sub octree)
	int childIndex = 0;

	if (offsetX > 0.f) childIndex += 1;
	if (offsetY > 0.f) childIndex += 2;
	if (offsetZ > 0.f) childIndex += 4;

	if (children_[childIndex] == nullptr) // if their is no children, we create it
	{
		Vector3d childOffset(w_ / 2.0f, h_ / 2.0f, d_ / 2.0f);
		children_[childIndex] = new OcTree(center_ + childOffset, w_ / 2.0f, h_ / 2.0f, d_ / 2.0f, minCapacity_, maxDepth_ - 1);
	}
	children_[childIndex]->insertRigidBody(rigidBody);
}