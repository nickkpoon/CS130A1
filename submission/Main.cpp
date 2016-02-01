//CS130A PROJECT 1 DOUBLEHASHING BY: NICHOLAS POON
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iterator>
#include <iomanip>
#include "Student.h"
#include "Hashtable.h"
#define MIN_TABLE_SIZE 5
using namespace std;
bool success = false;
bool isLinear = false;

bool isPrime(int x);
int findNextPrime(int y);

double i = 0.00;

int Hash1(int key, int size)
{
    return (key % 492113) % size;
}

int Hash2(int key, int size)
{
    if ((key % 392113) % size == 0) 
        return 1;
    else
        return (key % 392113) % size;
}

HashTable *initializeTable(int size)
{
    HashTable *htable;
    if (size < MIN_TABLE_SIZE)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    htable = new HashTable;
    if (htable == NULL)
    {
        cout<<"Out of Space"<<endl;
        return NULL;
    }
    htable->size = size;
    htable->table = new Student [htable->size];
    if (htable->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    for (int i = 0; i < htable->size; i++)
    {
        htable->table[i].status = Empty;
        htable->table[i].key = -1;
        htable->table[i].name = "";
        htable->table[i].gpa = -1;
    }
    return htable;
}

int Find(int key, HashTable *htable)
{
    int value= Hash1(key, htable->size);
    int step= Hash2(key, htable->size);
    while (htable->table[value].status != Empty &&
           htable->table[value].key != key)
    {
        value = value + step;
        value = value % htable->size;
    }
    return value;
}

int linearFind(int key, HashTable *htable)
{
    int value = Hash1(key, htable->size);
    int count = 0;

    while (htable->table[value].status != Empty &&
           htable->table[value].key != key)
    {
        value++;
        value = value % htable->size;
        /*if(!(htable->table[value+1]))
            value = 0;*/

        
        //value = value % htable->size;
    }
    return value;
}

void lookup(int key, HashTable *htable)
{
        int pos = Find(key, htable);
        if(isLinear)
            pos = linearFind(key, htable);
    if(key == htable->table[pos].key&&htable->table[pos].status==Legitimate)
        cout<<"item found; "<<htable->table[pos].name<<" "<<pos<<endl;
    else
        cout<<"item not found"<<endl;
}

void remove(int key, HashTable *htable)
{
    
        int pos = Find(key, htable);
        if(isLinear)
            pos = linearFind(key, htable);
    
    if(key == htable->table[pos].key&&htable->table[pos].status==Legitimate)
        {
            htable->table[pos].status = Deleted;
            cout<<"item successfully deleted"<<endl;
        }
    else
        cout<<"item not present in the table"<<endl;
}

void Insert(int key, string name, double gpa, HashTable *htable)
{
    //cout<<"insertting"<<endl;
    int pos = Find(key, htable);
    if(isLinear)
        pos = linearFind(key, htable);
    
    if (htable->table[pos].status == Legitimate && htable->table[pos].key == key)
    {
        //cout<<"item already present"<<endl;
        success = false;
        return;
    }
    
    if (htable->table[pos].status != Legitimate )
    {
        htable->table[pos].status = Legitimate;
        htable->table[pos].key = key;
        htable->table[pos].name = name;
        htable->table[pos].gpa = gpa;
        success = true;
        //cout<<"item successfully inserted"<<endl;
    }
}

HashTable *Rehash(HashTable *htable)
{
    int size = htable->size;
    int newsize = findNextPrime(2*size);
    Student *table = htable->table;
    htable = initializeTable(newsize);
    for (int i = 0; i < size; i++)
    {
        //cout<<"rehash forloop working"<<endl;
        if (table[i].status == Legitimate)
            Insert(table[i].key, table[i].name, table[i].gpa, htable);
    }
    //free(table);
    //cout<<"rehash successful"<<endl;

    return htable;
}

void Retrieve(HashTable *htable)
{
    for (int i = 0; i < htable->size; i++)
    {
        //<<"forloop working."<<endl;
        int value = htable->table[i].key;
        string name = htable->table[i].name;
        double gpa = htable->table[i].gpa;

        if (value == -1)
            continue;
        else if(htable->table[i].status == Deleted)
            continue;
        else
        {
            cout<<"("<<value<<","<<name<<",";
            cout<<std::fixed<<std::setprecision(1)<<gpa;
            cout<<")";
        }
    }
    cout<<endl;
 
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


int main()
{
    int ret, key, value, size, pos;
    string name, input, operation, hashkind, op;
    double gpa;
    int choice;
    HashTable *htable;
    htable = initializeTable(5);
    double factor, load = 0.00;


    getline(cin,hashkind);
    
    stringstream stream0(hashkind);

    stream0 >> op;

    if(op == "doublehashing")
    {
        isLinear = false;
        while(getline (cin,input))
        {
            
            //cin>>choice;

            //getline (cin,input);
            /*if (!getline(cin, hashkind));
            {
                cout<<"!getLine"<<endl;
                return 0;
            }*/
            stringstream stream(input);

            stream >> operation;
            stream >> key;
            stream >> name;
            stream >> gpa;

            if(operation == "insert")
                choice = 1;
            else if (operation == "lookup")
                choice = 2;
            else if (operation == "delete")
                choice = 3;
            else if (operation == "print")
                choice = 4;
            else if (operation == "rehash")
                choice = 5;
            else
                choice = 6;


            switch(choice)
            {
                case 1:
                    
                    pos = Find(key, htable);
                    if (htable->table[pos].status == Legitimate && htable->table[pos].key == key)
                    {
                        cout<<"item already present"<<endl;
                        break;
                    }
                    i++;
                    factor = (i / htable->size);
                    //cout<<factor<<endl;
                    if (factor >= 0.7)
                    {
                        htable = Rehash(htable);
                        cout<<"table doubled"<<endl;
                        //continue;
                    }
                    Insert(key, name, gpa, htable);
                    if(success)
                        cout<<"item successfully inserted"<<endl;
                    else
                        cout<<"BAD!!!!!!!item already present"<<endl;
                    
                    
                    break;
                case 2:
                    lookup(key, htable);
                    break;                   
                
                case 3:
                    remove(key, htable);
                    break;

                case 4:
                    Retrieve(htable);
                    break;

                case 5:
                    htable = Rehash(htable);
                    break;
                case 6:
                    exit(1);
                default:
                   cout<<"\nEnter correct option\n";
            }

        }
       
    }

    if(op == "linearprobing")
    {
        isLinear = true;
        while(getline (cin,input))
        {
            
            
            stringstream stream(input);

            stream >> operation;
            stream >> key;
            stream >> name;
            stream >> gpa;

            if(operation == "insert")
                choice = 1;
            else if (operation == "lookup")
                choice = 2;
            else if (operation == "delete")
                choice = 3;
            else if (operation == "print")
                choice = 4;
            else if (operation == "rehash")
                choice = 5;
            else
                choice = 6;


            switch(choice)
            {
                case 1:
                    
                    pos = linearFind(key, htable);
                    if (htable->table[pos].status == Legitimate && htable->table[pos].key == key)
                    {
                        cout<<"item already present"<<endl;
                        break;
                    }
                    i = i + 1.0;
                    factor = (i / htable->size);
                    cout<< std::fixed<<std::setprecision(2)<<factor;
                    if (factor > 0.701)
                    {
                        htable = Rehash(htable);
                        cout<<"table doubled"<<endl;
                        //continue;
                    }
                    Insert(key, name, gpa, htable);
                    if(success)
                        cout<<"item successfully inserted"<<endl;
                    else
                        cout<<"BAD!!!!!!!item already present"<<endl;
                    
                    
                    break;
                case 2:
                    lookup(key, htable);
                    break;                   
                
                case 3:
                    remove(key, htable);
                    break;

                case 4:
                    Retrieve(htable);
                    break;

                case 5:
                    htable = Rehash(htable);
                    break;
                case 6:
                    exit(1);
                default:
                   cout<<"\nEnter correct option\n";
            }

        }
    }





    return 0;
}