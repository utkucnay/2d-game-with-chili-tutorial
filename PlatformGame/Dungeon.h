#pragma once

#include "Mario.h"
#include "Background.h"
#include "Keyboard.h"
#include <random>
#include <vector>
#include "Gold.h"
#include<vector>

class Dungeon
{
public:
	Dungeon(const RectI& screenRect);
	void HandleInput(Keyboard& kbd);
	void Update(float dt);
	char MinCalLeftRight(RectF x, RectF y);
	char MinCalTopBot(RectF x, RectF y);
	void Draw(Graphics& gfx) const;
	const Mario& GetMarioConst() const;
	const Boundary& GetBoundsConst() const;
private:
	Background bg1;
	Mario mario = Vec2{ 200,80.0f };
	// boundary that characters must remain inside of
	Boundary bounds = RectF{ 0.0f,805.0f,0.0f,605.0f };
	Gold gold = Vec2{ 50,250 };
};