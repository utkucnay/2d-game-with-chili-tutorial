#include "Gold.h"


Gold::Gold(const Vec2& pos)
	:
	pos(pos)
{

}

void Gold::Draw(Graphics& gfx) const
{
	const auto draw_pos = pos;
	gfx.DrawSprite(int(draw_pos.x), int(draw_pos.y), *goldSurface, SpriteEffect::Chroma{ Colors::Cyan },false );
}

RectF Gold::GetHitbox()
{
	return RectF(pos.x,pos.x+5,pos.y,pos.y+5);
}

void Gold::Hide()
{
	pos.x = -15;
	pos.y = -50;
}

