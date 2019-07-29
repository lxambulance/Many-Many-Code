#include <chrono>//计时头文件
#include <random>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng((uint64_t) new char);
mt19937_64 rng64((uint64_t) new char);
shuffle(permutation.begin(), permutation.end(), rng);
int R=uniform_int_distribution<int>(0, i)(rng); //闭区间