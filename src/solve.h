#ifndef FOURIER_MOTZKIN_HPP
#define FOURIER_MOTZKIN_HPP

#include <vector>
#include "ineq.h"
#include "vector3d.h"

namespace FourierMotzkin
{

	// Check if a separating plane exists
	bool has_separating_plane(const std::vector<Vector3d>& left, const std::vector<Vector3d>& right);

} // namespace FourierMotzkin

#endif // FOURIER_MOTZKIN_HPP

