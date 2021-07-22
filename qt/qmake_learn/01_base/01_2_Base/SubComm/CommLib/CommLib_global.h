#ifndef COMMLIB_GLOBAL_H
#define COMMLIB_GLOBAL_H

#if defined(_MSC_VER) || defined(WIN64) ||defined(__WIN64__)
#define Q_DECL_EXPORT __declspec(dllexport)
#define Q_DECL_IMPORT __declspec(dllimport)
#else
#define Q_DECL_EXPORT __attribute__((visibility("default")))
#define Q_DECL_EXPORT __atrribute__((visibility("default")))
#endif

#if defined(COMMLIB_LIBRARY)
#define COMMLIB_EXPORT Q_DECL_EXPORT
#else
#  define COMMLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMLIB_GLOBAL_H
