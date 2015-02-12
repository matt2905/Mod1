/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/12 12:39:46 by mmartin          ###   ########.fr       */
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



void		GraphicalDisplay::draw(float **tab)
{
	int		proj_x;
	int		proj_y;

	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			proj_x = 0.5f * x - 0.5f * y + 500;
			proj_y = tab[y][x] * -100 + 0.25f * x + 0.25f * y;
			if (tab[y][x] < 0.1f)
				XDrawPoint(_dis, _win, _green, proj_x, proj_y);
			else if (tab[y][x] < 0.4f)
				XDrawPoint(_dis, _win, _brown, proj_x, proj_y);
			else if (tab[y][x] < 0.6f)
				XDrawPoint(_dis, _win, _grey, proj_x, proj_y);
			else
				XDrawPoint(_dis, _win, _white, proj_x, proj_y);
		}
	}
}

GC			GraphicalDisplay::setColor(const char *str)
{
	XColor		color;
	Colormap	colormap;
	GC			gc;

	gc = XCreateGC(_dis, _win, 0, 0);
	colormap = DefaultColormap(_dis, 0);
	XParseColor(_dis, colormap, str, &color);
	XAllocColor(_dis, colormap, &color);
	XSetForeground(_dis, gc, color.pixel);
	return (gc);
}

void		GraphicalDisplay::run(void)
{
	float		**tab = _map->getMap();

	_green = this->setColor("#096A09");
	_brown = this->setColor("#8B4513");
	_white = this->setColor("#FFFFFF");
	_grey = this->setColor("#D3D3D3");

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
