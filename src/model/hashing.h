/*
 * Name: Zachary Borden
 * Course: CS455
 * Date: 11/22/2024
 * Description: This is the header file for the hashing subsystem
 */

#ifndef HASHING_H
#define HASHING_H

#include <string>

using namespace std;

class hasher {
private:
  string ogPassword;
  string hashedPassword;

public:
  hasher() = delete;
  hasher(const string password);
  string getOriginal();
  string getHashed();
  void hashing(string password);
};
#endif
