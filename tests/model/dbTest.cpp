/*
 * Name: Drew Clark
 * Date: 11/26/2024
 * Last Updated: 12/6/2024
 * Collaborators: Zachary Borden
 * Description: Test for the database subsystem
 */

#include <gtest/gtest.h>
#include <sqlite3.h>
#include <fstream>
#include <string>

#include "database.h"

namespace {

// Fixture: Database (for testing purposes only)
class DatabaseTest : public ::testing::Test 
{
    protected:
       Database* db;

       void SetUp() override 
       {
       db = new Database("test.db");
       }

       void TearDown() override 
       {
	   delete db;
           std::remove("test.db");
       }
};

// Test for constructor
TEST_F(DatabaseTest, ConstructorOpensDatabase) 
{
    EXPECT_TRUE(db != nullptr);
}

// Test for record insertion
TEST_F(DatabaseTest, InsertRecord) 
{
    std::string table = "test_table";
    std::string data = "'1', 'Test Record'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));

    EXPECT_TRUE(db->insertRecord(table, data));

    std::string criteria = "id = 1";
    std::string result = db->retrieveRecord(table, criteria);
				        
    EXPECT_TRUE(result.find("1") != std::string::npos);
    EXPECT_TRUE(result.find("Test Record") != std::string::npos);
}

// Test for record retrival
TEST_F(DatabaseTest, RetrieveRecord) 
{
    std::string table = "test_table";
    std::string data = "'1', 'Test Record'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    db->createTable(createTableSQL);
    db->insertRecord(table, data);

    std::string criteria = "id = 1";
    std::string record = db->retrieveRecord(table, criteria);

    EXPECT_EQ(record, "1, Test Record;");
}

//Test for retrieving non existent record
TEST_F(DatabaseTest, RetrieveNullRecord)
{
    std::string table= "test_table";
    std::string data = "'1', 'Test Value'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    db->createTable(createTableSQL);
    db->insertRecord(table,data);

    std::string criteria = "id = 2";
    std:: string record = db->retrieveRecord(table, criteria);

    EXPECT_EQ(record, "");

}

// Test for updating a record
TEST_F(DatabaseTest, UpdateRecord) 
{
    std::string table = "test_table";
    std::string data = "'1', 'Test Record'";
    std::string updatedData = "name = 'Updated Record'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    db->createTable(createTableSQL);
    db->insertRecord(table, data);

    EXPECT_TRUE(db->updateRecord(table, updatedData, "id = 1"));

    std::string criteria = "id = 1";
    std::string record = db->retrieveRecord(table, criteria);

    EXPECT_TRUE(record.find("Updated Record") != std::string::npos);
}

//Test for updating non existing record
TEST_F(DatabaseTest, UpdateNullRecord)
{
    std::string table = "test_table";
    std::string data = "'1', 'Test Record'";
    std::string updatedData = "name = 'Updated Record'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    db->createTable(createTableSQL);
    db->insertRecord(table, data);

    std::string fakeTable = "fake table";
    std::string fakeData = "'2', 'fake record'";

    EXPECT_FALSE(db->updateRecord(table, fakeData, "id=1"));
}

// Test for record deletion
TEST_F(DatabaseTest, DeleteRecord) 
{
    std::string table = "test_table";
    std::string data = "'1', 'Test Record'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    db->createTable(createTableSQL);
    db->insertRecord(table, data);

    EXPECT_TRUE(db->deleteRecord(table, "id = 1"));

    std::string criteria = "id = 1";
    std::string record = db->retrieveRecord(table, criteria);

    EXPECT_EQ(record, "");
}

//Test for deleting non existent record
TEST_F(DatabaseTest, DeleteNullRecord)
{
    std::string table = "test_table";
    std::string data = "'1', 'Test Record'";
    std::string updatedData = "name = 'Updated Record'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER, name TEXT);";
    db->createTable(createTableSQL);
    db->insertRecord(table, data);

    EXPECT_FALSE(db->deleteRecord(table, "id = 2"));
}

}  

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

