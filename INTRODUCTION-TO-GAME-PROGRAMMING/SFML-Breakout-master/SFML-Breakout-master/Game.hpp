#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class Game {
// Private member variables
private:
	static const sf::Time FPS;
	static bool	 ShowFPS;

	sf::RenderWindow	m_Window;
	Paddle				m_Player;
	Ball				m_Ball;
	std::vector<Brick*> m_Level;
	
	int	m_Lives;
	int	m_Score;

	sf::Font	m_Font;
	sf::Text	m_LivesText;
	sf::Text	m_ScoreText;
	sf::Text	m_DrawFPSText;
	std::size_t m_DrawFPSFrames;
	sf::Time	m_DrawFPSTime;

// Private member functions
private:
	void CreateLevel(int numOfBlocks = 5, int numOfRows = 6, float padding = 5.f);

	void Input(sf::Keyboard::Key key, bool isPressed);
	void ProcessEvents();
	void Update(const sf::Time& deltaTime);
	void Render();

	void DrawFPS(const sf::Time& deltaTime);

// Public member functions
public:
	Game();
	~Game();

	sf::Vector2u GetWindowSize() const { return m_Window.getSize(); };
	Paddle* GetPaddle() { return &m_Player; }
	std::vector<Brick*>* GetLevel() { return &m_Level; }

	void Run();
};