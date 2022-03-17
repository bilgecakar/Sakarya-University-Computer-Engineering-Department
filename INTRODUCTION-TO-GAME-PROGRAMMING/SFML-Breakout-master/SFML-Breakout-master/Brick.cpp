#include "Brick.hpp"

// Public member functions
Brick::Brick(sf::Vector2f size, sf::Vector2f position, sf::Color color) :
	m_Brick(size)
{
	// Set up brick
	m_Brick.setPosition(position);
	m_Brick.setFillColor(color);
}

Brick::~Brick() {

}

// Private member functions
void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_Brick);
}

void Brick::Hurt() {
	m_Health--;
}

void Brick::Break() {
	
}