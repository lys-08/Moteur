/**
* \file solve.h
*/

#pragma once

#include <vector>
#include "inequalitySystem.h"
#include "vector3d.h"

namespace FourierMotzkin
{
	// Check if a separating plane exists
	bool has_separating_plane(const std::vector<Vector3d>& left, const std::vector<Vector3d>& right);

} // namespace FourierMotzkin