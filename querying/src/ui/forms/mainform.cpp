#include "mainform.h"
#include "ui_mainform.h"

#include <QMenu>
#include <QToolButton>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

MainForm::MainForm(QWidget *parent) :
        QMainWindow(parent),
        UI(new Ui::MainForm),
        documentsList(new QListWidget()),
        resultsList(new QListWidget()),
        openedDocument(new QTextBrowser()) {
    setupUi();
}


MainForm::~MainForm() {
    delete UI;
    delete documentsList;
    delete resultsList;
    delete openedDocument;
}


void MainForm::setupUi() {
    UI->setupUi(this);

    setWindowIcon(QIcon(":/resources/main-icon.png"));
    setWindowTitle("Querying: Vector model of information retrieval");

    trayIcon.setIcon(QIcon(":/resources/main-icon.png"));
    trayIcon.show();

    connect(&trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    UI->statusBar->hide();

    UI->toolBar->setIconSize(QSize(24, 24));
    UI->toolBar->setFloatable(false);
    UI->toolBar->setMovable(false);
}


void MainForm::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        setVisible(!isVisible());
    } else if (reason == QSystemTrayIcon::Context) {
        QMenu menu;

        if (isVisible()) {
            menu.addAction("Minimize", this, SLOT(hide()));
        } else {
            menu.addAction("Restore", this, SLOT(show()));
        }

        menu.addAction(settingsAction);

        menu.addSeparator();
        menu.addAction("Quit", qApp, SLOT(quit()));
        menu.exec(QCursor::pos());
    }
}

MainForm &MainForm::setAvailableDocuments(const std::vector<Document> &documents) {
    QStringList dummy;

    for (const auto &doc : documents)
        dummy.append(QString(doc.name.data()));

    UI->documentsList->addItems(dummy);

    return *this;
}

MainForm &MainForm::setResults(const std::vector<std::string> &results) {
    QStringList dummy;

    for (const auto &result : results)
        dummy.append(QString(result.data()));

    UI->resultsList->addItems(dummy);

    return *this;
}

MainForm &MainForm::setOpenedDocument(const Document &document) {
    QString path = QString::fromStdString(document.name);

    QFile file(path);

    file.open(QIODevice::ReadOnly);
    UI->documentBrowser->setText(QTextStream(&file).readAll());
    file.close();


    return *this;
}
