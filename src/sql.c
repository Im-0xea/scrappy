#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include <sqlite3.h>

#include "logging.h"

sqlite3 * db;

bool init_db(const char * db_path)
{
	int chk_fd;
	char * msg;
	if ((chk_fd = open(db_path, O_RDONLY))) {
		close(chk_fd);
		if (sqlite3_open(db_path, &db) != SQLITE_OK)
			lerror(1, "Failed to open db %s", db_path);
		return true;
	}
	
	if (sqlite3_open(db_path, &db) != SQLITE_OK)
		lerror(1, "Failed to open db %s", db_path);
	
	if (sqlite3_exec(db, "CREATE TABLE urls ("
	                     "id     INTEGER PRIMARY KEY,"
	                     "url    TEXT    UNIQUE,"
	                     "dumped BOOLEAN DEFAULT     '0',"
	                     "depth  INTEGER,"
	                     "ref    INTEGER DEFAULT     '1'",
	                     0, 0, &msg) != SQLITE_OK) {
		lerror(-1, "failed to create table: %s", msg);
		sqlite3_free(msg);
		sqlite3_close(db);
		exit(1);
	}
	
	return false;
}
void cleanup_db(void)
{
	sqlite3_close(db);
}
void insert_url(const char * url)
{
	sqlite3_stmt * stmt;
	if (sqlite3_prepare_v2(db, "INSERT INTO urls"
				   "(url, referenced)"
				   "VALUES (?, '0');",
				   -1, &stmt, NULL)
				   != SQLITE_OK) {
		sqlite3_close(db);
		lerror(1, "prepare for insertion failed");
	}
	//if (sqlite3_bind_text(stmt, 1, link, SQLITE_TRANSIENT) !=
	//    SQLITE_OK) {
	//	sqlite3_close(db);
	//	lerror(1, "binding url for insertion failed");
	//}
}
