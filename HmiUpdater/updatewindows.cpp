#include "updatewindows.h"
#include <QLayout>
#include <QFile>

#define STYLE_SHEET	":/style.css"

UpdateWindow::UpdateWindow(QWidget *parent):
	QMainWindow (parent)
{
	QWidget *centralW = new QWidget(this);
	QVBoxLayout* layout = new QVBoxLayout(centralW);
	layout->setMargin(200);

	layout->addStretch();
	_infoLabel = new QLabel(this);
	_infoLabel->setAlignment(Qt::AlignHCenter);
	layout->addWidget(_infoLabel);
	layout->addStretch();

	_progress = new QProgressBar(this);
	_progress->setMaximumHeight(3);
	_progress->setTextVisible(false);

	layout->addWidget(_progress);
	layout->addStretch();

	setCentralWidget(centralW);
	LoadStyle();

	_progress->setValue(10);
	_infoLabel->setText("Update in progress...");
}

UpdateWindow::~UpdateWindow()
{}

void UpdateWindow::onProgressChanged(const QString &text, int value)
{
	_infoLabel->setText(text);
	_progress->setValue(value);
}

#include <QDebug>
void UpdateWindow::LoadStyle()
{
	QFile css(STYLE_SHEET);
	if (css.open(QIODevice::ReadOnly))
	{
		QString style = css.readAll();
		this->setStyleSheet(style);
		css.close();
	}
	else {
		qDebug() << "File not opened: " << css.errorString();
	}
}
