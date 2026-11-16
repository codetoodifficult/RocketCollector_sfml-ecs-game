#include "System/PlayerSystem.h"
#include "Components/SpriteSheetComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

sf::Vector2f MousePosition;
sf::Vector2f m_previousMousePosition{};
sf::Vector2f m_smoothedMouseDelta{};
sf::Vector2f velocity;

float m_targetRotation = 0.f;

bool m_mouseInitialized = false;

void PlayerSystem::OnUpdate(float delta)
{
    auto* transform = EntityManager::GetComponentFromEntityIndex<TransformComponent>(1);

    if (!transform)
        return;

    if (!m_mouseInitialized)
    {
        m_previousMousePosition = MousePosition;
        m_mouseInitialized = true;
        return;
    }

    sf::Vector2f mouseDelta = MousePosition - m_previousMousePosition;
    m_previousMousePosition = MousePosition;
    float rotationAlpha = 1.f - std::exp(-25.f * delta);
    m_smoothedMouseDelta += (mouseDelta - m_smoothedMouseDelta) * rotationAlpha;

    if (m_smoothedMouseDelta.length() > 0.15f)
    {
        m_targetRotation = m_smoothedMouseDelta.angle().asDegrees();
    }

    float currentRotation = transform->rotation.asDegrees();
    float angleDiff = std::remainder(
        m_targetRotation - currentRotation,
        360.f
    );
    velocity = MousePosition - transform->position;
    currentRotation += angleDiff * rotationAlpha;
    transform->rotation = sf::degrees(currentRotation);
    transform->position = MousePosition;
}

void PlayerSystem::OnDraw(sf::RenderWindow& window, float delta)
{
	MousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    auto* spriteSheet = EntityManager::GetComponentFromEntityIndex<SpriteSheetComponent>(1);
    spriteSheet->sprite.setRotation(spriteSheet->sprite.getRotation() + sf::degrees(90.f));
    if (velocity.length() < 1) {
        spriteSheet->playedCol = 0;
    }else if (velocity.length() > 2) {
        spriteSheet->playedCol = 1;
        if (velocity.length() > 4) {
            spriteSheet->playedCol = 2;
            if (velocity.length() > 8) {
                spriteSheet->playedCol = 3;
            }
        }
    }
}



 