#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Node
{
public:
    Node* next;
    long long int data;
    Node(const long long int& item, Node* ptrnext = (Node*)NULL);
};

class HashTable
{
private:
    int N;
    Node** hash_table;               // An array that will hold the keys in separate chaining model with size N.
    int funct_select;                  // Function select 1 2 3 . 1 -> Folding 2->Middle Suqaring, 3-> Truncation
        // ********Inner Functions********
    bool ValidNumberCheck(const long long int& TC_number);           // Returns true if the given number is 11 digit false otherwise

    void FoldingAdd(long long int& TC_number);
    bool FoldingDelete(long long int& TC_number);          // Returns true if the item is found and deleted, false otherwise
    bool FoldingSearch(long long int& TC_number);

    void MiddleSquaringAdd(long long int& TC_number);
    bool MiddleSquaringDelete(long long int& TC_number);
    bool MiddleSquaringSearch(long long int& TC_number);

    void TruncationAdd(long long int& TC_number);
    bool TruncationDelete(long long int& TC_number);
    bool TruncationSearch(long long int& TC_number);
public:
    HashTable();
    ~HashTable();
    //HashTable& operator=(const HashTable& rhs);     // Assignment operator, will only assign if the hash sizes(N) are same!!
    //HashTable(const HashTable& obj);                // Copy constructor -> handle it later

    void LoadFromFile(string path);        // Should take the path and load value from it
    void PrintHashTable();

    void AddNewTC(long long int& TC_number);         // Checks funct_select variable and Inserts according to it
    bool DeleteTC(long long int& TC_number);            // Checks funct_select variable and Deletes according to it
    bool SearchTC(long long int& TC_number);            // Checks funct_select variable and Searchs according to it


};


int main()
{
    string path = "C:\\Users\\Halil\\Desktop\\Dersler\\441\\hash_table_init200.txt";    // DEFAULT PATH should be changed to be implemented on your PC!!
    HashTable* my_table_pntr = NULL;
    // TO DO -> LOOP
    cout << "Welcome user! You can select the operations to make changes on a Hash Table" << endl;

    while(true)
    {
        cout << endl;
        cout << "1(Initialize a Hash Table)         2(Load T.C ID Numbers from file)        3(Add New TC ID Number)" << endl;
        cout << "4(Delete a TC ID Number)           5(Search for a TC ID Number)            6(Print out Hash Table)" << endl;
        int given_number;
        cin >> given_number;
        if (given_number == 1)
        {
            if (my_table_pntr != (HashTable*)NULL)      // Deletes the old Hash Table if created before
                delete my_table_pntr;
            my_table_pntr = new HashTable;
            cout << "New Hash Table is created." << endl;
        }
        else if (given_number == 2)
        {
            cout << "Do you want to give your own path or use the default path from the code? 1: Default    2: Your own path" << endl;
            int dummy = 0;
            while (dummy > 2 || dummy < 1)
            {
                cin >> dummy;
                if (dummy == 1)      // Default path case, the default address in the code will be used!
                {
                    my_table_pntr->LoadFromFile(path);
                }
                else if (dummy == 2)
                {
                    cout << "Please enter a path now:" << endl;
                    string given_path;
                    cin >> given_path;
                    my_table_pntr->LoadFromFile(given_path);
                }
                else cout << "Please enter 1 or 2" << endl;
            }
        }
        else if (given_number == 3)      // Add New TC ID Number
        {
            cout << "Enter a 11 digit TC number to be added to Hash table" << endl;
            long long int dummy_number;
            cin >> dummy_number;
            my_table_pntr->AddNewTC(dummy_number);
        }
        else if (given_number == 4)
        {
            cout << "Enter a 11 digit TC number to be deleted from Hash table" << endl;
            long long int dummy_number;
            cin >> dummy_number;
            bool dummy_bool = my_table_pntr->DeleteTC(dummy_number);
            if (!dummy_bool)
                cerr << "Could not find the value" << endl;
        }
        else if (given_number == 5)
        {
            cout << "Enter a 11 digit TC number to be searched in Hash table" << endl;
            long long int dummy_number;
            cin >> dummy_number;
            bool dummy_bool = my_table_pntr->SearchTC(dummy_number);
            if (!dummy_bool)
                cerr << "Could not find the value given" << endl;
            else
                cout << "The value searched exists in the table" << endl;
        }
        else if (given_number == 6)
        {
            my_table_pntr->PrintHashTable();
        }
        else
            cerr << "Invalid Number Given!" << endl;
    }






    //long long int asdas = 84054721499;
    //HashTable mytable;
    //mytable.LoadFromFile(path);
    //mytable.PrintHashTable();
    //cout << mytable.SearchTC(asdas);
    //mytable.DeleteTC(asdas);
    //mytable.PrintHashTable();
}

Node::Node(const long long int& item, Node* ptrnext)       // constructor of the Node class
{
    data = item;
    next = ptrnext;
}

HashTable::HashTable()      // constructor is done
{
    cout << "Please enter the size of the Hash Table(between 10 and 101)" << endl;
    cin >> N;
    if(N > 100 || N < 10)
    {
        cerr << "Invalid N size " << N;
        exit(1);
    }
    hash_table = new Node*[N];                                           // Dynamic Memory Allocation !! Has to be dealt later.
    for(int i = 0; i < N; i++)                                           //     (Destructor and Assignment and Copy Constructor)
    {
        hash_table[i] = (Node*)NULL;
    }
    cout << "Please enter the function to be used, 1(Folding), 2(Middle Squaring), 3(Truncation): " << endl;
    cin >> funct_select;
    if(funct_select < 1 || funct_select > 3)
    {
        cerr << "Invalid function select number: " << funct_select;
        exit(1);
    }
}
HashTable::~HashTable()
{
    delete[] hash_table;
}
//HashTable& HashTable::operator=(const HashTable& rhs)       // Assignment Operator, handle it later
//{
//    //this->funct_select = rhs.funct_select;
//
//}

void HashTable::LoadFromFile(string path)
{
    string line;
    ifstream file;
    file.open(path);
    long long int dummy;
    if (file.is_open())
    {

        //  **********************************
        while (getline(file, line))                     // Getting the city names from the file is done here
        {                                               //  *****************************
            dummy = stoll(line, nullptr, 10);
            AddNewTC(dummy);
        }                                               // DONT FORGET TO COMPLETE
        file.close();
    }
    else cout << "Unable to open the file.";
}
// Prints the hash table with Seperate Chaining representative way.
void HashTable::PrintHashTable()
{
    cout << "Printing the table" << endl;
    if (funct_select == 1)
        cout << "Mode: Folding(1)" << endl;
    else if (funct_select == 2)
        cout << "Mode: Middle Squaring(2)" << endl;
    else if (funct_select == 3)
        cout << "Mode: Truncation(3)" << endl;
    for(int i = 0; i < N; i++)
    {
        cout << i << ": ";
        Node* hash_value_pointer = hash_table[i];
        while(hash_value_pointer != (Node*)NULL)
        {
            cout << hash_value_pointer->data << "->";
            hash_value_pointer = hash_value_pointer->next;
        }
        cout << "/" << endl;
    }
}

bool HashTable::ValidNumberCheck(const long long int& TC_number)    // Checks the given number is 11 digit or not
{
    long long int dummy = TC_number;
    int i = 0;
    if (dummy < 0)          // Negativity check.
    {
        cerr << "Invalid Number is given: " << dummy << endl;
        return false;
    }
    while(dummy)
    {
        dummy = dummy / 10;
        i++;
    }
    if(i != 11)
    {
        cerr << "Invalid Number is given: " << dummy << endl;
        return false;
    }
    return true;
}
void HashTable::AddNewTC(long long int& TC_number)   // EKSIK
{
    if (!ValidNumberCheck(TC_number)) return;       // Exit if the number is not valid and give an error message!
    if(funct_select == 1)
    {
        FoldingAdd(TC_number);          // Linker Tools Error LNK2019 SOLVED!!!
    }
    else if (funct_select == 2)
    {
        MiddleSquaringAdd(TC_number);
    }
    else if (funct_select == 3)
    {
        TruncationAdd(TC_number);
    }
}
bool HashTable::DeleteTC(long long int& TC_number)          // Eksik
{
    if (!ValidNumberCheck(TC_number)) return false;       // Exit if the number is not valid and give an erro message!

    bool dummy = false;
    if (funct_select == 1)
    {
        dummy = FoldingDelete(TC_number);
    }
    else if (funct_select == 2)
    {
        dummy = MiddleSquaringDelete(TC_number);
    }
    else if (funct_select == 3)
    {
        dummy = TruncationDelete(TC_number);
    }
    return dummy;
}
bool HashTable::SearchTC(long long int& TC_number)
{
    if (!ValidNumberCheck(TC_number)) return false;       // Exit if the number is not valid and give an error message!

    bool dummy = false;
    if (funct_select == 1)
    {
        dummy = FoldingSearch(TC_number);
    }
    else if (funct_select == 2)
    {
        dummy = MiddleSquaringSearch(TC_number);
    }
    else if (funct_select == 3)
    {
        dummy = TruncationSearch(TC_number);
    }
    return dummy;
}
void HashTable::FoldingAdd(long long int& TC_number)    // Folding adding to the HashTable
{
    long long int dummy = TC_number;
    int hash_value = dummy % 100;
    dummy = dummy / 100;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;

    hash_value = hash_value % N;        // Finally reduce the hash value to the table's size mod N

    if(hash_table[hash_value] == (Node*)NULL)                   // Handling the special case
    {
        hash_table[hash_value] = new Node(TC_number, (Node*)NULL);
        //cout << hash_table[hash_value]->data << endl;
        return;
    }

    Node* hash_value_pointer = hash_table[hash_value];

    while (hash_value_pointer->next != (Node*)NULL)
    {
        if(hash_value_pointer->data == TC_number)
        {
            cout << "The key value is already in the Table!" << endl;
            return;
        }
        hash_value_pointer = hash_value_pointer->next;      // Getting to the end of the Linked List
    }
    if(hash_value_pointer->data != TC_number)
        hash_value_pointer->next = new Node(TC_number, (Node*)NULL);    // Add the key value to the end of the Linked List if it is not in the list already.
    else
        cout << "The key value is already in the Table!" << endl;
}
bool HashTable::FoldingDelete(long long int& TC_number)     // Deletes a key using Folding HashFunction
{
    long long int dummy = TC_number;
    int hash_value = dummy % 100;
    dummy = dummy / 100;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;

    hash_value = hash_value % N;        // Finally reduce the hash value to the table's size mod N
                                        // h

    if(hash_table[hash_value] == (Node*)NULL)       // Handling the special case1
    {
        return false;
    }
    if(hash_table[hash_value]->data == TC_number)   // Handling the special case2
    {
        Node* temp = hash_table[hash_value]->next;
        delete hash_table[hash_value];
        hash_table[hash_value] = temp;
        return true;
    }

    Node* hash_value_pointer = hash_table[hash_value];
    while(hash_value_pointer->next != (Node*)NULL)
    {
        if(hash_value_pointer->next->data == TC_number)           // Key is found, Delete Operation must occur.
        {
            Node* temp = hash_value_pointer->next->next;          // Save the next value of the deleted Node
            delete hash_value_pointer->next;
            hash_value_pointer->next = temp;
            return true;
        }
        hash_value_pointer = hash_value_pointer->next;
    }
    return false;               // If the code reaches here, then it means it couldn't find the value.
}
bool HashTable::FoldingSearch(long long int& TC_number)     // Searches a key using Folding HashFunction
{
    long long int dummy = TC_number;
    int hash_value = dummy % 100;
    dummy = dummy / 100;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;
    hash_value = hash_value + dummy % 1000;
    dummy = dummy / 1000;

    hash_value = hash_value % N;        // Finally reduce the hash value to the table's size mod N
                                        // h

    if (hash_table[hash_value] == (Node*)NULL)       // Handling the special case1
    {
        return false;
    }
    if (hash_table[hash_value]->data == TC_number)   // Handling the special case2
    {
        return true;
    }

    Node* hash_value_pointer = hash_table[hash_value];
    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->next->data == TC_number)           // Key is found, Search Operation must finish here.
        {
            return true;
        }
        hash_value_pointer = hash_value_pointer->next;
    }
    return false;               // If the code reaches here, then it means it couldn't find the value.
}
// Adds the key value with Middle Squaring Hash Function  ->  _ _ _ _ (_ _ _)^2 _ _ _ _
void HashTable::MiddleSquaringAdd(long long int& TC_number)
{
    long long int hash_value = TC_number;
    hash_value = hash_value / 10000;
    hash_value = hash_value % 1000;
    hash_value = hash_value * hash_value;   // Taking the square of the mid digits
    hash_value = hash_value % N;            // Finally reduce the hash value to the table's size mod N

    if (hash_table[hash_value] == (Node*)NULL)                   // Handling the special case
    {
        hash_table[hash_value] = new Node(TC_number, (Node*)NULL);
        //cout << hash_table[hash_value]->data << endl;
        return;
    }

    Node* hash_value_pointer = hash_table[hash_value];

    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->data == TC_number)
        {
            cout << "The key value is already in the Table!" << endl;
            return;
        }
        hash_value_pointer = hash_value_pointer->next;      // Getting to the end of the Linked List
    }
    if (hash_value_pointer->data != TC_number)
        hash_value_pointer->next = new Node(TC_number, (Node*)NULL);    // Add the key value to the end of the Linked List if it is not in the list already.
    else
        cout << "The key value is already in the Table!" << endl;
}

bool HashTable::MiddleSquaringDelete(long long int& TC_number)
{
    long long int hash_value = TC_number;
    hash_value = hash_value / 10000;
    hash_value = hash_value % 1000;
    hash_value = hash_value * hash_value;   // Taking the square of the mid digits
    hash_value = hash_value % N;            // Finally reduce the hash value to the table's size mod N

    if (hash_table[hash_value] == (Node*)NULL)       // Handling the special case1
    {
        return false;
    }
    if (hash_table[hash_value]->data == TC_number)   // Handling the special case2
    {
        Node* temp = hash_table[hash_value]->next;
        delete hash_table[hash_value];
        hash_table[hash_value] = temp;
        return true;
    }

    Node* hash_value_pointer = hash_table[hash_value];
    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->next->data == TC_number)           // Key is found, Delete Operation must occur.
        {
            Node* temp = hash_value_pointer->next->next;          // Save the next value of the deleted Node
            delete hash_value_pointer->next;
            hash_value_pointer->next = temp;
            return true;
        }
        hash_value_pointer = hash_value_pointer->next;
    }
    return false;               // If the code reaches here, then it means it couldn't find the value.
}
bool HashTable::MiddleSquaringSearch(long long int& TC_number)
{
    long long int hash_value = TC_number;
    hash_value = hash_value / 10000;
    hash_value = hash_value % 1000;
    hash_value = hash_value * hash_value;   // Taking the square of the mid digits
    hash_value = hash_value % N;            // Finally reduce the hash value to the table's size mod N

    if (hash_table[hash_value] == (Node*)NULL)       // Handling the special case1
    {
        return false;
    }
    if (hash_table[hash_value]->data == TC_number)   // Handling the special case2
    {
        return true;
    }

    Node* hash_value_pointer = hash_table[hash_value];
    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->next->data == TC_number)           // Key is found, Search Operation must finish here.
        {
            return true;
        }
        hash_value_pointer = hash_value_pointer->next;
    }
    return false;               // If the code reaches here, then it means it couldn't find the value.
}

void HashTable::TruncationAdd(long long int& TC_number)
{
    long long int hash_value = TC_number;       // Copy the key
    hash_value = hash_value % 100;
    hash_value = hash_value % N;

    if (hash_table[hash_value] == (Node*)NULL)                   // Handling the special case
    {
        hash_table[hash_value] = new Node(TC_number, (Node*)NULL);
        //cout << hash_table[hash_value]->data << endl;
        return;
    }

    Node* hash_value_pointer = hash_table[hash_value];

    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->data == TC_number)
        {
            cout << "The key value is already in the Table!" << endl;
            return;
        }
        hash_value_pointer = hash_value_pointer->next;      // Getting to the end of the Linked List
    }
    if (hash_value_pointer->data != TC_number)
        hash_value_pointer->next = new Node(TC_number, (Node*)NULL);    // Add the key value to the end of the Linked List if it is not in the list already.
    else
        cout << "The key value is already in the Table!" << endl;
}
bool HashTable::TruncationDelete(long long int& TC_number)
{
    long long int hash_value = TC_number;       // Copy the key
    hash_value = hash_value % 100;
    hash_value = hash_value % N;

    if (hash_table[hash_value] == (Node*)NULL)       // Handling the special case1
    {
        return false;
    }
    if (hash_table[hash_value]->data == TC_number)   // Handling the special case2
    {
        Node* temp = hash_table[hash_value]->next;
        delete hash_table[hash_value];
        hash_table[hash_value] = temp;
        return true;
    }

    Node* hash_value_pointer = hash_table[hash_value];
    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->next->data == TC_number)           // Key is found, Delete Operation must occur.
        {
            Node* temp = hash_value_pointer->next->next;          // Save the next value of the deleted Node
            delete hash_value_pointer->next;
            hash_value_pointer->next = temp;
            return true;
        }
        hash_value_pointer = hash_value_pointer->next;
    }
    return false;               // If the code reaches here, then it means it couldn't find the value.
}
bool HashTable::TruncationSearch(long long int& TC_number)
{
    long long int hash_value = TC_number;       // Copy the key
    hash_value = hash_value % 100;
    hash_value = hash_value % N;

    if (hash_table[hash_value] == (Node*)NULL)       // Handling the special case1
    {
        return false;
    }
    if (hash_table[hash_value]->data == TC_number)   // Handling the special case2
    {
        return true;
    }

    Node* hash_value_pointer = hash_table[hash_value];
    while (hash_value_pointer->next != (Node*)NULL)
    {
        if (hash_value_pointer->next->data == TC_number)           // Key is found, Search Operation must finish here.
        {
            return true;
        }
        hash_value_pointer = hash_value_pointer->next;
    }
    return false;               // If the code reaches here, then it means it couldn't find the value.
}
