/*

CS130A WINT2016 
PROJECT 1 

BY: NICHOLAS POON
DATE: 1/31/2016
INSTRUCTOR: AMR EL ABBADI
COURSE: CS130A

*/

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
using namespace std;

bool success = false;
bool isLinear = false;
double i = 0.0;

bool isPrime(int x);
int findNextPrime(int y);

//HASH FUNCTIONS
//Linear Probing uses only 1  
int hash1(int key, int size)
{
    return (key % 492113) % size;
}

int hash2(int key, int size)
{
    if ((key % 392113) % size == 0) 
        return 1;
    else
        return (key % 392113) % size;
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

//Makes empty table
HashTable *initialize(int size)
{
    HashTable *htable;
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
        cout<<"initialize table UNSUCCESSFUL"<<endl;
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

//Looks for empty slot on table with doublehashing
int Find(int key, HashTable *htable)
{
    int hashkey= hash1(key, htable->size);
    int step= hash2(key, htable->size);

    while (htable->table[hashkey].status != Empty &&
           htable->table[hashkey].key != key)
    {
        hashkey = hashkey + step;
        hashkey = hashkey % htable->size;
    }
    return hashkey;
}

//Looks for empty slot on table with linear probing
int linearFind(int key, HashTable *htable)
{
    int hashkey = hash1(key, htable->size);

    while (htable->table[hashkey].status != Empty &&
           htable->table[hashkey].key != key)
    {
        hashkey++;
        hashkey = hashkey % htable->size;
        
    }
    return hashkey;
}

//Returns item's position and content
void lookup(int key, HashTable *htable)
{
    int pos = Find(key, htable);

    if(isLinear)
        pos = linearFind(key, htable);

    if(key == htable->table[pos].key&&htable->table[pos].status==Full)
        cout<<"item found; "<<htable->table[pos].name<<" "<<pos<<endl;
    else
        cout<<"item not found"<<endl;
}

//Removes item at position if present
void remove(int key, HashTable *htable)
{
    
    int pos = Find(key, htable);

    if(isLinear)
        pos = linearFind(key, htable);
    
    if(key == htable->table[pos].key&&htable->table[pos].status==Full)
    {
        htable->table[pos].status = Deleted;
        cout<<"item successfully deleted"<<endl;
    }
    else
        cout<<"item not present in the table"<<endl;
}

//Insert item in empty slot
void Insert(int key, string name, double gpa, HashTable *htable)
{
    int pos = Find(key, htable);

    if(isLinear)
        pos = linearFind(key, htable);
    
    if (htable->table[pos].status == Full && htable->table[pos].key == key)
    {
        success = false;
        return;
    }
    
    if (htable->table[pos].status != Full )
    {
        htable->table[pos].status = Full;
        htable->table[pos].key = key;
        htable->table[pos].name = name;
        htable->table[pos].gpa = gpa;
        success = true;
        //cout<<"item successfully inserted"<<endl;
    }
}

//Double table size (to the nearest prime), then rehash.
HashTable *rehash(HashTable *htable)
{
    int size = htable->size;
    int newsize = findNextPrime(2*size);
    Student *table = htable->table;
    htable = initialize(newsize);

    for (int i = 0; i < size; i++)
    {
        if (table[i].status == Full)
            Insert(table[i].key, table[i].name, table[i].gpa, htable);
    }
    //cout<<"rehash successful"<<endl;

    return htable;
}

//Prints entire table in format of (key,name,gpa)
void print(HashTable *htable)
{
    for (int i = 0; i < htable->size; i++)
    {
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


int main()
{
    int ret, key, value, pos, choice;
    string name, input, operation, hashkind, op;
    double gpa;
    HashTable *htable;
    double factor, load = 0.00;

    htable = initialize(5);
    
    getline(cin,hashkind);
    
    stringstream stream0(hashkind);
    stream0 >> op;

    if(op == "doublehashing")
    {
        isLinear = false;
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
            else
                choice = 5;


            switch(choice)
            {
                case 1:
                    
                    pos = Find(key, htable);
                    if (htable->table[pos].status == Full && htable->table[pos].key == key)
                    {
                        cout<<"item already present"<<endl;
                        break;
                    }
                    i++;
                    factor = (i / htable->size);
                    if (factor >= 0.7)
                    {
                        htable = rehash(htable);
                        cout<<"table doubled"<<endl;
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
                    print(htable);
                    break;

                case 5:
                    exit(1);
                default:
                   cout<<"\n";
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
            else
                choice = 5;

            switch(choice)
            {
                case 1:
                    
                    pos = linearFind(key, htable);
                    if (htable->table[pos].status == Full && htable->table[pos].key == key)
                    {
                        cout<<"item already present"<<endl;
                        break;
                    }
                    i = i + 1.0;
                    factor = (i / htable->size);
                    if (factor >= 0.71)
                    {
                        htable = rehash(htable);
                        cout<<"table doubled"<<endl;
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
                    print(htable);
                    break;

                case 5:
                    exit(1);
                default:
                   cout<<"\n";
            }

        }
    }





    return 0;
}