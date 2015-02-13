/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/13 14:33:42 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
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
	_data = new char[_width * _height * 32 / 8];
	bzero(_data, _width * _height * 32 / 8);
	_image = XCreateImage(_dis, visual, depth, XYPixmap, 0, _data, _width, _height, 32, 0);
}

GraphicalDisplay::~GraphicalDisplay(void)
{
	if (_map)
		delete _map;
	XDestroyImage(_image);
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
			proj_y = tab[y][x] * -100 + 0.25f * x + 0.25f * y + 500;
			if (tab[y][x] > 0.8)
				color = 0xFFFF00 + tab[y][x] * 255;
			else if (tab[y][x] > 0.6)
				color = 0x795227 + tab[y][x];
			else if (tab[y][x] > 0.2)
				color = 0x87591A + tab[y][x];
			else if (tab[y][x] > 0.01)
				color = 0x8B6C42 + tab[y][x];
			else
				color = 0x3A9D23;
			XPutPixel(_image, proj_x, proj_y, color);
		}
	}
}

/*
**		Run XQuartz in infinity loop for catch event
*/
void		GraphicalDisplay::run(void)
{
	GC			gc;
	float		**tab = _map->getMap();
	bool		run = true;

	gc = XCreateGC(_dis, _win, 0, 0);
	this->draw(tab);
	while (run)
	{
		XNextEvent(_dis, &_report);
		switch (_report.type) {
			case Expose:
				XPutImage(_dis, _win, gc, _image, 0, 0, 0, 0, _width, _height);
				XFlush(_dis);
			break;
			case KeyPress:
				if (XLookupKeysym(&_report.xkey, 0) == XK_q)
					run = false;
			break;
		}
	}
	XFreeGC(_dis, gc);
}
