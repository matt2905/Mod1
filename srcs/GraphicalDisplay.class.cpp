/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/01 12:03:31 by mmartin          ###   ########.fr       */
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



void		GraphicalDisplay::run(void)
{
	GC			green_gc;
	GC			brown_gc;
	GC			white_gc;
	XColor		color;
	Colormap	colormap;
	char		green[] = "#00FF00";
	char		brown[] = "#8B4513";
	char		white[] = "#FFFFFF";
	float		**tab = _map->getMap();


	colormap = DefaultColormap(_dis, 0);
	green_gc = XCreateGC(_dis, _win, 0, 0);
	brown_gc = XCreateGC(_dis, _win, 0, 0);
	white_gc = XCreateGC(_dis, _win, 0, 0);
	XParseColor(_dis, colormap, green, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, green_gc, color.pixel);

	XParseColor(_dis, colormap, brown, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, brown_gc, color.pixel);

	XParseColor(_dis, colormap, white, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, white_gc, color.pixel);

	while (1)
	{
		XNextEvent(_dis, &_report);
		switch (_report.type) {
			case Expose:
				for (size_t i = 0; i < _width; i++)
				{
					for (size_t y = 0; y < _height; y++)
					{
						if (tab[i][y] < 0.2)
							XDrawPoint(_dis, _win, green_gc, i, y);
						else if (tab[i][y] < 0.6)
							XDrawPoint(_dis, _win, brown_gc, i, y);
						else
							XDrawPoint(_dis, _win, white_gc, i, y);
					}
				}
				XFlush(_dis);
			break;
			case KeyPress:
				if (XLookupKeysym(&_report.xkey, 0) == XK_q)
					exit(0);
			break;
		}
	}
}
