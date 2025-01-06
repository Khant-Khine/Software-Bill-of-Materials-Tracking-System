/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/17/2024
 * Collaborators:
 * Description: This program initializes the Wt environment
 * 		and launches the application
 */

#include "sbomApplication.h"
#include <Wt/WApplication.h>

int main(int argc, char **argv) {
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
    return std::make_unique<SBOMApplication>(env);
  });
}
