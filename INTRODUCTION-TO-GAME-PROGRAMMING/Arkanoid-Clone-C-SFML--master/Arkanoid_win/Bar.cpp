#include "pch.h"
#include "Bar.h"
#include <iostream>


using namespace sf;

Bar::Bar(Vector2f size, double height, double x_pos, Texture tcolor, RenderWindow& window)
{
    t3.loadFromFile("bat_pink.png");
    body.setTexture(&t3);
    body.setTextureRect(IntRect(30, 150, 100, 480));
    body.setSize({100,80});
    body.setOutlineColor(Color::White);
    body.setOutlineThickness(1);
    body.setPosition(x_pos - body.getSize().x/2, window.getSize().y - height - body.getSize().y+30);
   
    isMoving = false;
	pause = false;
}

void Bar::move(Direction dir, double time)
{
	if (pause) return;
	if (dir != R && dir != L)
    {
        std::cout << "Invalid Move" << std::endl;
        return;
    }
    isMoving = true;
    int dirInt = (dir == R? 1: -1);
    body.move(vel * dirInt * time, 0);
}

void Bar::setPos(double x)
{
	body.setPosition(x - body.getSize().x/2, body.getPosition().y);
}

void Bar::drawTo(RenderWindow& app)
{
    app.draw(this->body);
}

void Bar::setVel(double v)
{
    vel = v;
}

double Bar::getVel()
{
    return vel;
}

Vector2f Bar::topRight()
{
	return Vector2f(body.getPosition().x + body.getSize().x,
		body.getPosition().y);
}

Vector2f Bar::topLeft()
{
	return body.getPosition();
}

Vector2f Bar::bottomRight()
{
	return Vector2f(body.getPosition().x + body.getSize().x,
		body.getPosition().y + body.getSize().y);
}

Vector2f Bar::bottomLeft()
{
	return Vector2f(body.getPosition().x,
					body.getPosition().y + body.getSize().y);
}

Vector2f Bar::pos()
{
    return body.getPosition();
}
Bar::~Bar()
{
    //dtor
}
