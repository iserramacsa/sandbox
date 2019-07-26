#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>


class DeviceManager : public QObject
{
		Q_OBJECT
	public:
		explicit DeviceManager(QObject *parent = nullptr);
		QStringList GetDetectedDevices(bool onlyRoot = true) const;
		QStringList GetMountedDevices() const;
		QStringList GetPartitions(const QString &device)const;
		bool IsMounted(const QString &device)const;
		bool HasPartitions(const QString &device)const;

	signals:
		void deviceDetected(QString path);
		void mountDetected(QString path); 

	private:
		bool ValidDevice(QString &mountPoint) const;
		QString GetDeviceMount(const QString & mountsLine)const;
		void RemovePartitions(QStringList& devList) const;
};

#endif // DEVICEMANAGER_H
