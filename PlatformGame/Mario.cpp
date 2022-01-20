#include "Mario.h"
#include "Keyboard.h"
#include "Dungeon.h"

Mario::Mario(const Vec2& pos)
	:
	pos(pos)
	
{
	const auto Walking = Codex<Surface>::Retrieve(L"Images\\MarioSprint.bmp");
	
	animations.emplace_back(Animation(0, 0, 48, 48, 2, Walking, 0.1f));
}

void Mario::Draw(Graphics& gfx) const
{
	dec.DrawChili(gfx);

}

void Mario::HandleInput(Keyboard& kbd)
{
	Vec2 dir = { 0.0f,0.0f };

	if (kbd.KeyIsPressed(VK_LEFT))
	{
		if (Move)
		{
			dir.x -= 1.0f;

		}
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		if (Move)
		{
			dir.x += 1.0f;
		}
		
	}
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		if (!jump)
		{
			jumpVec.y = -9.0f;
			jump = true;
		}
	}
	SetDirection(dir);
}

Vec2 Mario::Jump(float dt) {
	
	if (jump)
	{
		jumpVec.y += 0.2f;
		return jumpVec;
	}
 	else if (jumpVec.y < 0)
	{
		jump = false;
	}
	else
	{
		return Vec2(0, 0);
	}
}

void Mario::SetDirection(const Vec2& dir)
{
	
	// x vel determines direction
	if (dir.x > 0.0f)
	{
		iCurSequence = AnimationSequence::Walking;
		facingRight = false;
	}
	else if (dir.x < 0.0f)
	{
		iCurSequence = AnimationSequence::Walking;
		facingRight = true;
	}
	
	// completely stationary
	else
	{
		// direction remains same as last moving dir
		// just set animation
		iCurSequence = AnimationSequence::Standing;
	}
	if (jump)
	{
		iCurSequence = AnimationSequence::Air;
	}
	vel = dir * speed;
}

void Mario::Update(Dungeon& dungeon, float dt)
{
	pos += vel * dt;
	
	pos.y += gravity + Jump(dt).y;

	dungeon.GetBoundsConst().Adjust(*this);
	animations[0].Update(dt);
}

void Mario::DisplaceBy(const Vec2& d)
{
	pos += d;
}


void Mario::SetStation(char TopBottom,char LeftRight) {
	if (TopBottom == 'T')
	{
		pos.y -= gravity;
		jump = false;
	}
	if (TopBottom == 'B')
	{
		jumpVec.y=0;
	}
	if (LeftRight == 'R')
	{
		pos.x -= 5.0f;
	}
	if (LeftRight == 'L')
	{
		pos.x += 5.0f;
	}
}

RectF Mario::GetHitbox() const
{
	return RectF(pos.x,pos.x +40 ,pos.y ,pos.y+50);
}

bool Mario::GetJump() {
	return jump;
}

Mario::AnimationController::AnimationController(Mario& parent)
	:
	parent(parent)
{}

void Mario::AnimationController::Update(float dt)
{

}

void Mario::AnimationController::DrawChili(Graphics& gfx) const
{
	const auto draw_pos = parent.pos;
	const auto draw_posvei = Vei2(draw_pos);
	switch ((int)parent.iCurSequence)
	{
	case 0:
		parent.animations[0].Draw(draw_posvei,gfx,parent.facingRight);
		break;
	case 1:
		gfx.DrawSprite(int(draw_pos.x), int(draw_pos.y), *parent.MarioIdle,
			SpriteEffect::Chroma{ Colors::Magenta },
			parent.facingRight);
		break;
	case 2:
		gfx.DrawSprite(int(draw_pos.x), int(draw_pos.y), *parent.MarioUp,
			SpriteEffect::Chroma{ Colors::Magenta },
			parent.facingRight);
		break;
	}

	
	
}

