#pragma once

#include "Components/BaseComponent.h"
#include <SFML/Graphics.hpp>

class SpriteSheetComponent : public Component
{
public:
	SpriteSheetComponent(const std::string& InAddress, int width, int height, float originX = 0.0f, float originY = 0.0f)
		: texture(InAddress), sprite(texture)
	{
		if (width <= 0 || height <= 0) return;

		row = texture.getSize().x / width;
		col = texture.getSize().y / height;

		m_rects = std::vector<std::vector<sf::IntRect>>(col, std::vector<sf::IntRect>(row));
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				m_rects[i][j] = sf::IntRect({ j * width, i * height }, { width, height });
			}
		}
		sprite.setTextureRect(m_rects[0][0]);
		sprite.setOrigin({ originX, originY });
	}

	
private:
	sf::Texture texture;

public:
	sf::Sprite sprite;
	std::vector<std::vector<sf::IntRect>> m_rects;
	int col = 0;
	int row = 0;
	unsigned int playedCol = 0;
	unsigned int playedRow = 0;
};
