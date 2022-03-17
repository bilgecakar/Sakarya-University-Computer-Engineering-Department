#include <iostream>
#include "Ball.hpp"

// Public member functions
Ball::Ball(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity) :
	m_Ball(radius),
	m_Velocity(velocity) {
	// Set up ball
	m_Ball.setOrigin(radius, radius);
	m_Ball.setFillColor(color);
	m_Ball.setPosition(position);

	// Setup sound
	if(!m_BounceBuffer.loadFromFile("sounds/bounce.wav"))
		std::cout << "Failed to load sounds/bounce.wav" << std::endl;
	m_BounceSound.setBuffer(m_BounceBuffer);

	if(!m_BrickBuffer.loadFromFile("sounds/brick1.wav"))
		std::cout << "Failed to load sounds/brick1.wav" << std::endl;
	m_BrickSound.setBuffer(m_BrickBuffer);
}

Ball::~Ball() {

}

void Ball::Move(const sf::Time& deltaTime, const sf::Vector2u& windowSize, 
				const Paddle& paddle, std::vector<Brick*>& bricks, 
				int& lives, int& score) {
	// Get ball position
	sf::Vector2f pos = m_Ball.getPosition();

	// Bounce off walls or paddle
	if(pos.x < m_Ball.getRadius() || pos.x > windowSize.x - m_Ball.getRadius() ||
	   pos.y < m_Ball.getRadius() ||
	   paddle.GetBounds().intersects(m_Ball.getGlobalBounds())) {
		// If bounce off sides
		if(pos.x < m_Ball.getRadius() || pos.x > windowSize.x - m_Ball.getRadius())
			m_Velocity = sf::Vector2f(m_Velocity.x * -1.f, m_Velocity.y);

		// Bounce off top
		if(pos.y < m_Ball.getRadius())
			m_Velocity = sf::Vector2f(m_Velocity.x, m_Velocity.y * -1.f);

		// Bounce off paddle
		if(paddle.GetBounds().intersects(m_Ball.getGlobalBounds()))
			m_Velocity = sf::Vector2f(m_Velocity.x, m_Velocity.y * -1.f);

		// Play ball bouncing effects
		BounceFX(m_BounceSound);
	}

	// If hit bottom
	if(pos.y > (windowSize.y - m_Ball.getRadius())) {
		lives--;

		// Move ball out of paddle
		m_Ball.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	}

	// Check brick collisions
	std::vector<Brick*>::iterator itr;
	for(itr = bricks.begin(); itr != bricks.end(); itr++) {
		if(*itr != NULL && (**itr).GetBounds().intersects(m_Ball.getGlobalBounds())) {
			// Bounce ball (incorrectly)
			m_Velocity = sf::Vector2f(m_Velocity.x, m_Velocity.y * -1.f);

			// Delete brick
			delete *itr;
			*itr = NULL;

			score += 10;
			BounceFX(m_BrickSound);
		}
	}

	// Move the ball
	m_Ball.move(m_Velocity * deltaTime.asSeconds());
}

// Private member functions
void Ball::BounceFX(sf::Sound& sfx) {
	// Play bounce sound
	sfx.play();
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_Ball);
}