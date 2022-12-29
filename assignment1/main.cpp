#include "polynomial.h"
#include <iostream>
using namespace std;

int main()
{    
    int testCase = 1;
    cout << "Hello! Which test case do you want to run? ";
    cin >> testCase;
    // testCase = 5;
    // for(;testCase<=22;testCase++)`

    {
        cout << endl << "Test case " << testCase << ":" << endl;
        cout << "===================================" << endl;



        if(testCase == 1) //test the print function with the pre-made polynomials
        {
            for(int i=1; i<=4; i++)
            {
                Polynomial p(i);
                cout << "Polynomial " << i << ": \"";
                p.print();
                p.print();
                cout << "\"";
                cout << endl;
            }
        }
        else if(testCase == 2) //test the print function with the pre-made polynomials
        {
            for(int i=5; i<=7; i++)
            {
                Polynomial p(i);
                cout << "Polynomial " << i << ": \"";
                p.print();
                cout << "\"";
                cout << endl;
            }
        }
        else if(testCase == 3) //test the print function with the pre-made polynomials
        {
            for(int i=8; i<=15; i++)
            {
                Polynomial p(i);
                cout << "Polynomial " << i << ": \"";
                p.print();
                cout << "\"";
                cout << endl;
            }
        }

        else if(testCase == 4) //test the default constructor
        {
            Polynomial p;
            cout << "\"";
            p.print();
            cout << "\"";
        }
        
        else if(testCase == 5) //test the deep copy constructor
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(*p1);
            delete p1;
            cout << "\ncopy of p1: \"";
            p2->print();
            cout << "\"";
            delete p2;
        }

        else if(testCase == 6) //test the array constructor
        {                   
            int arr[12] = {0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 5};
            Polynomial* p1 = new Polynomial(arr, 12);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            delete p1;
        }
        else if(testCase == 7) //test the array constructor
        {
            int arr[7] = {8, 6, 4, 0, 0, 0, 1};
            Polynomial* p1 = new Polynomial(arr, 7);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(*p1);
            delete p1;
            cout << "\ncopy of p1: \"";
            p2->print();
        }
        else if(testCase == 8) //test the array constructor
        {
            int arr[4] = {2, 0, 0, 2};
            Polynomial* p1 = new Polynomial(arr, 4);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            delete p1;
        }

        else if(testCase == 9) //test add
        {
            Polynomial* p1 = new Polynomial(2);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(3);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->add(*p2);
            cout << "\np1+p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 10) //test add
        {
            for (int i = 1; i <= 19; i++) {
                for (int j = 1; j <= 19; j++) {
                    Polynomial* p1 = new Polynomial(i);
                    cout << "p1: \"";
                    p1->print();
                    cout << "\"";
                    Polynomial* p2 = new Polynomial(j);
                    cout << "\np2: \"";
                    p2->print();
                    cout << "\"";
                    Polynomial p3 = p1->add(*p2);
                    Polynomial p4 = p2->add(*p1);
                    cout << "\np3: \"";
                    p3.print();
                    cout << "\"";
                    cout << "\np4: \"";
                    p4.print();
                    cout << "\"";
                    cout << endl;
                    for (int k = 2; k <= 4; k++) {
                        int temp1 = p1->evaluate(k) + p2->evaluate(k);
                        int temp2 = p3.evaluate(k);
                        int temp3 = p2->evaluate(k) + p1->evaluate(k);
                        int temp4 = p4.evaluate(k);
                        cout << (temp1 == temp2) << " " << (temp3 == temp4) << " " << 
                        temp1 << " " << temp2 << " " << temp3 << " " << temp4 << endl;
                    }
                    cout << "\np1+p2: \"";
                    p3.print();
                    cout << "\"" << endl;
                    cout << endl;
                    delete p1;
                    delete p2;
                }
            }
        }
        else if(testCase == 11) //test add
        {
            Polynomial* p1 = new Polynomial();
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial();
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->add(*p2);
            cout << "\np1+p2: \"";
            p3.print();
            cout << "\"";
            Polynomial x;
            Polynomial p4 = p3.add(x);
            cout << "\np3+p3: \"";
            p4.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        
        else if(testCase == 12) //test subtract
        {
            for (int i = 1; i <= 19; i++) {
                for (int j = 1; j <= 19; j++) {
                    Polynomial* p1 = new Polynomial(i);
                    cout << "p1: \"";
                    p1->print();
                    cout << "\"";
                    Polynomial* p2 = new Polynomial(j);
                    cout << "\np2: \"";
                    p2->print();
                    cout << "\"";
                    Polynomial p3 = p1->subtract(*p2);
                    Polynomial p4 = p2->subtract(*p1);
                    cout << "\np3: \"";
                    p3.print();
                    cout << "\"";
                    cout << "\np4: \"";
                    p4.print();
                    cout << "\"";
                    cout << endl;
                    for (int k = 3; k <= 5; k++) {
                        int temp1 = p1->evaluate(k) - p2->evaluate(k);
                        int temp2 = p3.evaluate(k);
                        int temp3 = p2->evaluate(k) - p1->evaluate(k);
                        int temp4 = p4.evaluate(k);
                        cout << (temp1 == temp2) << " " << (temp3 == temp4) << " " << 
                        temp1 << " " << temp2 << " " << temp3 << " " << temp4 << endl;
                    }
                    cout << endl;
                    cout << "\np1-p2: \"";
                    p3.print();
                    cout << "\"" << endl << endl;
                    delete p1;
                    delete p2;
                }
            }
        }
        else if(testCase == 13) //test subtract
        {
            Polynomial* p1 = new Polynomial(17);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(16);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->subtract(*p2);
            cout << "\np1-p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 14) //test subtract
        {
            Polynomial* p1 = new Polynomial(8);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(10);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->subtract(*p2);
            cout << "\np1-p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }

        else if(testCase == 15) //test multiply
        {
            for (int i = 1; i <= 19; i++) {
                for (int j = 1; j <= 19; j++) {
                    Polynomial* p1 = new Polynomial(i);
                    cout << "p1: \"";
                    p1->print();
                    cout << "\"";
                    Polynomial* p2 = new Polynomial(j);
                    cout << "\np2: \"";
                    p2->print();
                    cout << "\"";
                    Polynomial p3 = p1->multiply(*p2);
                    Polynomial p4 = p2->multiply(*p1);
                    cout << "\np3: \"";
                    p3.print();
                    cout << "\"";
                    cout << "\np4: \"";
                    p4.print();
                    cout << "\"";
                    cout << endl;
                    for (int k = 22; k <= 25; k++) {
                        int temp1 = p1->evaluate(k) * p2->evaluate(k);
                        int temp2 = p3.evaluate(k);
                        int temp3 = p4.evaluate(k);
                        // cout << temp1 << " " << temp2 << " " << temp3 << " " <<
                        cout << (temp1 == temp2) << " " << (temp1 == temp3) << " ";
                    }
                    cout << endl;
                    cout << "\np1*p2: \"";
                    p3.print();
                    cout << "\"" << endl << endl;
                    delete p1;
                    delete p2;
                }
            }
        }
        
        else if(testCase == 16) //test multiply
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(1);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->multiply(*p2);
            cout << "\np1*p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 17) //test multiply
        {
            Polynomial* p1 = new Polynomial(13);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(14);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->multiply(*p2);
            cout << "\np1*p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        

        else if(testCase == 18) //test evaluate
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            cout << "\np1(2): ";
            cout << p1->evaluate(-2);
            delete p1;
        }
        else if(testCase == 19) //test evaluate
        {
            for (int i = 1; i <= 19; i++) {
                Polynomial* p1 = new Polynomial(i);
                cout << "p1: \"";
                p1->print();
                cout << "\"  ";
                cout << "p1(2): ";
                cout << p1->evaluate(-2) << endl;
                delete p1;
            }
        }

        else if(testCase == 20) //test compare
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(2);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            cout << "\ncompare p1 and p2: ";
            cout << p1->compare(*p2);
            cout << "\ncompare p2 and p1: ";
            cout << p2->compare(*p1);
            delete p1;
            delete p2;
        }
        else if(testCase == 21) //test compare
        {
            Polynomial* p1 = new Polynomial(9);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(8);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            cout << "\ncompare p1 and p2: ";
            cout << p1->compare(*p2);
            cout << "\ncompare p2 and p1: ";
            cout << p2->compare(*p1);
            delete p1;
            delete p2;
        }
        else if(testCase == 22) //test compare
        {
            int arr[1] = {0};
            Polynomial* p1 = new Polynomial(arr, 1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            int arr2[3] = {0,0,-1};
            Polynomial* p2 = new Polynomial(arr2, 3);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            cout << "\ncompare p1 and p2: ";
            cout << p1->compare(*p2);
            cout << "\ncompare p2 and p1: ";
            cout << p2->compare(*p1);
            delete p1;
            delete p2;
        }
        else if (testCase == 23) 
        {
            for (int i = 1; i <= 19; i++) {
                for (int j = 1; j <= 19; j++) {
                    Polynomial* p1 = new Polynomial(i);
                    cout << "p1: \"";
                    p1->print();
                    cout << "\"";
                    Polynomial* p2 = new Polynomial(j);
                    cout << "\np2: \"";
                    p2->print();
                    cout << "\"";
                    cout << "\ncompare p1 and p2: ";
                    cout << p1->compare(*p2);
                    cout << "\ncompare p2 and p1: ";
                    cout << p2->compare(*p1);
                    delete p1;
                    delete p2;
                    cout << endl<< endl;
                }
            }
        }

        cout << endl << "===================================" << endl;
    }

    return 0;
}