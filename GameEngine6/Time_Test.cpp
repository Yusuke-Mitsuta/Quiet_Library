#include "Time_Test.h"

#include"Array.h"

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
   // N_Tuple::I_Apply_Action<std::array<int, 4>, int, int, int, int>::Apply(2, 4, 4, 7);
   // constexpr 

    //constexpr 
    Array<int, 4> i{5, 10, 4,4};



     

   // std::array i{ 2, 3, 4, 5 };
}

void Time_Test::Test_2()
{
    //N_Array::S_Storge<int,4> i{ 2, 5, 10, 4 };
    
    int n = 0;
    std::array i{n, 3, 4, 5};
    //int a[4] = { 1,3,4,9 };
}
