// utilities class file

#pragma once

#include<iostream>
#include<cstring>

const char* hex_str = "0123456789ABCDEF";

inline char* lower(char* x)
{
    int sz = strlen(x);
    for(int i=0;i < sz;i++)
    {
        if(x[i] >= 65 && x[i] <= 90) x[i] += 32; 
    }
    return x;
}

inline char* upper(char* x)
{
    int sz = strlen(x);
    for(int i=0;i < sz;i++)
    {
        if(x[i] >= 97 && x[i] <= 122) x[i] -= 32;
    }
    return x;
}

inline char* lower(const char* x)
{
    int sz = strlen(x);
    char* a = reinterpret_cast<char*>(malloc(sz+1));
    int i;
    for(i=0;i < sz;i++)
    {
        if(x[i] >= 65 && x[i] <= 90) a[i] = x[i] + 32;
        else a[i] = x[i];
    }
    a[i] = '\0';
    return a;
}

inline char* upper(const char* x)
{
    int sz = strlen(x);
    char* a = reinterpret_cast<char*>(malloc(sz+1));
    int i;
    for(i=0;i < sz;i++)
    {
        if(x[i] >= 97 && x[i] <= 122) a[i] = x[i] - 32;
        else a[i] = x[i];
    }
    a[i] = '\0';
    return a;
}

template<typename T>
inline T max(T a,T b)
{
    if(a>b) return a;
    else return b;
}
template<typename T>
inline T max(T a,T b,T c)
{
    T tmp = max(a,b);
    if(tmp>c) return tmp;
    else return c;
}

template<typename T>
inline T min(T a,T b)
{
    if(a<b) return a;
    else return b;
}
template<typename T>
inline T min(T a,T b,T c)
{
    T tmp = min(a,b);
    if(tmp<c) return tmp;
    else return c;
}

template<class T>
inline int iof(T* arr,T x)
{
    int sz = strlen(arr);

    for(int i=0;i < sz;i++)
    {
        if(x == arr[i]) return i;
    }

    return 0;
}

template<class T>
inline int iof(const T* arr,T x)
{
    int sz = strlen(arr);

    for(int i=0;i < sz;i++)
    {
        if(x == arr[i]) return i;
    }

    return 0;
}

inline int from16to10(char* x)
{
    upper(x);
    int sz = strlen(x);
    int result = 0;
    for(int i = 0;i < sz;i++)
    {
        result += iof(hex_str,x[i]) * pow(16,sz - i - 1);
    }
    return result;
}

inline int from16to10(const char* X)
{
    char* x = upper(X);
    int sz = strlen(x);
    int result = 0;
    for(int i = 0;i < sz;i++)
    {
        result += iof(hex_str,x[i]) * pow(16,sz - i - 1);
    }
    return result;
}

inline char* reverse(char* arr)
{
    int sz = strlen(arr);
    char* res = new char[sz];
    for(int i = 0; i < sz ;i++)
    {
        res[i] = arr[sz-i-1];
    }
    return res;
}

 inline char* reverse(const char* arr)
{
    int sz = strlen(arr);
    char* res = new char[sz];
    for(int i = 0; i<sz/2 ;i++)
    {
        res[i] = arr[sz-i];
    }
    return res;
}

inline char* from10to16(int x)
{
    std::string res = "";
    char* result;
    if(!x) { res = "0"; result = (char*)malloc(res.size()); result = (char*)res.c_str();return result; }
    while(x)
    {
        res = hex_str[x % 16] + res;
        x /= 16;
    }
    result = (char*)malloc(res.size());
    result = (char*)res.c_str();
    return result;
}

inline const char* from10to16_2(int x)
{
    std::string res = "";
    const char* result;
    if(!x) { res = "0"; result = (const char*)malloc(res.size()); result = (const char*)res.c_str();return result; }
    while(x)
    {
        res = hex_str[x % 16] + res;
        x /= 16;
    }
    result = (const char*)malloc(res.size());
    result = (const char*)res.c_str();
    return result;
}