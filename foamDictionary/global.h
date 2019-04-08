#ifndef GLOBAL_H
#define GLOBAL_H
#ifdef Q_OS_WIN32
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT Q_DECL_EXPORT
#endif
#endif // GLOBAL_H
