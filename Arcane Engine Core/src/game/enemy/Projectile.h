#pragma once

//Dependancies
#include "../../Dependancies.h"

//Operation Skullrain Headers
#include "../Entity.h"
#include "../../graphics/renderer/Renderable3D.h"
#include "../../terrain/Terrain.h"
#include "../Player.h"

namespace arcane {
	namespace game {
		class Projectile : public Entity {
		public:
			Projectile();
			Projectile(graphics::Renderable3D *renderable);

			virtual void update(float deltaTime);
			void onRender();
			void shoot();

			inline graphics::Renderable3D* getRenderable() const { return m_Renderable; }

			std::vector<Projectile*> projectiles;
			arcane::graphics::Model* m_CannonBall;
			arcane::game::Player* m_Player;
			std::vector<game::Entity*>* m_Entities;
			arcane::terrain::Terrain* m_Terrain;
		};

		class Cannon : public Projectile {
		public:
			Cannon();
			Cannon(arcane::terrain::Terrain* terrain, graphics::Renderable3D *renderable, arcane::game::Player* player);
			void update(float deltatime);

			float m_HullSize = 10;
			glm::vec3 m_DirectionToMove;
		};

	}
}