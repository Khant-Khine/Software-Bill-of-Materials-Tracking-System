/*
 * Name: Zachary Borden
 * Course: CS455
 * Date: 12/1/2024
 *Description: Header file for the authentication management subsystem
 */

#include <string>

#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

using namespace std;

class authManager {
public:
  bool authenticateUser(string user, string password);
  bool checkUserPermissions(string UserID, string action);
};
#endif
