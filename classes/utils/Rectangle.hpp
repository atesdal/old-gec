#pragma once

namespace Util
{
	class Vector2;

	class Rectangle
	{
	public:
		//Rectangle constructor with custom locations for all positions
		Rectangle(int leftPos, int rightPos, int topPos, int botPos);
		//Zero based rectangle constructor taking width and height
		Rectangle(int width, int height);
		//Rectangle destructor
		~Rectangle() = default;
		//Returns left of rectangle
		int Get_Left() const;
		//Returns top of rectangle
		int Get_Top() const;
		//Returns width of rectangle
		int Get_Width() const;
		//Returns height of rectangle
		int Get_Height() const;
		//Sets width of rectangle
		void Set_Width(int width);
		//Sets height of rectangle
		void Set_Height(int height);
		//Moves rectangle
		void Translate(int dx, int dy);
		//Changes this instance of rectangle to the intersect value of another rectangle
		void Clip_To(const Rectangle *other, int posX, int posY);
		//Checks if this rectangle is completely contained within other rectangle
		bool Contained_In(const Rectangle *other, int posX, int posY);
		//Checks if this rectangle is completely outside other rectangle
		bool Not_Contained(const Rectangle *other, int posX, int posY);
		//Checks if this rectangle contains vector
		bool Contains(const Util::Vector2 *other, int posX, int posY);

	private:
		int left, right, top, bottom;
	};
}
