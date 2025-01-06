/*
 * Name: Khant Khine
 * Course: CS455
 * Date: 12/02/2024
 * Last updated: 12/03/2024
 * Collaborators: Drew Clark
 * Description : This program is a driver for SBOM class,export
 *		 subsystem, hashing subsystem, and the database manager.
 */

#include <fstream>
#include <iostream>
#include <string>

#include "ExportSubSystem.h"
#include "SBOM.h"
#include "database.h"
#include "hashing.h"
#include "management.h"

using namespace std;

// Declare Functions
void
choiceSwitch(int);
void
displayMenu();

// Declare a manager for operations
management manager("EXProject");

int
main()
{
    int choice = 0;

    // Display Welcome Message
    cout << "Welcome to the SBOM System. Please select any option." << endl
         << endl;

    // Display Menu
    displayMenu();

    while (choice != 10) {
        cout << endl << "Please enter your choice: ";
        cin >> choice;
        cout << endl;

        // Operate User Choices
        choiceSwitch(choice);
    }

    // Display Farewell Message
    cout << "Thank you for using our SBOM program. See you soon." << endl;
    return 0;
}

/*
 * This function displays the menu for the user when he requests it.
 */
void
displayMenu()
{
    cout << "Option 1: Add a SBOM" << endl;
    cout << "Option 2: Edit a SBOM" << endl;
    cout << "Option 3: Search index for a SBOM" << endl;
    cout << "Option 4: Delete a SBOM " << endl;
    cout << "Option 5: Display a SBOM" << endl;
    cout << "Option 6: Display all SBOMs" << endl;
    cout << "Option 7: Export a SBOM" << endl;
    cout << "Option 8: View history log of current session" << endl;
    cout << "Option 9: View menu" << endl;
    cout << "Option 10: Exit current session" << endl << endl;
}

/*
 * This function operates the user choices.
 */
void
choiceSwitch(int choice)
{
    // ID to store user inputted SBOM ID.
    string id;
    // Location to store SBOM index location.
    int location;

    switch (choice) {
        // Add a SBOM
        case 1 : {
            cout << "You have selected Option 1: Add a SBOM" << endl;
            cout << "Please enter the id of the new SBOM to be added: ";
            cin >> id;
            cout << endl;
            manager.addSBOM(id);
            break;
        }

        // Edit a SBOM
        case 2 : {
            cout << "You have selected Option 2: Edit a SBOM" << endl;
            cout << "Please enter the id of the SBOM to be edited: ";
            cin >> id;
            cout << endl;
            manager.editSBOM(id);
            break;
        }

        // Search for index of SBOM
        case 3 : {
            cout << "You have selected Option 3: Index for a SBOM" << endl;
            cout << "Please enter the id of the SBOM to be searched: ";
            cin >> id;
            cout << endl;
            location = manager.findIndex(id);

            if (location != -1) {
                cout << "Your SBOM is located in index " << location << endl;
            }

            else {
                cout << "Your SBOM does not exist." << endl;
            }
            break;
        }

        // Delete a SBOM
        case 4 : {
            cout << "You have selected Option 4: Delete a SBOM" << endl;
            cout << "Please enter the id of the SBOM to be deleted: ";
            cin >> id;
            cout << endl;
            manager.deleteSBOM(id);
            break;
        }

        // Display a SBOM
        case 5 : {
            cout << "You have selected Option 5: Display a SBOM" << endl;
            cout << "Please enter the id of the SBOM to be displayed: ";
            cin >> id;
            cout << endl;
            manager.displaySBOM(id);
            break;
        }

        // Display all SBOMs
        case 6 : {
            cout << "You have selected Option 6: Display all SBOM" << endl;
            cout << endl;
            manager.displayAll();
            break;
        }

        // Export a SBOM
        case 7 : {
            cout << "You have selected Option 7: Export a SBOM" << endl;
            cout << "Please enter the id of the SBOM to be exported: ";
            cin >> id;
            location = manager.findIndex(id);

            if (location != -1) {
                string file;
                string data = toCSV(manager.getSBOM(location));
                cout << "Please enter the name of the file: ";
                cin >> file;
                exportToCSV(file, data);
            }

            else {
                cout << "The SBOM you entered does not exist." << endl;
            }
            break;
        }

        // View history log
        case 8 : {
            string line;
            cout << "You have selected Option 8: View history log" << endl;
            ifstream readFile("log.txt");
            while (getline(readFile, line)) {
                cout << line << endl;
            }
            readFile.close();
            break;
        }

        // View menu
        case 9 :
            displayMenu();
            break;

        // Exit session
        case 10 :
            break;

        default : {
            cout << "Not a valid option." << endl;
            break;
        }
    }
}
