/*
 * ########################################################################
 * # File: GHangtuxmm - ghangtuxmm.cc                                     #
 * #                                                                      #
 * # Author: Patricia Santana Cruz  <patriciasc@openismus.com>            #
 * #                                                                      #
 * # Copyright (C) 2010 Openismus GmbH                                    #
 * #                                                                      #
 * # Version: 0.1                                                         #
 * #                                                                      #
 * # Description: A variation of the Hangman game.                        #
 * #                                                                      #
 * # GHangtuxmm is free software; you can redistribute it and/or modify   #
 * # it under the terms of the GNU General Public License as published by #
 * # the Free Software Foundation; either version 3 of the License,       #
 * # or (at your option) any later version.                               #
 * #                                                                      #
 * # GHangtuxmm is distributed in the hope that it will be useful,        #
 * # but WITHOUT ANY WARRANTY; without even the implied warranty of       #
 * # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    #
 * # General Public License for more details.                             #
 * #                                                                      #
 * # You should have received a copy of the GNU General Public License    #
 * # along with GHangtuxmm. If not, see <http://www.gnu.org/licenses/>.   #
 * ########################################################################
 */

#include "ghangtuxmm.h"
#include "ghangtuxmm_derived_window.h"
#include <gtkmm.h>
#include <iostream>

GHangtuxApp::GHangtuxApp()
{
    //Load the Glade file and instiate its widgets
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create(); 
    try
    {
        refBuilder->add_from_file("ghangtux.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    //Get the GtkBuilder-instantiated main window
    //Still need to make this window the one that is shown
    //when executing the programm
    DerivedWindow* pWindow = 0;
    refBuilder->get_widget_derived("main_window", pWindow);
}

GHangtuxApp::~GHangtuxApp()
{
}
