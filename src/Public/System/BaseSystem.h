#pragma once
#include <SFML/Graphics.hpp>


class System 
{
public:
	virtual void OnUpdate(float delta) = 0;
	virtual void OnDraw(sf::RenderWindow& window, float delta) = 0;
};