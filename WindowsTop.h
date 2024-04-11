#pragma once
#include <QtWidgets/QWidget>
#include "ui_WindowsTop.h"
#include <qsystemtrayicon.h>
#include <qevent.h>
#include <qcombobox.h>
#include <qhotkey.h>
#include <QMenu>
#include <qsettings.h>
#include <qformlayout.h>
#include "QJsonConfig.h"
#include <qkeysequenceedit.h>
#include <qmessagebox.h>
#include <qwindow.h>
#include <QSoundEffect>
#ifdef _WIN32
#include <Windows.h>
#endif

class WindowsTop : public QWidget
{
	Q_OBJECT

public:
	WindowsTop(QWidget* parent = nullptr);
	~WindowsTop();

private:
	Ui::WindowsTopClass ui;
	QSystemTrayIcon* trayIcon;
	QHotkey* hotkey;
	void initConnect() const;
	void initUi();
	void closeEvent(QCloseEvent* event);
	void setHotkey(const QKeySequence& keySequence);
	// ���ھ���б�
	QSet<void*> windowsSet;
	QJsonConfig config{ QApplication::applicationDirPath() + "/config.json" };
private slots:
	void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	void autoRun(bool isAutoRun);
	void setWindowTop();
};