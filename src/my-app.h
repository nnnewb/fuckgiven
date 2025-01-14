#pragma once
#if !defined(MY_APP_H)
#define MY_APP_H

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MY_TYPE_APP (my_app_get_type())
G_DECLARE_FINAL_TYPE(MyApp, my_app, MY, APP, AdwApplication)

MyApp* my_app_new(void);

G_END_DECLS

#endif // MY_APP_H
