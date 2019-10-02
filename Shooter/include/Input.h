#pragma once

class Input
{
private:

	// Structure to represent Mouse
	struct Mouse
	{
		int x, y;
		bool left;
	};

public:

	//setters
	void setKeyDown(int key_);
	void setKeyUp(int key_);
	void setMouseX(int lx_);
	void setMouseY(int ly_);
	void setMousePosition(int lx_, int ly_);
	void setMouseLeftDown(bool down_);

	//getters
	int getMouseX();
	int getMouseY();
	bool isMouseLeftDown();
	bool isKeyDown(int key_);


private:

	bool keys[256]{ false };
	Mouse mouse;

};

