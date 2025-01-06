# View source code

## signIn.h and signIn.cpp
	* Implements a simple web-based 'Sign In' page using the Wt C++ Web Toolkit
	* Main interface includes:
		- Username and Password fields
		- Login button with authentication logic
		- Button to redirect to Sign-Up page
	* Passwords are hashed using the Hasher class prior to authentication
	* Credentials are validated using authManager
	* Successful login clears current interface and loads the SBOM_library
	
## signUp.h and signUp.cpp
	* Implements web-based 'Sign Up' page using the Wt C++ Web Toolkit
	* Main interface includes:
		- Username, Email, and Password fields
		- "Create Account" button for submission
		- Button to redirect to Sign-In page
		- Feedback on validation errors and successful submission
	* Passwords are hashed with the hasher class
	* Database handles user validation and record insertion
	
## sbom_library.h and sbom_library.cpp
	* Implements web-based interface using the Wt C++ Web Toolkit for users to create, rename, delete, and export SBOMs
	* Main interface includes:
		- Table display of SBOM records
		- "Create" "Rename" "Delete" "View" and "Export" Buttons 
		- Button to redirect to Sign-Up page
	* "Create" "Rename" and "Delete" opens the respective dialog to validate and execute changes to the Database
	* "View" redirects to SBOMDetails page for selected SBOM
	* "Export" exports SBOM Details to .csv format using ExportSubSystem

## sbom_details.h and sbom_details.cpp
	*Implements web-based interface using the Wt C++ Web Toolkit for users to create, edit, and delete components for a selected SBOM
	* Main interface includes:
		- Table display of SBOM component records
		- "Create" "Edit" and "Delete" Buttons
		- Button to redirect to SBOM_library
	* "Create" "Edit" and "Delete" opens the respective dialog to validate and execute changes to the Database
	
## sbomApplication.h and sbomApplication.cpp
	* Implements SBOMApplication class, which serves as the main point of entry for the front-end application

## driver.cpp
	* Initializes Wt environment and launches the application
	