/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    brd( gfx ),
    rng(std::random_device()()),
    snek({2,2}),
    goal(rng,brd,snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    //use frametimer to get delta time each frame
    const float dt = ft.Mark();

    if ( IsStarted && !GameIsOver)
    {
        if (wnd.kbd.KeyIsPressed(VK_UP))
        {
            delta_loc = { 0, -1 };
        }
        else if (wnd.kbd.KeyIsPressed(VK_DOWN))
        {
            delta_loc = { 0, 1 };
        }
        else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
        {
            delta_loc = { 1,0 };
        }
        else if (wnd.kbd.KeyIsPressed(VK_LEFT))
        {
            delta_loc = { -1,0 };
        }

        snekMoveCounter+=dt;
        if (snekMoveCounter >= snekMovePeriod)
        {
            snekMoveCounter -= snekMovePeriod;
            //don't call GetNextHeadPositon() twice
            const Location nextLoc = snek.GetNextHeadPosition(delta_loc);
            if (!brd.IsInsideBoard(nextLoc) || snek.IsInTileExceptEnd(nextLoc))
            {
                GameIsOver = true;
            }
            else
            {
                const bool isEating = nextLoc == goal.GetLocation();
                if (isEating)
                {
                    snek.Grow();

                }
                snek.MoveBy(delta_loc);
                if (isEating)
                {
                    goal.Respawn(rng,brd,snek);
                }
            }
            // increase snek speed every frame by amount that is scaled by of time that is passed
            //snekMovePeriod -= dt * .001f;
            snekMovePeriod = std::max(snekMovePeriod - dt * snekSpeedFactor, snekMovePeriodMin);
        }
    }
    // snekMovePeriod = std::max(snekMovePeriod - 1, snekMovePeriodMin);
    if (snekMovePeriod <= snekMovePeriodMin)
    {
        snekMovePeriod = snekMovePeriodMin;
    }
    else
    {
        if (wnd.kbd.KeyIsPressed(VK_RETURN))
        {
            IsStarted = true;
        }
    }
}

void Game::ComposeFrame()
{
    if (!IsStarted)
    {
        SpriteCodex::DrawTitle(270, 200, gfx);
    }
    else
    {
        brd.DrawBorder();
        goal.Draw(brd);
        snek.Draw(brd);
        if (GameIsOver)
        {
            SpriteCodex::DrawGameOver(345, 260, gfx);
        }
    }

}
