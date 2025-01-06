/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/17/2024
 * Last Edited Date: 11/26/2024
 * Collaborators: Akashdeep Singh
 * Description: This program implements a simple web-based 'Sign In'
 * 		interface using the Wt C++ web toolkit.
 */

#include "signIn.h"
#include "sbom_library.h"
#include "signUp.h"

SignIn::SignIn(Wt::WApplication *app) : app(app) {
  auto container = this->addWidget(std::make_unique<Wt::WContainerWidget>());
  container->addWidget(std::make_unique<Wt::WText>("<h1>Sign In</h1>"));
  container->setStyleClass("wrapper");

  container->addWidget(std::make_unique<Wt::WBreak>());
  auto signInContainer =
      container->addWidget(std::make_unique<Wt::WContainerWidget>());
  signInContainer->setStyleClass("auth-form");

  signInContainer->addWidget(std::make_unique<Wt::WText>("Username: "));
  userEdit = signInContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  userEdit->setPlaceholderText("Enter Username");
  userEdit->setFocus();

  signInContainer->addWidget(std::make_unique<Wt::WBreak>());

  signInContainer->addWidget(std::make_unique<Wt::WText>("Password:  "));
  passwordEdit = signInContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  passwordEdit->setPlaceholderText("Enter Password");

  signInContainer->addWidget(std::make_unique<Wt::WBreak>());

  auto loginButton =
      signInContainer->addWidget(std::make_unique<Wt::WPushButton>("Login"));
  login = signInContainer->addWidget(std::make_unique<Wt::WText>());
  loginButton->clicked().connect(this, &SignIn::submitLogin);

  signInContainer->addWidget(std::make_unique<Wt::WBreak>());

  auto signUpButton =
      container->addWidget(std::make_unique<Wt::WPushButton>("Sign up"));
  signUpButton->setStyleClass("link");
  signUpButton->clicked().connect(this, &SignIn::displaySignUp);
}

// Placeholders
void SignIn::submitLogin() {
  std::string username = userEdit->text().toUTF8();
  std::string password = passwordEdit->text().toUTF8();

  if (username.empty() || password.empty()) {
    login->setText("All fields are required.");
    return;
  }

  // Hash the entered password
  hasher hashObj(password);
  std::string hashedPassword = hashObj.getHashed();

  // Authenticate user
  authManager auth;
  if (auth.authenticateUser(username, hashedPassword)) {
    login->setText("Login successful!");
    app->root()->clear();
    app->root()->addWidget(std::make_unique<SBOM_library>(app));
  } else {
    login->setText("Invalid username or password.");
  }
}

void SignIn::displaySignUp() {
  app->root()->clear();
  app->root()->addWidget(std::make_unique<SignUp>(app));
}
