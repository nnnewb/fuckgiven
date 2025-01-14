#include "my-window.h"
#include "my-app.h"
#include <gtk/gtk.h>

struct _MyWindow {
  GtkApplicationWindow parent;
};

G_DEFINE_FINAL_TYPE(MyWindow, my_window, GTK_TYPE_APPLICATION_WINDOW)

static void on_button_click(GtkEntry *entry, MyWindow *self) {
  g_print("clicked\n");
  gtk_window_destroy(GTK_WINDOW(self));
}

static void my_window_class_init(MyWindowClass *klass) {
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/site/weakptr/fucksgiven/my-window.ui");
  gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(klass), on_button_click);
}

static void my_window_init(MyWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}

MyWindow *my_window_new(MyApp *app) {
  return g_object_new(MY_TYPE_WINDOW, "application", app, NULL);
}
