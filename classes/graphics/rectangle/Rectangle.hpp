#pragma once

#include <algorithm>

class Rectangle
{
public:
	//Rectangle constructor with custom locations for all positions
	Rectangle(int leftPos, int rightPos, int topPos, int botPos) : left(leftPos), right(rightPos),
		top(topPos), bottom(botPos)
	{

	}
	//Zero based rectangle constructor taking width and height
	Rectangle(int width, int height) : left(0), right(width), top(0), bottom(height)
	{

	}
	//Rectangle destructor
	~Rectangle()
	{

	}
	//Returns left of rectangle
	int Get_Left() const { return left; }
	//Returns top of rectangle
	int Get_Top() const { return top; }
	//Returns width of rectangle
	int Get_Width() const { return (right - left); }
	//Returns height of rectangle
	int Get_Height() const { return (bottom - top); }
	//Sets width of rectangle
	void Set_Width(int width) { (width < 1) ? right = right : right = width; }
	//Sets height of rectangle
	void Set_Height(int height) { (height < 1) ? bottom = bottom : bottom = height; }

	void Translate(int dx, int dy)
	{
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}

	//Changes this instance of rectangle to the intersect value of another rectangle
	void Clip_To(const Rectangle &other, int posX, int posY)
	{
		Translate(posX, posY);

		left = std::max(left, other.left);
		right = std::min(right, other.right);
		top = std::max(top, other.top);
		bottom = std::min(bottom, other.bottom);

		Translate(-posX, -posY);
	}
	//Checks if this rectangle is completely contained within other rectangle
	bool Contained_In(const Rectangle &other, int posX, int posY) {
		Translate(posX, posY);

		if ((left > 0 && right < other.Get_Width()) && (top > 0 && bottom < other.Get_Height())) {
			Translate(-posX, -posY);
			return true;
		}
		Translate(-posX, -posY);
		return false;
	}
	//Checks if this rectangle is completely outside other rectangle
	bool Not_Contained(const Rectangle &other, int posX, int posY) {
		Translate(posX, posY);
		//Checks if rectangle is outside on the X axis
		if (right <= 0 || left > other.Get_Width()) {
			Translate(-posX, -posY);
			return true;
		}
		//And Y axis
		else if (bottom < 0 || top >= other.Get_Height()) {
			Translate(-posX, -posY);
			return true;
		}
		Translate(-posX, -posY);
		return false;
	}
private:
	int left, right, top, bottom;
};
