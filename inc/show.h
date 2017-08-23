#ifndef __SHOW_H_
#define __SHOW_H_

#include "head.h"

int create_table(sqlite3 *db);

int sqlite3_insert(sqlite3 *db, struct phone_info *ph);

int sqlite3_del(sqlite3 *db);

int display(sqlite3 *db);

int callback(void *data,int argc,char **cloumn_values, char **cloumn_name);

int sqlite3_update(sqlite3 *db);

#endif