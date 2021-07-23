#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CROSSPLATFORMLIB_LIB)
#  define CROSSPLATFORMLIB_EXPORT Q_DECL_EXPORT
# else
#  define CROSSPLATFORMLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define CROSSPLATFORMLIB_EXPORT
#endif
