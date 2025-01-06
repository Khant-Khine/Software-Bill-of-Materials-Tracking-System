/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/26/2024
 * Collaborators: Akashdeep Singh
 * Description: This program implements a simple web-based 'Sign Up'
 * 		interface using the Wt C++ web toolkit.
 */

#include "signUp.h"
#include "signIn.h"

SignUp::SignUp(Wt::WApplication *app) : app(app) {
  auto container = this->addWidget(std::make_unique<Wt::WContainerWidget>());
  container->addWidget(std::make_unique<Wt::WText>("<h1>Sign Up</h1>"));
  container->setStyleClass("wrapper");

  container->addWidget(std::make_unique<Wt::WBreak>());
  auto signUpContainer =
      container->addWidget(std::make_unique<Wt::WContainerWidget>());
  signUpContainer->setStyleClass("auth-form");

  signUpContainer->addWidget(std::make_unique<Wt::WText>("Username: "));
  createUserEdit =
      signUpContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  createUserEdit->setPlaceholderText("Enter Username");
  createUserEdit->setFocus();
  createEmailEdit =
      signUpContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  createEmailEdit->setPlaceholderText("Enter Email");

  signUpContainer->addWidget(std::make_unique<Wt::WBreak>());

  signUpContainer->addWidget(std::make_unique<Wt::WText>("Password:  "));
  createPasswordEdit =
      signUpContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  createPasswordEdit->setPlaceholderText("Enter Password");
  confirmPasswordEdit =
      signUpContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  confirmPasswordEdit->setPlaceholderText("Confirm Password");

  signUpContainer->addWidget(std::make_unique<Wt::WBreak>());

  auto signUpButton = signUpContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Create Account"));
  signUpMessage = signUpContainer->addWidget(std::make_unique<Wt::WText>());
  signUpButton->clicked().connect(this, &SignUp::submitSignUp);

  signUpContainer->addWidget(std::make_unique<Wt::WBreak>());

  auto backButton =
      container->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));
  backButton->setStyleClass("link");
  backButton->clicked().connect(this, &SignUp::cancelSignUp);
}

// Placeholders
void SignUp::submitSignUp() {
  std::string username = createUserEdit->text().toUTF8();
  std::string email = createEmailEdit->text().toUTF8();
  std::string password = createPasswordEdit->text().toUTF8();
  std::string confirmPassword = confirmPasswordEdit->text().toUTF8();

  if (username.empty() || email.empty() || password.empty() ||
      confirmPassword.empty()) {
    signUpMessage->setText("All fields are required.");
    return;
  }

  if (password != confirmPassword) {
    signUpMessage->setText("Passwords do not match.");
    return;
  }

  Database db("../../src/model/sbomDatabase.db");
  std::string criteria = "username = '" + username + "'";
  std::string existingUser = db.retrieveRecord("User", criteria);

  if (!existingUser.empty()) {
    signUpMessage->setText("Username already exists.");
    return;
  }

  // Hash the password
  hasher hashObj(password);
  std::string hashedPassword = hashObj.getHashed();

  // Insert new user into the database
  std::string record =
      "'" + username + "', '" + hashedPassword + "', '" + email + "'";
  if (db.insertRecord("User", record)) {
    signUpMessage->setText("Account created successfully!");
  } else {
    signUpMessage->setText("Error creating account. Please try again.");
  }
}

void SignUp::cancelSignUp() {
  app->root()->clear();
  app->root()->addWidget(std::make_unique<SignIn>(app));
}
