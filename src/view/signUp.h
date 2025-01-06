/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/26/2024
 * Collaborators:
 * Description: This program is a header file for signUp.cpp.
 *		This program implements a simple web-based 'Sign Up'
 *		interface using the Wt C++ web toolkit.
 */

#ifndef SBOM_SIGNUP_H
#define SBOM_SIGNUP_H

#include "database.h"
#include "hashing.h"

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class SignUp : public Wt::WContainerWidget {
public:
  SignUp(Wt::WApplication *app);

private:
  Wt::WApplication *app;

  Wt::WLineEdit *createUserEdit;
  Wt::WLineEdit *createEmailEdit;
  Wt::WLineEdit *createPasswordEdit;
  Wt::WLineEdit *confirmPasswordEdit;
  Wt::WText *signUpMessage;

  void cancelSignUp();
  void submitSignUp();
};

#endif
