/*
 * Name: Austin Davis
 * Course: CS455
 * Date: 11/22/2024
 * Collaborators: Zoe Ellis
 * Description: This program is the header file for
 *      sbom_details.cpp
 */
#ifndef SBOM_DETAILS_H
#define SBOM_DETAILS_H

#include "sbom_library.h"

#include <Wt/WApplication.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include <Wt/WText.h>
#include <string>

class SBOMDetails : public Wt::WContainerWidget {
public:
  SBOMDetails(Wt::WApplication *app);

private:
  Wt::WApplication *app;
  SBOM testSBOM; // Declare the SBOM object as a member

  void addComponent();
  void editComponent();
  void deleteComponent();
  void returnToLibrary();

  Wt::WTableView *tableView;
  Wt::WTableView *changeLog;
  std::shared_ptr<Wt::WStandardItemModel> model;
  std::shared_ptr<Wt::WStandardItemModel> clModel;
};

#endif // SBOM_DETAILS_H
