#include "pch.h"
#include "Blocks.h"

using namespace sf;

Blocks::Blocks() :body(Vector2f(0, 0)), alive(true)
{


}

Blocks::Blocks(Vector2f size, Vector2f pos)
{
	body.setSize(size);
	body.setPosition(pos);

}

Vector2f Blocks::topRight()
{
	return Vector2f(body.getPosition().x + body.getSize().x, 
					body.getPosition().y);
}

Vector2f Blocks::topLeft()
{
	return body.getPosition();
}

Vector2f Blocks::bottomRight()
{
	return Vector2f(body.getPosition().x + body.getSize().x,
					body.getPosition().y + body.getSize().y);
}

Vector2f Blocks::bottomLeft()
{
	return Vector2f(body.getPosition().x,
					body.getPosition().y + body.getSize().y);;
}

Vector2f Blocks::getPos()
{
	return body.getPosition();
}

void Blocks::dissapear()
{
	body.setPosition(1e7, 1e7);
	alive = false;
}
