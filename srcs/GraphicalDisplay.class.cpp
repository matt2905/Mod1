/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/01/31 19:55:56 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <stdlib.h>
#include "GraphicalDisplay.class.hpp"

GraphicalDisplay::GraphicalDisplay(unsigned int width, unsigned int height)
{
	_dis = XOpenDisplay(NULL);
	_win = XCreateSimpleWindow(_dis, RootWindow(_dis, 0), 0, 0, width, height, 0, BlackPixel(_dis, 0), BlackPixel(_dis, 0));
	XMapWindow(_dis, _win);

	XSelectInput(_dis, _win, ExposureMask | KeyPressMask | ButtonPressMask);
}

GraphicalDisplay::~GraphicalDisplay(void)
{
}



void		GraphicalDisplay::run(void)
{
	GC			green_gc;
	XColor		green_col;
	Colormap	colormap;
	char		green[] = "#00FF00";


	colormap = DefaultColormap(_dis, 0);
	green_gc = XCreateGC(_dis, _win, 0, 0);
	XParseColor(_dis, colormap, green, &green_col);
	XAllocColor(_dis, colormap, &green_col);
	XSetForeground(_dis, green_gc, green_col.pixel);

	XDrawPoint(_dis, _win, green_gc, 500, 500);

	XFlush(_dis);

	while (1)
	{
		XNextEvent(_dis, &_report);
		switch (_report.type) {
			case Expose:
				for (int i = 1; i < 1000; i++)
					XDrawPoint(_dis, _win, green_gc, i, i);
				XFlush(_dis);
			break;
			case KeyPress:
				if (XLookupKeysym(&_report.xkey, 0) == XK_q)
					exit(0);
			break;
		}
	}
}
