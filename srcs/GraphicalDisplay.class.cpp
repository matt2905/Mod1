/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:36:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/03/24 11:49:36 by mmartin          ###   ########.fr       */
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

	this->drawAllButton();

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
			}
			if (x == 0 || y == 0 )
			{
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


void		GraphicalDisplay::drawButton(int x, int y, int color)
{
	int		xmax = x + 200;
	int		ymax = y + 25;
	int		tmp_y;

	glBegin(GL_POINTS);
	for (; x < xmax; x++)
	{
		for (tmp_y = y; tmp_y < ymax; tmp_y++)
		{
			glColor3ub(color, color, color);
			glVertex2f(x, tmp_y);
		}
	}
	glEnd();
}

void		GraphicalDisplay::drawAllButton(void)
{
	int		color;

	// Rise
	color = (rise ? 0xFF : 0xD3);
	this->drawButton(-795, -495, color);
	// Rain
	color = (rain ? 0xFF : 0xD3);
	this->drawButton(-594, -495, color);
	// Evaporate
	color = (evaporate ? 0xFF : 0xD3);
	this->drawButton(-393, -495, color);
	// Reset
	this->drawButton(-192, -495, 0xD3);
	// Exit
	this->drawButton(9, -495, 0xD3);
	// South
	color = (south ? 0xFF : 0xD3);
	this->drawButton(-795, -469, color);
	// East
	color = (east ? 0xFF : 0xD3);
	this->drawButton(-594, -469, color);
	// North
	color = (north ? 0xFF : 0xD3);
	this->drawButton(-393, -469, color);
	// West
	color = (west ? 0xFF : 0xD3);
	this->drawButton(-192, -469, color);
	// All
	this->drawButton(9, -469, 0xD3);
}

/*
**	On click check position x | y for button event.
*/

bool		GraphicalDisplay::buttonEvent(void)
{
	double		x;
	double		y;

	glfwGetCursorPos(_win, &x, &y);
	if (x < 1005 && x > 5 && y < 55 && y > 5)
	{
		if (y < 30 && x > 809)
			return (true);
		if (y < 30)
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
		if (y < 30 && x < 205)
		{
			rise = (rise ? false : true);
			rain = false;
			evaporate = false;
		}
		else if (y < 30 && x < 406)
		{
			rise = false;
			rain = (rain ? false : true);
			evaporate = false;
		}
		else if (y < 30 && x < 607)
		{
			rise = false;
			rain = false;
			evaporate = (evaporate ? false : true);
		}
		else if (y < 30 && x < 808)
		{
			rise = false;
			rain = false;
			evaporate = false;
			_water->ClearCurMap();
		}
		else if (y > 30 && x < 205)
			south = (south ? false : true);
		else if (y > 30 && x < 406)
			east = (east ?  false: true);
		else if (y > 30 && x < 607)
			north = (north ? false: true);
		else if (y > 30 && x < 808)
			west = (west ? false : true);
		else if (y > 30 && x < 1009)
		{
			south = true;
			east = true;
			north = true;
			west = true;
		}
	}
	return (false);
}

/*
**		Catch Event for close window and run senary
*/
bool		GraphicalDisplay::run(void)
{
	static	bool release = true;

	glfwPollEvents();
	if (glfwWindowShouldClose(_win) || glfwGetKey(_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return (false);
	if (glfwGetMouseButton(_win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (release && this->buttonEvent())
			return (false);
		release = false;
	}
	else
		release = true;

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
