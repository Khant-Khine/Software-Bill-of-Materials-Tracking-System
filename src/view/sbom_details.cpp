/*
 * Name: Austin Davis
 * Course: CS455
 * Date: 11/22/2024
 * Last Edited Date: 12/04/2024
 * Collaborators: Zoe Ellis, Akashdeep Singh
 * Description: This program implements a web-based "SBOM Details"
 *      gui using the Wt C++ web toolkit
 */

#include "sbom_details.h"

SBOMDetails::SBOMDetails(Wt::WApplication *app)
    : app(app), testSBOM("SBOM_1") // Initialize testSBOM with a name
{
  auto container = this->addWidget(std::make_unique<Wt::WContainerWidget>());
  container->addWidget(std::make_unique<Wt::WText>("<h1>SBOM Details</h1>"));
  container->setStyleClass("center-form");

  auto returnButton = container->addWidget(
      std::make_unique<Wt::WPushButton>("Return to Library"));
  returnButton->setStyleClass("logout-button");
  returnButton->clicked().connect(this, &SBOMDetails::returnToLibrary);

  auto actionsContainer =
      container->addWidget(std::make_unique<Wt::WContainerWidget>());
  actionsContainer->setStyleClass("actions-ribbon");

  auto addButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Add Component"));
  addButton->clicked().connect(this, &SBOMDetails::addComponent);

  auto editButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Edit Component"));
  editButton->clicked().connect(this, &SBOMDetails::editComponent);

  auto deleteButton = actionsContainer->addWidget(
      std::make_unique<Wt::WPushButton>("Delete Component"));
  deleteButton->clicked().connect(this, &SBOMDetails::deleteComponent);

  tableView = container->addWidget(std::make_unique<Wt::WTableView>());
  model = std::make_shared<Wt::WStandardItemModel>(0, 4);
  tableView->setModel(model);

  model->setHeaderData(0, Wt::Orientation::Horizontal, "Name");
  model->setHeaderData(1, Wt::Orientation::Horizontal, "Version");
  model->setHeaderData(2, Wt::Orientation::Horizontal, "Hash");
  model->setHeaderData(3, Wt::Orientation::Horizontal, "Component ID");

  tableView->setSelectionMode(Wt::SelectionMode::Single);
  tableView->setColumnWidth(0, 250);
  tableView->setColumnWidth(1, 250);
  tableView->setColumnWidth(2, 250);
  tableView->setColumnWidth(3, 250);

  container->addWidget(std::make_unique<Wt::WText>("<h1>Change Log Tab</h1>"));

  // Create empty table for component changelog
  changeLog = container->addWidget(std::make_unique<Wt::WTableView>());
  clModel = std::make_shared<Wt::WStandardItemModel>(0, 2);
  changeLog->setModel(clModel);

  clModel->setHeaderData(0, Wt::Orientation::Horizontal, "Collaborator");
  clModel->setHeaderData(1, Wt::Orientation::Horizontal, "Description");

  changeLog->setColumnWidth(0, 500);
  changeLog->setColumnWidth(1, 500);
}

void SBOMDetails::addComponent() {
  // Create the dialog
  Wt::WDialog *dialog = new Wt::WDialog("Add Component");
  dialog->addStyleClass("dialogBox");

  Wt::WContainerWidget *dialogContainer = dialog->contents();

  // Create text fields for input
  dialogContainer->addWidget(
      std::make_unique<Wt::WText>("Enter component details:"));

  Wt::WLineEdit *nameInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  nameInput->setPlaceholderText("Name");

  Wt::WLineEdit *versionInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  versionInput->setPlaceholderText("Version");

  Wt::WLineEdit *hashInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  hashInput->setPlaceholderText("Hash");

  Wt::WLineEdit *componentIdInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  componentIdInput->setPlaceholderText("Component ID");

  // Create buttons for dialog actions
  Wt::WPushButton *addButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Add"));
  Wt::WPushButton *cancelButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));

  dialogContainer->addWidget(std::make_unique<Wt::WBreak>());

  Wt::WText *message =
      dialogContainer->addWidget(std::make_unique<Wt::WText>());

  // Add button click handler
  addButton->clicked().connect([=]() {
    std::string name = nameInput->text().toUTF8();
    std::string version = versionInput->text().toUTF8();
    std::string hash = hashInput->text().toUTF8();
    std::string componentId = componentIdInput->text().toUTF8();

    // Validate that the name is not empty
    if (name.empty()) {
      message->setText("Component Name is Required.");
      return;
    }

    // Use the SBOM member to add the component
    testSBOM.addComp(name, version, hash, componentId);

    // Add the component data to the table
    int rowIndex = model->rowCount();
    model->insertRows(rowIndex, 1);
    model->setData(rowIndex, 0, name);
    model->setData(rowIndex, 1, version);
    model->setData(rowIndex, 2, hash);
    model->setData(rowIndex, 3, componentId);

    dialog->accept();
  });

  // Cancel button click handler
  cancelButton->clicked().connect([=]() {
    dialog->reject(); // Close the dialog
  });

  dialog->show();
}

void SBOMDetails::editComponent() {
  // Checks for selected component
  auto selectedIndexes = tableView->selectionModel()->selectedIndexes();
  if (selectedIndexes.empty()) {
    return;
  }

  int selectedRow = selectedIndexes.begin()->row();

  Wt::WDialog *dialog = new Wt::WDialog("Edit Component");
  dialog->addStyleClass("dialogBox");

  Wt::WContainerWidget *dialogContainer = dialog->contents();
  dialogContainer->addWidget(
      std::make_unique<Wt::WText>("Edit Component Details: "));

  std::string currentName = testSBOM.getCompName(selectedRow);
  std::string currentVersion = testSBOM.getCompVersions(selectedRow);
  std::string currentHash = testSBOM.getCompHashes(selectedRow);
  std::string currentComponentId = testSBOM.getCompIds(selectedRow);

  // Input fields for the current values
  Wt::WLineEdit *nameInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  nameInput->setText(currentName);

  Wt::WLineEdit *versionInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  versionInput->setText(currentVersion);

  Wt::WLineEdit *hashInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  hashInput->setText(currentHash);

  Wt::WLineEdit *componentIdInput =
      dialogContainer->addWidget(std::make_unique<Wt::WLineEdit>());
  componentIdInput->setText(currentComponentId);

  // Buttons for dialog actions
  Wt::WPushButton *saveButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Save"));
  Wt::WPushButton *cancelButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));

  dialogContainer->addWidget(std::make_unique<Wt::WBreak>());

  Wt::WText *message =
      dialogContainer->addWidget(std::make_unique<Wt::WText>());
  saveButton->clicked().connect([=]() {
    std::string newName = nameInput->text().toUTF8();
    std::string newVersion = versionInput->text().toUTF8();
    std::string newHash = hashInput->text().toUTF8();
    std::string newComponentId = componentIdInput->text().toUTF8();

    // Validate that the name is not empty
    if (newName.empty()) {
      message->setText("Component Name is Required.");
      return;
    }

    // Only update the model if the new values are different
    if (newName != currentName) {
      model->setData(model->index(selectedRow, 0), newName);
      testSBOM.setCompName(selectedRow, newName);
    }

    if (newVersion != currentVersion) {
      model->setData(model->index(selectedRow, 1), newVersion);
      testSBOM.setCompVersions(selectedRow, newVersion);
    }

    if (newHash != currentHash) {
      model->setData(model->index(selectedRow, 2), newHash);
      testSBOM.setCompHashes(selectedRow, newHash);
    }

    if (newComponentId != currentComponentId) {
      model->setData(model->index(selectedRow, 3), newComponentId);
      testSBOM.setCompIds(selectedRow, newComponentId);
    }

    dialog->accept();
  });

  cancelButton->clicked().connect([=]() { dialog->reject(); });

  dialog->show();
}

void SBOMDetails::deleteComponent() {
  // checks for selected component
  auto selectedIndexes = tableView->selectionModel()->selectedIndexes();
  if (selectedIndexes.empty()) {
    return; // No component selected
  }

  int selectedRow = selectedIndexes.begin()->row();

  std::string name = testSBOM.getCompName(selectedRow);

  Wt::WDialog *dialog = new Wt::WDialog("Delete Component");
  dialog->addStyleClass("dialogBox");

  Wt::WContainerWidget *dialogContainer = dialog->contents();
  dialogContainer->addWidget(std::make_unique<Wt::WText>(
      "Are you sure you want to delete this component?"));

  Wt::WCheckBox *checkDelete = dialogContainer->addWidget(
      std::make_unique<Wt::WCheckBox>("Yes, I am sure."));
  checkDelete->setChecked(false);

  Wt::WPushButton *confirmButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("Yes"));
  Wt::WPushButton *cancelButton =
      dialogContainer->addWidget(std::make_unique<Wt::WPushButton>("No"));

  confirmButton->clicked().connect([=]() {
    if (checkDelete->isChecked()) {
      // Deletes component
      testSBOM.delComp(name);

      // Removes component from the table
      model->removeRow(selectedRow);

      dialog->accept();
    }
  });

  cancelButton->clicked().connect([=]() { dialog->reject(); });

  dialog->show();
}

void SBOMDetails::returnToLibrary() {
  app->root()->clear();
  app->root()->addWidget(std::make_unique<SBOM_library>(app));
}
