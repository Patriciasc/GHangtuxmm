#include "ghangtuxmm_app.h"
#include <iostream>


//FIX!!: Divide this code in multiple functions
GHangtuxmmApp::GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::Window(cobject),
  m_refBuilder(refBuilder),
  m_pImage(0),
  m_pSentenceLabel(0),
  m_pTitleLabel(0),
  m_pStatusbar(0)
{
    //Get the Glade-instantiated various widgets.
    m_refBuilder->get_widget("hangtux_area", m_pImage);
    if(m_pImage)
    {
        m_pImage->set("images/Tux0.png");
    }

    m_refBuilder->get_widget("for_sentence_label", m_pSentenceLabel);
    m_refBuilder->get_widget("for_title_label", m_pTitleLabel);
    m_refBuilder->get_widget("statusbar", m_pStatusbar);
    
    //Create actions for menus and toolbars.
    Glib::RefPtr<Gtk::ActionGroup> refActionGroup = Gtk::ActionGroup::create();

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

    Gtk::RadioAction::Group group_theme;
    Glib::RefPtr<Gtk::RadioAction> m_refFilms, m_refPersons, m_refObjects;
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

    // Get menubar and toolbar widgets.
    Gtk::VBox* pVBoxMenu;
    m_refBuilder->get_widget("vbox", pVBoxMenu);

    Gtk::Widget* pMenubar = refUIManager->get_widget("/Menubar");
    if(pMenubar)
    {
        pVBoxMenu->pack_start(*pMenubar, Gtk::PACK_SHRINK);
        pVBoxMenu->reorder_child(*pMenubar, 0);
    }

    Gtk::Widget* pToolbar = refUIManager->get_widget("/Toolbar");
    if(pToolbar)
    {
        pVBoxMenu->pack_start(*pToolbar, Gtk::PACK_SHRINK);
        pVBoxMenu->reorder_child(*pToolbar, 1);
    }

    // Set keyboard.
    Gtk::VBox* pVBoxKeyboard;
    m_refBuilder->get_widget("vbox2", pVBoxKeyboard);

    m_Keyboard.sig_on_button_clicked().connect( sigc::mem_fun(*this, &GHangtuxmmApp::test));
    m_Keyboard.show();
    pVBoxKeyboard->pack_start(m_Keyboard, Gtk::PACK_SHRINK);
    pVBoxKeyboard->reorder_child(m_Keyboard, 3);
    
    //Get a random sentence to guess.
    const std::string film_file = "films.txt";
    m_GuessSentence = get_sentence_from_file(film_file);
    std::cout << "Sentence = " << m_GuessSentence << std::endl;

    //test replace_characters
    m_DisplaySentence = "";
    replace_characters(m_GuessSentence, m_DisplaySentence, "AON", '_');
    std::cout << "Display Sentence = " << m_DisplaySentence << std::endl;
}

//For each character in guessSentence, if the character is not in valid_chars,
//replaces the character with substitutor. Modifies displaySentence.
//This function reproduce the behaviour of g_strcanon.
void GHangtuxmmApp::replace_characters(Glib::ustring& guessSentence,
                                                Glib::ustring& displaySentence,
                                                const Glib::ustring& validChars,
                                                char substitutor)
{
    for(Glib::ustring::iterator i=guessSentence.begin(); i!= -- guessSentence.end(); ++i)
    {
        bool is_valid_char = false;
        //Look if the guess char is a valid char.
        for(Glib::ustring::const_iterator j=validChars.begin(); j!=validChars.end(); ++j)
        {
            if(*i == *j)
            {
                is_valid_char = true;
                break;
            }
        }
        // When guess char is valid, we show it.
        if(is_valid_char)
        {
            displaySentence.push_back(*i);
        }
        // When guess char is not valid, we substitute it
        // with the substitutor if it is not a space or 
        // end of line.
        else 
        {
            if(*i==' ')
            {
                displaySentence.push_back(' ');
            }
            else
            {
                if(i != guessSentence.end())
                { 
                    displaySentence.push_back(substitutor);
                }
            }
        }
    }
}


GHangtuxmmApp::~GHangtuxmmApp()
{
}

//Test signal handler.
void GHangtuxmmApp::test(Glib::ustring label)
{
    std::cout << "Label = " << label << std::endl;
}

//Get a random sentece to guess from the given file
Glib::ustring GHangtuxmmApp::get_sentence_from_file(const std::string& file)
{
    //FIX: Need to create a function for looking for the correct
    //path and make it work in WIN too.
    const std::string file_path = "../data/themes/" + file;
    Glib::ustring sentence;

    try
    {
        //Open file.
        Glib::RefPtr<Glib::IOChannel> iochannel = Glib::IOChannel::create_from_file(file_path,"r");
        //Read a sentence from the file. 
        //FIX: Still need to find a GOOD way to get a random number.
        Glib::Rand num;
        int n_rand = num.get_int_range(1,20);

        int i=0;
        while (i != n_rand)
        {
            iochannel->read_line(sentence);
            ++i;
        }
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "FileError: "<< ex.what() << std::endl;
    }
    return sentence;
}

//Action handlers.
void GHangtuxmmApp::on_action_game_new()
{
}

void GHangtuxmmApp::on_action_game_solve()
{
}

void GHangtuxmmApp::on_action_game_quit()
{
    hide();
}

void GHangtuxmmApp::on_action_about_dialog()
{
}
