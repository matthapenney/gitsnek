#include "Snake.h"
#include "assert.h"

Snake::Snake(const Location& loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{ 153,153,255 },
		{102,102,255},
		{51,51,255},
		{102,102,255}
	};
	for (int i = 0; i < nSegMax; i++)
	{
		Seg[i].InitBody(bodyColors[i % nBodyColors]);
	}

	Seg[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSeg - 1; i > 0; i--)
	{
		Seg[i].Follow(Seg[i - 1]);
	}
	Seg[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadPosition(const Location& delta_loc) const
{
	Location l(Seg[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSeg - 1; ++i)
	{
		if (Seg[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSeg; ++i)
	{
		if (Seg[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Grow()
{
	if (nSeg < nSegMax)
	{
		//No longer need initbody() here because body will be initialized when snake is initialized
		//Seg[nSeg].InitBody(); 
		nSeg++;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSeg; i++)
	{
		Seg[i].Draw(brd);
	}
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;

}

void Snake::Segment::InitBody(Color c_in )
{
	c = c_in;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	/*check to make sure delta_loc is valid and snake will move 1 square
	 abs(0,1) + abs(1,0) == 1; */
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	// add delta value to location of segment
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc,c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
