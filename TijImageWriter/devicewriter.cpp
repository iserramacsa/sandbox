#include "devicewriter.h"
#include <QFile>
#define TMP_DD_PID	"/tmp/dd_pid"
#define TMP_DD_PROGRESS "/tmp/progress"

DeviceWriter::DeviceWriter(QObject *parent) :
	QObject (parent)
{

}

void DeviceWriter::StartCopy(QString source, QString destination)
{
	copyThread = std::thread(&DeviceWriter::WriteImage, source, destination);
}

int DeviceWriter::GetProgress()
{
	int pid = GetPid();
	if (pid != -1){
		//KILL USR1 pid -> Read progress
	}
}

void DeviceWriter::WriteImage(QString source, QString destination)
{
	Q_UNUSED(source);
	Q_UNUSED(destination);

	QString command = QString("dd if=%1 of=%2 status=progress bs=1M 2> %3 & echo $! > %4 && sync")
					  .arg(source)
					  .arg(destination)
					  .arg(TMP_DD_PROGRESS)
					  .arg(TMP_DD_PID);
	system(command.toStdString().c_str());
}

int DeviceWriter::GetPid()
{
	int pid = -1;
	QFile pidFile(TMP_DD_PID);
	if (pidFile.exists() && pidFile.open(QIODevice::ReadOnly)){
		QByteArray raw = pidFile.readAll();
		pid = std::atoi(raw.toStdString().c_str());
	}
	return pid;
}
