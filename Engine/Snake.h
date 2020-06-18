#pragma once
#include "Board.h"

class Snake 
{
private:
	class Segment 
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c_in);
		void MoveBy(const Location& delta_loc);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
 	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	// Move snake by delta value in x or y direction
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadPosition(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd ) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::White;
	static constexpr Color bodyColor = Colors::White;
	static constexpr int nSegMax = 100;
	Segment Seg[nSegMax];
	int nSeg = 1;
};