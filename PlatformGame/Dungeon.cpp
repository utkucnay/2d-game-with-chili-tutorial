#include "Dungeon.h"
#include "Background.h"
#include <functional>
#include <vector>

// these are the layout strings for the scenery (background tilemaps)
const std::string layer1 =
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAABBBBBBBBBB"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAABBBBBBBBAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"BBBBBBBAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAABBBBBBAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAABBBBBBB"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAA"
"BBBBBBBBBBBBBBBBBBBBBBBBB"
"BBBBBBBBBBBBBBBBBBBBBBBBB"
"BBBBBBBBBBBBBBBBBBBBBBBBB";

Dungeon::Dungeon(const RectI& screenRect)
	:
	bg1(screenRect, 25, 19, layer1)
{
	bg1.SetHitBox();
}
	

void Dungeon::HandleInput(Keyboard& kbd)
{
	mario.HandleInput(kbd);
	
}

void Dungeon::Update(float dt)
{
	
	mario.Update(*this, dt);
	for (auto obj : bg1.GetHitBox())
	{
		
		if (obj.IsOverlappingWith(mario.GetHitbox()))
		{
			mario.SetStation(MinCalTopBot(obj, mario.GetHitbox()), MinCalLeftRight(obj, mario.GetHitbox()));
		}
	}
	if (gold.GetHitbox().IsOverlappingWith(mario.GetHitbox()))
	{
		gold.Hide();

	}
	
}

char Dungeon::MinCalLeftRight(RectF x, RectF y) {
	auto dist2 = x.left - y.right;
	auto dist3 = x.right - y.left;

	if (-4 < dist2 && dist2 < 30 && y.top > x.top && !mario.GetJump())
	{
		return 'R';
	}
	if (-4 < dist3 && dist3 < 30 && y.top > x.top && !mario.GetJump())
	{
		return 'L';
	}
	
	return ' ';
}



char Dungeon::MinCalTopBot(RectF x,RectF y) {
	
	float min = 700;
	auto dist = x.top - y.bottom;
	auto dist1 = x.bottom - y.top;

	if (-15 < dist && dist < min)
	{
		min = dist;
	}
	if (-15 < dist1 && dist1 < min)
	{
		min = dist1;
	}
	
	if (dist == min)
	{
		return 'T';
	}
	if (dist1 == min)
	{
		return 'B';
	}
}

void Dungeon::Draw(Graphics& gfx) const
{
	mario.Draw(gfx);
	bg1.Draw(gfx);
	
		gold.Draw(gfx);
	
}

const Mario& Dungeon::GetMarioConst() const
{
	return mario;
}

const Boundary& Dungeon::GetBoundsConst() const
{
	return bounds;
}
