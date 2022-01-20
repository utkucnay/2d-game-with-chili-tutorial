#pragma once
#include "SpriteEffect.h"
#include "Codex.h"
#include "Rect.h"

class Gold
{
public:
public:
	Gold(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	RectF GetHitbox();
	void Hide();

private:
	Vec2 pos;
	const Surface* goldSurface = Codex<Surface>::Retrieve(L"Images\\gold.bmp");

};