/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenary.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AScenary.class.hpp"
#include <cmath>

//Public Functions:
//	Constructor
AScenary::AScenary(float **Map, unsigned int sizeX, unsigned int sizeY) :
	_w(true), _s(true), _e(true), _n(true), _Map(Map), _sizeX(sizeX), _sizeY(sizeY)
{
	double	PI = std::atan(1.0) * 8;

	_CurMap = new t_water*[_sizeX];
	for (unsigned int x = 0; x < _sizeX; x++)
	{
		_CurMap[x] = new t_water[_sizeY];
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			_CurMap[x][y].height = 0;
			_CurMap[x][y].speed = 0;
			_CurMap[x][y].dir = PI;
		}
	}
}

//	Destructor
AScenary::~AScenary(void)
{
	for (unsigned int x = 0; x < _sizeX; x++)
		delete [] _CurMap[x];
	delete [] _CurMap;
}

//	Getter
t_water	**AScenary::getCurMap(void) const
{
	return this->_CurMap;
}
