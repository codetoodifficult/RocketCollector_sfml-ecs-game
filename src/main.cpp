#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Coin.h"
#include "System/RenderSystem.h"
#include "System/PlayerSystem.h"
#include "System/CoinSystem.h"

int main()
{
	/*配置项*/
	std::string title = "SFML ECS";
	float delta;
	int FPS_limit{60};

	/*窗口*/
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), title, sf::Style::Close, sf::State::Windowed);
	window.setFramerateLimit(FPS_limit);
	window.setMouseCursorVisible(false);
	bool focus = window.hasFocus();
	bool fullscreen = false;

	/*实体和系统的注册*/
	EntityManager::Init();
	EntityManager::RegisterEntity<Player>();
	EntityManager::RegisterEntity<Coin>();
	EntityManager::RegisterSystem<RenderSystem>();
	EntityManager::RegisterSystem<PlayerSystem>();
	EntityManager::RegisterSystem<CoinSystem>();

	sf::Clock clock;

	const auto onClose = [&window](const sf::Event::Closed&)
	{
		window.close();
	};

	const auto onKeyPressed = [&](const sf::Event::KeyPressed& keyPressed)
	{
		if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
			window.close();
		else if (keyPressed.scancode == sf::Keyboard::Scancode::Enter) 
		{
			if (fullscreen) {
				window.create(sf::VideoMode({ 800,600 }), title, sf::State::Windowed);
				window.setFramerateLimit(FPS_limit);
			}
			else 
			{
				window.create(sf::VideoMode::getDesktopMode(), "", sf::State::Fullscreen);
				window.setFramerateLimit(FPS_limit);
			}
			fullscreen = !fullscreen;
		}
	};

	const auto onKeyReleased = [&](const sf::Event::KeyReleased& keyReleased)
	{

	};

	const auto onMouseMoved = [&](const sf::Event::MouseMoved& mouseMoved)
	{
			std::cout << "new mouse x: " << mouseMoved.position.x << std::endl;
			std::cout << "new mouse y: " << mouseMoved.position.y << std::endl;
	};

	const auto onFocusLost = [&](const sf::Event::FocusLost& FocusLost)
	{
		

	};

	const auto onFocusGained = [&](const sf::Event::FocusGained& FocusGained)
	{


	};

	const auto onUpdate = [&]()
	{
		EntityManager::OnUpdate(delta);
	};

	const auto onDraw = [&]()
	{
		window.clear();
		EntityManager::OnDraw(window, delta);
		window.display();
	};

	while (window.isOpen())
	{
		delta = clock.restart().asSeconds();
		window.handleEvents(onClose, onKeyPressed, onKeyReleased, onMouseMoved);
		onUpdate();
		onDraw();
	}
}
