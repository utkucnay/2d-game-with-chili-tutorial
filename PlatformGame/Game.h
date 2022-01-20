#pragma once


//#include "Graphics.h"
#include <random>
#include "FrameTimer.h"
#include "Dungeon.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
private:
	MainWindow& wnd;
	Graphics gfx;
	Dungeon dungeon;
	FrameTimer ft;
};
