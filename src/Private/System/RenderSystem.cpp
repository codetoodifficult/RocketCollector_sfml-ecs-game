#include "System/RenderSystem.h"
#include "Components/SpriteSheetComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

void RenderSystem::OnUpdate(float delta)
{

}

void RenderSystem::OnDraw(sf::RenderWindow& window, float delta)
{
	for (auto& [entityIndex, components] : EntityManager::GetEntityMap())
	{
		auto* sprite = EntityManager::GetComponentFromEntityIndex<SpriteComponent>(entityIndex);
		auto* spriteSheet = EntityManager::GetComponentFromEntityIndex<SpriteSheetComponent>(entityIndex);
		auto* transform = EntityManager::GetComponentFromEntityIndex<TransformComponent>(entityIndex);
		
		if (sprite) 
		{
			window.draw(sprite->sprite);
			if (transform) 
			{
				sprite->sprite.setPosition(transform->position);
				sprite->sprite.setRotation(transform->rotation);
				sprite->sprite.setScale(transform->scale);
			}
		}
		if (spriteSheet) 
		{
			spriteSheet->playedRow = (spriteSheet->playedRow + 1) % spriteSheet->row;
			spriteSheet->sprite.setTextureRect(spriteSheet->m_rects[spriteSheet->playedCol][spriteSheet->playedRow]);
			window.draw(spriteSheet->sprite);
			if (transform) 
			{
				spriteSheet->sprite.setPosition(transform->position);
				spriteSheet->sprite.setRotation(transform->rotation);
				spriteSheet->sprite.setScale(transform->scale);
			}
		}
	}
}
