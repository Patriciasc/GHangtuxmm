#include "ghangtuxmm_app.h"
#include <iostream>

//Constructor
//FIX!!: Divide this code in multiple functions
GHangtuxmmApp::GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::Window(cobject),
  m_refBuilder(refBuilder),
  m_pImage(0),
  m_pSentenceLabel(0),
  m_pTitleLabel(0),
  m_pStatusbar(0)
{
    //Get the Glade-instantiated Image
    m_refBuilder->get_widget("hangtux_area", m_pImage);
    if(m_pImage)
    {
        m_pImage->set("images/Tux0.png");
    }

    //Get the Glade-instantiated label for the game's sentence
    m_refBuilder->get_widget("for_sentence_label", m_pSentenceLabel);

    //Get the Glade-instantiated label for the game's title
    m_refBuilder->get_widget("for_title_label", m_pTitleLabel);

    //Get the Glade-instantiated status bar
    m_refBuilder->get_widget("statusbar", m_pStatusbar);
    
    //Create actions for menus and toolbars.
    Glib::RefPtr<Gtk::ActionGroup> refActionGroup = Gtk::ActionGroup::create();
    Gtk::RadioAction::Group group_theme;
    Glib::RefPtr<Gtk::RadioAction> m_refFilms, m_refPersons, m_refObjects;

    //Game menu.
    refActionGroup->add( Gtk::Action::create("MenuGame", "_Game"));
    refActionGroup->add( Gtk::Action::create("MenuGameNew",Gtk::Stock::NEW, "_New"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    refActionGroup->add( Gtk::Action::create("MenuGameSolve", Gtk::Stock::APPLY, "_Solve"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_solve));
    refActionGroup->add( Gtk::Action::create("MenuGameQuit", Gtk::Stock::QUIT, "_Quit"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_quit));

    //Settings menu.
    refActionGroup->add( Gtk::Action::create("MenuSettings", "_Settings"));
    refActionGroup->add( Gtk::Action::create("MenuSettingsThemes", "_Themes"));
    m_refFilms = Gtk::RadioAction::create(group_theme, "MenuThemesFilms", "_Films");
    refActionGroup->add(m_refFilms,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refPersons = Gtk::RadioAction::create(group_theme, "MenuThemesPersons", "_Persons");
    refActionGroup->add(m_refPersons,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refObjects = Gtk::RadioAction::create(group_theme, "MenuThemesObjects", "_Objects");
    refActionGroup->add(m_refObjects,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));

    //Help menu.
    refActionGroup->add( Gtk::Action::create("MenuHelp", "_Help"));
    refActionGroup->add( Gtk::Action::create("MenuHelpAbout", "_About"),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_about_dialog));

    //Create UIManager and add action group.
    Glib::RefPtr<Gtk::UIManager> refUIManager = Gtk::UIManager::create();
    refUIManager->insert_action_group(refActionGroup);

    //Make window respond to shortcuts.
    add_accel_group(refUIManager->get_accel_group());

    //UIManager layout.
    Glib::ustring ui_menu_toolbar=
        "<ui>"
        "   <menubar name='Menubar'>"
        "       <menu action='MenuGame'>"
        "           <menuitem action='MenuGameNew'/>"
        "           <menuitem action='MenuGameSolve'/>"
        "           <separator/>"
        "           <menuitem action='MenuGameQuit'/>"
        "       </menu>"
        "       <menu action='MenuSettings'>"
        "           <menu action='MenuSettingsThemes'>"
        "               <menuitem action='MenuThemesFilms'/>"
        "               <menuitem action='MenuThemesPersons'/>"
        "               <menuitem action='MenuThemesObjects'/>"
        "           </menu>"
        "       </menu>"
        "       <menu action='MenuHelp'>"
        "           <menuitem action='MenuHelpAbout'/>"
        "       </menu>"
        "   </menubar>"
        "   <toolbar name='Toolbar'>"
        "       <toolitem action='MenuGameNew'/>"
        "       <toolitem action='MenuGameSolve'/>"
        "       <toolitem action='MenuGameQuit'/>"
        "   </toolbar>"
        "</ui>";

    try
    {
        refUIManager->add_ui_from_string(ui_menu_toolbar);
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "Building menu or toolbar failed: " << ex.what();
    }

    // Get menubar and toolbar widgets
    Gtk::VBox *VBoxMenu;
    m_refBuilder->get_widget("vbox", VBoxMenu);

    Gtk::Widget* pMenubar = refUIManager->get_widget("/Menubar");
    if(pMenubar)
    {
        VBoxMenu->pack_start(*pMenubar, Gtk::PACK_SHRINK);
        VBoxMenu->reorder_child(*pMenubar, 0);
    }

    Gtk::Widget* pToolbar = refUIManager->get_widget("/Toolbar");
    if(pToolbar)
    {
        VBoxMenu->pack_start(*pToolbar, Gtk::PACK_SHRINK);
        VBoxMenu->reorder_child(*pToolbar, 1);
    }
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
