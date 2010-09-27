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
        m_pImage->set("Tux0.png");
        m_pImage->show();
    }
}

DerivedWindow::~DerivedWindow()
{
}
