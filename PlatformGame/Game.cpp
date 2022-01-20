#include "MainWindow.h"
#include "Game.h"

//#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	dungeon(gfx.GetScreenRect())
{}

void Game::Go()
{
	gfx.BeginFrame(Colors::Blue);
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
#ifdef NDEBUG
	const auto dt = ft.Mark();
#else
	const auto dt = 1.0f / 60.0f;
#endif
	dungeon.HandleInput(wnd.kbd);
	dungeon.Update(dt);
}

void Game::ComposeFrame()
{
	dungeon.Draw(gfx);
}
