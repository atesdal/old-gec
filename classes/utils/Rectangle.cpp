#include "Rectangle.hpp"
#include "Utilities.hpp"

Rectangle::Rectangle(int leftPos, int rightPos, int topPos, int botPos) :
	left(leftPos), right(rightPos), top(topPos), bottom(botPos)
{

}

Rectangle::Rectangle(int width, int height) :
	left(0), right(width), top(0), bottom(height)
{

}

int Rectangle::Get_Left() const
{
	return left;
}

int Rectangle::Get_Top() const
{
	return top;
}

int Rectangle::Get_Width() const 
{
	return (right - left);
}

int Rectangle::Get_Height() const
{
	return (bottom - top);
}

void Rectangle::Set_Width(int width)
{
	(width < 1) ? right = right : right = width;
}

void Rectangle::Set_Height(int height)
{
	(height < 1) ? bottom = bottom : bottom = height;
}

void Rectangle::Translate(int dx, int dy)
{
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}

void Rectangle::Clip_To(const Rectangle &other, int posX, int posY)
{
	Translate(posX, posY);

	left = Util::Max(left, other.left);
	right = Util::Min(right, other.right);
	top = Util::Max(top, other.top);
	bottom = Util::Min(bottom, other.bottom);

	Translate(-posX, -posY);
}

bool Rectangle::Contained_In(const Rectangle &other, int posX, int posY)
{
	Translate(posX, posY);

	if ((left > 0 && right < other.Get_Width()) && (top > 0 && bottom < other.Get_Height())) {
		Translate(-posX, -posY);
		return true;
	}
	Translate(-posX, -posY);
	return false;
}

bool Rectangle::Not_Contained(const Rectangle &other, int posX, int posY)
{
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