/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/15 15:30:11 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Water.class.hpp"

//TO DO:
//		Boost speed use ( divise calcul by 4, 8 or more ?)
//		Seek auto-generate water error
//		Add 4 angle for each function
//		seprate scenario and water function
/* ************************************************************************** */
//	Public Functions:

//	Constructor
Water::Water( float ** Map, unsigned int sizeX, unsigned int sizeY) :
	_w(true), _s(true), _e(true), _n(true), _Map(Map), _sizeX(sizeX), _sizeY(sizeY) {
	_CurMap = new t_water*[_sizeX];
	for (unsigned int x = 0; x < _sizeX; x++)
	{
		_CurMap[x] = new t_water[_sizeY];
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			_CurMap[x][y].height = 0;
			_CurMap[x][y].speed = 0;
			_CurMap[x][y].dir = 0;
		}
	}
}

//	Destructor
Water::~Water( void ) {
	for ( unsigned int x = 0; x < _sizeX; x++ )
		delete [] this->_CurMap[x];
	delete [] this->_CurMap;
}

//	Getter
t_water ** Water::getCurMap( void ) {
	return this->_CurMap;
}

//	Scenario
void Water::Rainy( void ) {
	double PI = std::atan(1.0)*8;

	//	Give speed of flowing
	float rainy = 0.01;

	//	Give density (lowest is the number, higher is the density)
	unsigned int density = 100;
	unsigned int precipitate = (_sizeX * _sizeY) / density;
	unsigned int x;
	unsigned int y;

	srand (time(NULL));
	for ( unsigned int rain = 0; rain < precipitate; rain++ ) {
		x = rand() % _sizeX;
		y = rand() % _sizeY;
		if ( _Map[x][y] + _CurMap[x][y].height + rainy < 1) {
			_CurMap[x][y].height += rainy;

			//	Give random direction
			if ( _CurMap[x][y].height == rainy )
				_CurMap[x][y].dir = (rand() * PI) / (RAND_MAX * PI);
		}
	}
}

void Water::Waves( bool n, bool s, bool e, bool w ) {
	double PI = std::atan(1.0);

	//	Give speed of flowing
	float waves = 0.01;

	//	Check lowest hight
	float zmin = WavesMin(n, s, e, w) + waves;

	//	Increase hight of wave
	//		North wave
	for ( unsigned int x = 0; x < _sizeX && n; x++ ) {
		if ( _CurMap[x][0].height + _Map[x][0] < zmin + waves )
			_CurMap[x][0].height += waves;
		if ( _CurMap[x][0].height + _Map[x][0] > 1 )
			_CurMap[x][0].height = 1 - _Map[x][0];
		_CurMap[x][0].dir = 5 * PI;
		_CurMap[x][0].speed = 0.5;
	}
	//		South wave
	for ( unsigned int x = 0; x < _sizeX && s; x++ ) {
		if ( _CurMap[x][_sizeY-1].height + _Map[x][_sizeY-1] < zmin + waves )
			_CurMap[x][_sizeY-1].height += waves;
		if ( _CurMap[x][_sizeY-1].height + _Map[x][_sizeY-1] > 1 )
			_CurMap[x][_sizeY-1].height = 1 - _Map[x][_sizeY-1];
		_CurMap[x][_sizeY-1].dir = PI;
		_CurMap[x][_sizeY-1].speed = 0.5;
	}
	//		West wave
	for ( unsigned int y = 0; y < _sizeY && w; y++ ) {
		if ( _CurMap[0][y].height + _Map[0][y] < zmin + waves )
			_CurMap[0][y].height += waves;
		if ( _CurMap[0][y].height + _Map[0][y] > 1 )
			_CurMap[0][y].height = 1 - _Map[0][y];
		_CurMap[_sizeX-1][y].dir = 7 * PI;
		_CurMap[0][y].speed = 0.5;
	}
	//		Est wave
	for ( unsigned int y = 0; y < _sizeY && e; y++ ) {
		if ( _CurMap[_sizeX-1][y].height + _Map[_sizeX-1][y] < zmin + waves )
			_CurMap[_sizeX-1][y].height += waves;
		if ( _CurMap[_sizeX-1][y].height + _Map[_sizeX-1][y] > 1 )
			_CurMap[_sizeX-1][y].height = 1 - _Map[_sizeX-1][y];
		_CurMap[0][y].dir = 3 * PI;
		_CurMap[_sizeX-1][y].speed = 0.5;
	}
}

void Water::Flood( void ) {
	double PI = std::atan(1.0)*8;

	//	Give speed of flowing
	float flood = 0.01;
	float hillmin = _Map[0][0];
	float zmin = _Map[0][0] + _CurMap[0][0].height;

	srand (time(NULL));
	//	Check lowest point of map
	if ( zmin < 1 && hillmin < 1 && hillmin > 0 ) {
		for ( unsigned int x = 0; x < _sizeX && hillmin > 0; x++ ) {
			for ( unsigned int y = 0; y < _sizeY && hillmin > 0; y++ ) {
				if ( _Map[x][y] < hillmin ) {
					hillmin = _Map[x][y];
					zmin = _Map[x][y] + _CurMap[x][y].height;
				}
			}
		}
	}
	zmin += flood;
	if ( zmin > 1 )
		zmin = 1;

	//	Add flood
	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			if ( _Map[x][y] + _CurMap[x][y].height < zmin )
				_CurMap[x][y].height += flood;

			if ( _CurMap[x][y].height == flood )
				_CurMap[x][y].dir = (rand() * PI) / (RAND_MAX * PI);

			//	limit flood
			if ( _Map[x][y] + _CurMap[x][y].height > 1 )
				_CurMap[x][y].height = 1 - _Map[x][y];
		}
	}
}

void Water::Evapor( void ) {

	//	Give evaporate speed;
	float hot = 0.01;

	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			_CurMap[x][y].height -= hot;
			if ( _CurMap[x][y].height <= 0.0 ) {
				_CurMap[x][y].height = 0;
				_CurMap[x][y].speed = 0;
			}
		}
	}
}

void Water::DiscWorld( bool n, bool s, bool e, bool w ) {
	double PI = std::atan(1.0);

	//	North fall
	for ( unsigned int x = 0; x < _sizeX && n; x++ ) {
		_CurMap[x][0].height = 0;
		_CurMap[x][0].speed = 0;
		_CurMap[x][0].dir = PI; 
	}
	//	South fall
	for ( unsigned int x = 0; x < _sizeX && s; x++ ) {
		_CurMap[x][_sizeY-1].height = 0;
		_CurMap[x][_sizeY-1].speed = 0;
		_CurMap[x][_sizeY-1].dir = 5 * PI;
	}
	//	Est fall
	for ( unsigned int y = 0; y < _sizeY && e; y++ ) {
		_CurMap[0][y].height = 0;
		_CurMap[0][y].speed = 0;
		_CurMap[0][y].dir = 3 * PI;
	}
	//	West fall
	for ( unsigned int y = 0; y < _sizeY && w; y++ ) {
		_CurMap[_sizeX-1][y].height = 0;
		_CurMap[_sizeX-1][y].speed = 0;
		_CurMap[_sizeX-1][y].dir = 7 * PI;
	}
}

//	Clear
void Water::ClearCurMap( void ) {
	for ( unsigned x = 0; x < _sizeX; x++) {
		for ( unsigned y = 0; y < _sizeY; y++) {
			_CurMap[x][y].height = 0;
			_CurMap[x][y].speed = 0.0;
			_CurMap[x][y].dir = 0.0;
		}
	}
}

//	Flowing
void Water::Flow( void ) {
	Drop();
	Speed();
}

/* ************************************************************************** */
//	Private Functions:


//To Do:
//		Add 4 angle (0; PI/2; PI; 3PI/2) to speed and drop;
//	Calcul flow
//		Compare height's difference, influent speed
void Water::Drop( void ) {
	double PI = std::atan(1.0);
	float drop = 0.01;
	float speed;
	float hgt;
	float dir;

	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			if ( _CurMap[x][y].height > drop ) {
				speed = drop;
				hgt = _CurMap[x][y].height + _Map[x][y];

				//	Check highest difference
/*				if ( x + 1 < _sizeX && y > 0
						&& speed < hgt - _CurMap[x+1][y-1].height - _Map[x+1][y-1] ) {
					speed = hgt - _CurMap[x+1][y-1].height - _Map[x+1][y-1];
					dir = 0;
				}
*/				if ( x + 1 < _sizeX
						&& speed < hgt - _CurMap[x+1][y].height - _Map[x+1][y] ) {
					speed = hgt - _CurMap[x+1][y].height - _Map[x+1][y];
					dir = 7 * PI;
				}
/*				if ( x + 1 < _sizeX && y + 1 < _sizeY
						&& speed < hgt - _CurMap[x+1][y+1].height - _Map[x+1][y+1] ) {
					speed = hgt - _CurMap[x+1][y].height - _Map[x+1][y];
					dir = 2*PI;
				}
*/				if ( y + 1 < _sizeY
						&& speed < hgt - _CurMap[x][y+1].height - _Map[x][y+1] ) {
					speed = hgt - _CurMap[x][y+1].height - _Map[x][y+1];
					dir = 5 * PI;
				}
/*				if ( y + 1 < _sizeY && x > 0
						&& speed < hgt - _CurMap[x-1][y+1].height - _Map[x-1][y+1] ) {
					speed = hgt - _CurMap[x-1][y+1].height - _Map[x-1][y+1];
					dir = 4*PI;
				}
*/				if ( x > 0 && speed < hgt - _CurMap[x-1][y].height - _Map[x-1][y] ) {
					speed = hgt - _CurMap[x-1][y].height - _Map[x-1][y];
					dir = 3 * PI;
				}
/*				if ( y > 0 && x > 0
						&& speed < hgt - _CurMap[x-1][y-1].height - _Map[x-1][y-1] ) {
					speed = hgt - _CurMap[x-1][y-1].height - _Map[x-1][y-1];
					dir = 6*PI;
				}
*/				if ( y > 0 && speed < hgt - _CurMap[x][y-1].height - _Map[x][y-1] ) {
					speed = hgt - _CurMap[x][y-1].height - _Map[x][y-1];
					dir = PI;
				}
				if ( speed > drop ) {
					DropNew(x, y, dir, speed);
				}
			}
		}
	}
}

//		Drop modification
void Water::DropNew( unsigned int x, unsigned int y, float dir, float speed ) {
	double PI = std::atan(1.0);
	float tmp;
	float way = _CurMap[x][y].dir;

	//	no divide by 0
	if ( _CurMap[x][y].speed + speed == 0 )
		return;

	//	new way value ((x / (x + y)) + (y / (x + y)))
	if ( _CurMap[x][y].dir - dir > (PI * 4) )
		dir += 8 * PI;
	if ( dir - _CurMap[x][y].dir > (PI * 4) )
		_CurMap[x][y].dir += 8 * PI;
	tmp = _CurMap[x][y].dir * (_CurMap[x][y].speed / (_CurMap[x][y].speed + speed));
	_CurMap[x][y].dir = tmp;
	_CurMap[x][y].dir += dir * (speed / (_CurMap[x][y].speed + speed));
	while ( _CurMap[x][y].dir >= 8 * PI )
		_CurMap[x][y].dir -= 8 * PI;

	//	new speed value (V(x * x + y * y))
	tmp = pow(((sin(way) * _CurMap[x][y].speed) + (sin(dir) * speed)), 2);
	tmp += pow(((cos(way) * _CurMap[x][y].speed) + (cos(dir) * speed)), 2);
	_CurMap[x][y].speed = sqrt(tmp);
	if ( _CurMap[x][y].speed > 1 )
		_CurMap[x][y].speed = 1;
}

//if ((n = x) == (n += y));?

//TO DO:
//		Boost speed (x + n where n = (int)(speed * 10));
//		Applicate speed
void Water::Speed( void ) {
	double PI = std::atan(1.0)*4;
	float slow = 0.6;
	float rlow = 0.0000;
	float lim = 0.0001;
/*	float tmp = 0;*/
	float drop;

/*	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			tmp += _CurMap[x][y].height;
		}
	}*/
	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			if ( _CurMap[x][y].speed > 0 ) {

				//	Verify valid direction (sens && edge && height)
				drop = _Map[x][y] + _CurMap[x][y].height + _CurMap[x][y].speed;
				//	x + 1
				for ( unsigned int n = 1;
						_CurMap[x][y].dir >= (3*PI/2) && _CurMap[x][y].dir < 2*PI &&
						(x + n) < _sizeX &&
						drop >= _CurMap[x+n-1][y+n-1].height + _Map[x][y] &&
						drop > _CurMap[x+n][y].height + _Map[x+n][y] &&
						(n == 1 ||
						drop >= _CurMap[x+n][y].height + _Map[x+n][y] + lim);
						n++ ) {
					drop -= (_CurMap[x+n][y].height + _Map[x+n][y]);
					drop = SpeedNew(x, y, x+n, y, slow, drop, rlow);
				}
				// x + 1 && y + 1
/*				else if ( _CurMap[x][y].dir >= (PI/4) && _CurMap[x][y].dir < (PI/2)
						&& (x + 1) < _sizeX && (y + 1) < _sizeY
						&& drop > _CurMap[x+1][y+1].height + _Map[x+1][y+1] ) {
					drop -= (_CurMap[x+1][y+1].height + _Map[x+1][y+1]);
					drop = SpeedNew(x, y, x+1, y+1, slow, drop/2);
					for ( unsigned int n = 2;
							(y + n) < _sizeY && (x + n) <_sizeX &&
							drop - _CurMap[x+n][y+n].height + _Map[x+n][y+n] >inertie;
							n++ ) {
						drop -= (_CurMap[x+n][y+n].height + _Map[x+n][y+n]);
						drop = SpeedNew(x, y, x+n, y+n, slow, drop/2);
					}
				}*/
				//	y + 1
				for ( unsigned int n = 1;
						_CurMap[x][y].dir >= PI && _CurMap[x][y].dir < (3*PI/2) &&
						(y + n) < _sizeY &&
						drop >= _CurMap[x][y+n-1].height + _Map[x][y+n-1] &&
						drop > _CurMap[x][y+n].height + _Map[x][y+n] &&
						(n == 1 ||
						drop >= _CurMap[x][y+n].height + _Map[x][y+n] + lim);
						n++ ) {
					drop -= (_CurMap[x][y+n].height + _Map[x][y+n]);
					drop = SpeedNew(x, y, x, y+n, slow, drop, rlow);
				}
				// x - 1 && y + 1
/*				else if ( _CurMap[x][y].dir >= (PI/4) && _CurMap[x][y].dir < (PI/2)
						&& (x - 1) > 0 && (y + 1) < _sizeY
						&& drop > _CurMap[x-1][y+1].height + _Map[x-1][y+1] ) {
					drop -= (_CurMap[x-1][y+1].height + _Map[x-1][y+1]);
					drop = SpeedNew(x, y, x-1, y+1, slow, drop/2);
					for ( unsigned int n = 2;
							(y + n) < _sizeY && x >= n &&
							drop - _CurMap[x-n][y+n].height + _Map[x-n][y+n] >inertie;
							n++ ) {
						drop -= (_CurMap[x-n][y+n].height + _Map[x+n][y+n]);
						drop = SpeedNew(x, y, x-n, y+n, slow, drop/2);
					}
				}*/
				// x - 1
				for ( unsigned int n = 1;
						_CurMap[x][y].dir >= (PI/2) && _CurMap[x][y].dir < PI &&
						x >= n &&
						drop >= _CurMap[x-n+1][y].height + _Map[x-n+1][y] &&
						drop > _CurMap[x-n][y].height + _Map[x-n][y] &&
						(n == 1 ||
						drop >= _CurMap[x-n][y].height + _Map[x-n][y] + lim);
						n++ ) {
					drop -= (_CurMap[x-n][y].height + _Map[x-n][y]);
					drop = SpeedNew(x, y, x-n, y, slow, drop, rlow);
				}
				// x - 1 && y - 1
/*				else if ( _CurMap[x][y].dir >= (PI/4) && _CurMap[x][y].dir < (PI/2)
						&& x > 0 && y > 0
						&& drop > _CurMap[x-1][y-1].height + _Map[x-1][y-1] ) {
					drop -= (_CurMap[x-1][y-1].height + _Map[x-1][y-1]);
					drop = SpeedNew(x, y, x-1, y-1, slow, drop/2);
					for ( unsigned int n = 2;
							y >= n && x >= n &&
							drop - _CurMap[x-n][y-n].height + _Map[x-n][y-n] >inertie;
							n++ ) {
						drop -= (_CurMap[x-n][y-n].height + _Map[x-n][y-n]);
						drop = SpeedNew(x, y, x-n, y-n, slow, drop/2);
					}
				}*/
				// y - 1
				for ( unsigned int n = 1;
						_CurMap[x][y].dir >= 0 && _CurMap[x][y].dir < (PI/2) &&
						y >= n &&
						drop >= _CurMap[x][y-n+1].height + _Map[x][y-n+1] &&
						drop > _CurMap[x][y-n].height + _Map[x][y-n] &&
						(n == 1 ||
						drop >= _CurMap[x][y-n].height + _Map[x][y-n] + lim);
						n++ ) {
					drop -= (_CurMap[x][y-n].height + _Map[x][y-n]);
					drop = SpeedNew(x, y, x, y-n, slow, drop, rlow);
				}
				// x + 1 && y - 1
/*				else if ( _CurMap[x][y].dir >= (PI/4) && _CurMap[x][y].dir < (PI/2)
						&& (x + 1) < _sizeX && y > 0
						&& drop > _CurMap[x+1][y-1].height + _Map[x+1][y-1] ) {
					drop -= (_CurMap[x+1][y-1].height + _Map[x+1][y-1]);
					drop = SpeedNew(x, y, x+1, y-1, slow, drop/2);
					for ( unsigned int n = 2;
							y >= n && (x + n) <_sizeX &&
							drop - _CurMap[x+n][y-n].height + _Map[x+n][y-n] >inertie;
							n++ ) {
						drop -= (_CurMap[x+n][y-n].height + _Map[x+n][y-n]);
						drop = SpeedNew(x, y, x+n, y-n, slow, drop/2);
					}
				}*/
				//	Counter speed
				if ((_CurMap[x][y].speed = _CurMap[x][y].speed - rlow) < 0)
					_CurMap[x][y].speed = 0;
				_CurMap[x][y].speed *= slow;
/*				_CurMap[x][y].dir += PI;
				if ( _CurMap[x][y].dir > 2 * PI)
					_CurMap[x][y].dir -= 2 * PI;
*/			}
		}
	}
/*	for ( unsigned int x = 0; x < _sizeX; x++ ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			tmp -= _CurMap[x][y].height;
		}
	}
	printf("tmp = %f\n", tmp);*/
}

//		Speed modification
float Water::SpeedNew( unsigned int x1, unsigned int y1,
		unsigned int x2, unsigned int y2, float slow, float drop, float rlow ) {
	double PI = std::atan(1.0)*4;
	float tmp;
	float way = _CurMap[x2][y2].dir;

	//	Inertie data
	float inertie = 0.4;

	//	Transfert of Water
	if (_CurMap[x1][y1].height < (drop * inertie) )
		drop = _CurMap[x1][y1].height;
	if ( (_CurMap[x2][y2].height + _Map[x2][y2] + (drop * inertie)) > 1 )
		drop = 1 - (_CurMap[x2][y2].height + _Map[x2][y2]);
	_CurMap[x1][y1].height -= drop * inertie;
	_CurMap[x2][y2].height += drop * inertie;
	if ( _CurMap[x2][y2].height + _Map[x2][y2] > 1 ) {
		tmp = _CurMap[x2][y2].height + _Map[x2][y2] - 1;
		_CurMap[x2][y2].height -= tmp;
		_CurMap[x1][y1].height += tmp;
	}
	drop = _Map[x1][y1] + _CurMap[x1][y1].height + _CurMap[x1][y1].speed;

	//	Transfert of Power
	//	no divide by 0
	if ( _CurMap[x1][y1].speed + _CurMap[x2][y2].speed == 0 )
		return drop;

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
	if ((_CurMap[x2][y2].speed = _CurMap[x2][y2].speed - slow) < 0)
		_CurMap[x2][y2].speed = 0;
	if (_CurMap[x2][y2].speed > 1)
		_CurMap[x2][y2].speed = 1;
	_CurMap[x2][y2].speed *= slow;

	//	new value of x1,y1 speed
	if ((_CurMap[x1][y1].speed = _CurMap[x1][y1].speed - rlow) < 0)
		_CurMap[x1][y1].speed = 0;
	_CurMap[x1][y1].speed *= slow;
	return drop;
}

//	Wave functions
float Water::WavesMin( bool n, bool s, bool e, bool w ) {
	float zmin = 1;

	//	Check lowest point of the edge
	if ( n ) {
		for ( unsigned int x = 0; x < _sizeX; x++ ) {
			if ( _CurMap[x][0].height + _Map[x][0] < zmin )
				zmin = _CurMap[x][0].height + _Map[x][0];
		}
	}
	if ( s ) {
		for ( unsigned int x = 0; x < _sizeX; x++ ) {
			if ( _CurMap[x][_sizeY - 1].height + _Map[x][_sizeY - 1] < zmin )
				zmin = _CurMap[x][_sizeY - 1].height + _Map[x][_sizeY - 1];
		}
	}
	if ( w ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			if ( _CurMap[0][y].height + _Map[0][y] < zmin )
				zmin = _CurMap[0][y].height + _Map[0][y];
		}
	}
	if ( e ) {
		for ( unsigned int y = 0; y < _sizeY; y++ ) {
			if ( _CurMap[_sizeX - 1][y].height + _Map[_sizeX - 1][y] < zmin )
				zmin = _CurMap[_sizeX - 1][y].height + _Map[_sizeX - 1][y];
		}
	}
	return zmin;
}
