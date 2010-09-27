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

//TODO: This class needs to be divided in sub-functions
//      This class will probably be disolved and I will 
//      just work with derived window

GHangtuxApp::GHangtuxApp()
{
    //Load the Glade file and instiate its widgets.
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create(); 
    try
    {
        refBuilder->add_from_file("ui/ghangtuxmm.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    //Get the GtkBuilder-instantiated main window.
    DerivedWindow* pWindow = 0;
    refBuilder->get_widget_derived("main_window", pWindow);
    pWindow->show();

    //Create actions for menus and toolbars.
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup = Gtk::ActionGroup::create();
    Gtk::RadioAction::Group group_theme;
    Glib::RefPtr<Gtk::RadioAction> m_refFilms, m_refPersons, m_refObjects;

    //Game menu.
    m_refActionGroup->add( Gtk::Action::create("MenuGame", "_Game"));
    m_refActionGroup->add( Gtk::Action::create("MenuGameNew", "_New"),
      sigc::mem_fun(*this, &GHangtuxApp::on_action_game_new));
    m_refActionGroup->add( Gtk::Action::create("MenuGameSolve", "_Solve"),
      sigc::mem_fun(*this, &GHangtuxApp::on_action_game_solve));
    m_refActionGroup->add( Gtk::Action::create("MenuGameQuit", "_Quit"),
      sigc::mem_fun(*this, &GHangtuxApp::on_action_game_quit));

    //Settings menu.
    m_refActionGroup->add( Gtk::Action::create("MenuSettings", "_Settings"));
    m_refActionGroup->add( Gtk::Action::create("MenuSettingsThemes", "_Themes"));
    m_refFilms = Gtk::RadioAction::create(group_theme, "MenuThemesFilm", "_Films");
    m_refActionGroup->add(m_refFilms,
      sigc::mem_fun(*this, &GHangtuxApp::on_action_game_new));
    m_refPersons = Gtk::RadioAction::create(group_theme, "MenuThemesPersons", "_Persons");
    m_refActionGroup->add(m_refPersons,
      sigc::mem_fun(*this, &GHangtuxApp::on_action_game_new));
    m_refObjects = Gtk::RadioAction::create(group_theme, "MenuThemesObjects", "_Objects");
    m_refActionGroup->add(m_refObjects,
      sigc::mem_fun(*this, &GHangtuxApp::on_action_game_new));

    //Help menu.
    m_refActionGroup->add( Gtk::Action::create("MenuHelp", "_About"),
      sigc::mem_fun(*this, &GHangtuxApp::on_action_about_dialog));

    //Create UIManager, add actions.
    Glib::RefPtr<Gtk::UIManager> m_refUIManager = Gtk::UIManager::create();
    m_refUIManager->insert_action_group(m_refActionGroup);

    pWindow->add_accel_group(m_refUIManager->get_accel_group());

    //TODO: Layout menubar and toolbar here
}

GHangtuxApp::~GHangtuxApp()
{
}

//Action handlers
void GHangtuxApp::on_action_game_new()
{
}

void GHangtuxApp::on_action_game_solve()
{
}

void GHangtuxApp::on_action_game_quit()
{
}

void GHangtuxApp::on_action_about_dialog()
{
}
