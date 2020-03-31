#include "textedit.h"

#include <QDebug>
#include <QKeyEvent>


TextEdit::TextEdit(QWidget* parent) :
	QPlainTextEdit(parent)
{

}


TextEdit::~TextEdit()
{

}


void TextEdit::keyPressEvent(QKeyEvent* e)
{
	if(e->key() == Qt::Key_Escape) {
		clear();
	}
	else {
		QPlainTextEdit::keyPressEvent(e);
	}
}

