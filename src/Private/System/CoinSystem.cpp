#include "System/CoinSystem.h"
#include "Entity/Coin.h"
#include <random>

float count = 0.f;
bool pick = false;
int score = 0;

void CoinSystem::OnUpdate(float delta)
{
	SpriteSheetComponent* spriteSheet = EntityManager::GetComponentFromEntityIndex<SpriteSheetComponent>(2);
	BoxCollisionComponent* boxCollision = EntityManager::GetComponentFromEntityIndex<BoxCollisionComponent>(2);
	TransformComponent* transform = EntityManager::GetComponentFromEntityIndex<TransformComponent>(2);

	
	if (count >= 3.f || pick == true)
	{
		EntityManager::RemoveEntity(2);
		EntityManager::RegisterEntity<Coin>();
		pick = false;
		spriteSheet = EntityManager::GetComponentFromEntityIndex<SpriteSheetComponent>(2);
		boxCollision = EntityManager::GetComponentFromEntityIndex<BoxCollisionComponent>(2);
		transform = EntityManager::GetComponentFromEntityIndex<TransformComponent>(2);
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> xDist(50, 750);
		std::uniform_int_distribution<int> yDist(50, 550);

		sf::Vector2f coinPos(xDist(rng), yDist(rng));
		if(transform) transform->position = coinPos;
		count = 0;
	}
	
	if (spriteSheet && transform && boxCollision) 
	{
		spriteSheet->sprite.setPosition(transform->position);
		boxCollision->box.position.x = (int)(transform->position.x - boxCollision->box.size.x * 0.5f);
		boxCollision->box.position.y = (int)(transform->position.y - boxCollision->box.size.y * 0.5f);

		TransformComponent* playerTransform = EntityManager::GetComponentFromEntityIndex<TransformComponent>(1);
		if (playerTransform) 
		{
			if (playerTransform->position.x >= boxCollision->box.position.x &&
				playerTransform->position.y >= boxCollision->box.position.y &&
				playerTransform->position.x <= boxCollision->box.position.x + boxCollision->box.size.x &&
				playerTransform->position.y <= boxCollision->box.position.y + boxCollision->box.size.y)
			{
				pick = true;
				score += 1;
			}
		}
	}
	count += delta;
}

void CoinSystem::OnDraw(sf::RenderWindow& window, float delta)
{
	std::string title("Score:");
	title += std::to_string(score);
	window.setTitle(title);
}
