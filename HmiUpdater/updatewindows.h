#ifndef UPDATE_WINDOW_H
#define UPDATE_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>

class UpdateWindow : public QMainWindow
{
		Q_OBJECT

	public:
		UpdateWindow(QWidget *parent = 0);
		~UpdateWindow();

	public slots:
		void onProgressChanged(const QString &text, int value);

	private:
		QLabel* _infoLabel;
		QProgressBar* _progress;

		void LoadStyle();


};

#endif //UPDATE_WINDOW_H
