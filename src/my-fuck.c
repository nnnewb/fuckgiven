#include "my-fuck.h"

struct _MyFuck {
  AdwActionRow parent;
};

G_DEFINE_FINAL_TYPE(MyFuck, my_fuck, ADW_TYPE_ACTION_ROW)

static void my_fuck_class_init(MyFuckClass *klass) {
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/site/weakptr/fucksgiven/src/my-fuck.ui");
}

static void my_fuck_init(MyFuck *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}

MyFuck *my_fuck_new(void) {
  return g_object_new(MY_TYPE_FUCK, NULL);
}
