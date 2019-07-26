#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QObject>

#include "devicemanager.h"

class DeviceItem : public QObject
{
		Q_OBJECT
	public:
		explicit DeviceItem(QString name, DeviceManager& manager, QObject *parent = nullptr);

	signals:

	public slots:
		void OnDeviceMounted(QString path);

	private:
		DeviceManager& devManager;
		QString root;
		int partition;
		bool mounted;

		QString GetRoot(const QString& devName)const;
};

#endif // DEVICEITEM_H
