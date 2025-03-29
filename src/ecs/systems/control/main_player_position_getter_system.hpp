#pragma once

#include <utility>

#include "MGL/include/action.hpp"

#include "../../core/system.hpp"

class MainPlayerPositionGetterSystem : public System {
	public:
		void Init() {}
		std::pair<double, double> get();
};