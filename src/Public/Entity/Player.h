#pragma once
#include "Entity/BaseEntity.h"
#include "Components/SpriteSheetComponent.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include <SFML/Graphics.hpp>


struct Player : public Entity
{
    Player()
    {
        EntityIndex = 1;
        EntityComponents.emplace_back(
            std::make_unique<SpriteSheetComponent>("img/rocket.png", 128, 128, 64, 64)
        );

        EntityComponents.emplace_back(
            std::make_unique<TransformComponent>(sf::Vector2f(100, 100))
        );
    }
};