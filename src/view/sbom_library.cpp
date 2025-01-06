/*
 * Name: Zoe Ellis
 * Course: CS455
 * Date: 11/26/2024
 * Last Edited Date: 12/04/2024
 * Collaborators: Akashdeep Singh
 * Description: This program implements a simple web-based
 *              interface using the Wt C++ web toolkit for
 *              users to create, rename, delete, and export
 *              SBOMs
 */

#include "sbom_library.h"

SBOM_library::SBOM_library(Wt::WApplication *app) : app(app) {
  auto container = this->addWidget(std::make_unique<Wt::WContainerWidget>());
  container->addWidget(std::make_unique<Wt::WText>("<h1>SBOM Library</h1>"));
  container->setStyleClass("center-form");

  container->addWidget(std::make_unique<Wt::WBreak>());

  auto logoutButton =
      container->addWidget(std::make_unique<Wt::WPushButton>("logout"));
  logoutButton->setStyleClass("logout-button");
  logoutButton->clicked().connect(this, &SBOM_library::logout);

  auto actionsContainer =
      container->addWidget(std::make_unique<Wt::WContainerWidget>());
  actionsContainer->setStyleClass("actions-ribbon");

  auto createButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Create SBOM"));
  createButton->clicked().connect(
      this, &SBOM_library::createSBOM); // either opens new row to edit or form

  auto renameButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Rename SBOM"));
  renameButton->clicked().connect(
      this, &SBOM_library::renameSBOM); // allows row edit or opens form

  auto deleteButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Delete SBOM"));
  deleteButton->clicked().connect(
      this, &SBOM_library::deleteSBOM); // opens confirm box

  auto detailsButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("View Details"));
  detailsButton->clicked().connect(this, &SBOM_library::viewSBOMDetails);

  auto exportButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Export SBOM"));
  exportButton->clicked().connect(
      this, &SBOM_library::exportSBOM); // exports selected SBOM to CSV

  actionsContainer->addWidget(std::make_unique<Wt::WBreak>());

  library = container->addWidget(std::make_unique<Wt::WTableView>());

  record = std::make_shared<Wt::WStandardItemModel>(0, 2);
  library->setModel(record);

  record->setHeaderData(0, Wt::Orientation::Horizontal, "SBOM");
  record->setHeaderData(1, Wt::Orientation::Horizontal, "Last Edited");

  library->setColumnResizeEnabled(false);
  library->setAlternatingRowColors(true);
  library->setColumnWidth(0, 500);
  library->setColumnWidth(1, 500);
  library->setRowHeight(28);
  library->setHeaderHeight(28);
  library->setSelectionMode(Wt::SelectionMode::Single);
  message = container->addWidget(std::make_unique<Wt::WText>());
}

void SBOM_library::createSBOM() {

  // Create the dialog
  Wt::WDialog *dialog = new Wt::WDialog("Create SBOM");
  dialog->addStyleClass("dialogBox");

  Wt::WContainerWidget *dialogContainer = dialog->contents();
  dialogContainer->addWidget(std::make_unique<Wt::WText>("Enter the SBOM ID:"));

  Wt::WLineEdit *sbomIdInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  sbomIdInput->setPlaceholderText("SBOM ID");

  // Buttons for dialog
  Wt::WPushButton *createButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Create"));
  Wt::WPushButton *cancelButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));

  createButton->clicked().connect([=]() {
    std::string sbomId = sbomIdInput->text().toUTF8();
    if (!sbomId.empty()) {
      SBOM newSbom(sbomId);
      sbomList.push_back(newSbom);
      // Populates column with time and date
      time_t currTime = time(0);
      char *currentTime = ctime(&currTime);
      std::string timestamp = std::string(currentTime);
      timestamp.pop_back();

      // Add new SBOM to the table
      int rowIndex = record->rowCount();
      record->insertRows(rowIndex, 1);
      record->setData(rowIndex, 0, sbomId);
      record->setData(rowIndex, 1, timestamp);

      message->setText("SBOM created successfully!");
    } else {
      message->setText("Please provide a valid SBOM ID.");
    }
    dialog->accept();
  });

  cancelButton->clicked().connect([=]() {
    dialog->reject(); // Close the dialog without any action
  });

  dialog->show();
}

void SBOM_library::renameSBOM() {
  // Checks for selected row
  auto selectedIndexes = library->selectionModel()->selectedIndexes();
  if (selectedIndexes.empty()) { // Use empty() instead of isEmpty()
    message->setText("Please select an SBOM to rename.");
    return;
  }

  // Get the row index of the selected SBOM
  int selectedRow = selectedIndexes.begin()->row(); // access first element

  // Confirm SBOM object corresponding to the row
  if (selectedRow >= sbomList.size()) {
    message->setText("Invalid row selected.");
    return;
  }

  // Create a dialog for renaming the SBOM
  Wt::WDialog *dialog = new Wt::WDialog("Rename SBOM");
  dialog->addStyleClass("dialogBox");

  Wt::WContainerWidget *dialogContainer = dialog->contents();
  dialogContainer->addWidget(
      std::make_unique<Wt::WText>("Enter the new SBOM ID:"));

  Wt::WLineEdit *newSbomIdInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  newSbomIdInput->setPlaceholderText("New SBOM ID");

  Wt::WPushButton *renameButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Rename"));
  Wt::WPushButton *cancelButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));

  renameButton->clicked().connect([=]() {
    std::string newSbomId =
        newSbomIdInput->text().toUTF8(); // Get the entered new ID
    if (!newSbomId.empty()) {
      // Access the SBOM object corresponding to the selected row
      SBOM &selectedSBOM = sbomList[selectedRow];

      // Use the setSBOM_ID method to change the SBOM ID
      selectedSBOM.setSBOM_ID(newSbomId);

      // Log Creation
      time_t currTime = time(0);
      char *currentTime = ctime(&currTime);
      std::string timestamp = std::string(currentTime);
      timestamp.pop_back();

      // Update the table with the new SBOM ID
      record->setData(selectedRow, 0, newSbomId);
      record->setData(selectedRow, 1, timestamp);

      message->setText("SBOM renamed successfully!");
    } else {
      message->setText("Please provide a valid SBOM ID.");
    }
    dialog->accept();
  });

  cancelButton->clicked().connect([=]() { dialog->reject(); });

  dialog->show();
}

void SBOM_library::deleteSBOM() {
  auto selectedIndexes = library->selectionModel()->selectedIndexes();
  if (selectedIndexes.empty()) {
    message->setText("Please select an SBOM to delete.");
    return;
  }

  int selectedRow = selectedIndexes.begin()->row();

  if (selectedRow >= sbomList.size()) {
    message->setText("Invalid row selected.");
    return;
  }

  Wt::WDialog *dialog = new Wt::WDialog("Delete SBOM");
  dialog->addStyleClass("dialogBox");

  // Set up the form elements
  Wt::WContainerWidget *dialogContainer = dialog->contents();
  dialogContainer->addWidget(std::make_unique<Wt::WText>(
      "Are you sure you would like to delete the selected SBOM?"));

  Wt::WCheckBox *checkDelete = dialogContainer->addWidget(
      std::make_unique<Wt::WCheckBox>("Yes, I am sure."));
  checkDelete->setChecked(false);

  Wt::WPushButton *deleteButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
  Wt::WPushButton *cancelButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));

  deleteButton->clicked().connect([=]() {
    if (checkDelete->isChecked()) {
      sbomList.erase(sbomList.begin() +
                     selectedRow); // remove SBOM from data structure

      record->removeRow(selectedRow); // remove SBOM from table

      message->setText("SBOM deleted successfully!");

      dialog->accept();
    }
  });

  cancelButton->clicked().connect([=]() { dialog->reject(); });

  dialog->show();
}

// Note: SBOM will not be written to .csv if it has 0 components
void SBOM_library::exportSBOM() {
  // Get the selected row from the table
  auto selectedIndexes = library->selectionModel()->selectedIndexes();
  if (selectedIndexes.empty()) {
    message->setText("Please select an SBOM to export.");
    return;
  }

  // Get the row index of the selected SBOM
  int selectedRow =
      selectedIndexes.begin()->row(); // Use iterator to access first element

  // Ensure there is an SBOM object corresponding to the row
  if (selectedRow >= sbomList.size()) {
    message->setText("Invalid row selected.");
    return;
  }

  const SBOM &exportedSBOM = sbomList[selectedRow];
  std::string csvData = toCSV(exportedSBOM);
  std::string filename = "exported_sbom_" + exportedSBOM.getSBOM_ID() + ".csv";
  exportToCSV(filename, csvData);

  message->setText("SBOM exported to file: " + filename);
}

void SBOM_library::viewSBOMDetails() {
  // Get the selected row from the table
  auto selectedIndexes = library->selectionModel()->selectedIndexes();
  if (selectedIndexes.empty()) {
    message->setText("Please select an SBOM to view details.");
    return;
  }

  // Get the row index of the selected SBOM
  int selectedRow = selectedIndexes.begin()->row();
  if (selectedRow >= record->rowCount()) {
    message->setText("Invalid selection.");
    return;
  }

  // placeholder navigation
  app->root()->clear();
  app->root()->addWidget(std::make_unique<SBOMDetails>(app));
}

void SBOM_library::logout() {
  app->root()->clear();
  app->root()->addWidget(std::make_unique<SignIn>(app));
}
