/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/02/13 22:32:11 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Water.hpp"

//	TO DO:
//	Scenario functions
//	Calcul flow functions
//	Seek if flowing function is usefull
/* ************************************************************************** */
//	Public Functions:

//	Constructor
Water::Water( float **& Map, unsigned int sizeX, unsigned int sizeY) : _Map(Map), _sizeX(sizeX), _sizeY(sizeY) {
	std::cout << "Water constructor called" << std::endl;
}

//	Destructor
Water::~Water( void ) {
}

//	Getter
t_water ** Water::getCurMap( void ) {
	return _curMap;
}

//	Scenario
void Water::Rainy( void ) {
	float rainy = 0.01;
	unsigned int density = 1000;
	unsigned int precipitate = (sizeX * sizeY) / density;
	unsigned int x;
	unsigned int y;

	for ( unsigned int rain = 0, rain < precipitate, rain++ ) {
		//	Randomize on the map;
		if ( _Map[x][y] + _curMap[x][y] + rainy < 1)
			_curMap[x][y] += rainy;
	}
}

void Water::Waves( bool n, bool s, bool e, bool w ) {
	float waves = 0.01;

	for ( unsigned int x = 0, x <= _sizeX && /*n s e ou w*/, ++x ) {
		if ( _curMap[][].height + _Map[][] + waves < 1 )
			_curMap[][].height += waves;
		else
			_curMap[][].height = 1 - _Map[][];
	}
	for ( unsigned int x = 0, x <= _sizeX && /*n s e ou w*/, ++x ) {
		if ( _curMap[][].height + _Map[][] + waves < 1 )
			_curMap[][].height += waves;
		else
			_curMap[][].height = 1 - _Map[][];
	}
	for ( unsigned int y = 0, y <= _sizeY && /*n s e ou w*/, ++y ) {
		if ( _curMap[][].height + _Map[][] + waves < 1 )
			_curMap[][].height += waves;
		else
			_curMap[][].height = 1 - _Map[][];
	}
	for ( unsigned int y = 0, y <= _sizeY && /*n s e ou w*/, ++y ) {
		if ( _curMap[][].height + _Map[][] + waves < 1 )
			_curMap[][].height += waves;
		else
			_curMap[][].height = 1 - _Map[][];
	}
}

void Water::Flood( void ) {
	float flood = 0.01;
	float hillmin = _Map[0][0];
	float zmin = _Map[0][0] + _curMap[0][0].height;

	if (zmin <= 1) {
		for ( unsigned int x = 0, x <= _sizeX, ++x ) {
			for ( unsigned int y = 0, y <= _sizeY, ++y ) {
				if ( _Map[x - 1][y - 1] < hillmin ) {
					hillmin = _Map[x - 1][y - 1];
					zmin = _Map[x - 1][y - 1] + _curMap[x - 1][y - 1].height;
				}
			}
		}
		zmin += flood;
	}
	for ( unsigned int x = 0, x <= _sizeX, ++x ) {
		for ( unsigned int y = 0, y <= _sizeY, ++y ) {
			if ( _Map[x - 1][y - 1] + _curMap[x - 1][y - 1].height < zmin ) {
				_curMap[x - 1][y - 1].height += flood;
			}
		}
	}
}

//	Flowing
void Water::Flow( void ) {
	speed();
	drop();
}

/* ************************************************************************** */
//	Private Functions:

//	Calcul flow
//		Applicate speed
void Water::Speed( void ) {
}

//		Compare height's difference, influent speed
void Water::Drop( void ) {
	for ( unsigned x = 0, x <= _sizeX, ++x) {
		for ( unsigned y = 0, y <= _sizeY, ++y) {
		}
	}
}

//	Clear
void Water::ClearCurMap( void ) {
	for ( unsigned x = 0, x <= _sizeX, ++x) {
		for ( unsigned y = 0, y <= _sizeY, ++y) {
		}
	}
}
