#pragma once
#include "System/BaseSystem.h"
#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class RenderSystem : public System
{
public:
	virtual void OnUpdate(float delta) override;
	virtual void OnDraw(sf::RenderWindow& window, float delta) override;
};