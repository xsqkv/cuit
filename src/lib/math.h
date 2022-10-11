int round(double x)
{
    return (x / 1) < 0.5 ? x : x+1;
}

double sqrt (double v)
{
    double L = 0, R = v;

    double M = (L + R) /2;

    while(R - L > 1)
    {
        if(M * M <= v)
        {
            L = M;
        }
        else
        {
            R = M;
        }
        M = (L + R)/2;
    }
}