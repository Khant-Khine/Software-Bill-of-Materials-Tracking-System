/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/26/2024
 * Collaborators:
 * Description: This program is a header file for sbom_library.cpp.
 */

#ifndef SBOM_LIBRARY_H
#define SBOM_LIBRARY_H

#include "ExportSubSystem.h"
#include "SBOM.h"
#include "sbom_details.h"
#include "signIn.h"

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include <Wt/WText.h>

class SBOM_library : public Wt::WContainerWidget {
public:
  SBOM_library(Wt::WApplication *app);

private:
  Wt::WApplication *app;

  Wt::WTableView *library;
  std::shared_ptr<Wt::WStandardItemModel> record;
  Wt::WText *message;
  std::vector<SBOM> sbomList;

  void createSBOM();
  void renameSBOM();
  void deleteSBOM();
  void exportSBOM();
  void viewSBOMDetails();
  void logout();
};

#endif
