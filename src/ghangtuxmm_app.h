#ifndef GHANGTUXMM_DERIVED_WINDOW_H
#define GHANGTUXMM_DERIVED_WINDOW_H

#include <gtkmm.h>
#include "ghangtuxmm_keyboard.h"

class GHangtuxmmApp : public Gtk::Window
{
public:
    GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    ~GHangtuxmmApp();
    void check_letter_in_sentence( Glib::ustring label);
    void replace_characters(Glib::ustring& guessSentence, Glib::ustring& displaySentence, const Glib::ustring& valid_chars, char substitutor);
    Glib::ustring get_sentence_from_file( const std::string &file);
    void start_game();
    void end_game();
    std::string get_system_file(const Glib::ustring& filename);

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

private:
    //Action handlers
    void on_action_game_new();
    void on_action_game_solve();
    void on_action_game_quit();
    void on_action_about_dialog();

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::Image* m_pImage;
    Gtk::Label* m_pDisplayLabel;
    Gtk::Label* m_pTitleLabel;
    GHangtuxmmKeyboard m_Keyboard;
    Gtk::Statusbar* m_pStatusbar;
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

#endif //GHANGTUXMM_DERIVED_WINDOW_H
