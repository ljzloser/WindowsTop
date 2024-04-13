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
#include <qtablewidget.h>
#include <QClipboard>
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#endif

static QString truncateString(const QString& str, int length);

class WindowsTop : public QWidget
{
	Q_OBJECT

public:
	WindowsTop(QWidget* parent = nullptr);
	~WindowsTop();
private:
	struct WindowInfo
	{
		LONG64  id;
		QString hex;
		QString title;
		QString className;
		QString processId;
		QString toJson(const QJsonDocument::JsonFormat& format = QJsonDocument::Indented) const;
		QStringList toList() const;
		WindowInfo(LONG64 id, bool isInit = true);
		void init();
	};
private:
	Ui::WindowsTopClass	ui;
	QSystemTrayIcon* trayIcon;			// 托盘图标
	QMap<QString, QHotkey*> hotkeyMap;
	QTableWidget* topWindowTableWidget;	// 窗口列表
	/**
	 * @brief 初始化信号连接
	 */
	void initConnect() const;
	/**
	 * @brief 初始化界面
	 */
	void initUi();
	void closeEvent(QCloseEvent* event);
	/**
	 * @brief 加载窗口列表
	 */
	void loadTable();
	void showEvent(QShowEvent* event);
	/**
	 * @brief 设置热键
	 * @param keySequence
	 */
	void setHotkey(const QKeySequence& keySequence);
	// 窗口句柄列表
	QSet<LONG64> windowsSet;
	QJsonConfig config{ QApplication::applicationDirPath() + "/config.json" };
private slots:
	void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	void autoRun(int isAutoRun);
	void setWindowTop();
	void showTableContextMenu();
};
