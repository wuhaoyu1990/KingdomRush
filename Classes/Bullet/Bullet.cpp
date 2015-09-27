#include "Bullet.h"

Bullet::Bullet()
:sprite(NULL),maxForce(0),bulletScope(0)
{
}

Bullet::~Bullet(){}

bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}