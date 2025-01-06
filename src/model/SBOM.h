/*
 * Name: Khant Khine
 * Course: CS455
 * Date: 11/10/2024
 * Collaborators: Drew Clark
 * Description: This program is a header file for SBOM class.
                 This class defines the structure of an SBOM.
 */

#ifndef SBOM_CLASS_H
#define SBOM_CLASS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SBOM
{
    private:
        string SBOM_ID;
	vector<string> compNames;
	vector<string> compVersions;
	vector<string> compHashes;
	vector<string> compIds;
    public:
	//Constructor
        SBOM(string);
	//Accessors
	string getSBOM_ID()const;
	string getComp(string)const;
	string getComp(int)const;
	string getCompName(int)const;
	string getCompVersions(int)const;
	string getCompHashes(int)const;
	string getCompIds(int)const;
	int getSize() const;
	void exportLog(const string&, const string&);
	//Mutators
	void setSBOM_ID(string);
	void addComp(string, string, string, string);
	void delComp(string);
	void setCompName(int, string);
	void setCompVersions(int, string);
	void setCompHashes(int, string);
	void setCompIds(int, string);
};
#endif//

