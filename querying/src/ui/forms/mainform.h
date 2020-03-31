#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include <string>
#include <vector>
#include <QtWidgets/QListView>
#include <QtCore/QStringListModel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextBrowser>

namespace Ui {
    class MainForm;
}


class MainForm : public QMainWindow {
Q_OBJECT
public:
    explicit MainForm(QWidget *parent = nullptr);

    ~MainForm() override;

    MainForm &setAvailableDocuments(const std::vector<std::string> &documents);

    MainForm &setResults(const std::vector<std::string> &results);

    MainForm &setOpenedDocument(const std::string &documentPath);

private:
    Ui::MainForm *UI;
    QSystemTrayIcon trayIcon;

    QAction *settingsAction;

    QListWidget *documentsList;
    QListWidget *resultsList;
    QTextBrowser *openedDocument;

    void setupUi();

private slots:

    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

};


#endif // MAINFORM_H
