/*
 * Name: Zachary Borden
 * Course: CS455
 * Date: 11/22/2024
 * Description: Implements the system to hash passwords
 */

#include "hashing.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// constuctor
hasher::hasher(const string password) {
  ogPassword = password;
  hashing(password);
}

// returns the original password
string hasher::getOriginal() { return (ogPassword); }

// returns the hashed password
string hasher::getHashed() { return (hashedPassword); }

// function to hash password
// Based on java code for forming a hashcode
// citation: isdanni.com/hash-flooding/
void hasher::hashing(string password) {
  int prime1 = 3;
  int prime2 = 7;

  stringstream hexConvert;
  string result;

  // provide padding for the password of necessary
  if (password.length() < 16) {
    while (password.length() < 16) {
      password.append("0");
    }
  }

  // iterate through the password calculating the hash
  unsigned long long int hash = prime1;
  for (char s : password) {
    hash = hash * (prime2 + int(s));
  }

  hexConvert << hex << hash;
  result = hexConvert.str();

  hashedPassword = result;
}
