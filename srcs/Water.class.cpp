/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/02/16 14:34:21 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Water.class.hpp"

//	TO DO:
//	Seek if flowing function is usefull
//	flowings functions
/* ************************************************************************** */
//	Public Functions:

//	Constructor
Water::Water( float ** Map, unsigned int sizeX, unsigned int sizeY) : _Map(Map), _sizeX(sizeX), _sizeY(sizeY) {
}

//	Destructor
Water::~Water( void ) {
	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		delete [] this->_CurMap[x];
	}
	delete [] this->_CurMap;
}

//	Getter
t_water ** Water::getCurMap( void ) {
	return this->_CurMap;
}

//	Scenario
void Water::Rainy( void ) {

	//	Give speed of flowing
	float rainy = 0.01;

	//	Give density (lowest is the number, higher is the density)
	unsigned int density = 1000;
	unsigned int precipitate = (_sizeX * _sizeY) / density;
	unsigned int x;
	unsigned int y;

	srand (time(NULL));
	for ( unsigned int rain = 0; rain < precipitate; rain++ ) {
		x = rand() % _sizeX;
		y = rand() % _sizeY;
		if ( _Map[x][y] + _CurMap[x][y].height + rainy < 1)
			_CurMap[x][y].height += rainy;
	}
}

void Water::Waves( bool n, bool s, bool e, bool w ) {

	//	Give speed of flowing
	float waves = 0.01;

	//	Check lowest hight
	float zmin = WavesMin(n, s, e, w) + waves;

	//	Increase hight of wave
	for ( unsigned int x = 0; x <= _sizeX && n; x++ ) {
		if ( _CurMap[x][0].height + _Map[x][0] < zmin + waves )
			_CurMap[x][0].height += waves;
		if ( _CurMap[x][0].height + _Map[x][0] > 1 )
			_CurMap[x][0].height = 1 - _Map[x][0];
	}
	for ( unsigned int x = 0; x <= _sizeX && s; x++ ) {
		if ( _CurMap[x][_sizeY].height + _Map[x][_sizeX] < zmin + waves )
			_CurMap[x][_sizeY].height += waves;
		if ( _CurMap[x][_sizeY].height + _Map[x][_sizeX] > 1 )
			_CurMap[x][_sizeX].height = 1 - _Map[x][_sizeX];
	}
	for ( unsigned int y = 0; y <= _sizeY && e; y++ ) {
		if ( _CurMap[0][y].height + _Map[0][y] < zmin + waves )
			_CurMap[0][y].height += waves;
		if ( _CurMap[0][y].height + _Map[0][y] > 1 )
			_CurMap[0][y].height = 1 - _Map[0][y];
	}
	for ( unsigned int y = 0; y <= _sizeY && w; y++ ) {
		if ( _CurMap[_sizeX][y].height + _Map[_sizeX][y] < zmin + waves )
			_CurMap[_sizeX][y].height += waves;
		if ( _CurMap[_sizeX][y].height + _Map[_sizeX][y] > 1 )
			_CurMap[_sizeX][y].height = 1 - _Map[_sizeX][y];
	}
}

void Water::Flood( void ) {

	//	Give speed of flowing
	float flood = 0.01;
	float hillmin = _Map[0][0];
	float zmin = _Map[0][0] + _CurMap[0][0].height;

	//	Check lowest point of map
	if ( zmin < 1 && hillmin < 1 && hillmin > 0 ) {
		for ( unsigned int x = 0; x <= _sizeX && hillmin > 0; x++ ) {
			for ( unsigned int y = 0; y <= _sizeY && hillmin > 0; y++ ) {
				if ( _Map[x][y] < hillmin ) {
					hillmin = _Map[x][y];
					zmin = _Map[x][y] + _CurMap[x][y].height;
				}
			}
		}
	}

	//	Add flood
	for ( unsigned int x = 0; x <= _sizeX; x++ ) {
		for ( unsigned int y = 0; y <= _sizeY; y++ ) {
			if ( _Map[x][y] + _CurMap[x][y].height < zmin )
				_CurMap[x][y].height += flood;

			//	limit flood
			if ( _Map[x][y] + _CurMap[x][y].height > 1 )
				_CurMap[x][y].height = 1 - _Map[x][y];
		}
	}
}

//	Flowing
void Water::Flow( void ) {
	Speed();
	Drop();
}

/* ************************************************************************** */
//	Private Functions:

//	Calcul flow
//		Compare height's difference, influent speed
void Water::Drop( void ) {
	double PI = std::atan(1.0)*4;
	float drop = 0.01;
	float speed;
	float hgt;
	float dir;
	unsigned int xMin;
	unsigned int yMin;

	for ( unsigned int x = 0; x <= _sizeX; x++ ) {
		for ( unsigned int y = 0; y <= _sizeY; y++ ) {
			if ( _CurMap[x][y].height > 0 ) {
				xMin = _sizeX;
				yMin = _sizeY;
				speed = 0;
				hgt = _CurMap[x][y].height + _Map[x][y] + drop;

				//	Check highest difference
				if ( x < _sizeX && speed < hgt - _CurMap[x+1][y].height + _Map[x+1][y] ) {
					speed = hgt - _CurMap[x+1][y].height + _Map[x+1][y];
					xMin = x;
					yMin = y;
					dir = PI / 4;
				}
				if ( y < _sizeY && speed < hgt - _CurMap[x][y+1].height + _Map[x][y+1] ) {
					speed = hgt - _CurMap[x][y+1].height + _Map[x][y+1];
					xMin = x;
					yMin = y;
					dir = 3 * PI / 4;
				}
				if ( x > 0 && speed < hgt - _CurMap[x+1][y].height + _Map[x+1][y] ) {
					speed = hgt - _CurMap[x-1][y].height + _Map[x-1][y];
					xMin = x;
					yMin = y;
					dir =  5 * PI / 4;
				}
				if ( y > 0 && speed < hgt - _CurMap[x][y-1].height + _Map[x][y-1] ) {
					speed = hgt - _CurMap[x][y-1].height + _Map[x][y-1];
					xMin = x;
					yMin = y;
					dir = 7 / PI / 4;
				}
				if ( speed > 0 ) {
					_CurMap[xMin][yMin].height += drop;
					DropNew(x, y, dir, speed);
				}
			}
		}
	}
}

//		Drop modification
void Water::DropNew( unsigned int x, unsigned int y, float dir, float speed ) {
	double PI = std::atan(1.0)*4;
	float tmp;
	float way = _CurMap[x][y].dir;

	//	no divide by 0
	if ( _CurMap[x][y].speed + speed == 0 )
		return;

	//	new way value ((x / (x + y)) + (y / (x + y)))
	tmp = _CurMap[x][y].dir * (_CurMap[x][y].speed / (_CurMap[x][y].speed + speed));
	_CurMap[x][y].dir = tmp;
	_CurMap[x][y].dir += dir * (speed / (_CurMap[x][y].speed + speed));
	while ( _CurMap[x][y].dir >= 2*PI )
		_CurMap[x][y].dir -= 2*PI;

	//	new speed value (V(x * x + y * y))
	tmp = pow((sin(way) * _CurMap[x][y].speed + sin(dir) * speed), 2);
	tmp += pow((cos(way) * _CurMap[x][y].speed + cos(dir) * speed), 2);
	_CurMap[x][y].speed = sqrt(tmp);
	if ( _CurMap[x][y].speed > 1 )
		_CurMap[x][y].speed = 1;
}

//if ((n = x) == (n += y));?

//		Applicate speed
void Water::Speed( void ) {
	double PI = std::atan(1.0)*4;
	float slow = 0.5;
	float drop = 0.0;

	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			if ( _CurMap[x][y].speed > 0 ) {

				//	Verify valid direction (sens && edge && height)
				drop = _Map[x][y] + _CurMap[x][y].height + _CurMap[x][y].speed;
				if ( _CurMap[x][y].dir >= 0 && _CurMap[x][y].dir < (PI/2)
						&& (x + 1) < _sizeX
						&& drop > _CurMap[x+1][y].height + _Map[x+1][y] ) {
					drop -= _CurMap[x+1][y].height + _Map[x+1][y];

					//	Transfert of water
					_CurMap[x + 1][y].height += drop;
					_CurMap[x][y].height -= drop;

					//	Transfert of power
					SpeedNew(x, y, x + 1, y, slow);
				}
				else if ( _CurMap[x][y].dir >= (PI/2) && _CurMap[x][y].dir < PI
						&& (y + 1) < _sizeY
						&& drop > _CurMap[x][y+1].height + _Map[x][y+1] ) {
					drop -= _CurMap[x][y+1].height + _Map[x][y+1];
					_CurMap[x][y + 1].height += drop;
					_CurMap[x][y].height -= drop;
					SpeedNew(x, y, x, y + 1, slow);
				} else if ( _CurMap[x][y].dir >= PI && _CurMap[x][y].dir < (3*PI/2)
						&& x > 0
						&& drop > _CurMap[x-1][y].height + _Map[x-1][y] ) {
					drop -= _CurMap[x-1][y].height + _Map[x-1][y];
					_CurMap[x - 1][y].height += drop;
					_CurMap[x][y].height -= drop;
					SpeedNew(x, y, x - 1, y, slow);
				} else if ( _CurMap[x][y].dir >= (3*PI/2) && _CurMap[x][y].dir < 2*PI
						&& y > 0
						&& drop > _CurMap[x][y-1].height + _Map[x][y-1] ) {
					drop -= _CurMap[x][y-1].height + _Map[x][y-1];
					_CurMap[x][y - 1].height += drop;
					_CurMap[x][y].height -= drop;
					SpeedNew(x, y, x, y - 1, slow);
				} else {

					//	Counter speed
					_CurMap[x][y].speed *= slow;
					_CurMap[x][y].dir += PI;
					if ( _CurMap[x][y].dir > 2 * PI)
						_CurMap[x][y].dir -= 2 * PI;
				}
			}
		}
	}
}

//		Speed modification
void Water::SpeedNew( unsigned int x1, unsigned int y1,
		unsigned int x2, unsigned int y2, float slow ) {
	double PI = std::atan(1.0)*4;
	float tmp;
	float way = _CurMap[x2][y2].dir;

	//	no divide by 0
	if ( _CurMap[x1][y1].speed + _CurMap[x2][y2].speed == 0 )
		return;

	//	new value of x2,y2 way ((x / (x + y)) + (y / (x + y)))
	tmp = _CurMap[x2][y2].speed / (_CurMap[x1][y1].speed + _CurMap[x2][y2].speed);
	_CurMap[x2][y2].dir = _CurMap[x2][y2].dir * tmp;
	tmp = _CurMap[x1][y1].speed / (_CurMap[x1][y1].speed + _CurMap[x2][y2].speed);
	_CurMap[x2][y2].dir += _CurMap[x1][y1].dir * tmp;
	while ( _CurMap[x2][y2].dir >= 2*PI )
		_CurMap[x2][y2].dir -= 2*PI;

	//	new value of x2,y2 speed (V(x * x + y * y))
	tmp = pow(sin(way) * _CurMap[x2][y2].speed +
			(sin(_CurMap[x1][y1].dir) * _CurMap[x1][y1].speed), 2);
	tmp += pow(cos(way) * _CurMap[x2][y2].speed +
			(cos(_CurMap[x1][y1].dir) * _CurMap[x1][y1].speed), 2);
	_CurMap[x2][y2].speed = sqrt(tmp);
	if (_CurMap[x2][y2].speed > 1)
		_CurMap[x2][y2].speed = 1;

	//	new value of x1,y1 speed
	_CurMap[x1][y1].speed *= slow;
}

//	Wave functions
float Water::WavesMin( bool n, bool s, bool e, bool w ) {
	float zmin = 1;

	//	Check lowest point of the edge
	if ( n ) {
		for ( unsigned int x = 0; x <= _sizeX; x++ ) {
			if ( _CurMap[x][0].height + _Map[x][0] < zmin )
				zmin = _CurMap[x][0].height + _Map[x][0];
		}
	}
	if ( s ) {
		for ( unsigned int x = 0; x <= _sizeX; x++ ) {
			if ( _CurMap[x][_sizeY].height + _Map[x][_sizeY] < zmin )
				zmin = _CurMap[x][_sizeY].height + _Map[x][_sizeY];
		}
	}
	if ( w ) {
		for ( unsigned int y = 0; y <= _sizeY; y++ ) {
			if ( _CurMap[0][y].height + _Map[0][y] < zmin )
				zmin = _CurMap[0][y].height + _Map[0][y];
		}
	}
	if ( e ) {
		for ( unsigned int y = 0; y <= _sizeY; y++ ) {
			if ( _CurMap[_sizeX][y].height + _Map[_sizeX][y] < zmin )
				zmin = _CurMap[_sizeX][y].height + _Map[_sizeX][y];
		}
	}
	return zmin;
}

//	Clear
void Water::ClearCurMap( void ) {
	for ( unsigned x = 0; x <= _sizeX; x++) {
		for ( unsigned y = 0; y <= _sizeY; y++) {
			_CurMap[x][y].height = 0;
		}
	}
}
