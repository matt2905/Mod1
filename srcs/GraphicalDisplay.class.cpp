/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/16 19:57:57 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "GraphicalDisplay.class.hpp"

/*
**	Constructor / destructor
*/
GraphicalDisplay::GraphicalDisplay(unsigned int width, unsigned int height)
{
	XSetWindowAttributes	attributes;
	Visual					*visual;
	int						screen;
	int						depth;

	_width = width;
	_height = height;
	_map = new Map(_width, _height);

	_dis = XOpenDisplay(NULL);
	screen = DefaultScreen(_dis);
	visual = DefaultVisual(_dis, screen);
	depth = DefaultDepth(_dis, screen);
	attributes.background_pixel = XBlackPixel(_dis, screen);

	_win = XCreateWindow(_dis, XRootWindow(_dis, screen), 0, 0, 1500, 900, 1, depth, InputOutput, visual, CWBackPixel, &attributes);
	XMapWindow(_dis, _win);
	XSelectInput(_dis, _win, ExposureMask | KeyPressMask | ButtonPressMask);

	_data = new char[_width * _height * 4];
	_image = XCreateImage(_dis, visual, depth, ZPixmap, 0, _data, _width, _height, 32, 0);
	_dataWater = new char[_width * _height * 4];
	_imageWater = XCreateImage(_dis, visual, depth, ZPixmap, 0, _dataWater, _width, _height, 32, 0);

	_dataGrey = new char[200 * 25 * 4];
	_greyBG = XCreateImage(_dis, visual, depth, ZPixmap, 0, _dataGrey, 200, 25, 32, 0);
	_dataWhite = new char[200 * 25 * 4];
	_whiteBG = XCreateImage(_dis, visual, depth, ZPixmap, 0, _dataWhite, 200, 25, 32, 0);

	rise = false;
	rain = false;
	evaporate = false;
	south = false;
	east = false;
	north = false;
	west = false;
}

GraphicalDisplay::~GraphicalDisplay(void)
{
	if (_map)
		delete _map;
	XDestroyImage(_image);
	XDestroyImage(_greyBG);
	XDestroyImage(_whiteBG);
	XCloseDisplay(_dis);
}

/*
**	Setter
*/
bool		GraphicalDisplay::setMap(std::list<t_map> &mapHill)
{
	if (!_map)
		return (false);

	_map->setMapHill(mapHill);

	return (true);
}

bool		GraphicalDisplay::setWater(void)
{
	_water = new Water(_map->getMap(), _width, _height);
	return (true);
}

/*
**		Draw pixel per pixel
**		TODO: degraded on color from 0.01 to 0.8 with brown
*/
void		GraphicalDisplay::draw(float **tab)
{
	int				r;
	int				g;
	int				b;
	int				proj_x;
	int				proj_y;
	int				i;

	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			proj_x = 0.5f * x - 0.5f * y + 500;
			proj_y = tab[x][y] * -100 + 0.25f * x + 0.25f * y + 200; 
			i = proj_y * _image->bytes_per_line + proj_x * 4;
			if (tab[x][y] > 0.8)
			{
				r = tab[x][y] * 255;
				g = tab[x][y] * 255;
				b = 255;
			}
			else if (tab[x][y] > 0.01)
			{
				r = 73 + tab[x][y] * 255;
				g = 49 + tab[x][y] * 255;
				b = 28 + tab[x][y] * 255 / 2;
			}
			else
			{
				r = 0;
				g = 255;
				b = 0;
			}
			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;
			_data[i] = b;
			_data[i + 1] = g;
			_data[i + 2] = r;
		}
	}
}

/*
**	Draw water in image.
*/
void		GraphicalDisplay::drawWater(GC gc, float **tab)
{
	int				r;
	int				g;
	int				b;
	t_water			**map;
	int				proj_x;
	int				proj_y;
	int				i;

	map = _water->getCurMap();
	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			proj_x = 0.5f * x - 0.5f * y + 500;
			proj_y = 0.25f * x + 0.25 * y + 200;
			if (tab[x][y] < map[x][y].height)
			{
				proj_y += map[x][y].height * -100;
				r = 0;
				g = 0;
				b = 255;
			}
			else
			{
				proj_y += tab[x][y] * -100;
				if (tab[x][y] > 0.8)
				{
					r = tab[x][y] * 255;
					g = tab[x][y] * 255;
					b = 255;
				}
				else if (tab[x][y] > 0.01)
				{
					r = 73 + tab[x][y] * 255;
					g = 49 + tab[x][y] * 255;
					b = 28 + tab[x][y] * 255 / 2;
				}
				else
				{
					r = 0;
					g = 255;
					b = 0;
				}
				if (r > 255)
					r = 255;
				if (g > 255)
					g = 255;
				if (b > 255)
					b = 255;

			}
			i = proj_y * _imageWater->bytes_per_line + proj_x * 4;
			if ( i < 0)
				continue ;
			_dataWater[i] = b;
			_dataWater[i + 1] = g;
			_dataWater[i + 2] = r;
		}
	}
	XPutImage(_dis, _win, gc, _imageWater, 0, 0, 200, 200, _width, _height);
}


/*
**	Draw image foreground for button.
*/
void		GraphicalDisplay::setBackground(void)
{
	for (int x = 0; x < 200; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			XPutPixel(_greyBG, x, y, (!y || !x ? 0x000000 : 0xd3d3d3));
			XPutPixel(_whiteBG, x, y, (!y || !x ? 0x000000 : 0xFFFFFF));
		}
	}
}


/*
**	Expose, redraw each button and the image.
*/
void		GraphicalDisplay::expose(GC gc)
{
	XPutImage(_dis, _win, gc, _imageWater, 0, 0, 200, 200, _width, _height);
	XPutImage(_dis, _win, gc, (rise ? _whiteBG : _greyBG), 0, 0, 0, 0, 200, 25);
	XDrawString(_dis, _win, gc, 50, 15, "Rise water", 10);
	XPutImage(_dis, _win, gc, (rain ? _whiteBG : _greyBG), 0, 0, 200, 0, 200, 25);
	XDrawString(_dis, _win, gc, 250, 15, "Rain water", 10);
	XPutImage(_dis, _win, gc, (evaporate ? _whiteBG : _greyBG), 0, 0, 400, 0, 200, 25);
	XDrawString(_dis, _win, gc, 450, 15, "Evaporate water", 15);
	XPutImage(_dis, _win, gc, (south ? _whiteBG : _greyBG), 0, 0, 0, 25, 200, 25);
	XDrawString(_dis, _win, gc, 50, 40, "South wave", 10);
	XPutImage(_dis, _win, gc, (east ? _whiteBG : _greyBG), 0, 0, 200, 25, 200, 25);
	XDrawString(_dis, _win, gc, 250, 40, "East wave", 9);
	XPutImage(_dis, _win, gc, (north ? _whiteBG : _greyBG), 0, 0, 400, 25, 200, 25);
	XDrawString(_dis, _win, gc, 450, 40, "North wave", 10);
	XPutImage(_dis, _win, gc, (west ? _whiteBG : _greyBG), 0, 0, 600, 25, 200, 25);
	XDrawString(_dis, _win, gc, 650, 40, "West wave", 9);
	XPutImage(_dis, _win, gc, _greyBG, 0, 0, 800, 25, 200, 25);
	XDrawString(_dis, _win, gc, 850, 40, "All wave", 8);
	XPutImage(_dis, _win, gc, _greyBG, 0, 0, 600, 0, 200, 25);
	XDrawString(_dis, _win, gc, 650, 15, "Reset", 5);
	XPutImage(_dis, _win, gc, _greyBG, 0, 0, 800, 0, 200, 25);
	XDrawString(_dis, _win, gc, 850, 15, "Exit", 4);
	XFlush(_dis);
}


/*
**	On click check position x | y for button event.
*/
bool		GraphicalDisplay::buttonEvent(GC gc, XEvent event)
{
	int		x = event.xbutton.x;
	int		y = event.xbutton.y;

	if (x < 1000 && y < 50)
	{
		if (y < 25 && x > 800 && x < 1000)
			return (true);
		if (y < 25)
		{
			south = false;
			east = false;
			north = false;
			west = false;
		}
		else
		{
			rain = false;
			rise = false;
			evaporate = false;
		}
		if (y < 25 && x < 200)
		{
			rise = (rise ? false : true);
			rain = false;
			evaporate = false;
		}
		else if (y < 25 && x < 400)
		{
			rise = false;
			rain = (rain ? false : true);
			evaporate = false;
		}
		else if (y < 25 && x < 600)
		{
			rise = false;
			rain = false;
			evaporate = (evaporate ? false : true);
		}
		else if (y < 25 && x < 800)
		{
			rise = false;
			rain = false;
			evaporate = false;
			memcpy(_dataWater, _data, _height * _width * 4);
			_water->ClearCurMap();
		}
		else if (y > 25 && x < 200)
			south = (south ? false : true);
		else if (y > 25 && x < 400)
			east = (east ?  false: true);
		else if (y > 25 && x < 600)
			north = (north ? false: true);
		else if (y > 25 && x < 800)
			west = (west ? false : true);
		else if (y > 25 && x < 1000)
		{
			south = true;
			east = true;
			north = true;
			west = true;
		}
		this->expose(gc);
	}
	return (false);
}

/*
**		Run XQuartz in infinity loop for catch event
*/
void		GraphicalDisplay::run(void)
{
	GC				gc;
	float			**tab = _map->getMap();
	bool			run = true;

	gc = XCreateGC(_dis, _win, 0, 0);
	this->setBackground();
	this->draw(tab);
	memcpy(_dataWater, _data, _height * _width * 4);

	while (run)
	{
		while (XPending(_dis))
		{
			XNextEvent(_dis, &_report);
			switch (_report.type) {
				case Expose:
					if (_report.xexpose.count == 0)
						this->expose(gc);
				break;
				case KeyPress:
					if (XLookupKeysym(&_report.xkey, 0) == XK_q)
						run = false;
				break;
				case ButtonPress:
					if (this->buttonEvent(gc, _report))
						run = false;
				break;
			}
		}
		if (rise || rain || south || east || north || west)
		{
			if (rise)
				_water->Flood();
			if (south || east ||  north || west)
				_water->Waves(north, south, east, west);
			if (rain)
				_water->Rainy();
			_water->Flow();
			this->drawWater(gc, tab);
		}
	}
	XFreeGC(_dis, gc);
}
