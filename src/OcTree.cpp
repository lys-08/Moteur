/**
* \file OcTree.cpp
* This file contains the implementation of all methods and attributes of the OcTree class
*/

#include "OcTree.h"
#include "solve.h"
#include <of3dGraphics.h>
#include <ofGraphics.h>

/**
 * @brief "Default" and evaluated constructor
 */
OcTree::OcTree(Vector3d center, float w, float h, float d, int minCapacity, int maxDepth, bool leaf)
{
    center_ = center;
	minCapacity_ = minCapacity;
	maxDepth_ = maxDepth;
	leaf_ = leaf;
	for (int i = 0; i < 8; ++i) 
	{
		children_[i] = nullptr;
	}

	if (w == 0.0f) w_ = 960;
	else w_ = w / 2.0;

	if (h == 0.0f) h_ = 540;
	else h_ = h / 2.0;

	if (d == 0.0f) d_ = 500;
	else d_ = d / 2.0;
}

/**
 * @brief Insert a rigidBody in the list to add it in the octree
 * 
 * @param rigidBody the rigidBody to insert
 * @return nothing
 */
void OcTree::insertRigidBody(RigidBody* rigidBody)
{
    /* If the number of RigidBody stocked is less than minimum capacity or if the max depth
	 * of the octree is reached, we directly add the rigidBody to the list of value
     */
    /*if (values_.size() < minCapacity_ || maxDepth_ == 0) {
        values_.push_back(rigidBody);
        return;
    }*/


	// we get the position of the rigidBody to add and the radius of it's bounding box
	Vector3d rbCenter = rigidBody->getMassCenter()->getPos();
	Vector3d rbRadius = rigidBody->calculateBoundingRadius();

	/* if the distance between the center of the rigidBody and the half size of the axe (for 
	 * each one, then the collider is overlaping the octree and we add it directly to the 
	 * list of rigidBody
	 */
	float offsetX, offsetY, offsetZ;
	offsetX = rbCenter.getX() - center_.getX();
	/*if (abs(offsetX) < w_) {
		values_.push_back(rigidBody);
		return;
	}*/

	offsetY = rbCenter.getY() - center_.getY();
	/*if (abs(offsetY) < h_) {
		values_.push_back(rigidBody);
		return;
	}*/

	offsetZ = rbCenter.getZ() - center_.getZ();
	/*if (abs(offsetZ) < d_) {
		values_.push_back(rigidBody);
		return;
	}*/


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

	for (int i = 0; i < values_.size(); i++)
	{
		Vector3d rbCenter = values_[i]->getMassCenter()->getPos();
		Vector3d rbRadius = values_[i]->calculateBoundingRadius();

		offsetX = rbCenter.getX() - center_.getX();
		offsetY = rbCenter.getY() - center_.getY();
		offsetZ = rbCenter.getZ() - center_.getZ();

		childIndex = 0;
		if (offsetX > 0.f) childIndex += 1;
		if (offsetY > 0.f) childIndex += 2;
		if (offsetZ > 0.f) childIndex += 4;

		if (children_[childIndex] == nullptr) // if their is no children, we create it
		{
			Vector3d childOffset(w_ / 2.0f, h_ / 2.0f, d_ / 2.0f);
			children_[childIndex] = new OcTree(center_ + childOffset, w_ / 2.0f, h_ / 2.0f, d_ / 2.0f, minCapacity_, maxDepth_ - 1);
		}
		children_[childIndex]->insertRigidBody(values_[i]);
	}
}

void OcTree::checkCollisionsInTree(std::vector<RigidBodyContact>& contacts)
{
	for (int i = 0; i < 8; ++i)
	{
		if (children_[i] != nullptr) {
			(*children_)[i].checkCollisionsInTree(contacts);
		}
	}

	if (checkBoundingVolumesOverlap())
	{
		checkCollisionsInChild(values_[0], values_[1], contacts);
	}
}

/**
 * @brief TODO
 * 
 * @return true if the volumes overlap the bounding box, otherwise false
 */
bool OcTree::checkBoundingVolumesOverlap()
{
	if (values_.empty()) return false;
	size_t n = values_.size();

	for (size_t i = 0; i < n-1; ++i) {
		for (size_t j = i + 1; j < n; ++j) {
			RigidBody* body1 = values_[i];
			RigidBody* body2 = values_[j];

			Vector3d center1 = body1->getMassCenter()->getPos();
			Vector3d center2 = body2->getMassCenter()->getPos();

			double radius1 = body1->calculateBoundingRadius();
			double radius2 = body2->calculateBoundingRadius();

			double distance = center1.distance(center2);

			return distance <= (radius1 + radius2);
		}
	}
	return false;
}

/**
 * @brief check if two rigid bodies in a single leaf are in collision. Their bounding volume are already in collision TODO
 * 
 * @return nothing
 */
void OcTree::checkCollisionsInChild(RigidBody* r1, RigidBody* r2, std::vector<RigidBodyContact>& contacts)
{
	//if (children_ != nullptr) return;

	//TODO allocation � chaque appel ?
	Vector3d xAxis(1, 0, 0);
	//Vector3d yAxis(0, 1, 0);
	//Vector3d zAxis(0, 0, 1);
	if (r1->getMassCenter()->getPos().getX() != r2->getMassCenter()->getPos().getX())
	{
		if (r1->getMassCenter()->getPos().dotProduct(xAxis) < r2->getMassCenter()->getPos().dotProduct(xAxis))
		{
			//values 0 est � gauche, donc on peut appeler has separating planes
			if (FourierMotzkin::has_separating_plane(r1->getVertex(), r2->getVertex()))
			{
				RigidBody* rigidBodies[2];
				rigidBodies[0] = r1;
				rigidBodies[1] = r2;

				//float interpenetration = distance - sumRadius;
				Vector3d normal = (r1->getMassCenter()->getPos() - r2->getMassCenter()->getPos()).normalise2();

				RigidBodyContact contact = RigidBodyContact(rigidBodies, 0, 1, Vector3d(),Vector3d());
				contacts.push_back(contact);
			}
		}
		else
		{
			if (FourierMotzkin::has_separating_plane(r2->getVertex(), r1->getVertex()))
			{
				RigidBody* rigidBodies[2];
				rigidBodies[0] = r2;
				rigidBodies[1] = r1;

				//float interpenetration = distance - sumRadius;
				//Vector3d normal = (particles_[i]->getPos() - particles_[j]->getPos()).normalise2();

				RigidBodyContact contact = RigidBodyContact(rigidBodies, 0, 1, Vector3d(), Vector3d());
				contacts.push_back(contact);
			}
		}
	}
}

/**
 * @brief Clear the octree
 *
 * @return nothing
 */
void OcTree::clearOctree()
{
	// if their is no children, we clear the value and return
	if (children_ == nullptr)
	{
		values_.clear();
		return;
	}

	// Otherwise, we call this method for each child that is not null
	for (int i = 0; i < 8; ++i) 
	{
		if (children_[i] != nullptr) (*children_)[i].clearOctree();
	}
	// We set the children to nullptr and clear the values
	*children_ = nullptr;
	values_.clear();
}

/**
 * @brief Draw the octree
 *
 * @return nothing
 */
void OcTree::draw()
{

	Vector3d vertices[8] = {
		center_ - w_ - w_ - w_,
		center_ + w_ - w_ - w_,
		center_ + w_ + w_ - w_,
		center_ - w_ + w_ - w_,
		center_ - w_ - w_ + w_,
		center_ + w_ - w_ + w_,
		center_ + w_ + w_ + w_,
		center_ - w_ + w_ + w_ 
	};

	const int edges[12][2] = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0},
		{4, 5}, {5, 6}, {6, 7}, {7, 4},
		{0, 4}, {1, 5}, {2, 6}, {3, 7}
	};

	for (const auto& edge : edges) {
		const Vector3d& start = vertices[edge[0]];
		const Vector3d& end = vertices[edge[1]];
		ofDrawLine(start.getX(), start.getY(), start.getZ(), end.getX(), end.getY(), end.getZ());
	}

	for (OcTree* child : children_) {
		if (child != nullptr) {
			child->draw();
		}
	}
}
