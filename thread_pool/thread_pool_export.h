#ifndef THREAD_POOL_EXPORT_H
#define THREAD_POOL_EXPORT_H

#ifdef _WIN32
#ifdef THREAD_POOL_EXPORT
#define THREAD_POOL_API __declspec(dllimport)
#else
#define THREAD_POOL_API __declspec(dllexport)
#endif
#else
#define THREAD_POOL_API 
#endif

#endif