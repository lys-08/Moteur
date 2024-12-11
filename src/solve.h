/**
* \file solve.h
* 
* This resolution is based on the code of Nicholas42 : https://github.com/Nicholas42/FourierMotzkin/tree/master
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