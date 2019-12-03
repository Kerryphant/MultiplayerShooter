#pragma once
#include "..\include\Sprite.h"

// Static class provide collision detection functions.
class Collision
{
public:
	//AABB
	static bool checkBoundingBox(Sprite* sp1, Sprite* sp2);
	// Bounding circle
	static bool checkBoundingSphere(Sprite* sp1, Sprite* sp2);

};