#include "QConfig.h"

QConfig::QConfig(const QString& path)
	: m_path(path), m_error(Error::NoError), m_errorString(QString())
{
}

QConfig::~QConfig()
{
}
QString QConfig::path() const
{
	return this->m_path;
}

void QConfig::setPath(const QString& path)
{
	this->m_path = path;
}

QConfig::Error QConfig::error() const
{
	return this->m_error;
}

QString QConfig::errorString() const
{
	return this->m_errorString;
}

bool QConfig::getFile(QFile& file, OpenMode mode)
{
	file.setFileName(this->m_path);
	QIODevice::OpenMode doMode = mode == ReadOnly ? QIODevice::ReadOnly : (QIODevice::WriteOnly | QIODevice::Text);
	if (!file.open(doMode))
		return this->setError(Error::OpenError, file.errorString());
	else
		return this->setError(Error::NoError, QString());
}

bool QConfig::setError(Error error, const QString& errorString)
{
	this->m_error = error;
	this->m_errorString = errorString;
	return error == Error::NoError;
}

bool QConfig::saveFile(const QByteArray& byte)
{
	QFile file;
	if (!this->getFile(file, QConfig::WriteOnly))
		return this->setError(Error::WriteError, file.errorString());
	file.write(byte);
	file.close();
	return this->setError(Error::NoError);
}