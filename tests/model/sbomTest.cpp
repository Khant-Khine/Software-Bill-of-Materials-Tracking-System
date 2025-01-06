/* Name: Drew Clark
 * Date: 11/26/2024
 * Last Updated: 12/3/2024
 * Collaborators: Zachary Borden
 * Description: Unit Test to validate the SBOM base class and all its member functions
 */

#include <gtest/gtest.h>
#include <fstream>
#include <string>

#include "SBOM.h"

namespace {

// Test for the constructor	
TEST(SBOMTest, Constructor) 
{
    SBOM sbom("SBOM123");
	        
    EXPECT_EQ(sbom.getSBOM_ID(), "SBOM123");
    EXPECT_EQ(sbom.getSize(), 0);  
}

// Test for adding a component
TEST(SBOMTest, AddComponent) 
{
    SBOM sbom("SBOM123");

    // Adding a component
    sbom.addComp("Component1", "1.0", "hash123", "id123");

    EXPECT_EQ(sbom.getSize(), 1);
    EXPECT_EQ(sbom.getCompName(0), "Component1");
    EXPECT_EQ(sbom.getCompVersions(0), "1.0");
    EXPECT_EQ(sbom.getCompHashes(0), "hash123");
    EXPECT_EQ(sbom.getCompIds(0), "id123");
}

// Test for deleting a component
TEST(SBOMTest, DeleteComponent) 
{
    SBOM sbom("SBOM123");

    // Add two components	        
    sbom.addComp("Component1", "1.0", "hash123", "id123");
    sbom.addComp("Component2", "2.0", "hash456", "id456");

    EXPECT_EQ(sbom.getSize(), 2);

    // Delete one component			    
    sbom.delComp("Component1");

    EXPECT_EQ(sbom.getSize(), 1);
    EXPECT_EQ(sbom.getCompName(0), "Component2");
}

// Test for deleting a non-existent component
TEST(SBOMTest, DeleteNonExistingComp)
{
    SBOM sbom("TestBOM123");

    //add component
    sbom.addComp("Comp1", "1.2", "randHash", "id1");

    EXPECT_EQ(sbom.getSize(), 1);

    //delete a component that does not exist
    sbom.delComp("NullComponent");

    EXPECT_EQ(sbom.getSize(), 1);
}

// Test for component details retrival by name
TEST(SBOMTest, GetComponentByName) 
{
    SBOM sbom("SBOM123");

    sbom.addComp("Component1", "1.0", "hash123", "id123");
		   
    std::string compDetails = sbom.getComp("Component1");
		        
    EXPECT_TRUE(compDetails.find("Component Name: Component1") != std::string::npos);
    EXPECT_TRUE(compDetails.find("Version: 1.0") != std::string::npos);
    EXPECT_TRUE(compDetails.find("Hash: hash123") != std::string::npos);
    EXPECT_TRUE(compDetails.find("ID: id123") != std::string::npos);
}

//Test for trying to retrieve a non existent component
TEST(SBOMTest, GetNonExistingCompName)
{
    SBOM sbom("Testbom");
    sbom.addComp("Comp1", "1", "testhash", "id1");

    std::string details = sbom.getComp("comp2");

    EXPECT_TRUE(details == "Component not found");

}

// Test for component details retrival by index
TEST(SBOMTest, GetComponentByIndex) 
{
    SBOM sbom("SBOM123");

    sbom.addComp("Component1", "1.0", "hash123", "id123");
    sbom.addComp("Component2", "2.0", "hash456", "id456");

    std::string compDetails = sbom.getComp(1);

    EXPECT_TRUE(compDetails.find("Component Name: Component2") != std::string::npos);
    EXPECT_TRUE(compDetails.find("Version: 2.0") != std::string::npos);
    EXPECT_TRUE(compDetails.find("Hash: hash456") != std::string::npos);
    EXPECT_TRUE(compDetails.find("ID: id456") != std::string::npos);
}

// Test for invalid index handling
TEST(SBOMTest, GetComponentInvalidIndex) 
{
    SBOM sbom("SBOM123");

    sbom.addComp("Component1", "1.0", "hash123", "id123");

    std::string result = sbom.getComp(5);
    EXPECT_EQ(result, "Invalid index");
}

// Test for modifying component details
TEST(SBOMTest, SetComponentDetails) 
{
    SBOM sbom("SBOM123");

    sbom.addComp("Component1", "1.0", "hash123", "id123");

    sbom.setCompName(0, "UpdatedComponent1");
    sbom.setCompVersions(0, "1.1");
    sbom.setCompHashes(0, "updatedhash123");
    sbom.setCompIds(0, "updatedid123");

    EXPECT_EQ(sbom.getCompName(0), "UpdatedComponent1");
    EXPECT_EQ(sbom.getCompVersions(0), "1.1");
    EXPECT_EQ(sbom.getCompHashes(0), "updatedhash123");
    EXPECT_EQ(sbom.getCompIds(0), "updatedid123");
}


// Helper for: history log test
std::string readLogFile(const std::string& filename) 
{
    std::ifstream logFile(filename);
    std::string content((std::istreambuf_iterator<char>(logFile)), std::istreambuf_iterator<char>());
    return content;
}

// Test for export log method (history log subsystem)
TEST(SBOMTest, ExportLog) 
{
    SBOM sbom("SBOM123");

    const std::string logFilename = "test_log.txt";
    std::ofstream logFile(logFilename, std::ios::trunc);
    logFile.close();

    sbom.exportLog(logFilename, "Test log entry");

    std::string logContent = readLogFile(logFilename);

    EXPECT_TRUE(logContent.find("Test log entry") != std::string::npos);
    EXPECT_TRUE(logContent.find("on") != std::string::npos);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
