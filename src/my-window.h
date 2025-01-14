#pragma once
#if !defined(MY_WINDOW_H)
#define MY_WINDOW_H

#include <gtk/gtk.h>
#include "my-app.h"

G_BEGIN_DECLS

#define MY_WINDOW_TYPE (my_window_get_type())
G_DECLARE_FINAL_TYPE(MyWindow, my_window, MY, WINDOW, GtkApplicationWindow)

MyWindow* my_window_new(MyApp* app);

G_END_DECLS

#endif // MY_WINDOW_H
