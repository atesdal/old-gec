#pragma once
class Rectangle
{
public:

	Rectangle(int topLeft, int topRight, int botLeft, int botRight);
	Rectangle(int width, int height);
	~Rectangle();

	int Get_T_Left() const { return tLeft; }
	int Get_T_Right() const { return tRight; }
	int Get_B_Left() const { return bLeft; }
	int Get_B_Right() const { return bRight; }

	Rectangle ClipTo(const Rectangle &other, int posX, int posY);

private:

	int tLeft, tRight, bLeft, bRight;
};

