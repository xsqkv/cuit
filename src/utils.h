#include<iostream>

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

inline constexpr uint8_t max(uint8_t a,uint8_t b)
{
    if(a>b) return a;
    else return b;
}

inline constexpr uint8_t max(uint8_t a,uint8_t b,uint8_t c)
{
    uint8_t tmp = max(a,b);
    if(tmp>c) return tmp;
    else return c;
}

inline constexpr uint8_t min(uint8_t a,uint8_t b)
{
    if(a<b) return a;
    else return b;
}

inline constexpr uint8_t min(uint8_t a,uint8_t b,uint8_t c)
{
    uint8_t tmp = min(a,b);
    if(tmp<c) return tmp;
    else return c;
}

inline constexpr float max(float a,float b)
{
    if(a>b) return a;
    else return b;
}

inline constexpr float max(float a,float b,float c)
{
    float tmp = max(a,b);
    if(tmp>c) return tmp;
    else return c;
}

inline constexpr float min(float a,float b)
{
    if(a<b) return a;
    else return b;
}

inline constexpr float min(float a,float b,float c)
{
    float tmp = min(a,b);
    if(tmp<c) return tmp;
    else return c;
}

inline constexpr double max(double a,double b)
{
    if(a>b) return a;
    else return b;
}

inline constexpr double max(double a,double b,double c)
{
    double tmp = max(a,b);
    if(tmp>c) return tmp;
    else return c;
}

inline constexpr double min(double a,double b)
{
    if(a<b) return a;
    else return b;
}

inline constexpr double min(double a,double b,double c)
{
    double tmp = min(a,b);
    if(tmp<c) return tmp;
    else return c;
}

inline constexpr int iof(char* arr,char x)
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
    constexpr char* s = "0123456789ABCDEF";
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
    constexpr char* s = "0123456789ABCDEF";
    int sz = strlen(x);
    int result = 0;
    for(int i = 0;i < sz;i++)
    {
        result += iof(s,x[i]) * pow(16,sz - i - 1);
    }
    return result;
}
