#ifndef TESTEMULATOR_GLOBAL_H
#define TESTEMULATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TESTEMULATOR_LIBRARY)
#  define TESTEMULATOR_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define TESTEMULATOR_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TESTEMULATOR_GLOBAL_H