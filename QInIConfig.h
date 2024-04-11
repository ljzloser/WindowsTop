#pragma once
#include "QConfig.h"
#include <qsettings.h>

class QInIConfig :
	public QConfig
{
public:
	QInIConfig(const QString& path) :QConfig(path) {};

	~QInIConfig() {};
	/**
	 * @brief ��ȡ�����ļ�
	 * @param key ��
	 * @param value ֵ
	 * @return �Ƿ��ȡ�ɹ�
	 */
	bool read(const QVariant& key, QVariant& value) override;
	/**
	 * @brief ��ȡ�����ļ�
	 * @param key ��
	 * @param value ֵ
	 * @return �Ƿ��ȡ�ɹ�
	 */
	bool read(const QVariantList& keys, QVariant& value) override;
	/**
	 * @brief ��ȡ�����ļ�
	 * @param key ��
	 * @return ֵ
	 */
	QVariant read(const QVariant& key) override;
	/**
	 * @brief ��ȡ�����ļ�
	 * @param key ��
	 * @return ֵ
	 */
	QVariant read(const QVariantList& keys) override;
	/**
	 * @brief д�������ļ�
	 * @param key ��
	 * @param value ֵ
	 * @param isAppend �Ƿ�׷��
	 * @return �Ƿ�д��ɹ�
	 */
	bool write(const QVariant& key, const QVariant& value, bool isAppend = true) override;
	/**
	 * @brief д�������ļ�
	 * @param key ��
	 * @param value ֵ
	 * @param isAppend �Ƿ�׷��
	 * @return �Ƿ�д��ɹ�
	 */
	bool write(const QVariantList& keys, const QVariant& value, bool isAppend = true) override;
private:
	/**
	 * @brief ���б�ת��Ϊ�ַ���
	 * @param list ��Ҫת�����б�
	 * @return QString
	 */
	QVariant listToValue(const QVariantList& list);
};
