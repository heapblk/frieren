//
// Created by heapblk on 1/22/26.
//
#pragma once

namespace Aircraft
{
// describes the Aircraft state in the current frame
struct State
{
    double x, y, z;             // position in m
    double vx, vy, vz;          // velocity in m/s
    double pitch, roll, yaw;    // orientation in radians
    double p, q, r;             // angular rates (rotation speeds)
    double fuel;                // fuel
};
}