/*
 * Name: Khant Khine
 * Course: CS455
 * Date: 11/10/2024
 * Last updated: 11/24/2024
 * Collaborators: Drew Clark
 * Description : This program is the implementation file for SBOM class.
                 This class defines the structure of an SBOM.
 */

#include "SBOM.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

//Constructor
SBOM::SBOM(string ID)
{
    	SBOM_ID = ID;
	compNames = vector<string>();
	compVersions = vector<string>();
	compHashes = vector<string>();
	compIds = vector<string>();
}

//Accessors
string SBOM::getSBOM_ID()const
{
    return SBOM_ID;
}

//Get details about a component from its name in compNames
string SBOM::getComp(string compName)const
{
    for(int i = 0; i < compNames.size(); i++)
    {
        if(compNames[i] == compName)
	{
	    return ("Component Name: " + compNames[i] +
		    "\nVersion: " + compVersions[i] +
		    "\nHash: " + compHashes[i] +
		    "\nID: " + compIds[i]);
	}
    }

    //Component not found in ComponentNames
    return "Component not found";
}

//Get details about a component from its index in compNames
string SBOM::getComp(int index)const
{
    //If index are out of bounds
    if(index < 0 || index >= compNames.size())
    {
        return "Invalid index";
    }
    //If index is within bounds
    return ("Component Name: " + compNames[index] + 
	    "\nVersion: " + compVersions[index] +
	    "\nHash: " + compHashes[index] +
	    "\nID: " + compIds[index]);
}

string SBOM::getCompName(int index)const
{
    return compNames.at(index);
}

string SBOM::getCompVersions(int index)const
{
    return compVersions.at(index);
}

string SBOM::getCompHashes(int index)const
{
    return compHashes.at(index);
}

string SBOM::getCompIds(int index)const
{
    return compIds.at(index);
}

int SBOM::getSize() const
{
    return compNames.size();
}

//Mutators
void SBOM::setSBOM_ID(string ID)
{
    string data = "SBOM ID changed from " + SBOM_ID + " to " + ID;
    SBOM_ID  = ID;
    exportLog("log.txt", data);
}

void SBOM::addComp(string nam, string ver, string hash, string id) 
{
    compNames.push_back(nam);
    compVersions.push_back(ver);
    compHashes.push_back(hash);
    compIds.push_back(id);
    string data = "SBOM Component " + nam 
	          + ", with version: " + ver 
	          + ", hash: " + hash 
		  + ", id: " + id 
		  + " was added to SBOM with SBOM ID: " + SBOM_ID;
    exportLog("log.txt", data);
}

void SBOM::delComp(string name)
{
    for(int i = 0; i < compNames.size(); i++)
    {
	//If component name is found
        if(compNames[i] == name)
	{
            string data = "SBOM Component " + compNames[i] 
		          + ", with version: " + compVersions[i]
		          + ", hash: " + compHashes[i] 
			  + ", id: " + compIds[i] 
			  + " was removed from SBOM with SBOM ID: " + SBOM_ID;
            exportLog("log.txt", data);
	    compNames.erase(compNames.begin() + i);
	    compVersions.erase(compVersions.begin() + i);
	    compHashes.erase(compHashes.begin() + i);
	    compIds.erase(compIds.begin() + i);
	}
    }
}

void SBOM::setCompName(int index, string name)
{
    if(index >= 0 && index < compNames.size())
    {
	string data = "SBOM Component Name changed from " + compNames[index] 
		      + " to " + name;
        compNames[index] = name;
	exportLog("log.txt", data);
    }
}

void SBOM::setCompVersions(int index, string version)
{
    if(index >= 0 && index < compVersions.size())
    {
	string data = "SBOM Component Version changed from " 
		      + compVersions[index] 
		      + " to " + version;
        compVersions[index] = version;
	exportLog("log.txt", data);
    }
}

void SBOM::setCompHashes(int index, string hash)
{
    if(index >= 0 && index < compHashes.size())
    {
	string data = "SBOM Component Hash changed from " 
		      + compHashes[index] + " to " + hash;
        compHashes[index] = hash;
	exportLog("log.txt", data);
    }
}

void SBOM::setCompIds(int index, string id)
{
    if(index >= 0 && index < compIds.size())
    {
	string data = "SBOM Component ID changed from " 
		      + compIds[index] + " to " + id;
        compIds[index] = id;
	exportLog("log.txt", data);
    }
}

//Log method
void SBOM::exportLog(const string& file, const string& data)
{
    time_t currTime = time(0);
    char* currentTime = ctime(&currTime);

    string newData = data;
    newData = newData + " on " + currentTime + "\n\n";

    ofstream exportFile(file, ios::app);

    exportFile<<newData;
    exportFile.close();
}
