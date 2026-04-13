// 다항식 곱을 고속 푸리에 변환으로 계산하는 코드
#include <complex>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using cd = std::complex<double>;
double PI = std::acos(-1);

std::vector<cd> fft(std::vector<cd> X, int N, bool invert = false)
{
    if (N == 1)
    {
        return X;
    }
    std::vector<cd> even_X(N / 2);
    std::vector<cd> odd_X(N / 2);
    for (int i = 0; i < N / 2; i++)
    {
        even_X[i] = X[i * 2];
        odd_X[i] = X[i * 2 + 1];
    }

    std::vector<cd> even = fft(even_X, N / 2);
    std::vector<cd> odd = fft(odd_X, N / 2);
    std::vector<cd> result(N);

    for (int k = 0; k < N / 2; k++)
    {
        
        double theta = (invert ? -2.0 * PI * k / N : 2.0 * PI * k / N);
        cd w = std::exp(cd(0, theta));
        cd t = odd[k] * w;
        result[k] = even[k] + t;
        result[k + N / 2] = even[k] - t;
    }

    return result;
}
int main()
{
    // 우선 간단한 확인을 위해 23 * 45 결과 확인
    // 2자리 다항식의 곱의 푸리에 변환은 3개 이상의 점이 필요

    std::string a = "23";
    std::string b = "45";
    if (a.length() < b.length())
    {
        std::swap(a, b);
    }
    int maxLen = a.length();

    int l = 2 * maxLen;
    int N = 1;
    while (N < l) {
        N *= 2;
    }

    a = std::string(a.rbegin(), a.rend());
    b = std::string(b.rbegin(), b.rend());

    std::vector<cd> num_a(N);
    std::vector<cd> num_b(N);

    for (int i = 0; i < maxLen; i++)
    {
        num_a[i] = cd(a[i] - '0', 0);
        num_b[i] = cd(b[i] - '0', 0);
    }

    std::vector<cd> x_a = fft(num_a, N);
    std::vector<cd> x_b = fft(num_b, N);
    std::vector<cd> c(N);

    for (int i = 0; i < N; i++)
    {
        std::cout << x_a[i] << ' ';
        c[i] = x_a[i] * x_b[i];
    }
    std::vector<cd> x = fft(c, N, true);
    for (int i = 0; i < N; i++)
    {
        std::cout << x[i] << ' ';
       
    }
}