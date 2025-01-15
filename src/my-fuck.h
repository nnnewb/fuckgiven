#pragma once
#ifndef MY_FUCK_H
#define MY_FUCK_H

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MY_TYPE_FUCK (my_fuck_get_type())

G_DECLARE_FINAL_TYPE(MyFuck, my_fuck, MY, FUCK, AdwActionRow)

MyFuck* my_fuck_new(void);

G_END_DECLS

#endif // MY_FUCK_H
