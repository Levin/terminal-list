#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "streaks.h"


void printColumnValue(sqlite3_stmt* stmt, int col) {
  int colType = sqlite3_column_type(stmt, col);
  switch(colType) {
    case SQLITE_TEXT:
      printf("\t\t\t~> %s", sqlite3_column_text(stmt, col));
      break;
    default: 
      printf("\t\t\t~> %u", sqlite3_column_text(stmt, col));
  }
}

void printColumnValueList(sqlite3_stmt* stmt, int col) {
  int colType = sqlite3_column_type(stmt, col);
  switch(colType) {
    case SQLITE_TEXT:
      printf("\t~> %s", sqlite3_column_text(stmt, col));
      break;
    default: 
      printf("\t\t\t~> %u", sqlite3_column_int(stmt, col));
  }
}

int get_done()
{
  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  int done_tasks = 0;

  sqlite3_exec(db, "SELECT COUNT(*) FROM done;", callback, &done_tasks, NULL);
  sqlite3_close(db);
  return done_tasks;
}


void list_offlist()
{
  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "select * from offlist;", -1, &stmt, NULL)) {
    printf("Error executing sql statement\n");
    sqlite3_close(db);
    exit(-1);
  }

  sqlite3_bind_int (stmt, 1, 2);
  while (sqlite3_step(stmt) != SQLITE_DONE) {
    for (int col=0; col<=1; col++) {
      printColumnValueList(stmt, col);
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

}
void offset_task(int *task)
{
  printf("\n\n");
  printf("\tFree Tasks: \n\n");

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char move_from_tasks[100];
  snprintf(move_from_tasks, sizeof(move_from_tasks), "insert into offlist select * from tasks where rowid == '%u';", task);
  sqlite3_exec(db, move_from_tasks, NULL, NULL, NULL);

  char move_from_backlog[100];
  snprintf(move_from_backlog, sizeof(move_from_backlog), "insert into offlist select * from backlog where rowid == '%u';", task);
  sqlite3_exec(db, move_from_backlog, NULL, NULL, NULL);


  char from_tasks[100];
  snprintf(from_tasks, sizeof(from_tasks), "delete from tasks where rowid == '%u';", task);
  sqlite3_exec(db, from_tasks, NULL, NULL, NULL);

  char from_backlog[100];
  snprintf(from_backlog, sizeof(from_backlog), "delete from backlog where rowid == '%u';", task);
  sqlite3_exec(db, from_backlog, NULL, NULL, NULL);
  sqlite3_close(db);
}

void done_task(int* task){

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char move_from_tasks[100];
  snprintf(move_from_tasks, sizeof(move_from_tasks), "insert into done select * from tasks where rowid == '%u';", task);
  sqlite3_exec(db, move_from_tasks, NULL, NULL, NULL);

  char from_tasks[100];
  snprintf(from_tasks, sizeof(from_tasks), "delete from tasks where rowid == '%u';", task);
  sqlite3_exec(db, from_tasks, NULL, NULL, NULL);

}

void done_backlog(int* task){

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char move_from_backlog[100];
  snprintf(move_from_backlog, sizeof(move_from_backlog), "insert into done select * from backlog where rowid == '%u';", *task);
  sqlite3_exec(db, move_from_backlog, NULL, NULL, NULL);

  char from_backlog[100];
  snprintf(from_backlog, sizeof(from_backlog), "delete from backlog where rowid == '%u';", *task);
  sqlite3_exec(db, from_backlog, NULL, NULL, NULL);

}

void delete_task_from_tasklist(int* task){

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char tasks[100];
  snprintf(tasks, sizeof(tasks), "DELETE FROM tasks where rowid == %u", *task);
  sqlite3_exec(db, tasks, NULL, NULL, NULL);

  sqlite3_close(db);
}

void delete_task_from_backlog(int* task){

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char backlog[100];
  snprintf(backlog, sizeof(backlog), "DELETE FROM backlog where rowid == '%u'", *task);
  sqlite3_exec(db, backlog, NULL, NULL, NULL);

  sqlite3_close(db);
}


void create(){
  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_exec(db, "create table tasks(title)", NULL, NULL, NULL);
  sqlite3_close(db);
}


void insert_task(char *task)
{

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char sql[100];
  snprintf(sql, sizeof(sql), "insert into tasks values('%s');", task);

  sqlite3_exec(db, sql, NULL, NULL, NULL);
  sqlite3_close(db);
}

void read_tasks()
{
  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "select * from tasks;", -1, &stmt, NULL)) {
    printf("Error executing sql statement\n");
    sqlite3_close(db);
    exit(-1);
  }

  sqlite3_bind_int (stmt, 1, 2);
  while (sqlite3_step(stmt) != SQLITE_DONE) {
    for (int col=0; col<=1; col++) {
      printColumnValue(stmt, col);
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

}

void list_tasks()
{
  printf("\n\n");
  printf("\tToday's left Tasks: \n\n");

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "select rowid, task from tasks;", -1, &stmt, NULL)) {
    printf("Error executing sql statement\n");
    sqlite3_close(db);
    exit(-1);
  }

  sqlite3_bind_int (stmt, 1, 2);
  while (sqlite3_step(stmt) != SQLITE_DONE) {
    for (int col=0; col<=1; col++) {
      printColumnValueList(stmt, col);
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

}


void read_backlog()
{
  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "select * from backlog;", -1, &stmt, NULL)) {
    printf("Error executing sql statement\n");
    sqlite3_close(db);
    exit(-1);
  }

  sqlite3_bind_int (stmt, 1, 2);

  while (sqlite3_step(stmt) != SQLITE_DONE) {
    for (int col=0; col<=1; col++) {
      printColumnValue(stmt, col);
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void list_backlog()
{
  printf("\n\n");
  printf("\tYesterdays leftovers: \n\n");

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "select rowid, task from backlog;", -1, &stmt, NULL)) {
    printf("Error executing sql statement\n");
    sqlite3_close(db);
    exit(-1);
  }

  sqlite3_bind_int (stmt, 1, 2);

  while (sqlite3_step(stmt) != SQLITE_DONE) {
    for (int col=0; col<=1; col++) {
      printColumnValueList(stmt, col);
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void backlog_tasks()
{

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char count[50];
  int streak = 0;
  snprintf(count, sizeof(count), "SELECT COUNT(*) FROM tasks;");
  sqlite3_exec(db, count, callback, &streak, NULL);

  if(streak != 0) {
    reset_streak();
  } 
  else {
    increment_streak();
  }

  char move[100];
  snprintf(move, sizeof(move), "insert into backlog select * from tasks;");

  sqlite3_exec(db, move, NULL, NULL, NULL);

  char remove[100];
  snprintf(remove, sizeof(remove), "DELETE FROM tasks;");

  sqlite3_exec(db, remove, NULL, NULL, NULL);
  sqlite3_close(db);
}

void cleanup_backlog()
{

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  char remove[100];
  snprintf(remove, sizeof(remove), "DELETE FROM backlog;");

  sqlite3_exec(db, remove, NULL, NULL, NULL);
  sqlite3_close(db);
}


void list_done()
{
  printf("\n\n");
  printf("\tThis Week's finished Tasks: \n\n");

  sqlite3 *db;
  if (sqlite3_open("/home/levin/code/c/system/tasks.db", &db)) {
    printf("Could not open the.db\n");
    exit(-1);
  }

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "select * from done;", -1, &stmt, NULL)) {
    printf("Error executing sql statement\n");
    sqlite3_close(db);
    exit(-1);
  }

  sqlite3_bind_int (stmt, 1, 2);

  while (sqlite3_step(stmt) != SQLITE_DONE) {
    for (int col=0; col<=1; col++) {
    printColumnValueList(stmt, col);
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}




