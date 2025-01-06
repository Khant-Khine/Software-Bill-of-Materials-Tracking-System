/*
 * Name: Zachary Borden
 * Date: 12/7/2024
 * Last Updated: 12/7/2024
 * Collaborators: N/A
 * Description: Test for the authManager
 */

#include <gtest/gtest.h>

#include "authManager.h"
#include "../../src/model/database.h"

namespace{
//Fixture: Database for testing
class DatabaseTest: public::testing::Test
{
    protected:
        Database* db;

        void SetUp() override
        {
            db = new Database("sbomDatabase.db");
        }

        void TearDown() override
        {
            delete db;
	    std::remove("sbomDatabase.db");
        }


};

//test to see if user exists in database
TEST_F(DatabaseTest, doesUserExist)
{
    authManager authorize;
    std::string table = "User";
    std::string data = "'James', 'Password'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (username TEXT, passwordHash TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));
    EXPECT_TRUE(db->insertRecord(table, data));

    EXPECT_TRUE(authorize.authenticateUser("James", "Password"));
}

//Test to see if user is not in database
TEST_F(DatabaseTest, nonExistentUser)
{
    authManager authorize;
    std::string table = "User";
    std::string data = "'James', 'Password'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (username TEXT, passwordHash TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));
    EXPECT_TRUE(db->insertRecord(table, data));

    EXPECT_FALSE(authorize.authenticateUser("Greg", "Password"));
}

//test to see if user enters wrong password
TEST_F(DatabaseTest, wrongPassword)
{
    authManager authorize;
    std::string table = "User";
    std::string data = "'James', 'Password'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (username TEXT, passwordHash TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));
    EXPECT_TRUE(db->insertRecord(table, data));

    EXPECT_FALSE(authorize.authenticateUser("James", "Wrong"));
}

//test to see if user has read permissions
TEST_F(DatabaseTest, readPermission)
{
    authManager authorize;
    std::string table = "UserAccess";
    std::string data = "'James', 'reader'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (userID TEXT, role TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));
    EXPECT_TRUE(db->insertRecord(table, data));

    EXPECT_TRUE(authorize.checkUserPermissions("'James'", "read"));
    EXPECT_FALSE(authorize.checkUserPermissions("'James'", "write"));
}

//Test to see if user has read/write permissions
TEST_F(DatabaseTest, writePermission)
{
    authManager authorize;
    std::string table = "UserAccess";
    std::string data = "'James', 'editor'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (userID TEXT, role TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));
    EXPECT_TRUE(db->insertRecord(table, data));

    EXPECT_TRUE(authorize.checkUserPermissions("'James'", "read"));
    EXPECT_TRUE(authorize.checkUserPermissions("'James'", "write"));
}

//Test to make sure users have correct permissions
TEST_F(DatabaseTest, multiUserPermissions)
{
    authManager authorize;
    std::string table = "UserAccess";
    std::string data1 = "'James', 'editor'";
    std::string data2 = "'Greg', 'reader'";

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + table + " (userID TEXT, role TEXT);";
    EXPECT_TRUE(db->createTable(createTableSQL));
    EXPECT_TRUE(db->insertRecord(table, data1));
    EXPECT_TRUE(db->insertRecord(table, data2));

    EXPECT_TRUE(authorize.checkUserPermissions("'Greg'", "read"));
    EXPECT_FALSE(authorize.checkUserPermissions("'Greg'", "write"));
}

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
