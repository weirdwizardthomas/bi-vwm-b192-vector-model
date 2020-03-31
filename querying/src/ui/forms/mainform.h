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
#include <src/database/Document.h>

namespace Ui {
    class MainForm;
}


class MainForm : public QMainWindow {
Q_OBJECT
public:
    explicit MainForm(QWidget *parent = nullptr);

    ~MainForm() override;

    /**
     * Diplays all available documents in @see documentsList
     * @param documents List of document names to display
     * @return self
     */
    MainForm &setAvailableDocuments(const std::vector<Document> &documents);

    /**
     * Displays the results in the @see resultsList
     * @param results Results to display
     * @return self
     */
    MainForm &setResults(const std::vector<std::string> &results);

    /**
     * Loads and opens a text document
     * @param document Document path to display
     * @return self
     */
    MainForm &setOpenedDocument(const Document &document);

private:
    Ui::MainForm *UI;
    QSystemTrayIcon trayIcon;

    QAction *settingsAction; /**< ? */

    QListWidget *documentsList;/**<List view of documents */
    QListWidget *resultsList;/**<List view of results - documents that are the result of the query*/
    QTextBrowser *openedDocument; /**<Browser for the currently opened document*/

    void setupUi();

private slots:

    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

};


#endif // MAINFORM_H
