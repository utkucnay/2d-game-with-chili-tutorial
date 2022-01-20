#pragma once

#include "Animation.h"
#include "SpriteEffect.h"
#include "Codex.h"

class Mario
{
private:
	class AnimationController
	{
	public:
		AnimationController(Mario& parent);
		void Update(float dt);
		void DrawChili(Graphics& gfx) const;
	private:
		Mario& parent;
		float time;
	};
	enum class AnimationSequence
	{
		Walking,
		Standing,
		Air
	};
public:
	Mario(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void HandleInput(class Keyboard& kbd);
	void Update(class Dungeon& Dungeon, float dt);
	void DisplaceBy(const Vec2& d);
	void SetStation(char TopBottom, char LeftRight);
	RectF GetHitbox() const;
	bool GetJump();
	Vec2 Jump(float dt);
private:
	void SetDirection(const Vec2& dir);
private:
	const Surface* MarioIdle = Codex<Surface>::Retrieve(L"Images\\Mario2.bmp");
	const Surface* MarioUp = Codex<Surface>::Retrieve(L"Images\\MarioUp.bmp");
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	bool facingRight = false;
	float speed = 110.0f;
	float gravity = 2.5f;
	bool jump = false;
	Vec2 jumpVec;
	bool Move = true;
	AnimationSequence iCurSequence = AnimationSequence::Standing;
	std::vector<Animation> animations;
	AnimationController dec = { *this };
};