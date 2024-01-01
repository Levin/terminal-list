#include <stdio.h>

int callback(void *data, int argc, char **argv, char **azColName) {
  int *count = (int *)data;
  *count = atoi(argv[0]);

  return 0;
}

int get_streak() 
{
  sqlite3 *db;
  if (sqlite3_open("/home/levin/dbs/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char sql[50];
  int streak = 0;
  snprintf(sql, sizeof(sql), "SELECT * FROM streak;");

  sqlite3_exec(db, sql, callback, &streak, NULL);
  sqlite3_close(db);
  return streak;
}

void increment_streak()
{

  sqlite3 *db;
  if (sqlite3_open("/home/levin/dbs/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char sql[50];
  snprintf(sql, sizeof(sql), "UPDATE streak SET day = day + 1;");

  sqlite3_exec(db, sql, NULL, NULL, NULL);
  sqlite3_close(db);
}

void reset_streak()
{

  sqlite3 *db;
  if (sqlite3_open("/home/levin/dbs/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char sql[50];
  snprintf(sql, sizeof(sql), "UPDATE streak SET day = 1;");

  sqlite3_exec(db, sql, NULL, NULL, NULL);
  sqlite3_close(db);
}
