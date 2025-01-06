# Model source code

## SBOM.h and SBOM.cpp
    * SBOM base class
    * SBOM object representative of an SBOM
    * Members to contain SBOM components characteristics
    * Methods to access SBOM components characteristics
    * Methods to edit the SBOM or its components

## ExportSubSystem.h and ExportSubSystem.cpp
    * Methods to export an SBOM as a .csv file

## Database.h and Database.cpp
    * Implements an SQLite3 database
    * Methods to create or delete a database
    * Methods to insert, delete, or update records

## management.h and management.cpp
    * Implements a basic control structure for managing SBOMs
    * Acts as a basic user interface for creating, editing, deleting,
      and exporting SBOMs

## hashing.h and hashing.cpp
    * Members to contain original password and hashed version
    * Method to hash passwords
    * Method to return original password
    * Method to return the hashed password

## testDriver.cpp
    * Basic example driver
    * Used for rudimentary tests

## sbomDatabase.db
    * Tables:
	* Project(ID, name)
	* SBOM(ID,projectID)
	* Component(sbomID,name,version,hash,ID)
	* User(username,passwordHash,email)
	* UserAccess(userID, projectID, role)
	* user .schema when opening database to view all info
