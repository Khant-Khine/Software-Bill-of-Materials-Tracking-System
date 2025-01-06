/*
 * Name: Drew Clark
 * Date: 11/26/2024
 * Last Updated: 12/5/2024
 * Collaborators: Zachary Borden
 * Description: Test of the hashing subsystem
 */

#include <gtest/gtest.h>

#include "hashing.h"

namespace {

// Fixture: Hasher (for test purposes only)
class HasherTest : public ::testing::Test
{
    protected:
        hasher* h;
	hasher* a;
	hasher* b;
	hasher* c;
	hasher* d;

	void SetUp() override 
	{
	    h = new hasher("testPassword123");
	    a = new hasher("A");
	    b = new hasher("asDFGHJKuytrds5321ClfeqlokjhgcvhV");
	    c = new hasher("123456789");
	    d = new hasher("!@#$%^&* _+\\");

	}

	void TearDown() override 
	{
  	    delete h;
	    delete a;
	    delete b;
	    delete c;
	    delete d;
	}
};

// Test for contstructor and hashing
TEST_F(HasherTest, ConstructorHashesPassword) 
{
    std::string expectedHash = "dcb11180414000";
    EXPECT_EQ(h->getHashed(), expectedHash);	
}

// Test for retrival of orginal password
TEST_F(HasherTest, GetOriginalPassword) 
{
    EXPECT_EQ(h->getOriginal(), "testPassword123");
}

// Test for retrival of hashed password
TEST_F(HasherTest, GetHashedPassword)
{
    std::string hashedPassword = h->getHashed();
    EXPECT_FALSE(hashedPassword.empty());
}

//test to ensure small password lengths produce a hash of 16 characters
TEST_F(HasherTest, smallPassword)
{
    std::string smallPass = a->getHashed();
    int smallLength = smallPass.length();
    EXPECT_EQ(smallLength, 16);
}

//test to ensure large password lengths produce a hash of 16 characters
TEST_F(HasherTest, bigPassword)
{
    std::string bigPass = b->getHashed();
    int bigLength = bigPass.length();
    EXPECT_EQ(bigLength, 16);
}

//test to ensure that hasher works with numbers
TEST_F(HasherTest, checkNumbers)
{
    std::string expectedHash = "da70f39df6dde000";
    EXPECT_EQ(c->getHashed(),expectedHash);
}

//test to ensure hasher works with special characters
TEST_F(HasherTest, specialChars)
{
  std::string expectedHash = "ecfc8b2e3f745300";
  EXPECT_EQ(d->getHashed(), expectedHash);
}

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
