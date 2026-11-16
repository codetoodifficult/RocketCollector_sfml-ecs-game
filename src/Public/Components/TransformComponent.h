#pragma once

#include "Components/BaseComponent.h"
#include <SFML/Graphics.hpp>


class TransformComponent : public Component
{
public:
    TransformComponent(sf::Vector2f InPosition, sf::Angle InRotation = sf::degrees(0.0f), sf::Vector2f InScale = sf::Vector2f(1.0f, 1.0f))
        :position(InPosition), rotation(InRotation), scale(InScale)
    {
    }

    sf::Vector2f position;
    sf::Angle rotation;
    sf::Vector2f scale{ 1.0f, 1.0f };
};