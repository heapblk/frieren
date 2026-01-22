//
// Created by heapblk on 1/22/26.
//
#include "simulator/Simulator.h"
#include "physics/Gravity.h"
#include <gtest/gtest.h>

TEST(Simulator, SanityTest)
{
    Aircraft::State s_aircraft_state{};
    s_aircraft_state.x = 0; s_aircraft_state.y = 0; s_aircraft_state.z = 1000; // 1000m altitude
    s_aircraft_state.vx = 0; s_aircraft_state.vy = 0; s_aircraft_state.vz = 0; // no velocity
    s_aircraft_state.pitch = 0; s_aircraft_state.roll = 0; s_aircraft_state.yaw = 0;
    s_aircraft_state.p = 0; s_aircraft_state.q = 0; s_aircraft_state.r = 0;
    s_aircraft_state.fuel = 1000; // 1000 kg of fuel

    Aircraft::Params s_aircraft_params{};
    s_aircraft_params.mass = 5000; // kg
    s_aircraft_params.wing_area  = 30; //m^2
    s_aircraft_params.chord = 2; // m

    Simulator o_sim(0.1);

    // run simulation for 5 seconds
    for (int i = 0; i < 50; i++)
    {
        Physics::Forces s_forces = Physics::Gravity::calc(s_aircraft_params);

        s_aircraft_state = o_sim.step(s_aircraft_state, s_aircraft_params, s_forces);

        std::cout << "t=" << i*0.1 << "s" << std::endl
                  << "z=" << s_aircraft_state.z << "m" << std::endl
                  << "vz=" << s_aircraft_state.vz << "m/s" << std::endl
                  << "------------" << std::endl;
    }
    ASSERT_TRUE(true);
}