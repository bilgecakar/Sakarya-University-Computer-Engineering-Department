#ifndef BLOCKS_H
#define BLOCKS_H

#include "pch.h"
#include "Direction.h"

using namespace sf;

class Blocks
{
private:
	RectangleShape body;
	

public:

		bool alive;
		Texture t1,t5;
		bool oldu = false;
		Blocks();
		Blocks(Vector2f size, Vector2f pos);
		void setSize(Vector2f size) { body.setSize(size); }
		void setPosition(Vector2f pos) { body.setPosition(pos); }
		void setFillColor(Texture color) { t1.loadFromFile("brick_yellow_small.png");   body.setTexture(&t1); body.setTextureRect(IntRect(138, 170, 240, 130));
		}
		void kirildi() { t5.loadFromFile("brick_yellow_small_cracked.png"); body.setTexture(&t5); body.setTextureRect(IntRect(138, 170, 240, 130));  oldu = true; }
		Vector2f getPos();

		Vector2f topRight();
		Vector2f topLeft();
		Vector2f bottomRight();
		Vector2f bottomLeft();
		void dissapear();
		void drawTo(RenderWindow& app) { app.draw(this->body); }
		~Blocks() {}

		friend class Ball;

    protected:

    
};

#endif // BLOCKS_H
