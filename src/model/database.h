/*
 * Name: Thomas Bendall
 * Course: CS455
 * Date: 11/15/2024
 * Description : This program is the header file for the
 *  database component, it handles storage through an SQL database
 *  and SQL queries
 */
#include <iostream>
#include <sqlite3.h>
#include <string.h>

#ifndef DATABASE_H
#define DATABASE_H

class Database
{
  private:
    sqlite3* database;
    bool openDatabase(const std::string& name);
    void closeDatabase();
    int getNumRows(const std::string& table);

  public:
    Database() = delete;
    Database(const std::string& databaseName);
    ~Database();
    bool insertRecord(const std::string& table, const std::string& data);
    std::string retrieveRecord(const std::string& table,
                               const std::string& criteria);
    bool updateRecord(const std::string& table,
                      const std::string& data,
                      const std::string& criteria);
    bool deleteRecord(const std::string& data, const std::string& criteria);
    bool createTable(const std::string& tableSchema);
};
#endif
