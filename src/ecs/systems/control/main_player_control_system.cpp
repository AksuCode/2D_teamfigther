#include "main_player_control_system.hpp"

#include "../../components/actor/main_player.hpp"
#include "../../components/physics/motion.hpp"

#include "../../core/coordinator.hpp"

extern Coordinator gCoordinator;

void MainPlayerControlSystem::Update(const std::array<bool, (int)ActionCode::ACTION_CODE_COUNT> & actions) {
	
	auto& entity = *mEntities.begin();

	auto& player = gCoordinator.GetComponent<MainPlayer>(entity);
	auto& motion = gCoordinator.GetComponent<Motion>(entity);

	if (actions[ActionCode::LEFT]) {
		motion.position.first -= 10;
	}

	if (actions[ActionCode::RIGHT]) {
		motion.position.first += 10;
	}

	if (actions[ActionCode::UP]) {
		motion.position.second += 10;
	}

	if (actions[ActionCode::DOWN]) {
		motion.position.second -= 10;
	}
}