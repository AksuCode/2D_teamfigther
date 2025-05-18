#pragma once

#include "../../core/system.hpp"

#include "../../../renderer/renderer.hpp"

class PlayerRenderSystem : public System {
	public:
		void Init(Renderer * renderer);
		void CreatePlayerRenders();
		void LoadPlayerRenders();
		void Render();
	private:
		Renderer * renderer_;
};