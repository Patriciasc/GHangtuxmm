#include "ghangtuxmm_derived_window.h"

DerivedWindow::DerivedWindow(BaseObjectType* cobject,
                             const Glib::RefPtr<Gtk::Builder>& refGlade)
:Gtk::Window(cobject),
 m_refGlade(refGlade)
{
    //Get the Glade-instantiated Image
    m_refGlade->get_widget("hangtux_area", m_pImage);
    if(m_pImage)
    {
        m_pImage->set("images/Tux0.png");
    }

    //Get the Glade-instantiated label for the game's sentence
    m_refGlade->get_widget("for_sentence_label", m_pSentenceLabel);

    //Get the Glade-instantiated label for the game's title
    m_refGlade->get_widget("for_title_label", m_pTitleLabel);

    //Get the Glade-instantiated status bar
    m_refGlade->get_widget("statusbar", m_pStatusbar);
}

DerivedWindow::~DerivedWindow()
{
}
