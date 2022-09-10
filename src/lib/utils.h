#pragma once

#include<iostream>

const char* s = "0123456789ABCDEF";

inline constexpr int strlen(char* str)
{
    int count = 0;
    while(*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

inline constexpr int strlen(const char* str)
{
    int count = 0;
    while(*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

inline constexpr char* lower(char* x)
{
    int sz = strlen(x);
    for(int i=0;i < sz;i++)
    {
        if(x[i] >= 65 && x[i] <= 90) x[i] += 32; 
    }
    return x;
}

inline constexpr char* upper(char* x)
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

inline constexpr float round(float x)
{
    return (int)(x + .51);
}

inline constexpr double round(double x)
{
    return (int)(x + .51);
}

inline constexpr std::string its(unsigned x)
{
    if(x==0)return std::string("0");
    std::string result;
    while(x!=0)
    {
        result = (char)(x%10+48) + result;
        x /= 10;
    }
    return result;
}

inline constexpr int pow(int x, int n)
{
    if(n == 0) return 1;
    if(n == 1) return x;

    int result = x;
    for(int i=0;i < n-1;i++) result *= x;

    return result;
}

template<typename T>
inline constexpr T max(T a,T b)
{
    if(a>b) return a;
    else return b;
}
template<typename T>
inline constexpr T max(T a,T b,T c)
{
    T tmp = max(a,b);
    if(tmp>c) return tmp;
    else return c;
}

template<typename T>
inline constexpr T min(T a,T b)
{
    if(a<b) return a;
    else return b;
}
template<typename T>
inline constexpr T min(T a,T b,T c)
{
    T tmp = min(a,b);
    if(tmp<c) return tmp;
    else return c;
}

template<class T>
inline constexpr int iof(T* arr,T x)
{
    int sz = strlen(arr);

    for(int i=0;i < sz;i++)
    {
        if(x == arr[i]) return i;
    }

    return 0;
}

template<class T>
inline constexpr int iof(const T* arr,T x)
{
    int sz = strlen(arr);

    for(int i=0;i < sz;i++)
    {
        if(x == arr[i]) return i;
    }

    return 0;
}

inline constexpr int from16to10(char* x)
{
    upper(x);
    int sz = strlen(x);
    int result = 0;
    for(int i = 0;i < sz;i++)
    {
        result += iof(s,x[i]) * pow(16,sz - i - 1);
    }
    return result;
}

inline constexpr int from16to10(const char* X)
{
    char* x = upper(X);
    int sz = strlen(x);
    int result = 0;
    for(int i = 0;i < sz;i++)
    {
        result += iof(s,x[i]) * pow(16,sz - i - 1);
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

constexpr inline char* reverse(const char* arr)
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
        res = s[x % 16] + res;
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
        res = s[x % 16] + res;
        x /= 16;
    }
    result = (const char*)malloc(res.size());
    result = (const char*)res.c_str();
    return result;
}