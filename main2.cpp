/*
 * C++ Program to Implement Hash Tables with Double Hashing
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iterator>
#define MIN_TABLE_SIZE 5
using namespace std;

bool isPrime(int x);
int findNextPrime(int y);
/*
 * Node Type Declaration
 */
enum EntryType {Legitimate, Empty, Deleted};
/*
 * Node Declaration
 */
struct HashNode
{
    int key;
    string name;
    double gpa;
    enum EntryType info;
};
/*
 * Table Declaration
 */
struct HashTable
{
    int size;
    HashNode *table;
    
};


/*
 * Function to Genereate First Hash
 */
int HashFunc1(int key, int size)
{
    return (key % 492113) % size;
}
/*
 * Function to Genereate Second Hash
 */
int HashFunc2(int key, int size)
{
    if ((key % 392113) % size == 0) 
        return 1;
    else
        return (key % 392113) % size;
}
/*
 * Function to Initialize Table
 */
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
    htable->table = new HashNode [htable->size];
    if (htable->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    for (int i = 0; i < htable->size; i++)
    {
        htable->table[i].info = Empty;
        htable->table[i].key = -1;
        htable->table[i].name = "";
        htable->table[i].gpa = -1;
    }
    return htable;
}
/*
 * Function to Find key from the table
 */
int Find(int key, HashTable *htable)
{
    int hashVal= HashFunc1(key, htable->size);
    int stepSize= HashFunc2(key, htable->size);
    while (htable->table[hashVal].info != Empty &&
           htable->table[hashVal].key != key)
    {
        hashVal = hashVal + stepSize;
        hashVal = hashVal % htable->size;
    }
    return hashVal;
}

void lookup(int key, HashTable *htable)
{
    int pos = Find(key, htable);
    if(key == htable->table[pos].key&&htable->table[pos].info==Legitimate)
        cout<<"item found; "<<htable->table[pos].name<<" "<<pos<<endl;
    else
        cout<<"item not found"<<endl;
}

void remove(int key, HashTable *htable)
{
    int pos = Find(key, htable);
    if(key == htable->table[pos].key&&htable->table[pos].info==Legitimate)
        {
            htable->table[pos].info = Deleted;
            cout<<"item successfully deleted; "<<htable->table[pos].name<<" "<<pos<<endl;
        }
    else
        cout<<"item not present in the table"<<endl;
}
/*
 * Function to Insert key into the table
 */
void Insert(int key, string name, double gpa, HashTable *htable)
{
    cout<<"insertting"<<endl;
    int pos = Find(key, htable);
    if (htable->table[pos].info == Legitimate && htable->table[pos].key == key)
    {
        cout<<"item already present"<<endl;
        return;
    }
    
    if (htable->table[pos].info != Legitimate )
    {
        htable->table[pos].info = Legitimate;
        htable->table[pos].key = key;
        htable->table[pos].name = name;
        htable->table[pos].gpa = gpa;
        cout<<"item successfully inserted"<<endl;
    }
}
/*
 * Function to Rehash the table
 */
HashTable *Rehash(HashTable *htable)
{
    int size = htable->size;
    int newsize = findNextPrime(2*size);
    HashNode *table = htable->table;
    htable = initializeTable(newsize);
    for (int i = 0; i < size; i++)
    {
        cout<<"rehash forloop working"<<endl;
        if (table[i].info == Legitimate)
            Insert(table[i].key, table[i].name, table[i].gpa, htable);
    }
    //free(table);
    cout<<"rehash successful"<<endl;

    return htable;
}
/*
 * Function to Retrieve the table
 */
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
        else if(htable->table[i].info == Deleted)
            continue;
        else
            cout<<"("<<value<<","<<name<<","<<gpa<<")";
    }
    cout<<endl;
 
}
/*
 *
 * Next prime function
 *
 */
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
/*
 * Main Contains Menu
 */
int main()
{
    int ret, key, value, size, pos, i = 1;
    string name, input, operation;
    double gpa;
    int choice;
    HashTable *htable;
    htable = initializeTable(5);

        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Double Hashing"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Initialize size of the table"<<endl;
        cout<<"2.Insert key into the table"<<endl;
        cout<<"3.Display Hash Table"<<endl;
        cout<<"4.Rehash The Table"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
    while(1)
    {
        
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
        else if (operation == "delete")
            choice = 3;
        else if (operation == "print")
            choice = 4;
        else if (operation == "rehash")
            choice = 5;
        else
            choice = -1;


        switch(choice)
        {
        case 1:
            i++;
            if ((i / htable->size) > 0.7)
            {
                htable = Rehash(htable);
                cout<<"table doubled"<<endl;
                continue;
            }
            Insert(key, name, gpa, htable);
            
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



















       /* switch(choice)
        {
        case 1:
            cout<<"Enter size of the Hash Table: ";
            cin>>size;
            htable = initializeTable(size);
            break;
        case 2:
            if (i > htable->size)
            {
                cout<<"Table is Full, Rehash the table"<<endl;
                continue;
            }
        	cout<<"Enter key to be inserted: ";
        	cin>>value;
            Insert(key, name, gpa, htable);
            i++;
            break;
        case 3:
            Retrieve(htable);
            break;
        case 4:
            htable = Rehash(htable);
            break;
        case 5:
            exit(1);
        default:
           cout<<"\nEnter correct option\n"; */
       }
    }
    return 0;
}