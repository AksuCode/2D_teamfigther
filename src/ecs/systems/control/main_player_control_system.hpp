#pragma once

#include "MGL/include/action.hpp"

#include "../../core/system.hpp"

class MainPlayerControlSystem : public System {
	public:
		void Init() {}
		void Update(const std::array<bool, (int)ActionCode::ACTION_CODE_COUNT> & actions);
};