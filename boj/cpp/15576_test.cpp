// 다항식 곱을 고속 푸리에 변환으로 계산하는 코드
#include <complex>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using cd = std::complex<double>;
double PI = std::acos(-1);

void fill_array(std::vector<int>& a, long long& value, int shift_count)
{
    int idx = shift_count;

    while (true)
    {
        a[idx] = value % 10;
        value /= 10;
        if (value == 0)
            break;
        idx++;
    }
}

// a와 b의 길이가 같다고 가정
void add(std::vector<int>& a, std::vector<int>& b)
{
    int prev = 0;
    
    for (int i = 0; i < b.size(); i++)
    {
        a[i] += b[i] + prev;
        if (a[i] >= 10)
        {
            prev = 1;
            a[i] -= 10;
        }
        else
            prev = 0;
    }
    int i = b.size();

    while (prev!=0)
    {
        a[i] += prev;
        if (a[i] >= 10)
        {
            prev = 1;
            a[i] -= 10;
            i++;
        }
        else
            prev = 0;
    }
}

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

    std::vector<cd> even = fft(even_X, N / 2, invert);
    std::vector<cd> odd = fft(odd_X, N / 2, invert);
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
    std::string a, b;

    std::cin >> a >> b;
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
    std::vector<int> mul_ret(N+1);

    a = std::string(a.rbegin(), a.rend());
    b = std::string(b.rbegin(), b.rend());

    std::vector<cd> num_a(N);
    std::vector<cd> num_b(N);

    for (int i = 0; i < maxLen; i++)
    {
        num_a[i] = cd(a[i] - '0', 0);
        if (i >= b.size())
            num_b[i] = cd(0, 0);
        else
            num_b[i] = cd(b[i] - '0', 0);
    }

    std::vector<cd> x_a = fft(num_a, N);
    std::vector<cd> x_b = fft(num_b, N);
    std::vector<cd> c(N);

    for (int i = 0; i < N; i++)
    {
        c[i] = x_a[i] * x_b[i];
    }
    std::vector<cd> x = fft(c, N, true);
    double norm = 1.0 / N;

    int ret = 0;
    int shift_count = 0;
    for (int i = 0; i < N; i++)
    {
        long long curr_value = round(norm * x[i].real());
        if (curr_value == 0)
        {
            shift_count++;
            continue;
        }
        std::cout << curr_value << ' ';
        std::vector<int> b(N + 1);
        fill_array(b, curr_value, shift_count);
        add(mul_ret, b);
       
        shift_count++;

    }

    mul_ret = std::vector<int>(mul_ret.rbegin(), mul_ret.rend());
    auto it = std::find_if(mul_ret.begin(), mul_ret.end(), [](int x) {
        return x != 0;
        });

    if (it != mul_ret.end())
    {
        std::vector<int> sub(it, mul_ret.end());

        for (int x : sub)
            std::cout << x;
    }
    else
        std::cout << "0";
    
}