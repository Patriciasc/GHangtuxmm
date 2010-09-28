#include "ghangtuxmm_app.h"
//#include <iostream>

//Constructor
//FIX: Divide this code in multiple functions
GHangtuxmmApp::GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject),
  m_pBuilder(builder),
  m_pImage(0),
  m_pSentenceLabel(0),
  m_pTitleLabel(0),
  m_pStatusbar(0)
{
    //Get the Glade-instantiated Image
    m_pBuilder->get_widget("hangtux_area", m_pImage);
    if(m_pImage)
    {
        m_pImage->set("images/Tux0.png");
    }

    //this->show();

    //Get the Glade-instantiated label for the game's sentence
    m_pBuilder->get_widget("for_sentence_label", m_pSentenceLabel);

    //Get the Glade-instantiated label for the game's title
    m_pBuilder->get_widget("for_title_label", m_pTitleLabel);

    //Get the Glade-instantiated status bar
    m_pBuilder->get_widget("statusbar", m_pStatusbar);
    
    //Create actions for menus and toolbars.
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup = Gtk::ActionGroup::create();
    Gtk::RadioAction::Group group_theme;
    Glib::RefPtr<Gtk::RadioAction> m_refFilms, m_refPersons, m_refObjects;

    //Game menu.
    m_refActionGroup->add( Gtk::Action::create("MenuGame", "_Game"));
    m_refActionGroup->add( Gtk::Action::create("MenuGameNew", "_New"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refActionGroup->add( Gtk::Action::create("MenuGameSolve", "_Solve"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_solve));
    m_refActionGroup->add( Gtk::Action::create("MenuGameQuit", "_Quit"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_quit));

    //Settings menu.
    m_refActionGroup->add( Gtk::Action::create("MenuSettings", "_Settings"));
    m_refActionGroup->add( Gtk::Action::create("MenuSettingsThemes", "_Themes"));
    m_refFilms = Gtk::RadioAction::create(group_theme, "MenuThemesFilm", "_Films");
    m_refActionGroup->add(m_refFilms,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refPersons = Gtk::RadioAction::create(group_theme, "MenuThemesPersons", "_Persons");
    m_refActionGroup->add(m_refPersons,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refObjects = Gtk::RadioAction::create(group_theme, "MenuThemesObjects", "_Objects");
    m_refActionGroup->add(m_refObjects,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));

    //Help menu.
    m_refActionGroup->add( Gtk::Action::create("MenuHelp", "_About"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_about_dialog));

    //Create UIManager, add actions.
    Glib::RefPtr<Gtk::UIManager> m_refUIManager = Gtk::UIManager::create();
    m_refUIManager->insert_action_group(m_refActionGroup);

    //pWindow->add_accel_group(m_refUIManager->get_accel_group());

    //TODO: Layout menubar and toolbar here
}

//Destructor
GHangtuxmmApp::~GHangtuxmmApp()
{
}

//Action handlers
void GHangtuxmmApp::on_action_game_new()
{
}

void GHangtuxmmApp::on_action_game_solve()
{
}

void GHangtuxmmApp::on_action_game_quit()
{
}

void GHangtuxmmApp::on_action_about_dialog()
{
}
