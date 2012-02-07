#include "mpc/magneticField/magneticFieldGrid.hpp"

namespace mpc {

void periodicClamp(double x, int n, int &lo, int &hi, double &fLo,
		double &fHi) {
	// closest lower and upper neighbour in a periodically continued grid
	lo = ((int(x) % n) + n) % n;
	hi = (lo + 1) % n;
	fLo = x - floor(x);
	fHi = 1 - fLo;
}

MagneticFieldGrid::MagneticFieldGrid(Vector3 origin, size_t samples,
		double spacing) {
	this->origin = origin;
	this->spacing = spacing;
	this->samples = samples;
	grid.resize(samples);
	for (int ix = 0; ix < samples; ix++) {
		grid[ix].resize(samples);
		for (int iy = 0; iy < samples; iy++) {
			grid[ix][iy].resize(samples);
		}
	}
}

Vector3 MagneticFieldGrid::getField(const Vector3 &position) const {
	Vector3 r = (position - origin) / spacing;
	int ix, iX, iy, iY, iz, iZ;
	double fx, fX, fy, fY, fz, fZ;
	periodicClamp(r.x(), samples, ix, iX, fx, fX);
	periodicClamp(r.y(), samples, iy, iY, fy, fY);
	periodicClamp(r.z(), samples, iz, iZ, fz, fZ);

	// trilinear interpolation
	// check: http://paulbourke.net/miscellaneous/interpolation/
	Vector3 b(0, 0, 0);
	//V000 (1 - x) (1 - y) (1 - z) +
	b += grid[ix][iy][iz] * fX * fY * fZ;
	//V100 x (1 - y) (1 - z) +
	b += grid[iX][iy][iz] * fx * fY * fZ;
	//V010 (1 - x) y (1 - z) +
	b += grid[ix][iY][iz] * fX * fy * fZ;
	//V001 (1 - x) (1 - y) z +
	b += grid[ix][iy][iZ] * fX * fY * fz;
	//V101 x (1 - y) z +
	b += grid[iX][iy][iZ] * fx * fY * fz;
	//V011 (1 - x) y z +
	b += grid[ix][iY][iZ] * fX * fy * fz;
	//V110 x y (1 - z) +
	b += grid[iX][iY][iz] * fx * fy * fZ;
	//V111 x y z
	b += grid[iX][iY][iZ] * fx * fy * fz;

	return b;
}

} // namespace mpc