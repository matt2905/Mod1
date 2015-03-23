/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/03/23 20:32:22 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "GraphicalDisplay.class.hpp"

/*
**	Constructor / destructor
*/
GraphicalDisplay::GraphicalDisplay(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;
	_map = new Map(_width, _height);

	_water = NULL;
	rise = false;
	rain = false;
	evaporate = false;
	south = false;
	east = false;
	north = false;
	west = false;

	if (!glfwInit())
		throw "GLFW init failed";
	_win = glfwCreateWindow(1800, 1300, "Mod1 by tbalea and mmartin", NULL, NULL);
	if (!_win)
		throw "GlFW create window failed";
	glfwMakeContextCurrent(_win);

	_data = new unsigned char[width * height * 4];
}

GraphicalDisplay::~GraphicalDisplay(void)
{
	if (_map)
		delete _map;
	if (_water)
		delete _water;
	if (_win)
		glfwDestroyWindow(_win);
	glfwTerminate();
}

/*
**	Getter
*/
Map			*GraphicalDisplay::getMap(void) const
{
	return (_map);
}

Water		*GraphicalDisplay::getWater(void) const
{
	return (_water);
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

void		GraphicalDisplay::getColor(float earth, float water, int *r, int *g, int *b)
{
	float			color;
	static t_color	blue[11] =
	{
		{36,185,228},
		{33,174,219},
		{31,164,211},
		{28,153,202},
		{26,142,194},
		{24,131,185},
		{21,120,177},
		{19,109,168},
		{16,99,160},
		{14,88,151},
		{11,77,143}
	};
	int				i = water * 10;

	*r = blue[i].r;
	*g = blue[i].g;
	*b = blue[i].b;
	if (!water)
	{
		color = earth * 255;
		*r = (earth > 0.01 ? 100 + color : 1);
		*g = (earth > 0.01 ? 60 + color : 121);
		*b = (earth > 0.01 ? 20 + color : 111);
	}
	*r = (*r > 255 ? 255 : *r);
	*g = (*g > 255 ? 255 : *g);
	*b = (*b > 255 ? 255 : *b);
}

/*
**	Draw water in image.
*/
void		GraphicalDisplay::drawWater(float **tab)
{
	int			r;
	int			g;
	int			b;
	t_water		**map;
	int			width;
	int			height;
	float		tmp_x = 0;
	float		tmp_y = 0;
	float		proj_x;
	float		proj_y;

	map = _water->getCurMap();

	glfwGetFramebufferSize(_win, &width, &height);
	glViewport(0, 0, width * 2, height * 2);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width, width, height, -height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1000, 500, 0);

	glBegin(GL_POINTS);
	for (size_t x = 0; x < _width; x++)
	{
		proj_x = tmp_x;
		proj_y = tmp_y;
		for (size_t y = 0; y < _height; y++)
		{
			getColor(tab[x][y], map[x][y].height, &r, &g, &b);
			glColor3ub(r, g, b);
			glVertex2f(proj_x, proj_y + (tab[x][y] + map[x][y].height) * -100);
			if (x == _width - 1)
			{
				for (float earth = 0.02; earth < tab[x][y]; earth += 0.01)
				{
					getColor(earth, 0, &r, &g, &b);
					glColor3ub(r, g, b);
					glVertex2f(proj_x, proj_y + earth * -100);
				}
				for (float water = map[x][y].height + tab[x][y]; water < 1; water += 0.01)
				{
					glColor3ub(0, 0, 0);
					glVertex2f(proj_x, proj_y + water * -100);
				}
			}
			proj_x -= 0.5;
			proj_y += 0.25;
		}
		for (float earth = 0.02; earth < tab[x][_height - 1]; earth += 0.01)
		{
			getColor(earth, 0, &r, &g, &b);
			glColor3ub(r, g, b);
			glVertex2f(proj_x, proj_y + earth * -100);
		}
		tmp_x += 0.5;
		tmp_y += 0.25;
	}
	glEnd();
	glfwSwapBuffers(_win);
}

/*
**		Catch Event for close window and run senary
*/
bool		GraphicalDisplay::run(void)
{
	glfwPollEvents();
	if (glfwWindowShouldClose(_win) || glfwGetKey(_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return (false);

	if (rise)
		_water->Flood();
	if (south || east || north || west)
		_water->Waves(north, south, east, west);
	if (rain)
		_water->Rainy();
	if (evaporate)
		_water->Evapor();

	return (true);
}
