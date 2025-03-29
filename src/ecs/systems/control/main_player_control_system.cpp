#pragma once

#include "main_player_control_system.hpp"

#include "../../components/actor/player.hpp"
#include "../../components/physics/motion.hpp"
#include "../../core/coordinator.hpp"

extern Coordinator gCoordinator;

void MainPlayerControlSystem::Update(const std::array<bool, (int)ActionCode::ACTION_CODE_COUNT> & actions) {
	auto& entity = mEntities[0];
	auto& player = gCoordinator.Get<Player>(entity);
	auto& motion = gCoordinator.Get<Motion>(entity);

	if (actions(ActionCode::LEFT)) {
		motion.position.first -= 10;
	}

	if (actions(ActionCode::RIGHT)) {
		motion.position.first += 10;
	}

	if (actions(ActionCode::UP)) {
		motion.position.second += 10;
	}

	if (actions(ActionCode::DOWN)) {
		motion.position.second -= 10;
	}
}