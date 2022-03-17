#include "pch.h"
#include "Direction.h"
#include "Bar.h"
#include "Ball.h"
#include "Blocks.h"
#include "Game_Control.h"
#include <iostream>

using namespace std;
using namespace sf;

#define C_MGreen Color(0, 230, 118)
#define C_MBlack Color(27, 27, 27)

vector <Color> colorChoice
{
	//Color::Cyan,
	C_MGreen
	//Color::Magenta
};

int main()
{
	Texture t1, t2,t3,t4;
	t4.loadFromFile("background.jpg");
	Sprite sBackground(t4);
	srand(time(0));

	const int width = 620;
	const int height = 700;
	Game_Control game;

	RenderWindow app(VideoMode(width, height), "Arkanoid Clone");
	Event event;
	double mousePosX;

	Clock frameT;
	double dt, mul = 100;

	Bar bar(Vector2f(100, 80), 1, width / 2,t3, app);
	bar.setVel(7);

	Ball ball(20, Vector2f(width / 2, height / 2), t2);
	ball.setVel(2.5, 2.5);

	const int grid_x(4);
	const int grid_y(5);
	vector <Blocks> grid(grid_y * grid_x);
	for (int i = 0; i < grid_y; i++)
	{
		for (int j = 0; j < grid_x; j++)
		{
			grid[i*grid_x + j].setSize(Vector2f((float)width / grid_x, (float)height / 2 / grid_y));
			grid[i*grid_x + j].setPosition(Vector2f((float)width / grid_x * j, (float)height / 2 / grid_y * i));
			grid[i*grid_x + j].setFillColor(t1);
		}
	}

	////// Score Text /////////
	int score = 0;
	Text scoreText;
	Font font;
	if (!font.loadFromFile("Content/Fonts/SIMPLIFICA Typeface.ttf"))
	{
		cerr << "Couldn't load font!!" << endl;
	}
	scoreText.setFont(font);
	scoreText.setFillColor(C_MBlack);
	scoreText.setCharacterSize(50);
	scoreText.setStyle(Text::Bold);
	/////////////////////////

	//////// Title //////////
	Text title;
	title.setFont(font);
	title.setString("Arkanoid");
	title.setCharacterSize(200);
	title.setFillColor(C_MBlack);
	title.setPosition(
		width / 2.0 - title.getGlobalBounds().width / 2.0, 
		height / 2.0 - title.getGlobalBounds().height - 75
	);
	Text instruct;
	instruct.setFont(font);
	instruct.setString("Press space to start");
	instruct.setCharacterSize(35);
	instruct.setFillColor(C_MBlack);
	instruct.setPosition(
		width / 2.0 - instruct.getGlobalBounds().width / 2.0,
		height / 2.0 + 20
	);
	////////////////////////

    app.setFramerateLimit(120);
    while(app.isOpen())
    {
        while(app.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::EventType::Closed:
                app.close();
                break;
			case Event::EventType::KeyPressed:
				if (game.GO) app.close();
				switch (event.key.code)
				{
				case Keyboard::Space:
					game.pause = !game.pause;
					break;
				default:
					break;
				}
				break;
            case Event::EventType::KeyReleased:
				if (event.key.code == Keyboard::Right or event.key.code == Keyboard::Left)
					bar.isMoving = false;
				break;
            default:
                break;
            }
        }

        dt = frameT.restart().asSeconds() * mul;
        //cerr << 1 / (dt / mul) << endl;

		ball.pause = game.pause;
		bar.pause = game.pause;
		if (!game.pause) game.start = false;
		
		///////////// Keyboard //////////
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
			bar.move(R, dt);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bar.move(L, dt);
        }
		////////////////////////////////

		/////////// Mouse //////////////
		mousePosX = Mouse::getPosition(app).x;
		if (mousePosX >= bar.getWidth()/2 and mousePosX <= width - bar.getWidth()/2 and !bar.pause)
			bar.setPos(mousePosX);
		////////////////////////////////

        ball.move(dt, bar);
		score += ball.collision(bar, grid, app, game);
		scoreText.setString(to_string(score));
		scoreText.setPosition(width - scoreText.getGlobalBounds().width - 15.f, 5.f);

		/////// draw //////////
        app.clear();
		app.draw(sBackground);


		for (auto& i : grid) i.drawTo(app);
		if (!game.start and !game.GO)
		{
			bar.drawTo(app);
			ball.drawTo(app);
			app.draw(scoreText);
		}
		if (game.start)
		{
			app.draw(title);
			app.draw(instruct);
		}
		if (game.GO)
		{
			scoreText.setCharacterSize(100);
			scoreText.setPosition(
				width / 2 - scoreText.getGlobalBounds().width / 2,
				height / 2 - scoreText.getGlobalBounds().height / 2 - 70
			);
			app.draw(scoreText);
			instruct.setString("Press any key to exit");
			app.draw(instruct);
		}

        app.display();
		//////////////////////
    }

    return 0;
}
