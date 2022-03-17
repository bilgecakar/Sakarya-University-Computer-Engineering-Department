#include "pch.h"
#include "Ball.h"
#include "Game_Control.h"

using namespace sf;

inline double dist(Vector2f a, Vector2f b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Ball::Ball(double rad, Vector2f pos, Texture color)
    :body(rad)
{
	t2.loadFromFile("ball_orange.png");
    body.setPosition(pos);
    body.setTexture(&t2);
	pause = false;
}

void Ball::move(double time, Bar& bar)
{
    if (!pause) body.move(dx * time, dy * time);
}

int Ball::collision(Bar & bar, std::vector <Blocks> & grid, RenderWindow & app, Game_Control & game)
{

	/////// Boundary ///////
	if (body.getPosition().x <= 0) dx = abs(dx);
	if (body.getPosition().y <= 0) dy = abs(dy);
	if (body.getPosition().x + body.getRadius() * 2 >= app.getSize().x) dx = -abs(dx);
	if (body.getPosition().y > app.getSize().y)
	{
		game.gameOver();
		dy *= -1;
	}

	/////// Bar /////////

	if (this->body.getGlobalBounds().intersects(bar.body.getGlobalBounds()))
	{
		dy = -dy;
		if (bar.topRight().y - centrePos().y <= 3)
			dx *= -1;
	}

	/////// Blocks ///////
	for (Blocks & block: grid)
	{
		if (body.getGlobalBounds().intersects(block.body.getGlobalBounds()))
		{
			if (body.getPosition().y + body.getRadius() <= block.body.getPosition().y + block.body.getSize().y
			and body.getPosition().y + body.getRadius() >= block.body.getPosition().y)
			{
				dx *= -1;
			}
			else if (dist(this->centrePos(), block.topRight()) <= this->body.getRadius()
				or dist(this->centrePos(), block.topLeft()) <= this->body.getRadius()
				or dist(this->centrePos(), block.bottomLeft()) <= this->body.getRadius()
				or dist(this->centrePos(), block.bottomRight()) <= this->body.getRadius())
			{
				dx *= -1;
				dy *= -1;
			}
			else
			{
				dy *= -1;
			}
		

			if (block.oldu == true)
			{
				block.dissapear();
			}

			block.kirildi();
			
			
			return 1;
		}
	}
	if (std::all_of(grid.begin(), grid.end(), [](Blocks& i) {return !(i.alive); }))
	{
		game.gameOver();
	}

	return 0;
}

Vector2f Ball::centrePos()
{
	return Vector2f(body.getPosition().x + body.getRadius(),
					body.getPosition().y + body.getRadius());
}

Ball::~Ball()
{
    //dtor
}
