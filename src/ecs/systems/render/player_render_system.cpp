#include "player_render_system.hpp"

#include "../../components/render/r_player.hpp"
#include "../../components/physics/motion.hpp"

#include "../../core/coordinator.hpp"

extern Coordinator gCoordinator;

void PlayerRenderSystem::Init(Renderer * renderer) {
	renderer_ = renderer;
}

void PlayerRenderSystem::CreatePlayerRenders() {
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		auto& entity = *it;

		auto& r_player = gCoordinator.GetComponent<R_Player>(entity);

		if (!r_player.rendered) {
			renderer_->createPlayerRender(r_player.player_id, r_player.skin_id);
			r_player.rendered = true;
		}
	}
}

void PlayerRenderSystem::LoadPlayerRenders() {
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		auto& entity = *it;

		auto& r_player = gCoordinator.GetComponent<R_Player>(entity);
		renderer_->loadPlayer(r_player.player_id, r_player.skin_id);
	}
}

void PlayerRenderSystem::Render() {
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		auto& entity = *it;

		auto& motion = gCoordinator.GetComponent<Motion>(entity);
		auto& r_player = gCoordinator.GetComponent<R_Player>(entity);

		const std::pair<double, double> position = motion.position;

		renderer_->renderPlayer(r_player.player_id, r_player.skin_id, 0, r_player.action_sprite_counter, motion.position, 1.0f);
	}
}