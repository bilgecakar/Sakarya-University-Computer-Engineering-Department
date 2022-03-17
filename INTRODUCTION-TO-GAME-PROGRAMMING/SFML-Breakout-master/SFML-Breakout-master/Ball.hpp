#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Brick.hpp"
#include "Paddle.hpp"

class Ball : public sf::Drawable {
// Private member variables
private:
	sf::CircleShape m_Ball;
	sf::Vector2f m_Velocity;

	sf::SoundBuffer m_BounceBuffer;
	sf::Sound		m_BounceSound;

	sf::SoundBuffer m_BrickBuffer;
	sf::Sound		m_BrickSound;

// Private member functions
private:
	void BounceFX(sf::Sound& sfx);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

// Public member functions
public:
	Ball(float radius = 5.f, sf::Color color = sf::Color::White,
		 sf::Vector2f position = sf::Vector2f(5.f, 5.f),
		 sf::Vector2f velocity = sf::Vector2f(200.f, 200.f));
	~Ball();

	void Move(const sf::Time& deltaTime, const sf::Vector2u& windowSize, 
			  const Paddle& paddle, std::vector<Brick*>& bricks,
			  int& lives, int& score);
};