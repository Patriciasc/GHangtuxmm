#ifndef GHANGTUXMM_DERIVED_WINDOW_H
#define GHANGTUXMM_DERIVED_WINDOW_H

#include <gtkmm.h>

class GHangtuxmmApp : public Gtk::Window
{
public:
    GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    ~GHangtuxmmApp();

private:
    //Action handlers
    void on_action_game_new();
    void on_action_game_solve();
    void on_action_game_quit();
    void on_action_about_dialog();

    Glib::RefPtr<Gtk::Builder> m_pBuilder;
    Gtk::Image* m_pImage;
    Gtk::Label* m_pSentenceLabel;
    Gtk::Label* m_pTitleLabel;
    Gtk::Statusbar* m_pStatusbar;
};

#endif //GHANGTUXMM_DERIVED_WINDOW_H
