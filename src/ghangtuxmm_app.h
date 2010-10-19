/*
 * ########################################################################
 * # File: GHangtux - ghangtuxmm_app.h                                    #
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
 * # GHangtuxmm  is distributed in the hope that it will be useful,       #
 * # but WITHOUT ANY WARRANTY; without even the implied warranty of       #
 * # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    #
 * # General Public License for more details.                             #
 * #                                                                      #
 * # You should have received a copy of the GNU General Public License    #
 * # along with GHangtuxmm. If not, see <http://www.gnu.org/licenses/>.   #
 * ########################################################################
 */
#ifndef GHANGTUXMM_APP_H
#define GHANGTUXMM_APP_H

#include <gtkmm.h>
#include "ghangtuxmm_keyboard.h"

class GHangtuxmmApp : public Gtk::Window
{
public:

    enum GameTheme
    {
        THEME_FILMS,
        THEME_PERSONS,
        THEME_OBJECTS
    };

    enum EndCondition
    {
        END_CONDITION_WON,     /*Player won*/
        END_CONDITION_LOST,    /*Player lost*/
        END_CONDITION_SOLUTION /*Player asked for the solution*/
    };

    enum FormatType
    {
        FORMAT_TYPE_DISPLAY,
        FORMAT_TYPE_TITLE
    };

    enum FileType
    {
        FILE_TYPE_PACKAGE,
        FILE_TYPE_EXTERN
    };

    GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    ~GHangtuxmmApp();
    static std::string get_system_file(const Glib::ustring& filename, FileType=FILE_TYPE_PACKAGE);


private:
    //Action handlers
    void on_action_game_new();
    void on_action_game_solve();
    void on_action_game_quit();
    void on_action_about_dialog();

    void format_text_with_markup(Glib::ustring& text, FormatType type);
    void check_letter_in_sentence( const Glib::ustring& label);
    void replace_characters(Glib::ustring& guessSentence, Glib::ustring& displaySentence, const Glib::ustring& valid_chars, char substitutor);
    Glib::ustring get_sentence_from_file( const std::string &file);
    void start_game();
    void end_game();

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::Image* m_pImage;
    Gtk::Label* m_pDisplayLabel;
    Gtk::Label* m_pTitleLabel;
    GHangtuxmmKeyboard m_Keyboard;
    Gtk::Statusbar* m_pStatusbar;
    guint m_ContextStatusbar;
    Glib::ustring m_GuessSentence;
    Glib::ustring m_DisplaySentence;
    Glib::ustring m_AssertedChars;
    GameTheme m_GameTheme;
    EndCondition m_Winner;
    int m_NImage;
    Glib::RefPtr<Gtk::RadioAction> m_refFilms;
    Glib::RefPtr<Gtk::RadioAction> m_refPersons;
    Glib::RefPtr<Gtk::RadioAction> m_refObjects;
};

#endif //GHANGTUXMM_APP_H
