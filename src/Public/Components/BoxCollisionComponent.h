#pragma once

#include "Components/BaseComponent.h"
#include <SFML/Graphics.hpp>


class BoxCollisionComponent : public Component
{
public:
    BoxCollisionComponent(sf::IntRect InBox)
        :box(InBox)
    {
    }

    sf::IntRect box;
};