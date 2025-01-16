#pragma once
#if !defined(MY_WINDOW_H)
#define MY_WINDOW_H

#include "my-app.h"
#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MY_TYPE_WINDOW (my_window_get_type())
G_DECLARE_FINAL_TYPE(MyWindow, my_window, MY, WINDOW, AdwApplicationWindow)

MyWindow *my_window_new(MyApp *app);

G_END_DECLS

#endif // MY_WINDOW_H
