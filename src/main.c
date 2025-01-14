#include <gtk/gtk.h>

static void on_clicked(GtkButton *button, gpointer user_data) {
  (void)button;
  (void)user_data;

  g_print("clicked\n");
}

static void on_activate(GtkApplication *app, gpointer user_data) {
  (void)user_data;

  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *vbox, *hbox;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "hello");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

  button = gtk_button_new_with_label("Hello, World!");
  g_signal_connect(button, "clicked", G_CALLBACK(on_clicked), NULL);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_append(GTK_BOX(hbox), gtk_label_new("horizontal label 1"));
  gtk_box_append(GTK_BOX(hbox), gtk_label_new("horizontal label 2"));
  gtk_box_set_homogeneous(GTK_BOX(hbox), TRUE);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(vbox), button);
  gtk_box_append(GTK_BOX(vbox), hbox);


  gtk_window_set_child(GTK_WINDOW(window), vbox);
  gtk_window_present(GTK_WINDOW(window));
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
