#pragma once
#include "..\include\Sprite.h"

class Cursor : public Sprite
{
public:

	Cursor();
	~Cursor();

	//used to switch sprites inside the level vs anywhere else
	enum CursorTexture { POINTER, TARGET };

	void changeTexture(CursorTexture tex_);
	void update(Input* input_);

private:
	
	bool outsideWindow;
	float speed;
	sf::Texture texture2;

};