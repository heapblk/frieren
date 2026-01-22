//
// Created by heapblk on 1/22/26.
//
#pragma once
#include "physics/Forces.h"
#include "aircraft/Params.h"
#include "aircraft/State.h"

class Simulator
{
public:

    // set timestep in seconds and init Simulator
    explicit Simulator(double timestep);

    // calculates the Aircraft state at each timestep
    Aircraft::State step(const Aircraft::State& aircraft_state, const Aircraft::Params& aircraft_params,
                         const Physics::Forces& forces) const;

private:
    double m_timestep;    // timestep in seconds
};
