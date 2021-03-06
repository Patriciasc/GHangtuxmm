/*
 * ########################################################################
 * # File: GHangtux - ghangtuxmm_app.cc                                   #
 * #                                                                      #
 * # Author: Patricia Santana Cruz  <patriciasc@openismus.com>            #
 * #                                                                      #
 * # Copyright (C) 2010 Openismus GmbH                                    #
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

#include "ghangtuxmm_app.h"
#include <iostream>
#include <glibmm/i18n.h>
#include "config.h"

static const int TUX_IMAGES = 7;
static const int MIN_RAND = 1;
static const int MAX_RAND = 41;


//FIX!!: Divide this code in multiple functions
GHangtuxmmApp::GHangtuxmmApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::Window(cobject),
  m_refBuilder(refBuilder),
  m_pImage(0),
  m_pDisplayLabel(0),
  m_pTitleLabel(0),
  m_pStatusbar(0),
  m_ContextStatusbar(0),
  m_GuessSentence(""),
  m_DisplaySentence(""),
  m_AssertedChars(""),
  m_GameTheme(THEME_FILMS),
  m_NImage(0)
{
    //Get the Glade-instantiated various widgets.
    m_refBuilder->get_widget("hangtux_area", m_pImage);
    m_refBuilder->get_widget("for_sentence_label", m_pDisplayLabel);
    m_refBuilder->get_widget("for_title_label", m_pTitleLabel);
    m_refBuilder->get_widget("statusbar", m_pStatusbar);

    //Create actions for menus and toolbars.
    Glib::RefPtr<Gtk::ActionGroup> refActionGroup = Gtk::ActionGroup::create();

    //Game menu.
    refActionGroup->add(Gtk::Action::create("MenuGame", _("_Game")));
    refActionGroup->add(Gtk::Action::create("MenuGameNew", Gtk::Stock::NEW, _("_New")),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    refActionGroup->add(Gtk::Action::create("MenuGameSolve", Gtk::Stock::APPLY, _("_Solve")),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_solve));
    refActionGroup->add(Gtk::Action::create("MenuGameQuit", Gtk::Stock::QUIT, _("_Quit")),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_quit));

    //Settings menu.
    refActionGroup->add(Gtk::Action::create("MenuSettings", _("_Settings")));
    refActionGroup->add(Gtk::Action::create("MenuSettingsThemes", _("_Themes")));

    Gtk::RadioAction::Group group_theme;
    m_refFilms = Gtk::RadioAction::create(group_theme, "MenuThemesFilms", _("_Films"));
    refActionGroup->add(m_refFilms,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refPersons = Gtk::RadioAction::create(group_theme, "MenuThemesPersons", _("_Persons"));
    refActionGroup->add(m_refPersons,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));
    m_refObjects = Gtk::RadioAction::create(group_theme, "MenuThemesObjects", _("_Objects"));
    refActionGroup->add(m_refObjects,
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_game_new));

    //Help menu.
    refActionGroup->add(Gtk::Action::create("MenuHelp", _("_Help")));
    refActionGroup->add(Gtk::Action::create("MenuHelpAbout", _("_About")),
      sigc::mem_fun(*this, &GHangtuxmmApp::on_action_about_dialog));

    //Create UIManager and add action group.
    Glib::RefPtr<Gtk::UIManager> refUIManager = Gtk::UIManager::create();
    refUIManager->insert_action_group(refActionGroup);

    //Make window respond to shortcuts.
    add_accel_group(refUIManager->get_accel_group());

    //UIManager layout.
    Glib::ustring ui_menu_toolbar =
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

    m_Keyboard.sig_button_clicked().connect(sigc::mem_fun(*this, &GHangtuxmmApp::check_letter_in_sentence));
    m_Keyboard.show();
    pVBoxKeyboard->pack_start(m_Keyboard, Gtk::PACK_SHRINK);
    pVBoxKeyboard->reorder_child(m_Keyboard, 3);

    //start_game()
    start_game();
}

GHangtuxmmApp::~GHangtuxmmApp()
{
}

//For each character in guessSentence, if the character is not in valid_chars,
//replaces the character with substitutor. Modifies displaySentence.
//This function reproduces the behaviour of g_strcanon.
void GHangtuxmmApp::replace_characters(Glib::ustring& guessSentence,
                                                Glib::ustring& displaySentence,
                                                const Glib::ustring& validChars,
                                                char substitutor)
{
    //Initialize the output parameter, in case the caller doesn't.
    displaySentence.clear();

    for(Glib::ustring::iterator i=guessSentence.begin(); i != guessSentence.end(); ++i)
    {
        bool is_valid_char = false;
        //Look if the guess char is a valid char.
        for(Glib::ustring::const_iterator j = validChars.begin(); j != validChars.end(); ++j)
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
            if(*i == ' ')
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

void GHangtuxmmApp::format_text_with_markup(Glib::ustring& text,
                                          FormatType type)
{
    switch(type)
    {
      case(FORMAT_TYPE_DISPLAY):  //Displayed sentence label
          text = text.compose("<span size=\"large\" font_weight=\"ultrabold\">%1</span>", text);
          break;
      case(FORMAT_TYPE_TITLE):    //Title label.
          text = text.compose("<span size=\"small\">%1</span>", text);
          break;
      default:
          g_critical("Non existent format type.");
    }
}

//Looks for a the player's given letter in the guess sentence.
//If the player does not assert, it will show the next Tux image.
void GHangtuxmmApp::check_letter_in_sentence(const Glib::ustring& label)
{
    if (m_GuessSentence.find(label) != Glib::ustring::npos)
    {
        m_AssertedChars.push_back(label[0]);
        replace_characters(m_GuessSentence, m_DisplaySentence, m_AssertedChars, '_');
        Glib::ustring formatDisplay = m_DisplaySentence;
        format_text_with_markup(formatDisplay, FORMAT_TYPE_DISPLAY);
        m_pDisplayLabel->set_markup(formatDisplay);

        if (m_DisplaySentence.compare(m_GuessSentence) == 0)
        {
            m_Winner = END_CONDITION_WON;
            end_game();
        }
    }
    else
    {
        if(m_NImage < TUX_IMAGES)
        {
            m_pImage->set(get_system_file(Glib::build_filename("images",
                "Tux" + (Glib::ustring::compose("%1", m_NImage)) + ".png")));
            ++m_NImage;
        }
        else
        {
            m_Winner = END_CONDITION_LOST;
            end_game();
        }
    }
}

//Get a random sentece to guess from the given file.
Glib::ustring GHangtuxmmApp::get_sentence_from_file(const std::string& file)
{
    Glib::ustring sentence;

    try
    {
        //Open file.
        const std::string file_path = get_system_file(Glib::build_filename("themes", file));
        Glib::RefPtr<Glib::IOChannel> iochannel = Glib::IOChannel::create_from_file(file_path, "r");

        //Read a random sentence from the file.
        Glib::Rand num;
        int n_rand = num.get_int_range(MIN_RAND, MAX_RAND);
        int i = 0;

        while(i != n_rand)
        {
            iochannel->read_line(sentence);
            ++i;
        }
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "FileError: "<< ex.what() << std::endl;
    }

    Glib::ustring::iterator end_of_line = sentence.erase(--sentence.end());
    return sentence;
}

//Set up the game.
void GHangtuxmmApp::start_game()
{
    Glib::ustring theme_file;
    Glib::ustring theme_label;

    //Set Statusbar context.
    m_ContextStatusbar = m_pStatusbar->get_context_id("GHangtuxmm Statusbar");

    //Choose the theme file.
    switch (m_GameTheme)
    {
      case THEME_FILMS:
          theme_file = "THEME_FILMS.txt";
          theme_label = _("FILM");
          m_pStatusbar->push(_("Playing theme: Films"), m_ContextStatusbar);
          break;
      case THEME_PERSONS:
          theme_file = "THEME_PERSONS.txt";
          theme_label = _("PERSON");
          m_pStatusbar->push(_("Playing theme: Persons"), m_ContextStatusbar);
          break;
      case THEME_OBJECTS:
          theme_file = "THEME_OBJECTS.txt";
          theme_label = _("OBJECT");
          m_pStatusbar->push(_("Playing theme: Objects"), m_ContextStatusbar);
          break;
      default:
          g_critical("No theme file found under the given name");
    }
    //Search for a random sentence to guess.
    m_GuessSentence = get_sentence_from_file(theme_file);

    //Initialize m_DisplaySentence and display it.
    m_DisplaySentence.clear();
    replace_characters(m_GuessSentence, m_DisplaySentence, "", '_');
    Glib::ustring formatDisplay = m_DisplaySentence;
    format_text_with_markup(formatDisplay, FORMAT_TYPE_DISPLAY);
    m_pDisplayLabel->set_markup(formatDisplay);

    //Initialize asserted characters.
    m_AssertedChars.clear();

    //Initialize the image's number.
    m_NImage = 0;

    //Display title label.
    Glib::ustring title;
    format_text_with_markup(title=(_("Guess the ") + theme_label), FORMAT_TYPE_TITLE);
    m_pTitleLabel->set_markup(title);

    //Set Keyboard to sensitive.
    m_Keyboard.set_sensitive();

    //Set inicial image.
    m_pImage->set(get_system_file(Glib::build_filename("images", "Tux0.png")));
    ++m_NImage;
}

//Finishes the game.
void GHangtuxmmApp::end_game()
{
    //Set display label.
    Glib::ustring formatDisplay = m_GuessSentence;
    format_text_with_markup(formatDisplay, FORMAT_TYPE_DISPLAY);
    m_pDisplayLabel->set_markup(formatDisplay);
    //Set title label.
    m_pTitleLabel->set_text("");
    //Set keyboard insensitive.
    m_Keyboard.set_sensitive(false);
    //Set other parameters depending on the way the game finishes.
    switch(m_Winner)
    {
      case(END_CONDITION_WON):
          m_pImage->set(get_system_file(Glib::build_filename("images", "Tux8.png")));
          m_pStatusbar->push(_("Congratulations!"), m_ContextStatusbar);
          break;
      case(END_CONDITION_LOST):
          m_pImage->set(get_system_file(Glib::build_filename("images", "Tux7.png")));
          m_pStatusbar->push(_("End of game. Try again!"), m_ContextStatusbar);
          break;
      case(END_CONDITION_SOLUTION):
          m_pImage->set(get_system_file(Glib::build_filename("images", "Tux7.png")));
          m_pStatusbar->push(_("Solution"), m_ContextStatusbar);
          break;
      default:
          g_critical("m_Winner Error");
    }
}

//Search system directories for the given filename.
std::string GHangtuxmmApp::get_system_file(const std::string& filename, FileType file)
{
    std::string pathname;
    std::string build_path;
    const gchar* const* system_data_dirs;
    std::vector<std::string> vec_system_data_dirs;

    //TODO: Use Glib::get_system_data_dirs() instead, when we can depend on glibmm 2.18.
    for(system_data_dirs = g_get_system_data_dirs(); *system_data_dirs != 0; system_data_dirs++)
    {
        vec_system_data_dirs.push_back(*system_data_dirs);
        if(file != FILE_TYPE_EXTERN)
        {
            vec_system_data_dirs.push_back(PACKAGE_NAME);
        }

        vec_system_data_dirs.push_back(filename);
        build_path = Glib::build_filename(vec_system_data_dirs);

        if(Glib::file_test(build_path, Glib::FILE_TEST_EXISTS))
        {
            pathname = build_path;
            break;
        }
    }

    return pathname;
}

//Action handlers.
//Starts a new game with the selected theme.
void GHangtuxmmApp::on_action_game_new()
{
    //Set actual theme.
    if(m_refFilms->get_active())
        m_GameTheme = THEME_FILMS;
    if(m_refPersons->get_active())
        m_GameTheme = THEME_PERSONS;
    if(m_refObjects->get_active())
        m_GameTheme = THEME_OBJECTS;

    //Start new game.
    start_game();
}

//Shows the solution for the game.
void GHangtuxmmApp::on_action_game_solve()
{
    m_Winner = END_CONDITION_SOLUTION;
    end_game();
}

//Quits the game.
void GHangtuxmmApp::on_action_game_quit()
{
    hide();
}

void GHangtuxmmApp::on_action_about_dialog()
{
    Gtk::AboutDialog aboutDialog;

    std::vector<Glib::ustring> authors;
    authors.push_back("Patricia Santana cruz");
    std::vector<Glib::ustring> artists;
    artists.push_back("Tux images Copyright Wikimedia:\n \
                      http://commons.wikimedia.org/wiki/File:Tux-G2.png. Jan Vansteenkiste.");
    aboutDialog.set_program_name(PACKAGE_NAME);
    aboutDialog.set_version(PACKAGE_VERSION);
    aboutDialog.set_copyright("Copyright (C) 2010 Openismus GmbH.");
    aboutDialog.set_comments(_("GHangtuxmm is a variation of the popular Hangman game."));
    aboutDialog.set_website("http://github.com//Patriciasc/GHantuxmm");
    aboutDialog.set_translator_credits("Patricia Santana Cruz");
    aboutDialog.set_authors(authors);
    aboutDialog.set_documenters(authors);
    aboutDialog.set_artists(artists);

    static const Glib::ustring license_text = "GHangtuxmm is free software; you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation; either version 3 of the License,\nor (at your option) any later version.\n\nGHangtuxmm  is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\nGeneral Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with GHangtuxmm. If not, see <http://www.gnu.org/licenses/>.";

    aboutDialog.set_license(license_text);

    std::vector<std::string> path_vec;
    path_vec.push_back("icons");
    path_vec.push_back("hicolor");
    path_vec.push_back("256x256");
    path_vec.push_back("apps");
    path_vec.push_back("ghangtuxmm.png");
    aboutDialog.set_logo_icon_name(get_system_file(Glib::build_filename(path_vec), FILE_TYPE_EXTERN));

    aboutDialog.run();
}
