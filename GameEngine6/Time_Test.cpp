#include "Time_Test.h"



void Time_Test::Action()
{
    using namespace std;

    cout << "No.1"<<endl;
    
    double sum = 0;
    for (int i = 0; i < count_N; ++i) {
        clock_t start = clock();      // *************** スタート時間

        for (int j = 0; j < one_cycle_N; j++)
        {
            Test_1();
        }

        clock_t end = clock();        // *************** エンド時間
        cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";
    }
    cout << endl;

    cout << "No.2" << endl;

    for (int i = 0; i < count_N; ++i) {
        clock_t start = clock();      // *************** スタート時間

        for (int j = 0; j < one_cycle_N; j++)
        {
            Test_2();
        }

        clock_t end = clock();        // *************** エンド時間
        cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";
    }

    cout << endl;
}

int* return_1()
{
    int a = 10;
    return &a;
}

int& return_2()
{
    int a = 10;
    return a;
}

void Time_Test::Test_1()
{
    int* a = return_1();
    
}

void Time_Test::Test_2()
{
    int& a = return_2();
}
