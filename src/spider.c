#include <stdlib.h>
#include <stdbool.h>

#include <sqlite3.h>

#include "logging.h"

void spider(const char * db_path, const char * link);
{
	if (link) {
		sqlite3_stmt * init_stmt;
		if (sqlite3_prepare_v2(db, "INSERT INTO urls"
		                           "(url, referenced)"
		                           "VALUES (?, '0');",
		                           -1, &init_stmt, NULL)
		                           != SQLITE_OK) {
			sqlite3_close(db);
			lerror(1, "prepare for insertion failed");
		}
		if (sqlite3_bind_text(init_stmt, 1, link, SQLITE_TRANSIENT) !=
		    SQLITE_OK) {
			sqlite3_close(db);
			lerror(1, "binding url for insertion failed");
		}
	}
}
