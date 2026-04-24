// https://pintia.cn/problem-sets/1996886805509959680/exam/problems/type/7?problemSetProblemId=1996886805539319808
// https://pintia.cn/problem-sets/2047484936923484160/exam/problems/type/7?problemSetProblemId=2047485146122784768

#include <bits/stdc++.h>

#define let const auto
#define var auto
#define fn auto
#define in :

using usize = size_t;

constexpr auto LNG_MAX = 100uz;

template <std::ranges::input_range A, std::ranges::input_range B>
fn lcs(A &&a, B &&b) -> usize {
    var dp = std::vector(b.size() + 1uz, 0uz);
    for (let a_ch in a) {
        // LI: a 已经被遍历过的部分和 b[:i] 的 LCS 长度记录在 dp[i] 中。
        // 推论：数组 dp 是非递减的。
        var dp_last = dp.begin();
        for (let b_ch in b) {
            // LI: *dp_last 表示 a 已经被遍历过的部分和 b[:b_ch] 的 LCS 长度。
            let dp_current = dp_last + 1;
            *dp_current = (b_ch == a_ch ? *dp_last + 1 : std::max(*dp_last, *dp_current));
            // Q: 这里为什么要取 std::max(*dp_last, *dp_current)，不能直接取 *dp_current？
            // A: *dp_last 是本次大循环的计算结果，而 *dp_current 则是上个大循环的计算结果，故单调性不保证。
            dp_last = dp_current;
        }
    }
    return dp[b.size()];
}

fn run() {
    std::string a, b;
    a.reserve(LNG_MAX);
    b.reserve(LNG_MAX);
    std::getline(std::cin, a);
    std::getline(std::cin, b);
    std::cout << lcs(a, b) << '\n';
}

fn main() -> int {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
}
