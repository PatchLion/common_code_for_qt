#include "QSSDataManager.h"
#include <QtCore>
#include "QtCommonMacros.h"

QSSData::CQSSDataManager::CQSSDataManager()
{

}

void QSSData::CQSSDataManager::reloadQSS(const QString& styleDir)
{
	m_mapKeyToData.clear();

	load(styleDir);
}

QString QSSData::CQSSDataManager::data(const QString& name) const
{
	if (name.isEmpty())
	{
		return  "";
	}

	MapKeyToStyleData::const_iterator dataItor = m_mapKeyToData.find(name);

	if (m_mapKeyToData.end() == dataItor)
	{
		qWarning() << "Can not find style data by name: " << name;
		return "";
	}

	return dataItor.value();
}

void QSSData::CQSSDataManager::load(const QString& styleDir)
{
	QFileInfoList fileInfoList = QDir(styleDir).entryInfoList(QDir::Files | QDir::Dirs);

	Q_FOREACH(QFileInfo fileInfo, fileInfoList)
	{
		//qDebug() << fileInfo.baseName() << " " << fileInfo.fileName() << " " << fileInfo.absoluteDir();
		if (fileInfo.isDir())
		{
			//д©б╪
			if (fileInfo.fileName() == ".." || fileInfo.fileName() == ".")
			{
				continue;
			}
			else
			{
				load(SAFE_JOIN_PATH(fileInfo.absolutePath(), fileInfo.fileName()));
			}
		}
		else
		{
			//нд╪Ч
			if (fileInfo.suffix().toLower() == "qss")
			{
				MapKeyToStyleData::iterator dataItor = m_mapKeyToData.find(fileInfo.baseName());
				if (m_mapKeyToData.end() != dataItor)
				{
					qWarning() << "Style key exist: " << fileInfo.baseName() << "(" << fileInfo.absolutePath() << ")";
					continue;
				}

				QFile file(fileInfo.absoluteFilePath());
				if (!file.open(QIODevice::ReadOnly))
				{
					qWarning() << "Can not open qss file: " << fileInfo.absoluteFilePath();
					continue;
				}
				else
				{
					QString style = file.readAll();
					file.close();

					m_mapKeyToData.insert(fileInfo.baseName(), style);
				}
			}
		}
	}
}

