#include <iostream>
#include <string>

#include "Game.hpp"

// Private member variables
const sf::Time Game::FPS = sf::seconds(1.f / 60.f);
bool Game::ShowFPS = false;

// Public member functions
Game::Game() :
	m_Window(sf::VideoMode(600, 800), "Breakout!"),
	m_Player(sf::Vector2f((m_Window.getSize().x / 2.f), (m_Window.getSize().y - 70.f))),
	m_Ball(5.f, sf::Color::Yellow, sf::Vector2f(m_Window.getSize().x / 2.f, m_Window.getSize().y / 2.f)),
	m_Lives(3),
	m_Score(0),
	m_Font(),
	m_LivesText(),
	m_ScoreText(),
	m_DrawFPSText(),
	m_DrawFPSFrames(0),
	m_DrawFPSTime()
{
	// Center window on screen
	int taskbarHeight = 40;
	int winX = (sf::VideoMode::getDesktopMode().width / 2) -
		(m_Window.getSize().x / 2);
	int winY = (sf::VideoMode::getDesktopMode().height / 2) -
		(m_Window.getSize().y / 2) - taskbarHeight;

	m_Window.setPosition(sf::Vector2i(winX, winY));

	// Setup debug
	if(!m_Font.loadFromFile("fonts/OpenSans-Regular.ttf"))
		std::cout << "Debug font failed to load." << std::endl;

	m_DrawFPSText.setFont(m_Font);
	m_DrawFPSText.setColor(sf::Color::White);
	m_DrawFPSText.setPosition(5.f, 5.f);
	m_DrawFPSText.setCharacterSize(10);

	// Set up game text
	m_LivesText.setFont(m_Font);
	m_LivesText.setColor(sf::Color::White);
	m_LivesText.setPosition(15.f, m_Window.getSize().y - 30.f);
	m_LivesText.setCharacterSize(20);
	m_LivesText.setString("Lives: " + std::to_string(m_Lives));

	m_ScoreText.setFont(m_Font);
	m_ScoreText.setColor(sf::Color::White);
	m_ScoreText.setPosition(400.f, m_Window.getSize().y - 30.f);
	m_ScoreText.setCharacterSize(20);
	m_ScoreText.setString("Score: " + std::to_string(m_Score));

	// Create a level
	CreateLevel();
}

Game::~Game() {
	std::vector<Brick*>::iterator itr;
	for(itr = m_Level.begin(); itr != m_Level.end(); itr++) {
		delete *itr;
		*itr = NULL;
	}

	m_Level.clear();
}

void Game::Run() {
	// Run the game
	sf::Clock deltaClock;
	sf::Time lastUpdate = sf::Time::Zero;

	while(m_Window.isOpen() && m_Lives > 0) {
		// Fixed time step
		sf::Time deltaTime = deltaClock.restart();
		lastUpdate += deltaTime;

		// Time step loop
		while(lastUpdate > FPS) {
			lastUpdate -= FPS;

			// Update at regular intervals
			ProcessEvents();
			Update(FPS);
		}

		// Toggle FPS
		if(ShowFPS)
			DrawFPS(deltaTime);

		// Render
		Render();
	}
}

// Private member functions
void Game::CreateLevel(int numOfBlocks, int numOfRows, float padding) {
	// Size of brick
	float width = ((m_Window.getSize().x - (padding * (numOfBlocks + 1))) / numOfBlocks);
	sf::Vector2f brickSize(width, 30.f);
	
	float accumRow = padding;

	for(int row = 0; row < numOfRows; row++) {
		float accumCol = padding;
		for(int col = 0; col < numOfBlocks; col++) {
			sf::Vector2f position = sf::Vector2f((col * brickSize.x) + (accumCol), (row * brickSize.y) + accumRow);
			m_Level.push_back(new Brick(brickSize, position, sf::Color::Red));
			accumCol += padding;
		}
		accumRow += padding;
	}
}

void Game::Input(sf::Keyboard::Key key, bool isPressed) {
	// Toggle FPS
	if(key == sf::Keyboard::F6 && !isPressed)
		ShowFPS = !ShowFPS;
}

void Game::ProcessEvents() {
	// Process events and user input
	sf::Event event;
	while(m_Window.pollEvent(event)) {
		switch(event.type) {
		case sf::Event::KeyPressed:
			Input(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			Input(event.key.code, false);
			break;
		case sf::Event::Closed:
			m_Window.close();
			break;
		}
	}
}

void Game::Update(const sf::Time& deltaTime) {
	// Update game logic
	m_Ball.Move(deltaTime, m_Window.getSize(), m_Player, m_Level, m_Lives, m_Score);
	m_Player.Move(sf::Mouse::getPosition(m_Window).x, m_Window.getSize().x);
}

void Game::Render() {
	m_Window.clear();

	// Draw what needs to be draw here
	m_Window.draw(m_Player);
	m_Window.draw(m_Ball);

	std::vector<Brick*>::iterator itr;
	for(itr = m_Level.begin(); itr != m_Level.end(); itr++) {
		if((*itr) != NULL)
			m_Window.draw(**itr);
	}

	// Draw game text
	m_LivesText.setString("Lives: " + std::to_string(m_Lives));
	m_ScoreText.setString("Score: " + std::to_string(m_Score));
	m_Window.draw(m_LivesText);
	m_Window.draw(m_ScoreText);


	// Toggle FPS
	if(ShowFPS)
		m_Window.draw(m_DrawFPSText);

	m_Window.display();
}

void Game::DrawFPS(const sf::Time& deltaTime) {
	m_DrawFPSTime += deltaTime;
	m_DrawFPSFrames += 1;

	if(m_DrawFPSTime >= sf::seconds(1.0f)) {
		m_DrawFPSText.setString(std::to_string(m_DrawFPSFrames) + " FPS");
		m_DrawFPSTime -= sf::seconds(1.0f);
		m_DrawFPSFrames = 0;
	}
}