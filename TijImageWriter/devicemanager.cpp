#include "devicemanager.h"

#include <QFileSystemWatcher>
#include <QFile>
#include <QTextStream>
#include <string>

#define DEVICES_PATH	"/dev"
#define MOUNTS_FILE "/proc/self/mounts"
#define TMP_FILE "/tmp/disks"


DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{
	QFileSystemWatcher* devWatcher = new QFileSystemWatcher(this);
	QFileSystemWatcher* mountWatcher = new QFileSystemWatcher(this);
	devWatcher->addPath(DEVICES_PATH);
	mountWatcher->addPath(MOUNTS_FILE);

	connect(devWatcher, SIGNAL(directoryChanged(QString)), this, SIGNAL(deviceDetected(QString)));
	connect(mountWatcher, SIGNAL(fileChanged(QString)), this, SIGNAL(mountDetected(QString)));

}

QStringList DeviceManager::GetDetectedDevices(bool onlyRoot) const
{
	QStringList devices;

	QString listDevices = QString("ls /dev/ -lha | grep \"root disk\" > %1").arg(TMP_FILE);
	system(listDevices.toStdString().c_str());
	devices.clear();
	QFile tmp(TMP_FILE);
	if (tmp.exists()&& tmp.open(QIODevice::ReadOnly)) {
		QTextStream in(&tmp);
		while(!in.atEnd()){
			QString line = in.readLine();
			int pos = line.lastIndexOf(" ");
			if (pos < line.length() - 1){
				QString device = line.mid(pos).trimmed();
				QString entry = QString("/dev/%1").arg(device);
				if(ValidDevice(entry)){
					devices << device;
				}
			}
		}

	}
	tmp.remove();

	if(onlyRoot){
		RemovePartitions(devices);
	}

	return  devices;
}

QStringList DeviceManager::GetMountedDevices() const
{
	QString listMountedDevices = QString("cat %1 | grep \"/dev\" > %2").arg(MOUNTS_FILE).arg(TMP_FILE);
	system(listMountedDevices.toStdString().c_str());
	QFile mount(TMP_FILE);

	QStringList devices;
	if(mount.exists() && mount.open(QIODevice::ReadOnly)) {
		QTextStream in(&mount);
		while(!in.atEnd()){
			QString line = in.readLine();
			QString device = GetDeviceMount(line);
			if(ValidDevice(device)){
				devices << device.mid(5);
			}
		}
		mount.close();
	}
	if(mount.exists()){
		mount.remove();
	}
	return  devices;
}

QStringList DeviceManager::GetPartitions(const QString &device) const
{
	const bool onlyRoot = false;
	QStringList devList = GetDetectedDevices(onlyRoot);
	QStringList partitions;
	partitions.clear();
	for (int i = 0; i < devList.count(); i++) {
		if(devList.at(i).startsWith(device) && devList.at(i) != device){
			partitions << devList.at(i);
		}
	}

	return partitions;
}

bool DeviceManager::IsMounted(const QString & device) const
{
	QStringList devices = GetMountedDevices();
	for (int i = 0; i < devices.count(); i++){
		if(devices.at(i) == device){
			return true;
		}
	}
	return  false;
}

bool DeviceManager::HasPartitions(const QString &device) const
{
	return (GetPartitions(device).count() > 0);
}

bool DeviceManager::ValidDevice(QString& mountPoint) const
{
	bool valid = false;
	mountPoint = mountPoint.trimmed();
	if(!mountPoint.isEmpty() && mountPoint.startsWith(DEVICES_PATH)){
		if ((!mountPoint.contains("nvme0n")) &&
			(!mountPoint.contains("sda")) &&
			(!mountPoint.contains("loop"))){
			valid = true;
		}
	}
	return  valid;
}

QString DeviceManager::GetDeviceMount(const QString & mountsLine) const
{
	QString device = "";
	if(mountsLine.startsWith(DEVICES_PATH)){
		int pos = static_cast<int>(mountsLine.toStdString().find_first_of(" "));
		if (pos > 5){
			device = mountsLine.mid(0, pos);
		}
	}
	return  device;
}

void DeviceManager::RemovePartitions(QStringList &devList) const
{
	QString root;
	root.clear();
	for (int i = 0; i < devList.count(); i++){
		if(root.isEmpty() || !devList.at(i).startsWith(root)){
			root = devList.at(i);
		}
		else if(devList.at(i).startsWith(root)) {
			devList.removeAt(i);
			i--;
		}
	}
}

