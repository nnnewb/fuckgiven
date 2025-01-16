#include "my-window.h"
#include "my-app.h"
#include "my-fuck.h"

#include <gtk/gtk.h>

struct _MyWindow {
  GtkApplicationWindow parent;
  GtkListBox          *list_box;
};

G_DEFINE_FINAL_TYPE(MyWindow, my_window, ADW_TYPE_APPLICATION_WINDOW)

static void my_window_class_init(MyWindowClass *klass) {
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/site/weakptr/fucksgiven/src/my-window.ui");
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), MyWindow, list_box);
}

static void my_window_init(MyWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));

  g_return_if_fail(self->list_box != NULL);

  MyFuck *row = my_fuck_new();
  gtk_list_box_append(self->list_box, GTK_WIDGET(row));
}

MyWindow *my_window_new(MyApp *app) {
  return g_object_new(MY_TYPE_WINDOW, "application", app, NULL);
}
