#include "deviceitem.h"

DeviceItem::DeviceItem(QString name, DeviceManager& manager, QObject *parent) : QObject(parent),
	devManager(manager)
{
	root = name;
}

void DeviceItem::OnDeviceMounted(QString path)
{
	Q_UNUSED(path);
}

QString DeviceItem::GetRoot(const QString &devName) const
{
	Q_UNUSED(devName);
	return  QString();
}
