/*
 * C++ Program to Implement Hash Tables with Linear Probing
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
using namespace std;
const int TSIZE = 5;
int factor = 5;
double current = 0.0;
  
/*
 * Main Contains Menu
 */


int findNextPrime(int n); 
bool isPrime(int n);  

int main()
{

    int key, value;
    int choice;
    string input;
    int operation;
    string name;
    double gpa;

    


    while(1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        //cin>>choice;
        getline (cin,input);
        stringstream stream(input);

        stream >> operation;
        findNextPrime(operation);
        cout<<findNextPrime(operation)<<endl;
        break;
        

    }
    return 0;
}

bool isPrime(int n)
{
    //loop from 2 to n/2 to check for factors
    for (int i = 2; i <= n/2; i++)
    {
        if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
            return false;
    }

    return true;
}

int findNextPrime(int n)
{
    int nextPrime = n;
    bool found = false;

    if(isPrime(n))
        return n;

    //loop continuously until isPrime returns true for a number above n
    while (!found)
    {
        nextPrime++;
        if (isPrime(nextPrime))
            found = true;
    }

    return nextPrime;
}
