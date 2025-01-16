#include "my-app.h"

#include "my-storage.h"
#include "my-window.h"

#include <gtk/gtk.h>

struct _MyApp {
  GtkApplication parent;

  MyStorage *storage;
};

G_DEFINE_FINAL_TYPE(MyApp, my_app, ADW_TYPE_APPLICATION)

static void my_app_activate(GApplication *app) {
  MyWindow *window = my_window_new(MY_APP(app));
  gtk_window_present(GTK_WINDOW(window));
}

static void my_app_init(MyApp *self) {
  GError *err   = NULL;
  self->storage = my_storage_new();
  if (!my_storage_init_database(self->storage, &err)) {
    g_warning("Failed to initialize database: %s", err->message);
    g_clear_error(&err);
    return;
  }
}

static void my_app_class_init(MyAppClass *klass) {
  G_APPLICATION_CLASS(klass)->activate = my_app_activate;
}

MyApp *my_app_new(void) {
  return g_object_new(MY_TYPE_APP, "application-id", "org.gtk.example", NULL);
}
