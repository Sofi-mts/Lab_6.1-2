// Юніт-тести до лабораторної роботи № 6.1 (рекурсивний спосіб), варіант 8
// Критерій: b[i] - парний і b[i] <= 0.
// Запуск: відкрити цей файл у VS Code і натиснути F5 (або Ctrl+F5).

#define main lab_main          // беремо функції з лаби, але без її main()
#include "Lab_6.1(3).cpp"
#undef main

#include <sstream>
#include <string>

static int passed = 0, failed = 0;

#define CHECK_EQ(expected, actual)                                          \
    do {                                                                    \
        auto e_ = (expected);                                               \
        auto a_ = (actual);                                                 \
        if (e_ == a_) {                                                     \
            ++passed;                                                       \
        } else {                                                            \
            ++failed;                                                       \
            cout << "  FAIL line " << __LINE__ << ": " #actual              \
                 << " = " << a_ << ", expected " << e_ << endl;             \
        }                                                                   \
    } while (0)

#define CHECK(cond) CHECK_EQ(true, (bool)(cond))

static void RunTest(const char* name, void (*test)()) {
    int failedBefore = failed;
    test();
    cout << (failed == failedBefore ? "[ OK ] " : "[FAIL] ") << name << endl;
}

// ---------- Count ----------

void TestCount_Mixed() {
    int b[] = {-14, 7, 0, 22, -3, -8, 15, 4};
    // підходять: -14, 0, -8
    CHECK_EQ(3, Count(b, 8, 0));
}

void TestCount_NoneMatch() {
    int b[] = {1, 2, 3, 4, 75, -15, -1};   // додатні та непарні від'ємні
    CHECK_EQ(0, Count(b, 7, 0));
}

void TestCount_AllMatch() {
    int b[] = {-2, -4, 0, -14};
    CHECK_EQ(4, Count(b, 4, 0));
}

void TestCount_ZeroCounts() {
    int b[] = {0};
    CHECK_EQ(1, Count(b, 1, 0));           // 0 - парний і не додатний
}

// ---------- Sum ----------

void TestSum_Mixed() {
    int b[] = {-14, 7, 0, 22, -3, -8, 15, 4};
    CHECK_EQ(-22, Sum(b, 8, 0));           // -14 + 0 + (-8)
}

void TestSum_NoneMatch() {
    int b[] = {1, 2, 3, -5};
    CHECK_EQ(0, Sum(b, 4, 0));
}

void TestSum_StartIndex() {
    int b[] = {-10, -2, 5};
    CHECK_EQ(-2, Sum(b, 3, 1));            // рахуємо лише з i = 1
}

// ---------- Replace ----------

void TestReplace_Mixed() {
    int b[] = {-14, 7, 0, 22, -3, -8, 15, 4};
    int expected[] = {0, 7, 0, 22, -3, 0, 15, 4};
    Replace(b, 8, 0);
    for (int i = 0; i < 8; i++) CHECK_EQ(expected[i], b[i]);
}

void TestReplace_ThenCountAndSum() {
    int b[] = {-6, -6, 3, -12, 9};
    Replace(b, 5, 0);
    CHECK_EQ(0, Sum(b, 5, 0));             // після заміни сума = 0
    CHECK_EQ(3, Count(b, 5, 0));           // нулі теж підходять під критерій
}

// ---------- Create ----------

void TestCreate_Range() {
    const int n = 24, Low = -15, High = 75;
    int b[n];
    srand(12345);
    Create(b, n, Low, High, 0);
    for (int i = 0; i < n; i++) CHECK(b[i] >= Low && b[i] <= High);
}

void TestCreate_SingleValueRange() {
    int b[5];
    Create(b, 5, 7, 7, 0);                 // Low == High -> усі елементи = 7
    for (int i = 0; i < 5; i++) CHECK_EQ(7, b[i]);
}

// ---------- Print ----------

void TestPrint_Format() {
    int b[] = {-15, 0, 75};
    stringstream out;
    streambuf* old = cout.rdbuf(out.rdbuf());   // перехоплюємо cout
    Print(b, 3, 0);
    cout.rdbuf(old);
    CHECK_EQ(string(" -15   0  75\n"), out.str());
}

int main() {
    cout << "Lab 6.1 unit tests" << endl;
    RunTest("Count: mixed array", TestCount_Mixed);
    RunTest("Count: no matching elements", TestCount_NoneMatch);
    RunTest("Count: all elements match", TestCount_AllMatch);
    RunTest("Count: zero is counted", TestCount_ZeroCounts);
    RunTest("Sum: mixed array", TestSum_Mixed);
    RunTest("Sum: no matching elements", TestSum_NoneMatch);
    RunTest("Sum: start index i = 1", TestSum_StartIndex);
    RunTest("Replace: matching elements become 0", TestReplace_Mixed);
    RunTest("Replace: then Count and Sum", TestReplace_ThenCountAndSum);
    RunTest("Create: values in [-15, 75]", TestCreate_Range);
    RunTest("Create: Low == High", TestCreate_SingleValueRange);
    RunTest("Print: output format", TestPrint_Format);

    cout << endl << "Checks passed: " << passed << ", failed: " << failed << endl;
    cout << (failed == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << endl;
    system("pause");    // щоб вікно не закривалося одразу
    return failed == 0 ? 0 : 1;
}
