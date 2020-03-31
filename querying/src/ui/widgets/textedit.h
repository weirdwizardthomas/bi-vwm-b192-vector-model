#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QPlainTextEdit>


class TextEdit : public QPlainTextEdit {
	Q_OBJECT
public:
	TextEdit(QWidget* parent = nullptr);
	~TextEdit();

private:
	void keyPressEvent(QKeyEvent* e);
};


#endif // TEXTEDIT_H
