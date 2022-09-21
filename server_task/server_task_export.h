#ifndef SERVER_TASK_EXPORT_H
#define SERVER_TASK_EXPORT_H

#ifdef _WIN32

#ifdef SERVER_TASK_EXPORT
	#define SERVER_TASK_API __declspec(dllimport)
#else
	#define SERVER_TASK_API __declspec(dllexport)
#endif

#else
	#define SERVER_TASK_API 
#endif

#endif