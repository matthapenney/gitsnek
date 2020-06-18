#pragma once

#include "Graphics.h"
#include "Location.h"

class Board 
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridHeight() const;
	int GetGridWidth() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
private:
	static constexpr Color borderColor = Colors::Gray;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;
	static constexpr int cellPadding = 1;
	static constexpr int x = 20;
	static constexpr int y = 20;
	static constexpr int borderwidth = 4;
	static constexpr int borderpadding = 2;
	Graphics& gfx;
};