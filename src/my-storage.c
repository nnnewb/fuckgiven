#include "my-storage.h"
#include "sqlite3.h"

#define FUCK_TBL_NAME "records"

// clang-format off
G_DEFINE_QUARK(my-storage-error-quark, my_storage_error)
// clang-format on

#define MY_SQLITE3_ERRMSG(conn, err)                                                             \
  do {                                                                                           \
    const char *errmsg = sqlite3_errmsg((conn));                                                 \
    g_warning("SQLite3 error: %s", errmsg);                                                      \
    g_clear_error((err));                                                                        \
    g_set_error((err), MY_STORAGE_ERROR, MY_STORAGE_ERROR_SQLITE3, "SQLite3 error: %s", errmsg); \
  } while (0)

#define MY_SQLITE3_ERRSTR(code, err)                                                             \
  do {                                                                                           \
    const char *errmsg = sqlite3_errstr((code));                                                 \
    g_warning("SQLite3 error: %s", errmsg);                                                      \
    g_clear_error((err));                                                                        \
    g_set_error((err), MY_STORAGE_ERROR, MY_STORAGE_ERROR_SQLITE3, "SQLite3 error: %s", errmsg); \
  } while (0)

struct _MyStorage {
  GObject *parent;

  GMutex   mutex; // protect the sqlite connection
  sqlite3 *conn;
};

G_DEFINE_FINAL_TYPE(MyStorage, my_storage, G_TYPE_OBJECT)

static void my_storage_class_init(MyStorageClass *klass) {
  (void)klass;
}

static void my_storage_init(MyStorage *self) {
  g_mutex_init(&self->mutex);
}

MyStorage *my_storage_new(void) {
  return MY_STORAGE(g_object_new(MY_TYPE_STORAGE, NULL));
}

static gboolean my_storage_table_exists(const MyStorage *self, gboolean *result, GError **err) {
  g_debug("check table " FUCK_TBL_NAME " exists");

  // prepare statement
  sqlite3_stmt *stmt  = NULL;
  const char   *query = "SELECT COUNT(*) FROM sqlite_master WHERE tbl_name='" FUCK_TBL_NAME "'";
  int           code  = sqlite3_prepare_v2(self->conn, query, -1, &stmt, NULL);
  if (code != SQLITE_OK) {
    MY_SQLITE3_ERRMSG(self->conn, err);
    return FALSE;
  }

  // execute
  code = sqlite3_step(stmt);
  if (code != SQLITE_ROW) {
    MY_SQLITE3_ERRSTR(code, err);
    return FALSE;
  }

  // get result
  const int count = sqlite3_column_int(stmt, 0);
  if (count > 0) {
    *result = TRUE;
  }

  // finalize statement
  code = sqlite3_finalize(stmt);
  if (code != SQLITE_OK) {
    MY_SQLITE3_ERRMSG(self->conn, err);
    return FALSE;
  }
  stmt = NULL;
  return TRUE;
}

static gboolean my_storage_create_table(const MyStorage *self, GError **err) {
  g_debug("create table: " FUCK_TBL_NAME);

  // prepare statement
  const char *query = "CREATE TABLE " FUCK_TBL_NAME "(id INTEGER, message TEXT);";
  const int   code  = sqlite3_exec(self->conn, query, NULL, NULL, NULL);
  if (code != SQLITE_OK) {
    MY_SQLITE3_ERRMSG(self->conn, err);
    return FALSE;
  }

  return TRUE;
}

static gboolean my_storage_open_db(MyStorage *self, const char *dsn, GError **err) {
  g_debug("open database: %s", dsn);

  const int code = sqlite3_open(dsn, &self->conn);
  if (code != SQLITE_OK) {
    MY_SQLITE3_ERRMSG(self->conn, err);
    g_mutex_unlock(&self->mutex);
    return FALSE;
  }
  return TRUE;
}

gboolean my_storage_init_database(MyStorage *self, GError **err) {
  g_mutex_lock(&self->mutex);

  // close already opened database
  if (self->conn != NULL) {
    const int code = sqlite3_close_v2(self->conn);
    if (code != SQLITE_OK) {
      MY_SQLITE3_ERRMSG(self->conn, err);
      g_mutex_unlock(&self->mutex);
      return FALSE;
    }

    self->conn = NULL;
  }

  // open sqlite db
  if (!my_storage_open_db(self, ":memory:", err)) {
    g_mutex_unlock(&self->mutex);
    return FALSE;
  }

  // check table exists
  gboolean exists = FALSE;
  if (!my_storage_table_exists(self, &exists, err)) {
    g_mutex_unlock(&self->mutex);
    return FALSE;
  }

  if (exists) {
    g_mutex_unlock(&self->mutex);
    return TRUE;
  }

  // create table
  if (!my_storage_create_table(self, err)) {
    g_mutex_unlock(&self->mutex);
    return FALSE;
  }

  g_mutex_unlock(&self->mutex);
  return TRUE;
}

gboolean my_storage_add_record(MyStorage *self, const gchar *message, GError **err) {
  g_mutex_lock(&self->mutex);

  (void)message;
  g_set_error(err, MY_STORAGE_ERROR, MY_STORAGE_ERROR_FAILED, "not implemented");

  g_mutex_unlock(&self->mutex);
  return TRUE;
}
