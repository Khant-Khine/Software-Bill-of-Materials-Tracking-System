# Test Descriptions for signIn.h and signIn.cpp
* Tests done by: Zoe Ellis
	observed by: Jacob Pearson
## Unit Tests
	1. Test: Submit Login - Empty Fields
		* Description: Verifies that the appropriate validation message (All Fields Required) is displayed when username or password fields are left empty
		* Test Cases:
			- Leave different combinations of input fields empty
			- Attempt to submit the form
			- Verify that the correct message (All Fields Required) is displayed
		
	2. Test: Submit Login - Invalid Credentials
		* Description: Verifies that the appropriate validation message (Invalid User) is displayed when the user submits invalid credentials
		* Test Cases:
			- Test different combinations of valid/invalid user Credentials (Ex. Correct Username:Incorrect Password)
			- Attempt to submit the form
			- Verify that the correct message (Invalid User) is displayed
		
	3. Test: Submit Login - Successful Login
		* Description: Verifies that the SBOM_library is loaded when the user submits valid Credentials
		* Test Cases:
			- Input a valid username-password
			- Attempt to submit the form
			- Verify that the correct interface (SBOM_library) is loaded
	
	4. Test: Redirect to Sign-Up Page
		* Description: Verifies that when "Sign-Up" Button is clicked, the user is redirected to the sign-up page
		* Test Case:
			- Click "Sign-Up" Button
			- Verify the application navigates to Sign-Up page
			
## Integration Tests
	1. Test: Integration between SignIn Interface and User Management
		* Description: Verifies that the SignIn form correctly integrates with the User Management (authManager, database, hashing) subsystem
		* Test Case:
			- Insert a new record into the User Table
			- Attempt to login using those Credentials
			- Verify that the login is Successful
		* Test Case: 
			- Using a record from the User Table, attempt to login with an incorrect password
			- Verify that the correct message (Invalid User) is displayed 
	