/* Name: Zoe Ellis
 * Course: CS455
 * Date: 11/26/2024
 * Description: This program is a header file
 * 		for sbomApplication.cpp
 */
#ifndef SBOMAPPLICATION_H
#define SBOMAPPLICATION_H

#include "signIn.h"

#include <Wt/WApplication.h>

class SBOMApplication : public Wt::WApplication {
public:
  SBOMApplication() = delete;
  explicit SBOMApplication(const Wt::WEnvironment &env);

private:
  void initializeApp();
};

#endif // SBOMAPPLICATION_H
