#pragma once
#include <SFML/Graphics.hpp>
#include "System/BaseSystem.h"
#include "EntityManager.h"

class PlayerSystem : public System
{
public:
	virtual void OnUpdate(float delta) override;
	virtual void OnDraw(sf::RenderWindow& window, float delta) override;
};