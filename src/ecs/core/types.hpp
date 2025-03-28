#pragma once

#include <bitset>
#include <cstdint>

// A simple type alias
using Entity = std::uint32_t;

// Used to define the size of arrays
const Entity MAX_ENTITIES = 10000;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;

// A simple type alias
using ComponentType = std::uint16_t;

// Used to define the size of arrays
const ComponentType MAX_COMPONENTS = 32;