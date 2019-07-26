#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("TIJ Image Writer");

	connect(&deviceManager, SIGNAL(deviceDetected(QString)), SLOT(OnDeviceDetected(QString)));
	connect(ui->listDevices, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(OnDeviceSelected(QListWidgetItem*)));

	OnDeviceDetected();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::OnDeviceDetected(QString path)
{
	//Q_UNUSED(path)
	qDebug() << __PRETTY_FUNCTION__ << " path:" << path;
	QStringList devices = deviceManager.GetDetectedDevices();
	ui->listDevices->clear();
	ui->listDevices->addItems(devices);
}

void MainWindow::OnDeviceSelected(QListWidgetItem *item)
{
	QString device = item->text();
	QString mountPoint = QString("/dev/%1").arg(item->text());

	qDebug() << " Device: " << item->text() << " mounted:" << deviceManager.IsMounted(mountPoint);

	if (deviceManager.HasPartitions(device)){
		QStringList partitions = deviceManager.GetPartitions(device);
		for (int i = 0; i < partitions.count(); i++){
			qDebug() << "Partition: " << partitions.at(i) << " mounted:" << deviceManager.IsMounted(partitions.at(i));
		}

	}
}
