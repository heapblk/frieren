//
// Created by heapblk on 1/22/26.
//
#include "physics/Gravity.h"

using namespace Physics;

Forces Gravity::calc(const Aircraft::Params& aircraft_params)
{
    Forces _s_forces{};

    _s_forces.fz = -9.80665 * aircraft_params.mass; // z is down because aerodynamics professors decided that NED is the way to go ig

    return _s_forces;
}
