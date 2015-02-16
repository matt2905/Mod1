/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/16 17:40:19 by mmartin          ###   ########.fr       */
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
	attributes.background_pixel = XWhitePixel(_dis, screen);

	_win = XCreateWindow(_dis, XRootWindow(_dis, screen), 0, 0, _width, _height, 1, depth, InputOutput, visual, CWBackPixel, &attributes);
	XMapWindow(_dis, _win);
	XSelectInput(_dis, _win, ExposureMask | KeyPressMask | ButtonPressMask);

	_data = new char[_width * _height * 4];
	_image = XCreateImage(_dis, visual, depth, XYPixmap, 0, _data, _width, _height, 32, 0);
	_dataWater = new char[_width * _height * 4];
	_imageWater = XCreateImage(_dis, visual, depth, XYPixmap, 0, _dataWater, _width, _height, 32, 0);

	_dataGrey = new char[200 * 25 * 4];
	_greyBG = XCreateImage(_dis, visual, depth, XYPixmap, 0, _dataGrey, 200, 25, 32, 0);
	_dataWhite = new char[200 * 25 * 4];
	_whiteBG = XCreateImage(_dis, visual, depth, XYPixmap, 0, _dataWhite, 200, 25, 32, 0);

	rise = true;
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
	unsigned int	color;
	int				proj_x;
	int				proj_y;

	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			proj_x = 0.5f * x - 0.5f * y + 500;
			proj_y = tab[x][y] * -100 + 0.25f * x + 0.25f * y + 500;
			if (tab[x][y] > 0.8)
				color = 0xFFFF00 + tab[x][y] * 255;
			else if (tab[x][y] > 0.6)
				color = 0x795227 + tab[x][y];
			else if (tab[x][y] > 0.2)
				color = 0x87591A + tab[x][y];
			else if (tab[x][y] > 0.01)
				color = 0x8B6C42 + tab[x][y];
			else
				color = 0x3A9D23;
			XPutPixel(_image, proj_x, proj_y, color);
			XPutPixel(_imageWater, proj_x, proj_y, color);
		}
	}
}

void		GraphicalDisplay::drawWater(float **tab)
{
	unsigned int	color;
	t_water			**map;
	int				proj_x;
	int				proj_y;

	map = _water->getCurMap();
	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			if (tab[x][y] < map[x][y].height)
			{
				proj_x = 0.5f * x - 0.5f * y + 500;
				proj_y = map[x][y].height * -100 + 0.25f * x + 0.25f * y + 500;
				color = 0x0000FF;
			}
			else
			{
				proj_x = 0.5f * x - 0.5f * y + 500;
				proj_y = tab[x][y] * -100 + 0.25f * x + 0.25f * y + 500;
				if (tab[x][y] > 0.8)
					color = 0xFFFF00 + tab[x][y] * 255;
				else if (tab[x][y] > 0.6)
					color = 0x795227 + tab[x][y];
				else if (tab[x][y] > 0.2)
					color = 0x87591A + tab[x][y];
				else if (tab[x][y] > 0.01)
					color = 0x8B6C42 + tab[x][y];
				else
					color = 0x3A9D23;
			}
			XPutPixel(_imageWater, proj_x, proj_y, color);
		}
	}

}

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

void		GraphicalDisplay::expose(GC gc)
{
	XPutImage(_dis, _win, gc, _imageWater, 0, 0, 0, 0, _width, _height);
	XPutImage(_dis, _win, gc, (rise ? _whiteBG : _greyBG), 0, 0, 0, 0, 200, 25);
	XDrawString(_dis, _win, gc, 50, 15, "Rise water", 10);
	XPutImage(_dis, _win, gc, (south ? _whiteBG : _greyBG), 0, 0, 200, 0, 200, 25);
	XDrawString(_dis, _win, gc, 250, 15, "South wave", 10);
	XPutImage(_dis, _win, gc, (east ? _whiteBG : _greyBG), 0, 0, 200, 25, 200, 25);
	XDrawString(_dis, _win, gc, 250, 40, "East wave", 9);
	XPutImage(_dis, _win, gc, (north ? _whiteBG : _greyBG), 0, 0, 200, 50, 200, 25);
	XDrawString(_dis, _win, gc, 250, 65, "North wave", 10);
	XPutImage(_dis, _win, gc, (west ? _whiteBG : _greyBG), 0, 0, 200, 75, 200, 25);
	XDrawString(_dis, _win, gc, 250, 90, "West wave", 9);
	XPutImage(_dis, _win, gc, _greyBG, 0, 0, 200, 100, 200, 25);
	XDrawString(_dis, _win, gc, 250, 115, "All wave", 8);
	XPutImage(_dis, _win, gc, (rain ? _whiteBG : _greyBG), 0, 0, 400, 0, 200, 25);
	XDrawString(_dis, _win, gc, 450, 15, "Rain water", 10);
	XPutImage(_dis, _win, gc, (evaporate ? _whiteBG : _greyBG), 0, 0, 600, 0, 200, 25);
	XDrawString(_dis, _win, gc, 650, 15, "Evaporate water", 15);
	XPutImage(_dis, _win, gc, _greyBG, 0, 0, 800, 0, 200, 25);
	XDrawString(_dis, _win, gc, 850, 15, "Exit", 4);
	XFlush(_dis);
}

bool		GraphicalDisplay::buttonEvent(GC gc, XEvent event)
{
	int		x = event.xbutton.x;
	int		y = event.xbutton.y;

	if (x < 1000 && y < 125)
	{
		if (y < 25 || (x > 200 && x < 400))
		{
			rise = false;
			rain = false;
			evaporate = false;
			if (!(x > 200 && x < 400))
			{
				south = false;
				east = false;
				north = false;
				west = false;
			}
		}
		if (y < 25 && x < 200)
			rise = (rise ? false : true);
		else if (y < 25 && x < 400)
			south = (south ? false : true);
		else if (y < 50 && x < 400)
			east = (east ?  false: true);
		else if (y < 75 && x < 400)
			north = (north ? false: true);
		else if (y < 100 && x < 400)
			west = (west ? false : true);
		else if (y < 125 && x < 400)
		{
			south = true;
			east = true;
			north = true;
			west = true;
		}
		else if (y < 25 && x < 600)
			rain = (rain ? false : true);
		else if (y < 25 && x < 800)
			evaporate = (evaporate ? false : true);
		else if (y < 25 && x < 1000)
			return (true);
		if (y < 25 || (x > 200 && x < 400))
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
	int				fd;
	fd_set			in_fds;
	struct timeval	tv;


	fd = ConnectionNumber(_dis);
	gc = XCreateGC(_dis, _win, 0, 0);
	this->setBackground();
	this->draw(tab);
	while (run)
	{
		FD_ZERO(&in_fds);
		FD_SET(fd, &in_fds);

		tv.tv_usec = 10000;
		tv.tv_sec = 0;

		if (select(fd + 1, &in_fds, 0, 0, &tv))
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
		else
		{
			if (rise)
				_water->Flood();
			if (south || east ||  north || west)
				_water->Waves(north, south, east, west);
			if (rain)
				_water->Rainy();
			this->drawWater(tab);
			this->expose(gc);
		}
	}
	XFreeGC(_dis, gc);
}
