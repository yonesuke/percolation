#include <vector>
#include <cmath>

double mean(std::vector<double> arr)
{
    int n = arr.size();
    double m = 0.0;
    for (int i=0; i<n; i++) m += arr[i];
    m /= static_cast<double>(n);
    return m;
}

double var(std::vector<double> arr)
{
    int n = arr.size();
    double m = 0.0;
    double m2 = 0.0;
    for (int i=0; i<n; i++)
    {
        m += arr[i];
        m2 += arr[i] * arr[i];
    }
    m /= static_cast<double>(n);
    m2 /= static_cast<double>(n);
    return m2 - m * m;
}

double interval(std::vector<double> arr)
{
    double v = var(arr);
    if (v < 0.0) v = 0.0;
    return std::sqrt(v / (static_cast<double>(arr.size()) - 1.0));
}