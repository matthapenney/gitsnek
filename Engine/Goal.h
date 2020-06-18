#pragma once

#include "Board.h"
#include "Snake.h"
#include <random>

class Goal 
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snek);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snek );
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Magenta;
	static constexpr Color obstacleColor = Colors::Green;
	Location loc;
};
