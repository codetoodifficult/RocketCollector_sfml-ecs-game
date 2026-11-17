#include "EntityManager.h"

void EntityManager::RemoveEntity(int InEntityIndex)
{
	m_entitys->erase(InEntityIndex);
}

const std::unordered_map<int, std::vector<std::unique_ptr<Component>>>& EntityManager::GetEntityMap()
{
	return *m_entitys;
}

void EntityManager::OnUpdate(float delta) 
{
	if (m_systems == nullptr) return;
	for (auto& system : *m_systems)
	{
		system->OnUpdate(delta);
	}
}

void EntityManager::OnDraw(sf::RenderWindow& window, float delta)
{
	if (m_systems == nullptr) return;
	for (auto& system : *m_systems)
	{
		system->OnDraw(window, delta);
	}
}
