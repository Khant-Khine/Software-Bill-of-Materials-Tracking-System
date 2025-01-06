/*
 * Name: Thomas Bendall
 * Course: CS455
 * Date: 11/15/2024
 * Description : This program is the implementation for the database component
 */
#include "database.h"

// private section
bool
Database::openDatabase(const std::string& name)
{
    bool status = true;
    // open database, check to see if properly working
    if ((sqlite3_open(name.c_str(), &database)) != SQLITE_OK) {
        std::cerr << "Error occurred when opening database: "
                  << sqlite3_errmsg(database) << std::endl;
        status = false;
    }
    return status;
}

void
Database::closeDatabase()
{
    sqlite3_close(database);
}

int
Database::getNumRows(const std::string& table)
{
    int rows = 0;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT * FROM " + table + ";";

    if ((sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, nullptr)) !=
        SQLITE_OK) {
        std::cerr << "Error occurred when getting number of rows: "
                  << sqlite3_errmsg(database) << std::endl;
        return 0;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
        rows++;

    return rows;
}

// public section
Database::Database(const std::string& databaseName)
{
    openDatabase(databaseName);
}

// destructor, closes database
Database::~Database()
{
    closeDatabase();
}

bool
Database::insertRecord(const std::string& table, const std::string& data)
{
    char* errMsg = nullptr;
    bool status = true;

    std::string sql = "INSERT INTO " + table + " VALUES(" + data + ");";

    if ((sqlite3_exec(database, sql.c_str(), 0, 0, &errMsg)) != SQLITE_OK) {
        std::cerr << "Error occurred when inserting record: " << errMsg
                  << std::endl;
        sqlite3_free(errMsg);
        status = false;
    }

    return status;
}

std::string
Database::retrieveRecord(const std::string& table, const std::string& criteria)
{
    std::string record = "";
    sqlite3_stmt* stmt;

    std::string sql = "SELECT * FROM " + table + " WHERE " + criteria + ";";

    if ((sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, nullptr)) !=
        SQLITE_OK) {
        std::cerr << "Error occurred when retrieving record: "
                  << sqlite3_errmsg(database) << std::endl;
        return record;
    }

    int rows = getNumRows(table);
    for (int i = 0; i < rows; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int cols = sqlite3_column_count(stmt);
            for (int i = 0; i < cols; i++) {
                record += (const char*)sqlite3_column_text(stmt, i);
                if (i < cols - 1)
                    record += ", ";
            }
            record += ";"; // splits distinct rows by ';'
        }
    }

    sqlite3_finalize(stmt);
    return record;
}

bool
Database::updateRecord(const std::string& table,
                       const std::string& data,
                       const std::string& criteria)
{
    bool status = true;
    char* errMsg = nullptr;

    std::string sql =
        "UPDATE " + table + " SET " + data + " WHERE " + criteria + ";";

    if ((sqlite3_exec(database, sql.c_str(), 0, 0, &errMsg)) != SQLITE_OK) {
        std::cerr << "Error occurred when updating record: " << errMsg
                  << std::endl;
        sqlite3_free(errMsg);
        status = false;
    }

    return status;
}

bool
Database::deleteRecord(const std::string& table, const std::string& criteria)
{
    bool status = true;
    char* errMsg = nullptr;

    std::string sql = "DELETE FROM " + table + " WHERE " + criteria + ";";

    if (retrieveRecord(table, criteria) == "") {
        std::cout << "record doesn't exist, didn't delete anything"
                  << std::endl;
        status = false;
    } else if ((sqlite3_exec(database, sql.c_str(), 0, 0, &errMsg)) !=
               SQLITE_OK) {
        std::cerr << "Error occurred trying to delete record: " << errMsg
                  << std::endl;
        sqlite3_free(errMsg);
        status = false;
    }

    return status;
}

bool
Database::createTable(const std::string& tableSchema)
{
    char* errMsg = nullptr;
    bool status = true;

    if ((sqlite3_exec(database, tableSchema.c_str(), 0, 0, &errMsg)) !=
        SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        status = false;
    }

    return status;
}
