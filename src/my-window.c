#include "my-window.h"
#include "my-app.h"
#include <gtk/gtk.h>

struct _MyWindow {
  GtkApplicationWindow parent;
};

G_DEFINE_FINAL_TYPE(MyWindow, my_window, ADW_TYPE_APPLICATION_WINDOW)

static void my_window_class_init(MyWindowClass *klass) {
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/site/weakptr/fucksgiven/src/my-window.ui");
}

static void my_window_init(MyWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}

MyWindow *my_window_new(MyApp *app) {
  return g_object_new(MY_TYPE_WINDOW, "application", app, NULL);
}
