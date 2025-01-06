/*
 * Name: Zachary Borden
 * Course: CS455
 * Date: 12/1/2024
 * Description: Implementation for the authentication manager
 */

#include "authManager.h"
#include "database.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool authManager::authenticateUser(string user, string password) {
  // opens database holding user information
  Database userDB("../../src/model/sbomDatabase.db");
  bool status = true;

  if (userDB.retrieveRecord("User", "username = '" + user + "'") == "" ||
      userDB.retrieveRecord("User", "passwordHash ='" + password + "'") == "") {
    cout << "Username/password not found" << endl;
    status = false;
    return status;
  }

  return status;
}
bool authManager::checkUserPermissions(string UserID, string action) {
  // open database holding user permissions
  Database userDB("sbomDatabase.db");
  bool status = false;
  string role = "";
  string output = userDB.retrieveRecord("UserAccess", "userID = " + UserID);

  if (output.find("reader") != string::npos) {
    role = "reader";
  } else if (output.find("editor") != string::npos) {
    role = "editor";
  }

  if (action == "read") {
    if (role == "reader" || role == "editor") {
      status = true;
    }
  }

  else if (action == "write" || action == "delete") {
    if (role == "editor") {
      status = true;
    }
  }

  return status;
}
