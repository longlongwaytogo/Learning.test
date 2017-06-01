#ifndef HELLO_H
#define HELLO_H

//#ifdef EXPORT_HELLO
#ifdef HELLO_SHARED_EXPORTS

#define HELLO_API __declspec(dllexport)
#else
#define HELLO_API 
#endif 
void HELLO_API Hello(void);

#endif
