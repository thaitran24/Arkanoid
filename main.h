#ifndef MAIN_H_
#define MAIN_H_
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Object {
private:
	Sprite sprite;
	Texture t;
	int x;
	int y;
public:
	Object(const char* txtr);
	void setPosition(int x, int y);
	int getX();
	int getY();
	void draw(RenderWindow& app);
	void move(int x, int y);
	FloatRect getGlobalBounds();
	void setTexture(const char* txtr);
};

Object::Object(const char* txtr) {
	t.loadFromFile(txtr);
	this->sprite.setTexture(t);
}

void Object::setTexture(const char* txtr) {
	t.loadFromFile(txtr);
	this->sprite.setTexture(t);
}

void Object::move(int x, int y) {
	this->sprite.move(x, y);
	this->x = this->sprite.getPosition().x;
	this->y = this->sprite.getPosition().y;
}

void Object::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
	this->sprite.setPosition(x, y);
}

int Object::getX() { return this->x; }
int Object::getY() { return this-> y; }

FloatRect Object::getGlobalBounds() {
	return this->sprite.getGlobalBounds();
}

void Object::draw(RenderWindow& app) {
	app.draw(this->sprite);
}

class Ball : public Object {
public:
	Ball() : Object("images/ball.png") {}
};

class Block : public Object {
public:
	Block() : Object("images/block01.png") {}
};

class Paddle : public Object {
public:
	Paddle() : Object("images/paddle.png") {}
};

class Game {
private:
	Ball ball;
	Paddle paddle;
	Block block[1000];
	int block_count; 
	int life_count;
	int life_count_nor;
	int point;
public:
	Game();
	void screenDisplay();
	void run();
	void newLevel(int level_num, int ver_v, int hor_v, RenderWindow& app);
	void newLevelNor(int level_num, int ver_v, int hor_v, RenderWindow& app);
	void runNor();
};


Game::Game() {
	this->life_count = 3;
	this->life_count_nor = 6;
	this->point = 0;
}

void Game::newLevel(int level_num, int ver_v, int hor_v, RenderWindow& app) {
	Texture t;
	t.loadFromFile("images/background_1.png");
	this->ball.setTexture("images/ball.png");
	this->paddle.setTexture("images/paddle.png");
	Sprite background(t);
	this->paddle.setPosition(300, 440);
	int n = 0;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			this->block[n].setPosition(i * 43, j * 20);
			this->block[n].setTexture("images/block04.png");
			n++;
		}
	}

	float dx = hor_v, dy = ver_v;
    float x = 300, y = 300;
	block_count = 100;

	while (app.isOpen()) {
       	Event e;
       	while (app.pollEvent(e)) {
         	if (e.type == Event::Closed)
             	app.close();
       }

		x += dx;
		for (int i = 0; i < n; i++) {
			if (this->ball.getY() >= 450) {
				x = 300; y = 250;
				this->ball.setPosition(x, y);
				this->life_count--;
				break;
			}
			if (this->life_count == 0)
				app.close();

			if (FloatRect(x + 3, y + 3, 6, 6).intersects(this->block[i].getGlobalBounds())) {
				this->block[i].setPosition(-100, 0); 
				dx = -dx;
				--block_count;
			}
			if (block_count == 0)
				return;
		}

		y += dy;
		for (int i = 0; i < n; i++) {
			if (this->ball.getY() >= 450) {
				x = 300; y = 250;
				this->ball.setPosition(x, y);
				this->life_count--;
				break;
			}
			if (this->life_count == 0)
				app.close();

			if (FloatRect(x + 3, y + 3, 6, 6).intersects(this->block[i].getGlobalBounds()) ) {
				this->block[i].setPosition(-100, 0); 
				dy = -dy;
				--block_count;
			}
			if (block_count == 0)
				return;
		}

		if (x < 0 || x > 520)  dx = -dx;
		if (y < 0 || y > 450)  dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (this->paddle.getX() < 430)
				this->paddle.move(6, 0);
		} 
		else if (Keyboard::isKeyPressed(Keyboard::Left) && x < 300) {
			if (this->paddle.getX() > 0)
				this->paddle.move(-6, 0);
		}

		if (FloatRect(x, y, 12, 12).intersects(this->paddle.getGlobalBounds())) 
			dy = -dy;

		this->ball.setPosition(x, y);

		app.clear();
		app.draw(background);
		this->ball.draw(app);
		this->paddle.draw(app);

		for (int i = 0; i < n; i++)
			this->block[i].draw(app);

		app.display();
    }
}



void Game::run() {
	srand(time(0));
	RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);
	int level = 0, ver_v = 3, hor_v = 4;
	while (app.isOpen()) {
		this->newLevel(0, ver_v++, hor_v++, app);
	}
}

void Game::runNor() {
	srand(time(0));
	RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);
	int level = 0, ver_v = 3, hor_v = 4;
	while (app.isOpen()) {
		this->newLevelNor(0, ver_v++, hor_v++, app);
	}
}


void Game::newLevelNor(int level_num, int ver_v, int hor_v, RenderWindow& app) {
    Texture t1, t2, t3, t4;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/background_1.png");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

    Sprite background(t2), ball(t3), paddle(t4);
    paddle.setPosition(300, 440);

    Sprite block[1000];

    int n = 0;
    for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}
	}

    float dx = ver_v, dy = hor_v;
    float x = 300, y = 300;
	int block_count = 100;

    while (app.isOpen()) {
       	Event e;
       	while (app.pollEvent(e)) {
         	if (e.type == Event::Closed)
             	app.close();
       }

		x += dx;
		for (int i = 0; i < n; i++) {
			if (ball.getPosition().y > 450) {
				this->life_count_nor--;
				break;
			}

			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds())) {
				block[i].setPosition(-100, 0); 
				dx = -dx;
				--block_count;
			}

			if (block_count == 0)
				return;
		}

		if (this->life_count_nor == 0)
			app.close();

		y += dy;

		for (int i = 0; i < n; i++) {
			if (ball.getPosition().y > 450) {
				this->life_count_nor--;
				break;
			}

			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()) )  {
				block[i].setPosition(-100, 0); 
				dy = -dy;
				--block_count;
			}

			if (block_count == 0)
				return;
		}

		if (this->life_count_nor == 0)
			app.close();

		if (x < 0 || x > 520)  dx = -dx;
		if (y < 0 || y > 450)  dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (paddle.getPosition().x < 430)
				paddle.move(6, 0);
		} 
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (paddle.getPosition().x > 0)
			paddle.move(-6, 0);
		}

		if (FloatRect(x , y, 12, 12).intersects(paddle.getGlobalBounds())) 
			dy = -dy;

		ball.setPosition(x, y);

		app.clear();
		app.draw(background);
		app.draw(ball);
		app.draw(paddle);

		for (int i = 0; i < n; i++)
			app.draw(block[i]);
		app.display();
    }
}

#endif