#include "my-fuck.h"

struct _MyFuck {
  AdwActionRow parent;
};

G_DEFINE_FINAL_TYPE(MyFuck, my_fuck, ADW_ACTION_ROW)

static void my_fuck_init(MyFuck *self) {}

static void my_fuck_class_init(MyFuckClass *klass) {}

MyFuck *my_fuck_new(void) {
  return g_object_new(MY_TYPE_FUCK, NULL);
}
