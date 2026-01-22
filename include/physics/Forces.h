//
// Created by heapblk on 1/22/26.
//
#pragma once

namespace Physics
{
    struct Forces
    {
        double fx = 0, fy = 0, fz = 0; // forces in Newtons
        double mx = 0, my = 0, mz = 0; // moments in Newtonmeters (torques)
    };
}