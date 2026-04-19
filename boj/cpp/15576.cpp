// 다항식 곱을 고속 푸리에 변환으로 계산하는 코드
#include <complex>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <queue>

using cd = std::complex<double>;
double PI = std::acos(-1);
std::vector<cd> fft(std::queue<int> q, std::vector<cd>& init, int N, bool invert)
{
    std::vector<cd> a(N);
    std::vector<cd> b(N);
    double inv = (invert ? 1.0 : -1.0);

    std::vector<cd>* prev_result = &a;
    std::vector<cd>* curr_result = &b;

    for (size_t step = 1; step < N; step *= 2)
    {
        int idx = 0;
        if (step == 1)
        {

            while (!q.empty())
            {
                cd w = cd(1, 0);
                int even = q.front();
                q.pop();
                int odd = q.front();
                q.pop();
                cd t = init[odd] * w;
                int next_idx = idx + step;
                (*curr_result)[idx] = init[even] + t;
                (*curr_result)[next_idx] = init[even] - t;
                //std::cout << "n = " << step << " 일 때, " << idx << ", " << next_idx << '\n';

                idx += 2;
            }
            std::swap(prev_result, curr_result);
        }
        else
        {
            for (size_t i = 0; i < N / (step * 2); i++)
            {
                double theta = inv * 2.0 * PI / (step * 2.0);
                cd w1 = std::exp(cd(0, theta));
                cd w = 1;

                for (size_t j = 0; j < step; j++)
                {
                    int next_idx = idx + step;
                    cd t = (*prev_result)[next_idx] * w;
                    (*curr_result)[idx] = (*prev_result)[idx] + t;
                    (*curr_result)[next_idx] = (*prev_result)[idx] - t;
                    //std::cout << "n = " << step << " 일 때, " << idx << ", " << next_idx << '\n';
                    w *= w1;
                    idx++;

                }
                idx += step;
            }
            std::swap(prev_result, curr_result);
        }
    }

    return *prev_result;

}
void indexing(std::queue<int>& q, std::vector<int> v)
{
    int n = v.size();
    if (n == 1) {
        q.push(v[0]);
        return;
    }
    std::vector<int> even, odd;
    for (size_t i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            even.push_back(v[i]);
        else
            odd.push_back(v[i]);
    }
    indexing(q, even);
    indexing(q, odd);
}
int main()
{
    std::cin.tie(0)->sync_with_stdio(0);
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
    std::vector<int> mul_ret(N + 1);

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
    std::queue<int> q;
    std::vector<int> v(N);
    for (size_t i = 0; i < N; i++)
    {
        v[i] = i;
    }
    indexing(q, v);

    std::vector<cd> a_ret = fft(q, num_a, N, false);
    std::vector<cd> b_ret = fft(q, num_b, N, false);
    std::vector<cd> c(N);

    for (size_t i = 0; i < N; i++)
    {
        c[i] = a_ret[i] * b_ret[i];
    }
    std::vector<cd> c_ret = fft(q, c, N, true);

    int carry = 0;
    for (size_t i = 0; i < N; i++)
    {
        int final_ret = int(std::round(c_ret[i].real() / N)) + carry;
        mul_ret[i] = (final_ret) % 10;
        carry = final_ret / 10;
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