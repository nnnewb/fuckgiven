#include "my-app.h"
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
  MyApp *app    = my_app_new();
  int    status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
