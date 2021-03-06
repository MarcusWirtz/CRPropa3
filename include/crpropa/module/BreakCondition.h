#ifndef CRPROPA_BREAKCONDITION_H
#define CRPROPA_BREAKCONDITION_H

#include "crpropa/Module.h"

namespace crpropa {

/**
 @class MaximumTrajectoryLength
 @brief Deactivates the candidate beyond a maximum trajectory length

 This modules deactivates the candidate at a given maximum trajectory length.
 In that case the property ("Deactivated", module::description) is set.
 It also limits the candidates next step size to ensure the maximum trajectory length is no exceeded.
 */
class MaximumTrajectoryLength: public AbstractCondition {
	double maxLength;
public:
	MaximumTrajectoryLength(double length = 0);
	void setMaximumTrajectoryLength(double length);
	double getMaximumTrajectoryLength() const;
	std::string getDescription() const;
	void process(Candidate *candidate) const;
};

/**
 @class MinimumEnergy
 @brief Deactivates the candidate below a minimum energy

 This modules deactivates the candidate below a given minimum energy.
 In that case the property ("Deactivated", module::description) is set.
 */
class MinimumEnergy: public AbstractCondition {
	double minEnergy;
public:
	MinimumEnergy(double minEnergy = 0);
	void setMinimumEnergy(double energy);
	double getMinimumEnergy() const;
	std::string getDescription() const;
	void process(Candidate *candidate) const;
};

/**
 @class MinimumRedshift
 @brief Deactivates the candidate below a minimum redshift

 This modules deactivates the candidate below a given minimum redshift.
 In that case the property ("Deactivated", module::description) is set.
 */
class MinimumRedshift: public AbstractCondition {
	double zmin;
public:
	MinimumRedshift(double zmin = 0);
	void setMinimumRedshift(double z);
	double getMinimumRedshift();
	std::string getDescription() const;
	void process(Candidate *candidate) const;
};

} // namespace crpropa

#endif // CRPROPA_BREAKCONDITION_H
