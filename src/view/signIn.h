/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/17/2024
 * Last Edited Date: 11/26/2024
 * Collaborators:
 * Description: This program is a header file for signIn.cpp.
 *		This program implements a simple web-based 'Sign In'
 *		interface using the Wt C++ web toolkit.
 */

#ifndef SBOM_SIGNIN_H
#define SBOM_SIGNIN_H

#include "authManager.h"
#include "database.h"
#include "hashing.h"

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
class SignIn : public Wt::WContainerWidget {
public:
  SignIn(Wt::WApplication *app);

private:
  Wt::WApplication *app;

  Wt::WLineEdit *userEdit;
  Wt::WLineEdit *passwordEdit;
  Wt::WText *login;

  void submitLogin();
  void displaySignUp();
};

#endif
