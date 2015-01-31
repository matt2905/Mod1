/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 11:56:04 by mmartin           #+#    #+#             */
/*   Updated: 2015/01/31 12:23:39 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <gtkmm/window.h>

int		display(int &argc, char **&argv, std::list<t_map>)
{
	argc = 1;
	Glib::RefPtr<Gtk::Application>	app = Gtk::Application::create(argc, argv, "Mod 1");
	Gtk::Window						win;

	return (app->run(win));
}
