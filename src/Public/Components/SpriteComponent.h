#pragma once

#include "Components/BaseComponent.h"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component
{
public:
	SpriteComponent(const std::string& InAddress, float originX = 0.0f, float originY = 0.0f)
		: texture(InAddress), sprite(texture)
	{
		sprite.setOrigin({ originX, originY });
	}

	
private:
	sf::Texture texture;

public:
	sf::Sprite sprite;
};
