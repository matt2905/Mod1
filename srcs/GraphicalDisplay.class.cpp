/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/12 11:10:40 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <stdlib.h>
#include "GraphicalDisplay.class.hpp"

GraphicalDisplay::GraphicalDisplay(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;
	_map = new Map(width, height);

	_dis = XOpenDisplay(NULL);
	_win = XCreateSimpleWindow(_dis, RootWindow(_dis, 0), 0, 0, width, height, 0, BlackPixel(_dis, 0), BlackPixel(_dis, 0));
	XMapWindow(_dis, _win);

	XSelectInput(_dis, _win, ExposureMask | KeyPressMask | ButtonPressMask);

	_green = XCreateGC(_dis, _win, 0, 0);
	_brown = XCreateGC(_dis, _win, 0, 0);
	_white = XCreateGC(_dis, _win, 0, 0);
}

GraphicalDisplay::~GraphicalDisplay(void)
{
	if (_map)
		delete _map;
}



bool		GraphicalDisplay::setMap(std::list<t_map> &mapHill)
{
	if (!_map)
		return (false);

	_map->setMapHill(mapHill);

	return (true);
}



void		GraphicalDisplay::draw(float **tab)
{
	int		proj_x;
	int		proj_y;

	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			proj_x = 0.5 * x - 0.5 * y + 500;
			proj_y = tab[y][x] + 0.25 * x + 0.25 * y + 500;
			if (tab[y][x] < 0.01)
				XDrawPoint(_dis, _win, _green, proj_x, proj_y);
			else if (tab[y][x] < 0.6)
				XDrawPoint(_dis, _win, _brown, proj_x, proj_y);
			else
				XDrawPoint(_dis, _win, _white, proj_x, proj_y);
		}
	}
}

void		GraphicalDisplay::run(void)
{
	XColor		color;
	Colormap	colormap;
	char		green[] = "#096A09";
	char		brown[] = "#8B4513";
	char		white[] = "#FFFFFF";
	float		**tab = _map->getMap();

	colormap = DefaultColormap(_dis, 0);
	XParseColor(_dis, colormap, green, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, _green, color.pixel);

	XParseColor(_dis, colormap, brown, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, _brown, color.pixel);

	XParseColor(_dis, colormap, white, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, _white, color.pixel);

	while (1)
	{
		XNextEvent(_dis, &_report);
		switch (_report.type) {
			case Expose:
				this->draw(tab);
				XFlush(_dis);
			break;
			case KeyPress:
				if (XLookupKeysym(&_report.xkey, 0) == XK_q)
					exit(0);
			break;
		}
	}
}
