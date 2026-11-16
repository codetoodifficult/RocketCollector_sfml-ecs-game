#pragma once
#include "Entity/BaseEntity.h"
#include "Components/SpriteSheetComponent.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Components/BoxCollisionComponent.h"
#include <SFML/Graphics.hpp>


struct Coin : public Entity
{
    Coin()
    {
        EntityIndex = 2;
        EntityComponents.emplace_back(
            std::make_unique<SpriteSheetComponent>("img/coin.png", 128, 128, 64, 64)
        );

        EntityComponents.emplace_back(
            std::make_unique<TransformComponent>(sf::Vector2f(400, 400), sf::degrees(0.0f), sf::Vector2f{0.5f, 0.5f})
        );

        EntityComponents.emplace_back(
            std::make_unique<BoxCollisionComponent>(sf::IntRect({400,400}, {32,32}))
        );
    }
};