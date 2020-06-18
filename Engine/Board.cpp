#include "Board.h"
#include "Assert.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int offsetX = x + borderwidth + borderpadding;
	const int offsetY = y + borderwidth + borderpadding;

	gfx.DrawRectDim(loc.x * dimension + offsetX + cellPadding, loc.y * dimension + offsetY + cellPadding, dimension - (cellPadding * 2), dimension - (cellPadding * 2), c );
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetGridWidth() const
{
	return width;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + 2 * (borderwidth + borderpadding) + (height * dimension);
	const int right = left + 2* (borderwidth + borderpadding) + (width * dimension);

	gfx.DrawRect(left,top,right,top + borderwidth, borderColor );
	gfx.DrawRect(left, bottom - borderwidth, right, bottom, borderColor);
	gfx.DrawRect(left, top + borderwidth, left + borderwidth, bottom - borderwidth, borderColor);
	gfx.DrawRect(right - borderwidth, top + borderwidth, right, bottom - borderwidth, borderColor);

}
