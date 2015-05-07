/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/07 16:36:24 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Water.class.hpp"

static const double PI = std::atan(1.0);
static const double	g_tab_pi[] = {0, PI, 2 * PI, 3 * PI, 4 * PI, 5 * PI, 6 * PI, 7 * PI, 8 * PI};

//TO DO:
//		Boost speed use (divise calcul by 4, 8 or more ?)
//		Seek auto-generate water error
//		Add 4 angle for each function
/* ************************************************************************** */
//	Public Functions:

//	Constructor
Water::Water(float ** Map, unsigned int sizeX, unsigned int sizeY) :
	AScenary(Map, sizeX, sizeY), AScenaryRain(Map, sizeX, sizeY), AScenaryWave(Map, sizeX, sizeY), AScenaryFlood(Map, sizeX, sizeY), AScenaryEvap(Map, sizeX, sizeY), AScenaryDisc(Map, sizeX, sizeY)
{
}

//	Destructor
Water::~Water(void)
{
}

//	Clear
void Water::ClearCurMap(void)
{
	for (unsigned x = 0; x < _sizeX; x++)
	{
		for (unsigned y = 0; y < _sizeY; y++)
		{
			_CurMap[x][y].height = 0.0;
			_CurMap[x][y].speed = 0.0;
			_CurMap[x][y].dir = g_tab_pi[8];
		}
	}
}

//	Flowing
void Water::Flow(void)
{
	Drop();
	Speed();
}

/* ************************************************************************** */
//	Private Functions:


//To Do:
//		Add 4 angle (0; PI/2; PI; 3PI/2) to speed and drop;
//	Calcul flow
//		Compare height's difference, influent speed
void Water::Drop(void)
{
	float	drop = 0.001;
	float	speed;
	float	new_speed;
	float	hgt;
	float	dir = PI;

	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			if (_CurMap[x][y].height > drop)
			{
				speed = drop;
				hgt = _CurMap[x][y].height + _Map[x][y];

				//	Check highest difference
/*				if (x + 1 < _sizeX && y > 0
						&& speed < (new_speed = hgt - _CurMap[x+1][y-1].height - _Map[x+1][y-1]))
				{
					speed = new_speed;
					dir = g_tab_pi[8];
				}*/
				if (x + 1 < _sizeX
						&& speed < (new_speed = hgt - _CurMap[x+1][y].height - _Map[x+1][y]))
				{
					speed = new_speed;
					dir = g_tab_pi[7];
				}
/*				if (x + 1 < _sizeX && y + 1 < _sizeY
						&& speed < (new_speed = hgt - _CurMap[x+1][y+1].height - _Map[x+1][y+1]))
				{
					speed = new_speed;
					dir = g_tab_pi[2];
				}*/
				if (y + 1 < _sizeY
						&& (speed < (new_speed = hgt - _CurMap[x][y+1].height - _Map[x][y+1])
						|| (speed <= new_speed && _CurMap[x][y].dir > g_tab_pi[4]
								&& _CurMap[x][y].dir <= g_tab_pi[6])))
				{
					speed = new_speed;
					dir = g_tab_pi[5];
				}
/*				if (y + 1 < _sizeY && x > 0
						&& speed < (new_speed = hgt - _CurMap[x-1][y+1].height - _Map[x-1][y+1]))
				{
					speed = new_speed;
					dir = g_tab_pi[4];
				}*/
				if (x > 0 && (speed < (new_speed = hgt - _CurMap[x-1][y].height - _Map[x-1][y])
						|| (new_speed && _CurMap[x][y].dir > g_tab_pi[2]
								&& _CurMap[x][y].dir <= g_tab_pi[4])))
				{
					speed = new_speed;
					dir = g_tab_pi[3];
				}
/*				if (y > 0 && x > 0
						&& speed < (new_speed = hgt - _CurMap[x-1][y-1].height - _Map[x-1][y-1]))
				{
					speed = hgt - _CurMap[x-1][y-1].height - _Map[x-1][y-1];
					dir = g_tab_pi[6];
				}*/
				if (y > 0 && (speed < (new_speed = hgt - _CurMap[x][y-1].height - _Map[x][y-1])
						|| (speed <= new_speed && _CurMap[x][y].dir > g_tab_pi[0]
								&& _CurMap[x][y].dir <= g_tab_pi[2])))
				{
					speed = new_speed;
					dir = g_tab_pi[1];
				}

				if (speed > drop)
					DropNew(x, y, dir, speed);
			}
		}
	}
}

//		Drop modification
void Water::DropNew(unsigned int x, unsigned int y, float dir, float speed)
{
	float	gravity = 1.7;
	float	way = _CurMap[x][y].dir;

	speed = speed * gravity;
	//	new way value ((x / (x + y)) + (y / (x + y))
	NewDir(x, y, dir, speed);

	//	new speed value (V(x * x + y * y))
	NewSpd(x, y, dir, speed, way);
}

//if ((n = x) == (n += y));?

//TO DO:
//		Boost speed (x + n where n = (int)(speed * 10));
//		Applicate speed
void Water::Speed(void)
{
	float	lim = 0.001;
	float	drop;
/*	float tmp = 0;

	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			tmp += _CurMap[x][y].height;
		}
	}
*/	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			if (_CurMap[x][y].speed > 0)
			{
				//	Verify valid direction (sens && edge && height)
				drop = _Map[x][y] + _CurMap[x][y].height + _CurMap[x][y].speed;
				//	x + 1
				for (unsigned int n = 1;
						_CurMap[x][y].dir > g_tab_pi[6] && _CurMap[x][y].dir <= g_tab_pi[8] &&
						(x + n) < _sizeX &&
						n == 1 &&
						drop > _CurMap[x+n][y].height + _Map[x+n][y] + lim &&
						(n == 1 ||
							drop >= _CurMap[x+1][y].height + _Map[x+1][y] + lim);
						n++)
					drop = Transfert(x, y, x+n, y, drop);
				// x + 1 && y + 1
/*				dir >= g_tab_pi[5] && dir < g_tab_pi[7]
				NOT AVAIBLE*/
				//	y + 1
				for (unsigned int n = 1;
						_CurMap[x][y].dir > g_tab_pi[4] && _CurMap[x][y].dir <= g_tab_pi[6] &&
						(y + n) < _sizeY &&
						n == 1 &&
						drop > _CurMap[x][y+n].height + _Map[x][y+n] + lim &&
						(n == 1 ||
						drop >= _CurMap[x][y+1].height + _Map[x][y+1] + lim);
						n++)
					drop = Transfert(x, y, x, y+n, drop);
				// x - 1 && y + 1
/*				dir >= g_tab_pi[3] && dir < g_tab_pi[5]
				NOT ABAIBLE*/
				// x - 1
				for (unsigned int n = 1;
						_CurMap[x][y].dir > g_tab_pi[2] && _CurMap[x][y].dir <= g_tab_pi[4] &&
						x >= n &&
						n == 1 &&
						drop > _CurMap[x-n][y].height + _Map[x-n][y] + lim &&
						(n == 1 ||
						drop >= _CurMap[x-1][y].height + _Map[x-1][y] + lim);
						n++)
					drop = Transfert(x, y, x-n, y, drop);
				// x - 1 && y - 1
/*				dir >= g_tab_pi[1] && .dir < g_tab_pi[3]
				NOT AVAIBLE*/
				// y - 1
				for (unsigned int n = 1;
						_CurMap[x][y].dir > g_tab_pi[0] && _CurMap[x][y].dir <= g_tab_pi[2] &&
						y >= n &&
						n == 1 &&
						drop > _CurMap[x][y-n].height + _Map[x][y-n] + lim &&
						(n == 1 ||
						drop >= _CurMap[x][y-1].height + _Map[x][y-1] + lim);
						n++)
					drop = Transfert(x, y, x, y-n, drop);
				// x + 1 && y - 1
/*				dir >= g_tab_pi[7] && dir < g_tab_pi[1]
				NOT AVAIBLE*/
			}
		}
	}
/*	printf("quantite = %f\n", tmp);
	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			tmp = tmp - _CurMap[x][y].height;
		}
	}
	printf("perte/ajout = %f\n", tmp);
	tmp = 0;
	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			tmp = tmp + _CurMap[x][y].height;
		}
	}
	printf("quantite 2 = %f\n\n", tmp);*/
}

//		Speed modification
float Water::Transfert(unsigned int x1, unsigned int y1,
		unsigned int x2, unsigned int y2, float drop)
{
	float	slow = 0.5;
	float	way = _CurMap[x2][y2].dir;
	float	transfert = 0.25;

	//	Transfert of Water
	drop = 0.01;
	transfert = 1.0;
	if (drop * transfert > _CurMap[x1][y1].height)
		drop = _CurMap[x1][y1].height / transfert;
	if ((_CurMap[x2][y2].height + _Map[x2][y2] + (drop * transfert)) > 1)
		drop = (1 - (_CurMap[x2][y2].height + _Map[x2][y2])) * (1 / transfert);
	_CurMap[x1][y1].height = _CurMap[x1][y1].height - (drop * transfert);
	_CurMap[x2][y2].height = _CurMap[x2][y2].height + (drop * transfert);
/*	if (_CurMap[x2][y2].height + _Map[x2][y2] > 1)
	{
		_CurMap[x2][y2].height = 1 - _Map[x2][y2];
	}*/

	//	Transfert of Power
	//	no divide by 0
	if (_CurMap[x1][y1].speed + _CurMap[x2][y2].speed == 0)
		return (_CurMap[x1][y1].height + _CurMap[x1][y1].speed + _Map[x1][y1]);

	transfert = 0;
	//	new value of x2,y2 way ((x / (x + y)) + (y / (x + y)))
	NewDir(x2, y2, _CurMap[x2][y2].dir, _CurMap[x2][y2].speed * transfert * slow);

	//	new value of x2,y2 speed (V(x * x + y * y))
	NewSpd(x2, y2, _CurMap[x2][y2].dir, _CurMap[x2][y2].speed * transfert * slow, way);

	_CurMap[x1][y1].speed *= slow;
	return (_CurMap[x1][y1].height + _CurMap[x1][y1].speed + _Map[x1][y1]);
}

void Water::NewDir(unsigned int x, unsigned int y, float dir, float speed)
{
	float	speedTotal = speed + _CurMap[x][y].speed;

	if (speedTotal == 0)
		return ;
	if (dir - _CurMap[x][y].dir > g_tab_pi[4])
		_CurMap[x][y].dir += g_tab_pi[8];
	else if (_CurMap[x][y].dir - dir > g_tab_pi[4])
		dir += g_tab_pi[8];
	_CurMap[x][y].dir = _CurMap[x][y].dir * (_CurMap[x][y].speed / speedTotal);
	_CurMap[x][y].dir += dir * (speed / speedTotal);
	while (_CurMap[x][y].dir > g_tab_pi[8])
		_CurMap[x][y].dir -= g_tab_pi[8];
	while (_CurMap[x][y].dir <= 0)
		_CurMap[x][y].dir += g_tab_pi[8];
}
//ª lol;
void Water::NewSpd(unsigned int x, unsigned int y, float dir, float spd, float odir)
{
	float	rlow = 0.01;
	float	tmp;

	tmp = pow(sin(odir) * _CurMap[x][y].speed + (sin(dir) * spd), 2);
	tmp += pow(cos(odir) * _CurMap[x][y].speed + (cos(dir) * spd), 2);
	_CurMap[x][y].speed = sqrt(tmp);
	if ((_CurMap[x][y].speed = _CurMap[x][y].speed - rlow) < 0)
		_CurMap[x][y].speed = 0;
	if (_CurMap[x][y].speed > 1)
		_CurMap[x][y].speed = 1;
	return ;
}
