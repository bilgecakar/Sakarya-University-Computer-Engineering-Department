#pragma once

#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable {
// Private member variables
private:
	sf::RectangleShape m_Brick;
	short m_Health;

// Private member functions
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

// Public member functions
public:
	Brick(sf::Vector2f size = sf::Vector2f(60.f, 40.f), 
		  sf::Vector2f position = sf::Vector2f(0.f, 0.f),
		  sf::Color color = sf::Color::Green);
	~Brick();

	sf::FloatRect GetBounds() const { return m_Brick.getGlobalBounds(); }
	void Hurt();
	void Break();
};