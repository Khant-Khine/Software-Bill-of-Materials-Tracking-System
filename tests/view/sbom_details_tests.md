# Test Descriptions for signUp.h and signUp.cpp
* Tests done by: Zoe Ellis
	observed by: Jacob Pearson
## Unit Tests
		1. Test: Open Dialog
		* Description: Ensures that addComponent(), editComponent(), and deleteComponent() initialize and display the appropriate respective dialog
		* Test Cases:
			- Click Button (Ex. Rename SBOM)
			- Verify that the correct dialog is opened
		
	2. Test: Add Component
		* Description: Verifies that addComponent() dialog demonstrates the appropriate behavior when interacted with 
		* Test Case:
			- Test "Cancel" Button
			- Verify that dialog is closed and that no changes have been saved
		* Test Case:
			- Test Name Field's Required Property
			- Leave Name Field Empty
			- Attempt to submit changes using "Add" Button
			- Verify that the correct error message is displayed (Name Required)
		* Test Case:
			- Enter Name in the Component Name Field
			- Attempt to submit changes using "Add" Button
			- Verify that the dialog has been closed and that the component has been added to the table
	
	2. Test: Edit Component
		* Description: Verifies that editComponent() dialog demonstrates the appropriate behavior when interacted with 
		* Test Case:
			- Without selecting an SBOM, click "Edit Component" Button
			- Verify that the dialog does not open
		* Test Case:
			- Select an SBOM
			- Click "Edit Component" Button
			- Verify that the correct dialog is opened
		* Test Case:
			- Test "Cancel" Button
			- Verify that dialog is closed and that no changes have been saved
		* Test Case:
			- Leave Component Name Field Empty
			- Attempt to submit changes using "Save" Button
			- Verify that the correct error message is displayed (Name Required)
		* Test Case:
			- Enter Component Name in the Name Field
			- Attempt to submit changes using "Save" Button
			- Verify that the dialog has been closed and that the appropriate changes have been made to the table
		
	3. Test: Delete Component
		* Description: Verifies that deleteComponent() dialog demonstrates the appropriate behavior when interacted with 
		* Test Case:
			- Without selecting an SBOM, click "Delete Component" Button
			- Verify that the dialog does not open
		* Test Case:
			- Select a component
			- Click "Delete Component" Button
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
			- Verify that the dialog has been closed and that the correct component has been deleted
	
	5. Test: Return to Library Button
		* Description: Verifies that "Return to Library" Button will redirect user to SBOM_library
		* Test Case:
			- Click "Return to Library" Button
			- Verify that user is redirected to SBOM_library
			
## Integration Tests
	1. Test: Integration between SBOMDetails Interface and SBOM Management and Database
		* Description: Verifies that SBOMDetails correctly integrates with SBOM Management and Database subsystems
		* Test Case:
			- Open SBOMDetails Interface
			- Confirm that table information matches database records for the selected SBOM
		* Test Case:
			- Add a new component
			- Select component
			- Click "Edit Component" Button 
			- Fill and Submit the Form
			- Open log.txt to confirm that the correct methods were called and that changes were properly recorded
		* Test Case: 
			- Select component
			- Click "Delete Component" Button
			- Confirm and Submit the Form
			- Open log.txt to confirm that the correct methods were called and that changes were properly recorded
