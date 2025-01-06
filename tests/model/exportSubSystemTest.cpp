/*
 * Name: Zachary Borden
 * Date: 12/8/2024
 * Last Updated: 12/8/2024
 * Collaborators: N/A
 * Description: Tests for the export SubSystem
 */

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <iostream>

#include "ExportSubSystem.h"
#include "SBOM.h"

namespace{

//Test to see if converts to csv format
TEST(ExportSystemTest, toCSVTest)
{
    SBOM sbom("Testbom");
    sbom.addComp("Comp1", "1.0", "testhash", "id1");
    EXPECT_EQ(sbom.getSBOM_ID(), "Testbom");

    EXPECT_EQ(toCSV(sbom), "SBOM ID, Component Name, Version, Hash, ID\nTestbom,Comp1,1.0,testhash,id1\n");
}

//test to see if exportToCSV produces a file
TEST(ExportSystemTest, makeExportFileTest)
{
    std::string data = "Test";
    exportToCSV("test.txt", data);
    ofstream testFile;
    testFile.open("test.txt");

    EXPECT_TRUE(testFile.is_open());
    testFile.close();
}

//test to see if exportToCsv works with the toCsv function
TEST(ExportSystemTest, exportFileIsCSV)
{
    SBOM sbom("Testbom");
    sbom.addComp("Comp1", "1.0", "testhash", "id1");

    exportToCSV("test.txt", toCSV(sbom));
    ifstream testFile;
    testFile.open("test.txt");

    std::string data;
    std::getline(testFile, data);
    
    EXPECT_EQ(data, "SBOM ID, Component Name, Version, Hash, ID");

    std::getline(testFile, data);
    EXPECT_EQ(data, "Testbom,Comp1,1.0,testhash,id1");
}


}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
