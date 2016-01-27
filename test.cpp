/*
 * C++ Program to Implement Hash Tables with Linear Probing
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;
const int TABLE_SIZE = 5;
  
/*
 * Main Contains Menu
 */
int main()
{
    int key, value;
    int choice;
    string input;
    string operation;
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
        stream >> key;
        stream >> name;
        stream >> gpa;

        if(operation == "insert")
            choice = 1;
        else if (operation == "lookup")
            choice = 2;
        else if (operation == "remove")
            choice = 3;

        if(key == 12345)
            choice = 4;

        if(gpa == 4.2)
            choice = 5;

        cout<<choice<<endl;

    }
    return 0;
}