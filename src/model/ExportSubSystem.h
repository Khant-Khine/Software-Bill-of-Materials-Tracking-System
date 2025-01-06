/*
 * Name: Khant Khine
 * Course: CS455
 * Date: 11/17/2024
 * Description : This program is the header file for export subsytem.
 */

#ifndef EXPORTSUBSYSTEM_H
#define EXPORTSUBSYSTEM_H

#include "SBOM.h"
#include <string>

using namespace std;

string toCSV(const SBOM& sbom);
void exportToCSV(const string& file, const string& data);

#endif
