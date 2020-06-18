#pragma once

class Location 
{
public:
	void Add(const Location& moveVal)
	{
		x += moveVal.x;
		y += moveVal.y;
	}
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};
