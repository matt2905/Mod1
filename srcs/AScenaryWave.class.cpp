/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenaryWave.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 12:56:50 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AScenaryWave.class.hpp"
#include <cmath>

//Public Funcions:
//	Constructor
AScenaryWave::AScenaryWave(float **Map, unsigned int sizeX, unsigned sizeY) :
	AScenary(Map, sizeX, sizeY)
{
}

//	Destructor
AScenaryWave::~AScenaryWave(void)
{
}

//	Scenario
void AScenaryWave::Waves(bool n, bool s, bool e, bool w)
{
	double PI = std::atan(1.0);

	//	Give speed of flowing
	float	waves = 0.01;

	//	Check lowest hight
	float	zmin = WavesMin(n, s, e, w) + waves;

	//	Increase hight of wave
	//		North wave
	for (unsigned int x = 0; x < _sizeX && n; x++)
	{
		if (_CurMap[x][0].height + _Map[x][0] < zmin + waves)
			_CurMap[x][0].height += waves;
		if (_CurMap[x][0].height + _Map[x][0] > 1)
			_CurMap[x][0].height = 1 - _Map[x][0];
		_CurMap[x][0].dir = 5 * PI;
//		_CurMap[x][0].speed = 0.5;
	}
	//		South wave
	for (unsigned int x = 0; x < _sizeX && s; x++)
	{
		if (_CurMap[x][_sizeY-1].height + _Map[x][_sizeY-1] < zmin + waves)
			_CurMap[x][_sizeY-1].height += waves;
		if (_CurMap[x][_sizeY-1].height + _Map[x][_sizeY-1] > 1)
			_CurMap[x][_sizeY-1].height = 1 - _Map[x][_sizeY-1];
		_CurMap[x][_sizeY-1].dir = PI;
//		_CurMap[x][_sizeY-1].speed = 0.5;
	}
	//		West wave
	for (unsigned int y = 0; y < _sizeY && w; y++)
	{
		if (_CurMap[0][y].height + _Map[0][y] < zmin + waves)
			_CurMap[0][y].height += waves;
		if (_CurMap[0][y].height + _Map[0][y] > 1)
			_CurMap[0][y].height = 1 - _Map[0][y];
		_CurMap[_sizeX-1][y].dir = 7 * PI;
//		_CurMap[0][y].speed = 0.5;
	}
	//		Est wave
	for (unsigned int y = 0; y < _sizeY && e; y++)
	{
		if (_CurMap[_sizeX-1][y].height + _Map[_sizeX-1][y] < zmin + waves)
			_CurMap[_sizeX-1][y].height += waves;
		if (_CurMap[_sizeX-1][y].height + _Map[_sizeX-1][y] > 1)
			_CurMap[_sizeX-1][y].height = 1 - _Map[_sizeX-1][y];
		_CurMap[0][y].dir = 3 * PI;
//		_CurMap[_sizeX-1][y].speed = 0.5;
	}
}

//Private Functions:
float AScenaryWave::WavesMin(bool n, bool s, bool e, bool w)
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
	if (s)
	{
		for (unsigned int x = 0; x < _sizeX; x++)
		{
			if (_CurMap[x][_sizeY - 1].height + _Map[x][_sizeY - 1] < zmin)
				zmin = _CurMap[x][_sizeY - 1].height + _Map[x][_sizeY - 1];
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
