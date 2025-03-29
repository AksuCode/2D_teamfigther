#include "main_player_position_getter_system.hpp"

#include "../../components/actor/main_player.hpp"
#include "../../components/physics/motion.hpp"
#include "../../core/coordinator.hpp"

extern Coordinator gCoordinator;

std::pair<double, double> MainPlayerPositionGetterSystem::get() {
	auto& entity = *mEntities.begin();
	auto& player = gCoordinator.GetComponent<MainPlayer>(entity);
	auto& motion = gCoordinator.GetComponent<Motion>(entity);

	return {motion.position.first, motion.position.second};
}