#pragma once
#include <QtWidgets/QWidget>
#include "ui_WindowsTop.h"
#include <qsystemtrayicon.h>
#include <qevent.h>
#include <qcombobox.h>
#include <qhotkey.h>
#include <qmenu.h>
#include <qsettings.h>
#include <qformlayout.h>
#include "QJsonConfig.h"
#include <qkeysequenceedit.h>
#include <qmessagebox.h>
#include <qwindow.h>
#include <QSoundEffect>
#include <qtablewidget.h>
#include <qclipboard.h>
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#endif
/**
 * @brief 截断字符串并添加省略号
 * @param str 需要截断的字符串
 * @param length 截断长度
 * @return 截断后的字符串
 */

static QString truncateString(const QString& str, int length);

class WindowsTop : public QWidget
{
	Q_OBJECT

public:
	WindowsTop(QWidget* parent = nullptr);
	~WindowsTop();
private:

	struct WindowInfo 	// 窗口信息
	{
		LONG64  id;			// 窗口句柄
		QString hex;		// 窗口句柄十六进制
		QString title;		// 窗口标题
		QString className;	// 窗口类名
		QString processId;	// 窗口进程ID
		/**
		 * @brief 将窗口信息转换为JSON
		 * @param format JSON格式
		 * @return 转换后的JSON
		 */
		QString toJson(const QJsonDocument::JsonFormat& format = QJsonDocument::Indented) const;
		/**
		 * @brief 将窗口信息转换为列表
		 * @return 转换后的列表
		 */
		QStringList toList() const;
		/**
		 * @brief 构造函数
		 * @param id 窗口句柄
		 * @param isInit 是否初始化
		 */
		WindowInfo(LONG64 id, bool isInit = true);
		/**
		 * @brief 初始化
		 */
		void init();
	};
private:
	Ui::WindowsTopClass	ui;				// 界面
	QSystemTrayIcon* trayIcon;			// 托盘图标
	QMap<QString, QHotkey*> hotkeyMap;	// 热键映射
	QTableWidget* topWindowTableWidget;	// 窗口列表
	QJsonConfig config;					// 配置文件
	QSet<LONG64> windowsSet;			// 窗口句柄集合
	/**
	 * @brief 初始化信号连接
	 */
	void initConnect() const;
	/**
	 * @brief 初始化界面
	 */
	void initUi();
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
	void closeEvent(QCloseEvent* event) override;

private slots:
	/**
	 * @brief 托盘图标激活槽函数
	 * @param reason
	 */
	void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	/**
	 * @brief 自启动槽函数
	 * @param isAutoRun
	 */
	void autoRun(int isAutoRun);
	/**
	 * @brief 窗口指定
	 */
	void setWindowTop();
	/**
	 * @brief tableWidget上下文菜单槽函数
	 */
	void showTableContextMenu();
};
