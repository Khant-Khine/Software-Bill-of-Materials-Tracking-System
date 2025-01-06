/*
 * Name: Khant Khine
 * Course: CS455
 * Date: 11/17/2024
 * Description : This program is the implementation file for export subsytem.
 */

#include "SBOM.h"
#include "ExportSubSystem.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string toCSV(const SBOM& sbom)
{
    //Header for CSV file
    string data = "SBOM ID, Component Name, Version, Hash, ID\n";

    for(int i = 0; i < sbom.getSize(); i++)
    {
        data = data + sbom.getSBOM_ID() + "," + 
		      sbom.getCompName(i) + "," +
	              sbom.getCompVersions(i) + "," +
		      sbom.getCompHashes(i) + "," +
		      sbom.getCompIds(i) + "\n";
    }
    return data;
}


void exportToCSV(const string& file, const string& data)
{
    ofstream exportFile(file);

    exportFile << data;
    exportFile.close();
}
