//
// Created by heapblk on 1/22/26.
//
#include "simulator/Simulator.h"

//----------------------------------------------------------------------
Simulator::Simulator(double timestep) : m_timestep(timestep) {};

//----------------------------------------------------------------------
Aircraft::State Simulator::step(const Aircraft::State &aircraft_state, const Aircraft::Params &aircraft_params,
                                const Physics::Forces &forces) const
{
    Aircraft::State _s_new_aircraft_state = aircraft_state;

    // acceleration = force / mass
    double _ax = forces.fx / aircraft_params.mass;
    double _ay = forces.fy / aircraft_params.mass;
    double _az = forces.fz / aircraft_params.mass;

    // update velocity
    _s_new_aircraft_state.vx += _ax * m_timestep;
    _s_new_aircraft_state.vy += _ay * m_timestep;
    _s_new_aircraft_state.vz += _az * m_timestep;

    // update position
    _s_new_aircraft_state.x += _s_new_aircraft_state.vx * m_timestep;
    _s_new_aircraft_state.y += _s_new_aircraft_state.vy * m_timestep;
    _s_new_aircraft_state.z += _s_new_aircraft_state.vz * m_timestep;

    return _s_new_aircraft_state;
}
