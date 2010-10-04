/*
 * ########################################################################
 * # File: GHangtuxmm - ghangtuxmm_keyboard.h                             #
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

#ifndef GHANGTUXMM_KEYBOARD_H__
#define GHANGTUXMM_KEYBOARD_H__

#include <gtkmm.h>

class GHangtuxmmKeyboard : public Gtk::Table
{
public:
    GHangtuxmmKeyboard();
    ~GHangtuxmmKeyboard();
    void set_sensitive(bool sensitive);

    //Signal accessor for the only keyboard's signal.
    typedef sigc::signal<void, const Glib::ustring> T_signal_clicked;
    T_signal_clicked sig_on_button_clicked();

private:
    void on_button_clicked(Gtk::Button* button);
    void on_set_sensitive(Gtk::Widget& button, const bool& sensitive);

    T_signal_clicked m_on_button_clicked;
};

#endif /* GHANGTUXMM_KEYBOARD_H__ */
