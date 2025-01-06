/*
 * Name: Jahnavi
 * Course: CS455
 * Date: 11/18/2024
 * Last modified: 12/03/2024
 * Collaborators: Khant Khine, Thomas Bendall
 * Description: this is the management subsystem class
 * It lets the users create, edit, delete and view the SBOM entries.
 */

#include "management.h"
#include "SBOM.h"
#include "database.h"
#include "hashing.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

vector<string>
split(const string& str, const char& delimeter)
{
    vector<string> result;
    stringstream ss(str);
    string item;

    while (getline(ss, item, delimeter))
        result.push_back(item);

    return result;
}

management::management(string ID)
{
    projectID = ID;
    Database database("sbomDatabase.db");
    string condition = "ID = '" + projectID + "'";
    string record = database.retrieveRecord("Project", condition);
    if (record == "") {
        cout << "creating project..." << endl;

        // change this when integrating front-end:
        // for now I'm just giving a project the same name as its ID,
        //   this can be changed later in front-end integration if wanted.
        string inRecord = "'" + projectID + "', '" + projectID + "'";
        if (! (database.insertRecord("Project", inRecord)))
            cout << "Error inserting project" << endl;
    } else {
        cout << "loading project..." << endl;

        // load sboms
        condition = "projectID = '" + ID + "'";
        record = database.retrieveRecord("SBOM", condition);

        if (record == "")
            return;

        char delimeter = ';';
        vector<string> boms = split(record, delimeter);

        for (auto bom : boms)
            loadSBOM(bom);
    }
}

void
management::loadSBOM(string record)
{
    cout << "loading sbom..." << endl;
    char delimeter = ',';
    vector<string> info = split(record, delimeter);
    SBOM bom(info[0]);
    Database database("sbomDatabase.db");
    string condition = "sbomID = '" + bom.getSBOM_ID() + "'";
    record = database.retrieveRecord("Component", condition);
    if (record != "") {
        delimeter = ';';
        vector<string> comps = split(record, delimeter);

        delimeter = ',';

        for (auto comp : comps) {
            vector<string> parts = split(comp, delimeter);
            bom.addComp(parts[1], parts[2], parts[3], parts[4]);
        }
    }
    addSbomObject(bom);
}

void
management::addSbomObject(SBOM inSBOM)
{
    sbom.push_back(inSBOM);
}

int
management::findIndex(const string& id)
{
    for (int i = 0; i < sbom.size(); i++) {
        if (sbom[i].getSBOM_ID() == id) {
            return i; // returning the index of the id
        }
    }
    return -1; // this is returned when id is not found.
}

SBOM&
management::getSBOM(const int& index)
{
    return sbom[index];
}

void
management::addSBOM(const string& id)
{
    if (findIndex(id) != -1) {
        cout << "This SBOM ID already exists" << endl;
        return;
    }

    else {
        Database database("sbomDatabase.db");
        SBOM newSBOM(id);
        string sbomRecord = "'" + id + "', '" + projectID + "'";

        if (! (database.insertRecord("SBOM", sbomRecord)))
            return;

        string compName, version, hash, compID;
        char moreComp; // this will be used to ask user if they want to
                       // add more records
                       //  enter y OR Y to add more records
                       //  enter n or N to stop adding
        do {
            cout << "Enter component name: ";
            cin.ignore();
            getline(cin, compName);
            cout << "Enter version: ";
            cin >> version;
            cout << "Enter Hash: ";
            cin >> hash;
            cout << "Enter component ID: ";
            cin >> compID;

            newSBOM.addComp(compName, version, hash, compID);

            string compRecord = "'" + id + "', '" + compName + "', '" +
                                version + "', '" + hash + "', '" + compID + "'";

            if (! (database.insertRecord("Component", compRecord)))
                return;

            cout << "Do you want to add more components? (y/n): ";
            cin >> moreComp;
            cout << endl;

        } while (moreComp == 'y' or moreComp == 'Y');

        sbom.push_back(newSBOM);
        cout << "SBOM with ID " << id << " was created succesfully." << endl;
    }
}

void
management::editSBOM(const string& id)
{
    int index = findIndex(id);
    if (index == -1) {
        cout << "SBOM ID " << id << " does not exist." << endl;
        return;
    }

    SBOM& record = sbom[index];
    int choice, compIndex;
    string compName, version, hash, compID;
    cout << "Editing the record with ID: " << id << endl;
    cout << "Select an opiton to edit?" << endl;
    cout << "1. Component name" << endl;
    cout << "2. Component version" << endl;
    cout << "3. Component hash" << endl;
    cout << "4. Component ID" << endl;
    cout << "Enter a choice: ";
    cin >> choice;
    cout << endl;

    Database database("sbomDatabase.db");
    string criteria;
    string data;
    switch (choice) {
        case 1 :
            cout << "Enter the index of the component you want to edit: ";
            cin >> compIndex;
            cout << "Enter the new name: ";
            cin.ignore();
            getline(cin, compName);
            record.setCompName(compIndex, compName);
            criteria = "ID = '" + record.getCompIds(compIndex) +
                       "' AND sbomID = '" + id + "'";
            data = "name = '" + compName + "'";
            database.updateRecord("Component", data, criteria);
            cout << "Component name was updated." << endl << endl;
            break;

        case 2 :

            cout << "Enter the index of the component you want to edit: ";
            cin >> compIndex;
            cout << "Enter the new version: ";
            cin >> version;
            criteria = "ID = '" + record.getCompIds(compIndex) +
                       "' AND sbomID = '" + id + "'";
            data = "version = '" + version + "'";
            if (! (database.updateRecord("Component", data, criteria)))
                return;
            record.setCompVersions(compIndex, version);
            cout << "Component version was updated." << endl << endl;
            break;

        case 3 : {

            cout << "Enter the index of the component you want to edit: ";
            cin >> compIndex;
            cout << "Enter the new hash: ";
            cin >> hash;
            hasher Hashing(hash);
            record.setCompHashes(compIndex, Hashing.getHashed());
            criteria = "ID = '" + record.getCompIds(compIndex) +
                       "' AND sbomID = '" + id + "'";
            data = "hash = '" + hash + "'";
            database.updateRecord("Component", data, criteria);
            cout << "Component hash was updated." << endl << endl;
            break;
        }

        case 4 :

            cout << "Enter the index of the component you want to edit: ";
            cin >> compIndex;
            cout << "Enter the new component ID: ";
            cin >> compID;
            criteria = "ID = '" + record.getCompIds(compIndex) +
                       "' AND sbomID = '" + id + "'";
            data = "ID = '" + compID + "'";

            if (! (database.updateRecord("Component", data, criteria))) {
                cout << "ID already exists" << endl;
                break;
            }

            record.setCompIds(compIndex, compID);
            cout << "Component ID was updated." << endl << endl;
            break;

        default :
            cout << "Invalid" << endl;
            break;
    }
}

void
management::deleteSBOM(const string& id)
{
    int index = findIndex(id);
    if (index == -1) {
        cout << "SBOM ID " << id << " was not found." << endl;
        return;
    }

    Database database("sbomDatabase.db");

    string criteria = "ID = '" + id + "'";
    if (! (database.deleteRecord("SBOM", criteria)))
        return;

    criteria = "sbomID = '" + id + "'";
    if (! (database.deleteRecord("Component", criteria)))
        return;
    sbom.erase(sbom.begin() + index);
    cout << "SBOM ID " << id << " was deleted." << endl << endl;
}

void
management::displaySBOM(const string& id)
{
    int index = findIndex(id);
    if (index == -1) {
        cout << "SBOM ID " << id << " was not found." << endl;
        return;
    }

    cout << "SBOM ID: " << sbom[index].getSBOM_ID() << endl;
    for (int i = 0; i < sbom[index].getSize(); i++) {
        cout << sbom[index].getComp(i) << endl << endl;
    }
}

void
management::displayAll()
{
    if (sbom.empty()) {
        cout << "No SBOM entries currently." << endl;
        return;
    }

    for (const auto& sboms : sbom) {
        cout << "SBOM ID: " << sboms.getSBOM_ID() << endl;
    }
}
