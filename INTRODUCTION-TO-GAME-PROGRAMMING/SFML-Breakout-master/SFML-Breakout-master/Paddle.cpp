#include "Paddle.hpp"

// Public member functions
Paddle::Paddle(sf::Vector2f position, sf::Color color, sf::Vector2f size) :
	m_Paddle(sf::Vector2f(size.x, size.y)) {
	// Set up paddle
	m_Paddle.setFillColor(color);
	m_Paddle.setOrigin((size.x / 2.f), (size.y / 2.f));
	m_Paddle.setPosition(position);
}

Paddle::~Paddle() {

}

void Paddle::Move(const int position, const int windowWidth) {
	// Get bounds
	float radius = (m_Paddle.getGlobalBounds().width / 2);

	// Set the position
	if((position - radius) > 0 && (position + radius) < windowWidth)
		m_Paddle.setPosition(position, m_Paddle.getPosition().y);
}

// Private member functions
void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_Paddle);
}