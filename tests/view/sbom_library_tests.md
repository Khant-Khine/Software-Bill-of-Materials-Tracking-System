# Test Descriptions for signUp.h and signUp.cpp
* Tests done by: Zoe Ellis
	observed by: Jacob Pearson
## Unit Tests
	1. Test: Open Dialog
		* Description: Ensures that createSBOM(), renameSBOM(), and deleteSBOM() initialize and display the appropriate respective dialog
		* Test Cases:
			- Click Button (Ex. Rename SBOM)
			- Verify that the correct dialog is opened
		
	2. Test: Create SBOM
		* Description: Verifies that createSBOM() dialog demonstrates the appropriate behavior when interacted with 
		* Test Case:
			- Test "Cancel" Button
			- Verify that dialog is closed and that no changes have been saved
		* Test Case:
			- Leave SBOM ID Field Empty
			- Attempt to submit changes using "Create" Button
			- Verify that the correct error message is displayed (SBOM ID Required)
		* Test Case:
			- Enter SBOM ID in the SBOM ID Field
			- Attempt to submit changes using "Create" Button
			- Verify that the dialog has been closed and that the appropriate changes have been made to the table
	
	2. Test: Rename SBOM
		* Description: Verifies that renameSBOM() dialog demonstrates the appropriate behavior when interacted with 
		* Test Case:
			- Without selecting an SBOM, click "Rename SBOM" Button
			- Verify that the correct error message is displayed (Please select a valid SBOM)
		* Test Case:
			- Select an SBOM
			- Click "Rename SBOM" Button
			- Verify that the correct dialog is opened
		* Test Case:
			- Test "Cancel" Button
			- Verify that dialog is closed and that no changes have been saved
		* Test Case:
			- Leave SBOM ID Field Empty
			- Attempt to submit changes using "Save" Button
			- Verify that the correct error message is displayed (SBOM ID Required)
		* Test Case:
			- Enter SBOM ID in the SBOM ID Field
			- Attempt to submit changes using "Save" Button
			- Verify that the dialog has been closed and that the appropriate changes have been made to the table
		
	3. Test: Delete SBOM
		* Description: Verifies that deleteSBOM() dialog demonstrates the appropriate behavior when interacted with 
		* Test Case:
			- Without selecting an SBOM, click "Delete SBOM" Button
			- Verify that the correct error message is displayed (Please select a valid SBOM)
		* Test Case:
			- Select an SBOM
			- Click "Delete SBOM" Button
			- Verify that the correct dialog is opened
		* Test Case:
			- Test "No" Button
			- Verify that dialog is closed and that no changes have been saved
		* Test Case:
			- Uncheck confirmation box 
			- Click "Yes" Button to Delete
			- Verify that no action occurs
		*Test Case:
			- Check confirmation box
			- Click "Yes" Button to Delete
			- Verify that the dialog has been closed and that the SBOM has been deleted
			
	4. Test: View SBOM Details
		* Description: Verifies that "view details" opens the correct details page for a selected SBOM
		* Test Case:
			- Without selecting an SBOM, click "View Details" Button
			- Verify that the correct error message is displayed (Please select a valid SBOM)
		* Test Case:
			- Select an SBOM
			- Click "View Details" Button
			- Verify that the correct details page is opened 
			
	4. Test: Export SBOM
		* Description: Verifies that "Export SBOM" exports SBOM Details to .csv file
		* Test Case:
			- Without selecting an SBOM, click "Export SBOM" Button
			- Verify that the correct error message is displayed (Please select a valid SBOM)
		* Test Case:
			- Select an SBOM
			- Click "Export SBOM" Button
			- Verify that the file is saved with the correct name and contents
	
	5. Test: Logout Button
		* Description: Verifies that "Logout" Button will redirect user to sign-in page
		* Test Case:
			- Click "logout" Button
			- Verify that user is redirected to sign-in page
			
## Integration Tests
	1. Test: Integration between SBOM_library Interface and SBOM Management and Database
		* Description: Verifies that the SBOM_library correctly integrates with SBOM Management and Database subsystems
		* Test Case:
			- Open SBOM_library Interface
			- Confirm that table information matches database records
		* Test Case:
			- Create a New SBOM
			- Select SBOM
			- Click "Rename SBOM" Button 
			- Fill and Submit the Form
			- Open log.txt to confirm that the correct methods were called and that changes were properly recorded
		* Test Case: 
			- Select SBOM
			- Click "Delete SBOM" Button
			- Confirm and Submit the Form
			- Open log.txt to confirm that the correct methods were called and that changes were properly recorded
		* Test Case:
			- Select an SBOM
			- Click "Export SBOM" Button
			- Verify that the file is saved with the correct name and contents
	