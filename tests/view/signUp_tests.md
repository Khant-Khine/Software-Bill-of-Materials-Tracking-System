# Test Descriptions for signUp.h and signUp.cpp
* Tests done by: Zoe Ellis
	observed by: Jacob Pearson
## Unit Tests
	1. Test: Submit - Empty Fields
		* Description: Verifies that the appropriate validation message (All Fields Required) is displayed when username, email, or password fields are left empty
		* Test Cases:
			- Leave different combinations of input fields empty
			- Attempt to submit the form
			- Verify that the correct message (All Fields Required) is displayed
		
	2. Test: Submit - Passwords Do Not Match
		* Description: Verifies that the appropriate validation message (Passwords Do Not Match) is displayed when password != confirm Password
		* Test Case:
			- Test where "confirm password" does not match "password"
			- Attempt to submit the form
			- Verify that the correct message (Passwords do not match) is displayed
		* Test Case:
			- Test where "confirm password" and "password" are equal
			- Attempt to submit the form
			- Verify other critera for Successful submission
	
		
	3. Test: Submit - Successful Submission
		* Description: Verifies the appropriate validation message (Successful submission) is displayed
		* Test Cases:
			- Input a valid username, email, and matching pasword-confirm password
			- Attempt to submit the form
			- Verify that the correct message (successful submission) is displayed
	
	4. Test: Redirect to Sign-In Page
		* Description: Verifies that when "Cancel" Button is clicked, the user is redirected to the sign-in page
		* Test Case:
			- Click "Cancel" Button
			- Verify the application navigates to Sign-In page
			
## Integration Tests
	1. Test: Integration between SignUp Interface and User Management
		* Description: Verifies that the SignIn form correctly integrates with the User Management (database, hashing) subsystem
		* Test Case:
			- Insert a new record into the User Table using SignUp interface
			- Attempt to login using those Credentials
			- Verify that the login is Successful
		* Test Case: 
			- Using a record from the User Table, attempt to login with an incorrect password
			- Verify that the correct message (Invalid User) is displayed 
	