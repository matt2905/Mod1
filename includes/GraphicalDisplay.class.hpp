/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:33:30 by mmartin           #+#    #+#             */
/*   Updated: 2015/03/24 11:25:24 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICALDISPLAY_CLASS_HPP
# define GRAPHICALDISPLAY_CLASS_HPP

# include <GLFW/glfw3.h>
# include <list>
# include "Map.class.hpp"
# include "Water.class.hpp"
# include "map.h"

class	GraphicalDisplay
{
	public:
		GraphicalDisplay(unsigned int, unsigned int);
		~GraphicalDisplay(void);

		Map					*getMap(void) const;
		Water				*getWater(void) const;

		bool				setMap(std::list<t_map> &);
		bool				setWater(void);

		bool				run();
		void				drawWater(float **);

	private:
		unsigned int	_width;
		unsigned int	_height;
		Map				*_map;
		Water			*_water;
		bool			rise;
		bool			south;
		bool			east;
		bool			north;
		bool			west;
		bool			rain;
		bool			evaporate;
		GLFWwindow		*_win;
		unsigned char	*_data;

		GraphicalDisplay(void);
		GraphicalDisplay(const GraphicalDisplay &);

		GraphicalDisplay	&operator=(const GraphicalDisplay &);

		void				getColor(float, float, int *, int *, int *);
		void				drawButton(int x, int y, int color);
		void				drawAllButton(void);
		bool				buttonEvent(void);

};

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

#endif
