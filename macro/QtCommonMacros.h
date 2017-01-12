#ifndef QtCommonMacros_h__
#define QtCommonMacros_h__

#include <QtCore>
#include "CommonMacros.h"

//check double or float equal
#ifndef FLOAT_VALUE_EQUAL
#define FLOAT_VALUE_EQUAL(src, dest) (qAbs(src - dest) < 0.00000001)
#endif

///delete a qobject pointer and make it null
#ifndef SAFE_DELETE_QOBJECT
#define SAFE_DELETE_QOBJECT(p)  { if(p) { p->deleteLater(); (p)=0; } }
#endif    

///full path jion with qdir
#define SAFE_JOIN_PATH(path, dirOrFileName) QDir(path).filePath(dirOrFileName)
#endif // QtCommonMacros_h__
