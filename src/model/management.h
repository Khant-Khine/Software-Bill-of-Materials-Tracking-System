/*
 * Name: Jahnavi
 * Course: CS455
 * Date: 11/17/2024
 * Last modified: 12/06/2024
 * Collaborators: Khant Khine, Thomas Bendall
 * Description: This is the Management subsystem of SBOM
 * It lets the users create, edit delete and view the SBOM entries.
 */

#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "SBOM.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class management
{
  private:
    vector<SBOM> sbom;
    string projectID; // Thomas: for database purposes
    // each SBOM in the database has a projectID,
    // so I made that a part of this class
    void loadSBOM(string record);
    void loadComponents(string name, string version, string hash, string ID);
    void addSbomObject(SBOM inSBOM);

  public:
    management(string ID);
    int findIndex(const string& id);
    SBOM& getSBOM(const int& index);
    void addSBOM(const string& id);
    void editSBOM(const string& id);
    void deleteSBOM(const string& id);
    void displaySBOM(const string& id);
    void displayAll();
};

#endif
