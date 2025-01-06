/* Name: Zoe Ellis
 * Course: CS455
 * Date: 11/26/2024
 * Description: This program implements the SBOMApplication class, which
 * 		serves as the main point of entry for the SBOM front-end
 * 		application.
 */
#include "sbomApplication.h"
SBOMApplication::SBOMApplication(const Wt::WEnvironment &env)
    : WApplication(env) {

  setTitle("SBOM Application");
  useStyleSheet("style.css");

  root()->addWidget(std::make_unique<SignIn>(this));
}
