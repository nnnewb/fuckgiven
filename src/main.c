#include <gtk/gtk.h>

static void on_clicked(GtkButton *button, gpointer user_data) {
  (void)button;
  (void)user_data;

  g_print("clicked\n");
}

static void on_activate(GtkApplication *app, gpointer user_data) {
  (void)user_data;

  GError *err = NULL;
  GtkBuilder *builder;
  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "src/ui/app_window.ui", &err)) {
    g_error(err != NULL ? err->message : "no error");
    g_error_free(err);
    err = NULL;
    g_object_unref(builder);
    return;
  }

  GObject *window;
  GObject *button;

  window = gtk_builder_get_object(builder, "main_window");
  g_return_if_fail(window != NULL);

  gtk_window_set_application(GTK_WINDOW(window), app);

  button = gtk_builder_get_object(builder, "button");
  g_return_if_fail(button != NULL);

  g_signal_connect(button, "clicked", G_CALLBACK(on_clicked), NULL);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  gtk_window_present(GTK_WINDOW(window));
  g_object_unref(builder);
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("site.weakptr.demo", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
