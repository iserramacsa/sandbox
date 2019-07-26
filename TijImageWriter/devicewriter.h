#ifndef DEVICEWRITER_H
#define DEVICEWRITER_H
#include <QObject>
#include <thread>
class DeviceWriter : public QObject
{
		Q_OBJECT
	public:
		explicit DeviceWriter(QObject *parent = nullptr);
		void StartCopy(QString source, QString destination);
		int GetProgress();

	signals:
		void deviceWrited(int progress);

	private:
		std::thread copyThread;

		void WriteImage(QString source, QString destination);
		int GetPid();
};
#endif // DEVICEWRITER_H
