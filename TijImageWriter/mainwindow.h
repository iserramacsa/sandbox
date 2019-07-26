#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "devicemanager.h"
#include <QListWidgetItem>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private:
		Ui::MainWindow *ui;
		DeviceManager deviceManager;

	private slots:
		void OnDeviceDetected(QString path = QString());
		void OnDeviceSelected(QListWidgetItem* item);
};

#endif // MAINWINDOW_H
