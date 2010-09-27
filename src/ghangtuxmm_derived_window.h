#ifndef GHANGTUXMM_DERIVED_WINDOW_H
#define GHANGTUXMM_DERIVED_WINDOW_H

#include <gtkmm.h>

class DerivedWindow : public Gtk::Window
{
public:
    DerivedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    ~DerivedWindow();

private:

    Glib::RefPtr<Gtk::Builder> m_refGlade;
    Gtk::Image* m_pImage;
};

#endif //GHANGTUXMM_DERIVED_WINDOW_H
