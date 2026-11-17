#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Components/BaseComponent.h"
#include "Components/SpriteComponent.h"
#include "System/BaseSystem.h"
#include "Entity/BaseEntity.h"
#include <SFML/Graphics.hpp>


class EntityManager
{
public:
	static void Init()
	{
		if (self_ptr == nullptr) self_ptr = new EntityManager();
		if (m_entitys == nullptr) m_entitys = new std::unordered_map<int, std::vector<std::unique_ptr<Component>>>();
		if (m_systems == nullptr) m_systems = new std::vector<std::unique_ptr<System>>();
	}

	static void Destroy()
	{
		delete self_ptr;
		self_ptr = nullptr;
		delete m_entitys;
		m_entitys = nullptr;
		delete m_systems;
		m_systems = nullptr;
	}

	template<typename T>
	static void RegisterEntity();

	template<typename T>
	static void RegisterSystem();

	static void RemoveEntity(int InEntityIndex);

	template<typename T>
	static void RemoveSystem();

	template<typename T>
	static T* GetComponentFromEntityIndex(int InEntityIndex);

	static const std::unordered_map<int, std::vector<std::unique_ptr<Component>>>& GetEntityMap();

	static void OnUpdate(float delta);
	static void OnDraw(sf::RenderWindow& window, float delta);

	EntityManager(const EntityManager& other) = delete;
private:
	inline static const EntityManager* self_ptr = nullptr;	
	inline static std::unordered_map<int, std::vector<std::unique_ptr<Component>>>* m_entitys = nullptr;
	inline static std::vector<std::unique_ptr<System>>* m_systems;

	EntityManager() = default;
	~EntityManager() = default;
};



template<typename T>
void EntityManager::RegisterEntity()
{
	std::unique_ptr<Entity> entity = std::make_unique<T>();
	m_entitys->emplace(entity->EntityIndex, std::move(entity->EntityComponents));
}

template<typename T>
void EntityManager::RegisterSystem()
{
	m_systems->emplace_back(std::make_unique<T>());
}

template<typename T>
void EntityManager::RemoveSystem()
{
	for (auto it = m_systems->begin(); it < m_systems->end(); it++)
	{
		if (dynamic_cast<T*>(it->get()))
		{
			m_systems->erase(it);
			return;
		}
	}
}

template<typename T>
T* EntityManager::GetComponentFromEntityIndex(int InEntityIndex)
{
	auto it = m_entitys->find(InEntityIndex);
	if (it == m_entitys->end()) return nullptr;

	auto& components = m_entitys->at(InEntityIndex);
	for (auto it = components.begin(); it < components.end(); it++)
	{
		if (T* res = dynamic_cast<T*>(it->get()))
		{
			return res;
		}
	}
	return nullptr;
}
