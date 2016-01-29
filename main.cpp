/*
 * CS130A Proj1
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;
const int TSIZE = 5;
 
/*
 * HashNode Class Declaration
 */
class HashNode
{
    public:
        int key;
        string value;
        double gpa;
        HashNode(int key, string value, double GPA)
        {
            this->key = key;
            this->value = value;
            this->gpa = gpa;
        }
};
 
/*
 * DeletedNode Class Declaration
 */
class DeletedNode:public HashNode
{
    private:
        static DeletedNode *entry;
        DeletedNode():HashNode(-1, "", -1.0)
        {}
    public:
        static DeletedNode *getNode()
        {
            if (entry == NULL)
                entry = new DeletedNode();
            return entry; 
        }
};
DeletedNode *DeletedNode::entry = NULL;
/*
 * HashMap Class Declaration
 */
class HashMap
{
    private:
        HashNode **htable;
    public:
        HashMap()
        {
            htable = new HashNode* [TSIZE];
            for (int i = 0; i < TSIZE; i++)
            {
                htable[i] = NULL;
            }
        }
 
        ~HashMap()
        {
            for (int i = 0; i < TSIZE; i++)
            {
                if (htable[i] != NULL && htable[i] != DeletedNode::getNode())
                    delete htable[i];
            }
            delete[] htable;
        }
        /*
         * Hash Function
         */
        int HashFunc(int key)
        {
            return (key%492113) % TSIZE;
        }
        /*
         * Insert Element at a key
         */
        void Insert(int key, string value, double gpa)
        {
            int hash_val = HashFunc(key);
            int init = -1;
            int deletedindex = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                if (htable[hash_val] == DeletedNode::getNode())
                    deletedindex = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }

            if(htable[hash_val] != NULL && 
                hash_val != init &&
                htable[hash_val]->key == key) 
            {
                cout<<"item already present"<<endl;
                return;

            }
            if (htable[hash_val] == NULL || hash_val == init)
            {
                if(deletedindex != -1)
                    htable[deletedindex] = new HashNode(key, value, gpa);
                else
                    htable[hash_val] = new HashNode(key, value, gpa);

                cout<<"item successfully inserted"<<endl;
            }
            if(init != hash_val)
            {
                if (htable[hash_val] != DeletedNode::getNode())
                {
                    if (htable[hash_val] != NULL)
                    {
                        if (htable[hash_val]->key == key)
                        {
                            htable[hash_val]->value = value;
                            htable[hash_val]->gpa = gpa;
                            //cout<<"item successfully inserted"<<endl;
                            
                        }
                    }
                }
                else
                {
                    htable[hash_val] = new HashNode(key, value, gpa);
                    cout<<"item successfully inserted2222"<<endl;
                }
            }
        }
        /*
         * Search Element at a key
         */
        string Search(int key)
        {
            int hash_val = HashFunc(key);
            int init = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (htable[hash_val]== NULL || hash_val==init)
                return "NO";
            else
            {
                int position = hash_val; //might need +1
                string value = htable[hash_val]->value;
                string index;
                stringstream convert;
                convert << position;
                index = convert.str();

                return value + " " + index;
            }
        }
        /*
         * Remove Element at a key
         */
        void Remove(int key)
        {
            int hash_val = HashFunc(key);
            int init = -1;
            if(htable[hash_val] == NULL || 
                hash_val == init ||
                htable[hash_val]->key != key) 
            {
                cout<<"item not present in the table"<<endl;
                return;

            }
            while (hash_val != init&&(htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL&&htable[hash_val]->key!=key))
            {
                if (init == -1)
                    init = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (hash_val != init && htable[hash_val] != NULL)
            {
                delete htable[hash_val];
                htable[hash_val] = DeletedNode::getNode();
                cout<<"item successfully deleted"<<endl;
            }
        }

        string print()
        {
            string print;
            int hash_val = 0;
            while(1)
            {
                if (hash_val == TSIZE)
                    break;
                
                if(htable[hash_val] == NULL)
                {
                    hash_val++;
                   // cout<<hash_val<<endl; FOR DEBUGGING
                    continue;
                }

                if (htable[hash_val]->key == -1)
                {
                    hash_val++;
                    continue;
                }
                
                int perm = htable[hash_val]->key;
                string name = htable[hash_val]->value;
                double score = htable[hash_val]->gpa;

                string permstr;
                string scorestr;

                stringstream convert;
                convert << perm;
                permstr = convert.str();

                stringstream convert2;
                convert2 << score;
                scorestr = convert2.str();



                print.append("(");
                print.append(permstr);
                print.append(",");
                print.append(name);
                print.append(",");
                print.append(scorestr);
                print.append(")");

                hash_val++;                
            }
            return print;
        }



};
 
/*
 * Main Contains Menu
 */
int main()
{
    HashMap hash;
    int key; //value;
    string value;
    double gpa;
    int choice;
    string input;
    string operation;
    string name;
    //double gpa;

    cout<<"\n----------------------"<<endl;
    cout<<"Operations on Hash Table"<<endl;
    cout<<"\n----------------------"<<endl;
    cout<<"insert <perm> <name> <GPA>"<<endl;
    cout<<"lookup <perm>"<<endl;
    cout<<"delete <perm>"<<endl;

    while(1)
    {
        

        //cin>>choice;


        getline (cin,input);
        stringstream stream(input);

        stream >> operation;
        stream >> key;
        stream >> value;
        stream >> gpa;
        //stream >> name;
        
        //stream >> gpa;
        

        if(operation == "insert")
            choice = 1;
        else if (operation == "lookup")
            choice = 2;
        else if (operation == "delete")
            choice = 3;
        else if (operation == "print")
            choice = 4;
        else
            choice = -1;


        switch(choice)
        {
        case 1:
            /*
            cout<<"Enter element to be inserted: ";
            cin>>value;
            cout<<"Enter key at which element to be inserted: ";
            cin>>key;
            */

            hash.Insert(key, value, gpa);
          //  cout<<key<<" "<<value<<" "<<gpa<<" "<<endl;
            //cout<<"item successfully inserted"<<endl;
            break;

        case 2:
            /*
            cout<<"Enter key of the element to be searched: ";
            cin>>key;
            */
            if(hash.Search(key)=="NO")
            {
                cout<<"item not found"<<endl;
                continue;
            }
            else
            {
                cout<<"item found at "<<key<<" ; ";
                cout<<hash.Search(key)<<endl;
            }
            break;

        case 3:
            
            hash.Remove(key);
            //cout<<"item successfully deleted"<<endl;
            break;

        case 4:
            cout<<hash.print()<<endl;
            break;
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}