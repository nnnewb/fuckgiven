#pragma once
#ifndef MY_STORAGE_H
#define MY_STORAGE_H
#include "gtk/gtk.h"

G_BEGIN_DECLS

#define MY_STORAGE_ERROR (my_storage_error_quark())

GQuark my_storage_error_quark(void);

enum MyStorageError {
  MY_STORAGE_ERROR_OK      = 0,
  MY_STORAGE_ERROR_SQLITE3 = 1,
  MY_STORAGE_ERROR_FAILED  = G_MAXINT32,
};

#define MY_TYPE_STORAGE (my_storage_get_type())
G_DECLARE_FINAL_TYPE(MyStorage, my_storage, MY, STORAGE, GObject)

MyStorage *my_storage_new(void);

/**
 * open database.
 *
 * @param self instance
 * @param err exception pointer
 * @return TRUE if success
 */
gboolean my_storage_init_database(MyStorage *self, GError **err);

/**
 * Do give a fuck to something. write it to database.
 * You must open database first. see my_storage_open_database.
 *
 *
 * @param self instance
 * @param message user input message
 * @param err exception pointer
 * @return TRUE if success
 */
gboolean my_storage_add_record(MyStorage *self, const gchar *message, GError **err);

G_END_DECLS

#endif // MY_STORAGE_H
