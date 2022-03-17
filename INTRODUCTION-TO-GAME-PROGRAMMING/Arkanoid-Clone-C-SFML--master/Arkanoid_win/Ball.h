#ifndef BALL_H
#define BALL_H

#include "pch.h"
#include "Direction.h"
#include "Bar.h"
#include "Blocks.h"

using namespace sf;

class Game_Control; //forward declaration to resolve circular dependency

class Ball
{
    public:
		bool pause;
        Texture t2;
		Ball(double rad, Vector2f pos, Texture color);
        void move(double time, Bar& bar);
		int collision(Bar & bar, std::vector<Blocks> & grid, RenderWindow & app, Game_Control & game);
        void setVel(double xv, double yv) {dx = xv; dy = yv;}
        inline double DX() {return dx;}
        inline double DY() {return dy;}
		inline Vector2f centrePos();
        void drawTo(RenderWindow& app) {app.draw(body);}
		void speedup(double by) { dx += by, dy += by; }
        ~Ball();

        friend class Bar;

    protected:

    private:
        CircleShape body;
        double dx;
        double dy;
};

#endif // BALL_H
