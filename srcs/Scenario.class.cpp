/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenario.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/18 16:43:42 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scenario.class.hpp"

//TO DO:
//		Boost speed use (divise calcul by 4, 8 or more ?)
//		Seek auto-generate water error
//		Add 4 angle for each function
//		seprate scenario and water function
/* ************************************************************************** */
//	Public Functions:

//	Constructor
Scenario::Scenario(float ** Map, unsigned int sizeX, unsigned int sizeY, int type) :
	Liquid(Map, sizeX, sizeY, type)
{
}

//	Destructor
Scenario::~Scenario(void)
{
}

//	Scenario
void Scenario::Rainy(void)
{
	double	PI = std::atan(1.0)*8;

	//	Give speed of flowing
	float			rainy = 0.01;

	//	Give density (lowest is the number, higher is the density)
	unsigned int	density = 1000;
	unsigned int	precipitate = (_sizeX * _sizeY) / density;
	unsigned int	x;
	unsigned int	y;

	srand (time(NULL));
	for (unsigned int rain = 0; rain < precipitate; rain++)
	{
		x = rand() % _sizeX;
		y = rand() % _sizeY;
		if (_Map[x][y] + _CurMap[x][y].height + rainy < 1)
		{
			_CurMap[x][y].height += rainy;

			//	Give random direction
			if (_CurMap[x][y].height == rainy)
				_CurMap[x][y].dir = ((rand() + 1.0) * PI) / ((1.0 + RAND_MAX) * PI);
		}
	}
}

void Scenario::Waves(bool n, bool s, bool e, bool w)
{
	double PI = std::atan(1.0);

	//	Give speed of flowing
	float	waves = 0.05;

	//	Check lowest hight
	float	zmin = WavesMin(n, s, e, w) + waves;

	if (waves < 0.04)
		zmin += waves * 9;
	//	Increase hight of wave
	//		North wave
	for (unsigned int x = 0; x < _sizeX && n; x++)
	{
		if (_CurMap[x][0].height + _Map[x][0] <= zmin)
			_CurMap[x][0].height += waves;
		if (_CurMap[x][0].height + _Map[x][0] > 1)
			_CurMap[x][0].height = 1 - _Map[x][0];
		_CurMap[x][0].dir = 5 * PI;
	}
	//		West wave
	for (unsigned int y = 0; y < _sizeY && w; y++)
	{
		if (_CurMap[0][y].height + _Map[0][y] <= zmin)
			_CurMap[0][y].height += waves;
		if (_CurMap[0][y].height + _Map[0][y] > 1)
			_CurMap[0][y].height = 1 - _Map[0][y];
		_CurMap[_sizeX-1][y].dir = 7 * PI;
	}
	//		South wave
	for (unsigned int x = 0; x < _sizeX && s; x++)
	{
		if (_CurMap[x][_sizeY-1].height + _Map[x][_sizeY-1] <= zmin)
			_CurMap[x][_sizeY-1].height += waves;
		if (_CurMap[x][_sizeY-1].height + _Map[x][_sizeY-1] > 1)
			_CurMap[x][_sizeY-1].height = 1 - _Map[x][_sizeY-1];
		_CurMap[x][_sizeY-1].dir = PI;
	}
	//		Est wave
	for (unsigned int y = 0; y < _sizeY && e; y++)
	{
		if (_CurMap[_sizeX-1][y].height + _Map[_sizeX-1][y] <= zmin)
			_CurMap[_sizeX-1][y].height += waves;
		if (_CurMap[_sizeX-1][y].height + _Map[_sizeX-1][y] > 1)
			_CurMap[_sizeX-1][y].height = 1 - _Map[_sizeX-1][y];
		_CurMap[0][y].dir = 3 * PI;
	}
}

void Scenario::Flood(void)
{
	double	PI = std::atan(1.0)*8;

	//	Give speed of flowing
	float	flood = 0.01;
	float	hillmin = _Map[0][0];
	float	zmin = _Map[0][0] + _CurMap[0][0].height;

	//	Check lowest point of map
	if (zmin < 1 && hillmin < 1 && hillmin > 0)
	{
		for (unsigned int x = 0; x < _sizeX && hillmin > 0; x++)
		{
			for (unsigned int y = 0; y < _sizeY && hillmin > 0; y++)
			{
				if (_Map[x][y] < hillmin)
				{
					hillmin = _Map[x][y];
					zmin = _Map[x][y] + _CurMap[x][y].height;
				}
			}
		}
	}
	zmin += flood;
	if (zmin > 1)
		zmin = 1;

	//	Add flood
	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			if (_Map[x][y] + _CurMap[x][y].height < zmin)
				_CurMap[x][y].height += flood;

			if (_CurMap[x][y].height == flood)
				_CurMap[x][y].dir = ((1.0 + rand()) * PI) / ((RAND_MAX + 1.0) * PI);

			//	limit flood
			if (_Map[x][y] + _CurMap[x][y].height > 1)
				_CurMap[x][y].height = 1 - _Map[x][y];
		}
	}
}

void Scenario::Evapor(void)
{

	//	Give evaporate speed;
	float	hot = 0.01;

	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
	{
			_CurMap[x][y].height -= hot;
			if (_CurMap[x][y].height <= 0.0)
			{
				_CurMap[x][y].height = 0;
				_CurMap[x][y].speed = 0;
			}
		}
	}
}

void Scenario::DiscWorld(bool n, bool s, bool e, bool w)
{
	double	PI = std::atan(1.0);

	//	North fall
	for (unsigned int x = 0; x < _sizeX && n; x++)
	{
		_CurMap[x][0].height = 0;
		_CurMap[x][0].speed = 0;
		_CurMap[x][0].dir = PI; 
	}
	//	South fall
	for (unsigned int x = 0; x < _sizeX && s; x++)
	{
		_CurMap[x][_sizeY-1].height = 0;
		_CurMap[x][_sizeY-1].speed = 0;
		_CurMap[x][_sizeY-1].dir = 5 * PI;
	}
	//	Est fall
	for (unsigned int y = 0; y < _sizeY && e; y++)
	{
		_CurMap[0][y].height = 0;
		_CurMap[0][y].speed = 0;
		_CurMap[0][y].dir = 3 * PI;
	}
	//	West fall
	for (unsigned int y = 0; y < _sizeY && w; y++)
	{
		_CurMap[_sizeX-1][y].height = 0;
		_CurMap[_sizeX-1][y].speed = 0;
		_CurMap[_sizeX-1][y].dir = 7 * PI;
	}
}

/* ************************************************************************** */
//	Private Functions:

//	Wave functions
float Scenario::WavesMin(bool n, bool s, bool e, bool w)
{
	float	zmin = 1.0;

	//	Check lowest point of the edge
	if (n)
	{
		for (unsigned int x = 0; x < _sizeX; x++)
		{
			if (_CurMap[x][0].height + _Map[x][0] < zmin)
				zmin = _CurMap[x][0].height + _Map[x][0];
		}
	}
	if (w)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			if (_CurMap[0][y].height + _Map[0][y] < zmin)
				zmin = _CurMap[0][y].height + _Map[0][y];
		}
	}
	if (s)
	{
		for (unsigned int x = 0; x < _sizeX; x++)
		{
			if (_CurMap[x][_sizeY - 1].height + _Map[x][_sizeY - 1] < zmin)
				zmin = _CurMap[x][_sizeY - 1].height + _Map[x][_sizeY - 1];
		}
	}
	if (e)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			if (_CurMap[_sizeX - 1][y].height + _Map[_sizeX - 1][y] < zmin)
				zmin = _CurMap[_sizeX - 1][y].height + _Map[_sizeX - 1][y];
		}
	}
	return zmin;
}
