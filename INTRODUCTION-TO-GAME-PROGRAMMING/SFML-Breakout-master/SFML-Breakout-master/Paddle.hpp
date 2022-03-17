#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable {
// Private member variables
private:
	sf::RectangleShape m_Paddle;

// Private member functions
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

// Public member functions
public:
	Paddle(sf::Vector2f position = sf::Vector2f(30.f, 2.5f),
		   sf::Color color = sf::Color::White,
		   sf::Vector2f size = sf::Vector2f(60.f, 5.f));
	~Paddle();

	void Move(const int position, const int windowWidth);
	sf::FloatRect GetBounds() const { return m_Paddle.getGlobalBounds(); };
};