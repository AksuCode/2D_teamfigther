#pragma once

#include "main_player_position_getter_system.hpp"

#include "../../components/actor/player.hpp"
#include "../../components/physics/motion.hpp"
#include "../../core/coordinator.hpp"

extern Coordinator gCoordinator;

std::pair<double, double> MainPlayerPositionGetterSystem::get() {
	auto& entity = mEntities[0];
	auto& player = gCoordinator.Get<Player>(entity);
	auto& motion = gCoordinator.Get<Motion>(entity);

	return {motion.position.first, motion.position.second};
}