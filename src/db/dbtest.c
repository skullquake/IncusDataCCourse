/*!@file db/dbtest.c
 * @brief sqlite datbaase test
 */
#include"db/dbtest.h"
#include<stdio.h>
#include"sqlite/sqlite.h"
#include"incus/cadv/prg000.h"
int dbtest(void){
  printf("info:sqlitetest:start\n");
  sqlite3 *db;
  sqlite3_stmt *res;
  int rc = sqlite3_open(":memory:", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }
  rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);    
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }    
  rc = sqlite3_step(res);
  if (rc == SQLITE_ROW) {
    printf("%s\n", sqlite3_column_text(res, 0));
  }
  sqlite3_finalize(res);
  sqlite3_close(db);
  printf("info:sqlitetest:end\n");
  return 0;
}
int dbtest2(void){
	printf("info:sqlitetest:start\n");
	sqlite3 *db;
	int rc = sqlite3_open("./db/a.db", &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	{/* create table */
		char *err_msg = 0;
		char *sql = "CREATE TABLE IF NOT EXISTS TEST(VAL TEXT);";
		rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
		if (rc != SQLITE_OK ) {
			fprintf(stderr, "SQL error: %s\n", err_msg);
			sqlite3_free(err_msg);
		}
	}
	{/* populate table - non prepared*/
		char *err_msg = 0;
		char *sql="INSERT INTO TEST(VAL) VALUES('test0');";
		rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
		if (rc != SQLITE_OK ) {
			fprintf(stderr, "SQL error: %s\n", err_msg);
			sqlite3_free(err_msg);
		}
	}
	{/* populate table - prepared*/
		//todo
	}
	{/* select from table */
		sqlite3_stmt *res;
		rc = sqlite3_prepare_v2(db, "SELECT * FROM TEST;", -1, &res, 0);    
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		}    
		int rowcount = sqlite3_column_int(res, 0);
		while(sqlite3_step(res)== SQLITE_ROW){
			for(int colidx=0;colidx<sqlite3_column_count(res);++colidx){
				printf("%s\n", sqlite3_column_text(res,colidx));
			}
		}
		sqlite3_finalize(res);
	}
	sqlite3_close(db);
	printf("info:sqlitetest:end\n");
	return 0;
}
