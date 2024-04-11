#include "WindowsTop.h"

WindowsTop::WindowsTop(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->trayIcon = new QSystemTrayIcon(this);
	this->trayIcon->setIcon(QIcon(":/WindowsTop/res/WindowsTop.png"));
	this->trayIcon->setToolTip("WindowsTop");
	this->trayIcon->show();
	this->initUi();
	this->initConnect();
}

WindowsTop::~WindowsTop()
{
	for (auto it = this->windowsSet.begin(); it != this->windowsSet.end(); it++)
	{
#ifdef WIN32
		HWND hwnd = (HWND)*it;
		// 判断是否存在这个窗口
		if (::IsWindow(hwnd))
			::SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif // WIN32
	}
}

void WindowsTop::initConnect() const
{
	connect(this->trayIcon, &QSystemTrayIcon::activated, this, &WindowsTop::onTrayIconActivated);
	connect(this->hotkey, SIGNAL(activated()), this, SLOT(setWindowTop()));
}

void WindowsTop::initUi()
{
	QFormLayout* layout = new QFormLayout(this);

	QComboBox* comboBox = new QComboBox(this);
	comboBox->setObjectName("AutoRun");
	comboBox->addItems({ "否", "是" });
	layout->addRow("开机自启", comboBox);
	QVariant autoRun = config.read(comboBox->objectName());
	if (!autoRun.isValid())
	{
		this->config.write(comboBox->objectName(), false);
		autoRun = QVariant(false);
	}
	comboBox->setCurrentIndex(autoRun.toBool() ? 1 : 0);
	connect(comboBox, &QComboBox::currentIndexChanged, this, &WindowsTop::autoRun);

	QComboBox* playSoundComboBox = new QComboBox(this);
	playSoundComboBox->setObjectName("playSound");
	playSoundComboBox->addItems({ "否", "是" });
	layout->addRow("播放提示音", playSoundComboBox);
	QVariant playSound = config.read(playSoundComboBox->objectName());
	if (!playSound.isValid())
	{
		this->config.write(playSoundComboBox->objectName(), false);
		playSound = QVariant(false);
	}
	playSoundComboBox->setCurrentIndex(playSound.toBool() ? 1 : 0);
	connect(playSoundComboBox, &QComboBox::currentIndexChanged, [=](int index)
		{
			this->config.write(playSoundComboBox->objectName(), index == 1);
		});

	QKeySequenceEdit* keySequenceEdit = new QKeySequenceEdit(this);
	this->hotkey = new QHotkey(this);
	keySequenceEdit->setObjectName("Hotkey");
	layout->addRow("快捷键", keySequenceEdit);
	QVariant hotkeyVar = config.read(keySequenceEdit->objectName());
	if (!hotkeyVar.isValid())
	{
		hotkeyVar = QKeySequence(Qt::CTRL | Qt::Key_T);
		config.write(keySequenceEdit->objectName(), QKeySequence(Qt::CTRL | Qt::Key_T).toString());
	}
	keySequenceEdit->setKeySequence(hotkeyVar.toString());
	this->hotkey->setShortcut(keySequenceEdit->keySequence(), true);
	connect(keySequenceEdit, &QKeySequenceEdit::keySequenceChanged, this, &WindowsTop::setHotkey);

	this->setLayout(layout);
}

void WindowsTop::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}

void WindowsTop::setHotkey(const QKeySequence& keySequence)
{
	this->hotkey->setShortcut(keySequence, true);
	this->config.write("Hotkey", keySequence.toString());
}

void WindowsTop::setWindowTop()
{
#ifdef WIN32
	POINT pt;
	GetCursorPos(&pt); // 获取当前鼠标位置
	HWND hwnd = WindowFromPoint(pt); // 获取该位置的窗口句柄
	// 判断是否存在这个窗口
	if (!::IsWindow(hwnd))	return;

	// 判断当前窗口是否已经置顶
	LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

	bool isTopmost = (exStyle & WS_EX_TOPMOST) != 0;
	if (!isTopmost)
	{
		::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		this->windowsSet.insert(hwnd);
	}
	else
	{
		::SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		this->windowsSet.remove(hwnd);
	}

#endif // WIN32
	if (this->config.read("playSound").toBool())
	{
		QSoundEffect* startSound = new QSoundEffect();
		startSound->setSource(QUrl::fromLocalFile(":/WindowsTop/res/sound.wav"));
		connect(startSound, &QSoundEffect::playingChanged, startSound, [=]()
			{
				if (!startSound->isPlaying())
					startSound->deleteLater();
			});
		startSound->play();
	}
}

void WindowsTop::autoRun(bool isAutoRun)
{
	QString appPath = QCoreApplication::applicationFilePath();

#ifdef _WIN32
	QString regPath = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	QSettings settings(regPath, QSettings::NativeFormat);
	if (isAutoRun)
		settings.setValue("WindowsTop", appPath);
	else
		settings.remove("WindowsTop");
#elif defined(__linux__)
	QString autostartPath = QDir::homePath() + "/.config/autostart/";
	QString desktopFileName = "WindowsTop.desktop";
	QString desktopFileContent = QString(
		"[Desktop Entry]\n"
		"Type=Application\n"
		"Exec=%1\n"
		"Hidden=false\n"
		"NoDisplay=false\n"
		"X-GNOME-Autostart-enabled=true\n"
		"Name[en_US]=WindowsTop\n"
	).arg(appPath);

	QDir autostartDir(autostartPath);
	if (!autostartDir.exists()) {
		QDir().mkpath(autostartPath); // Ensure the autostart directory exists
	}

	QString desktopFilePath = autostartPath + desktopFileName;
	QFile desktopFile(desktopFilePath);

	if (isAutoRun) {
		if (desktopFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(&desktopFile);
			out << desktopFileContent;
			desktopFile.close();
		}
	}
	else {
		if (desktopFile.exists()) {
			QFile::remove(desktopFilePath);
		}
	}
#endif
	this->config.write("AutoRun", isAutoRun);
}

void WindowsTop::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger) // 托盘图标被单击
	{
		this->show();
	}
	else if (reason == QSystemTrayIcon::Context)
	{
		QMenu menu;
		QAction* showWindowAction = menu.addAction("设置");
		QAction* exitAction = menu.addAction("退出");

		connect(showWindowAction, &QAction::triggered, this, &WindowsTop::show);
		connect(exitAction, &QAction::triggered, this, &QApplication::quit);

		menu.exec(QCursor::pos());
	}
}