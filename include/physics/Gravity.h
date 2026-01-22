//
// Created by heapblk on 1/22/26.
//
#pragma once
#include "Forces.h"
#include "../aircraft/Params.h"

namespace Physics
{
class Gravity
{
public:
    static Forces calc(const Aircraft::Params& aircraft_params);
};
}
