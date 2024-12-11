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
OcTree::OcTree(Vector3d center, float w, float h, float d, int minCapacity, int maxDepth)
{
    center_ = center;
	minCapacity_ = minCapacity;
	maxDepth_ = maxDepth;
	for (int i = 0; i < 8; ++i) 
	{
		children_[i] = nullptr;
	}

	if (w == 0.0f) w_ = 960;
	else w_ = w;

	if (h == 0.0f) h_ = 540;
	else h_ = h;

	if (d == 0.0f) d_ = 500;
	else d_ = d;
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
	offsetY = rbCenter.getY() - center_.getY();
	offsetZ = rbCenter.getZ() - center_.getZ();

	// If the rigidBody is entirely in a leaf, we add it to this list
	// the childIndex depend on the offset value (vary between 0 and 7 => 8 sub octree)
	int childIndex = 0;
	Vector3d childOffset = Vector3d();

	if (offsetX > 0.f)
	{
		childIndex += 1;
		childOffset.setX(w_ / 2.0);
	}
	else childOffset.setX(-w_ / 2.0);

	if (offsetY > 0.f)
	{
		childIndex += 2;
		childOffset.setY(h_ / 2.0);
	}
	else childOffset.setY(-h_ / 2.0);

	if (offsetZ > 0.f)
	{
		childIndex += 4;
		childOffset.setZ(d_ / 2.0);
	}
	else childOffset.setZ(-d_ / 2.0);

	if (children_[childIndex] == nullptr) // if their is no children, we create it
	{
		children_[childIndex] = new OcTree(center_ + childOffset, w_ / 2.0f, h_ / 2.0f, d_ / 2.0f, minCapacity_, maxDepth_ - 1);
	}
	children_[childIndex]->insertRigidBody(rigidBody);

	// For the values in the curent node
	for (int i = 0; i < values_.size(); i++)
	{

		Vector3d rbCenter = values_[i]->getMassCenter()->getPos();
		Vector3d rbRadius = values_[i]->calculateBoundingRadius();

		offsetX = rbCenter.getX() - center_.getX();
		offsetY = rbCenter.getY() - center_.getY();
		offsetZ = rbCenter.getZ() - center_.getZ();

		childIndex = 0;
		Vector3d childOffset = Vector3d();

		if (offsetX > 0.f)
		{
			childIndex += 1;
			childOffset.setX(w_ / 2.0);
		}
		else childOffset.setX(-w_ / 2.0);

		if (offsetY > 0.f)
		{
			childIndex += 2;
			childOffset.setY(h_ / 2.0);
		}
		else childOffset.setY(-h_ / 2.0);

		if (offsetZ > 0.f)
		{
			childIndex += 4;
			childOffset.setZ(d_ / 2.0);
		}
		else childOffset.setZ(-d_ / 2.0);

		if (children_[childIndex] == nullptr) // if their is no children, we create it
		{
			children_[childIndex] = new OcTree(center_ + childOffset, w_ / 2.0f, h_ / 2.0f, d_ / 2.0f, minCapacity_, maxDepth_ - 1);
		}
		children_[childIndex]->insertRigidBody(values_[i]);
	}

	values_.clear();
}

/**
 * @brief Check the collision in the octree
 *
 * @param contacts the contact to check in the octree
 * @return nothing
 */
void OcTree::checkCollisionsInTree(std::vector<RigidBodyContact>& contacts)
{
	for (int i = 0; i < 8; ++i)
	{
		if (children_[i] != nullptr) {
			children_[i]->checkCollisionsInTree(contacts);
		}
	}
	std::vector<OcTree*> c = { children_[0],children_[1],children_[2],children_[3],children_[4],children_[5],children_[6],children_[7] };
	if (std::all_of(c.begin(), c.end(), [](OcTree* child) { return child == nullptr; }))
	{
		auto p = checkBoundingVolumesOverlap();
		if (p.first)
		{
			checkCollisionsInChild(p.second.first, p.second.second, contacts);
		}
	}
}

/**
 * @brief Check if the bounding volumes of the rigid bodies in the octree overlap
 * 
 * @return a boolean and a pair of rigid bodies. The boolean indicates if the bodies volume overlap
 */
std::pair<bool,std::pair<RigidBody*,RigidBody*>> OcTree::checkBoundingVolumesOverlap()
{
	if (values_.empty()) return std::pair(false,std::pair(nullptr,nullptr));
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

			return std::pair((distance <= (radius1 + radius2)), std::pair(body1, body2));
		}
	}
	return std::pair(false, std::pair(nullptr, nullptr));
}

/**
 * @brief check if two rigid bodies in a single leaf are in collision. Their bounding volume are already in collision TODO
 * 
 * @param r1 the first rigidBody
 * @param r2 the second rigidBody
 * @param contacts the contacts to test
 * @return nothing
 */
void OcTree::checkCollisionsInChild(RigidBody* r1, RigidBody* r2, std::vector<RigidBodyContact>& contacts)
{

	Vector3d xAxis(1, 0, 0);

	if (r1->getMassCenter()->getPos() != r2->getMassCenter()->getPos())
	{
		if (r1->getMassCenter()->getPos().dotProduct(xAxis) < r2->getMassCenter()->getPos().dotProduct(xAxis))
		{
			if (!FourierMotzkin::has_separating_plane(r1->getVertex(), r2->getVertex()))
			{
				RigidBody* rigidBodies[2];
				rigidBodies[0] = r1;
				rigidBodies[1] = r2;

				Vector3d center1 = r1->getMassCenter()->getPos();
				Vector3d center2 = r2->getMassCenter()->getPos();
				Vector3d middle = center2 - center1;
				middle.setW(1); //is a point 

				double radius1 = r1->calculateBoundingRadius();
				double radius2 = r2->calculateBoundingRadius();

				double distance = center1.distance(center2);

				double interpenetration = distance - (radius1 + radius2);
				Vector3d normal = (r1->getMassCenter()->getPos() - r2->getMassCenter()->getPos()).normalise2();

				RigidBodyContact contact = RigidBodyContact(rigidBodies, 1, interpenetration, middle, normal);
				contacts.push_back(contact);
			}
		}
		else
		{
			if (!FourierMotzkin::has_separating_plane(r2->getVertex(), r1->getVertex()))
			{
				RigidBody* rigidBodies[2];
				rigidBodies[0] = r1;
				rigidBodies[1] = r2;

				Vector3d center1 = r1->getMassCenter()->getPos();
				Vector3d center2 = r2->getMassCenter()->getPos();
				Vector3d middle = center2 - center1;
				middle.setW(1); //is a point 

				double radius1 = r1->calculateBoundingRadius();
				double radius2 = r2->calculateBoundingRadius();

				double distance = center1.distance(center2);

				double interpenetration = distance - (radius1 + radius2);
				Vector3d normal = (r1->getMassCenter()->getPos() - r2->getMassCenter()->getPos()).normalise2();

				RigidBodyContact contact = RigidBodyContact(rigidBodies, 1, interpenetration, middle, normal);
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
	for (int i = 0; i < 8; ++i) 
	{
		if (children_[i] != nullptr)
		{
			children_[i]->clearOctree();
			children_[i] = nullptr;
		}
	}
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
		center_ + Vector3d(-w_, -h_, -d_),
		center_ + Vector3d( w_, -h_, -d_),
		center_ + Vector3d( w_,  h_, -d_),
		center_ + Vector3d(-w_,  h_, -d_),
		center_ + Vector3d(-w_, -h_,  d_),
		center_ + Vector3d( w_, -h_,  d_),
		center_ + Vector3d( w_,  h_,  d_),
		center_ + Vector3d(-w_,  h_,  d_)
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
