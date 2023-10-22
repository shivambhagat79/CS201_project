// * PROJECT  -  PHONE DIRECTORY USING TRIE DATA STRUCTURE

// * Imports
#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include <stdbool.h> // for using boolean data type
#include <string.h>  // for performing string operations

// * Macros
#define NAME_TRIE_SIZE 27 // 26 alphabets and 1 blank space
#define NUM_TRIE_SIZE 10  // 10 numbers
#define MAX_NAME_SIZE 30  // max length for name

// ------------------------------------------- Name trie --------------------------------------------------------

// * Defining struct for Name Trie Node
struct NameTrieNode
{
    struct NameTrieNode *children[NAME_TRIE_SIZE];
    bool isEnd;
    long int number;
};

// * Function to convert string to lowercase and check for invalid characters
void rectifyString(char *key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] >= 65 && key[i] <= 90) // if character is UpperCase
        {
            key[i] = key[i] + 32;
        }
        else if (!((key[i] >= 97 && key[i] <= 122) | key[i] == ' ')) // remaining cases
        {
            printf("Invalid String entered\n");
            printf("%s\n", key);
            exit(0);
        }
    }
}

// * Functoin for getting a new NameTrieNode
struct NameTrieNode *newNameTrieNode()
{
    // allocating memory
    struct NameTrieNode *n = (struct NameTrieNode *)malloc(sizeof(struct NameTrieNode));

    // initialising node parameters
    n->isEnd = false;
    n->number = -1;

    for (int i = 0; i < NAME_TRIE_SIZE; i++)
    {
        n->children[i] = NULL;
    }

    return n;
}

// * Function to print search results
void nameTreeDisplay(struct NameTrieNode *root, char *str, int level)
{
    // Printing when end is found
    if (root->isEnd)
    {
        char temp[MAX_NAME_SIZE];
        strncpy(temp, str, level);
        temp[level] = '\0';
        printf("%s     :     %ld\n", temp, root->number);
    }

    int i;

    // Recursively printing for similar search results
    for (i = 0; i < NAME_TRIE_SIZE; i++)
    {
        if (root->children[i] != NULL)
        {

            if (i == 26)
            {
                str[level] = ' ';
            }
            else
            {
                str[level] = i + 97;
            }
            nameTreeDisplay(root->children[i], str, level + 1);
        }
    }
}

// * Function to insert in the name trie
void nameTrieInsert(struct NameTrieNode *root, char *key, long int phoneNo)
{
    rectifyString(key); // get the string in required format

    int index; // stores the index where each character in key is to be added

    for (int i = 0; i < strlen(key); i++)
    {
        // getting index
        if (key[i] == ' ')
        {
            index = 26;
        }
        else
        {
            index = key[i] - 97;
        }

        // setting child if it does not exist
        if (root->children[index] == NULL)
        {
            root->children[index] = newNameTrieNode();
        }

        root = root->children[index]; // traversing
    }

    // setting node parameters
    root->isEnd = true;
    root->number = phoneNo;
}

// * Function to search in name trie
void nameTrieSearch(struct NameTrieNode *root, char *key)
{
    rectifyString(key); // get the string in required format
    int index;          // stores the index where each character in key is to stored
    int length = strlen(key);

    for (int i = 0; i < length; i++)
    {
        if (key[i] == ' ')
        {
            index = 26;
        }
        else
        {
            index = key[i] - 97;
        }

        if (!root->children[index])
        {
            printf("No Results Found.\n");
            return;
        }

        root = root->children[index];
    }

    nameTreeDisplay(root, key, length);
}

// * check if the node has no children
bool isNameEmpty(struct NameTrieNode *root)
{
    for (int i = 0; i < NAME_TRIE_SIZE; i++)
    {
        if (root->children[i])
        {
            return false;
        }
    }
    return true;
}

// *   Function to delete from name trie
struct NameTrieNode *NameTrieDelete(struct NameTrieNode *root, char *key, int depth)
{
    // if root is null
    if (!root)
    {
        return NULL;
    }

    int len = strlen(key);

    // if we are at the last character
    if (depth == len)
    {

        if (root->isEnd)
        {
            root->isEnd = false;
        }

        if (isNameEmpty(root))
        {
            free(root);
            root = NULL;
        }
        return root;
    }

    // recursive call
    int index;
    if (key[depth] == ' ')
    {
        index = 26;
    }
    else
    {
        index = key[depth] - 'a';
    }
    root->children[index] = NameTrieDelete(root->children[index], key, depth + 1);

    if (isNameEmpty(root) && root->isEnd == false)
    {
        free(root);
        root = NULL;
    }
    return root;
}

// --------------------------------------------------------------------------------------------------------------

// --------------------------------------------- Number Trie ----------------------------------------------------

// * Defining struct for Num Trie Node
struct NumTrieNode
{
    struct NumTrieNode *children[NUM_TRIE_SIZE];
    bool isEnd;
    char *name;
};

// * Functoin for getting a new NumTrieNode
struct NumTrieNode *newNumTrieNode()
{
    // allocating memory
    struct NumTrieNode *n = (struct NumTrieNode *)malloc(sizeof(struct NumTrieNode));

    // initialising node parameters
    n->isEnd = false;
    n->name = "-1";

    for (int i = 0; i < NUM_TRIE_SIZE; i++)
    {
        n->children[i] = NULL;
    }

    return n;
}

// * Function to rectify the number to required format
void rectifyNum(char *key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (!(key[i] >= '0' && key[i] <= '9'))
        {
            printf("Invalid Phone number.\n");
            exit(-1);
        }
    }
}

// * Function to insert in the num trie
void numTrieInsert(struct NumTrieNode *root, char *key, char *Pname)
{
    rectifyNum(key);

    if (strlen(key) != 10)
    {
        printf("Phone number must have 10 digits.\n");
        return;
    }

    int index; // stores the index where each character in key is to be added

    for (int i = 0; i < 10; i++)
    {

        index = key[i] - '0';

        // setting child if it does not exist
        if (root->children[index] == NULL)
        {
            root->children[index] = newNumTrieNode();
        }

        root = root->children[index]; // traversing
    }

    // setting node parameters
    root->isEnd = true;
    root->name = Pname;
}

// * Function to print search results
void numTreeDisplay(struct NumTrieNode *root, char *num, int level)
{
    // Printing when end is found
    if (root->isEnd)
    {
        printf("%s     :     %s\n", num, root->name);
    }

    int i;

    // Recursively printing for similar search results
    for (i = 0; i < NUM_TRIE_SIZE; i++)
    {
        if (root->children[i] != NULL)
        {
            num[level] = i + '0';
            numTreeDisplay(root->children[i], num, level + 1);
        }
    }
}

// * Function to search in num trie
void numTrieSearch(struct NumTrieNode *root, char *key)
{
    rectifyNum(key); // get the string in required format
    int index;       // stores the index where each character in key is to stored
    int length = strlen(key);

    for (int i = 0; i < length; i++)
    {
        index = key[i] - '0';

        if (!root->children[index])
        {
            printf("No Results Found.\n");
            return;
        }

        root = root->children[index];
    }

    numTreeDisplay(root, key, length);
}

// * check if the node has no children
bool isNumEmpty(struct NumTrieNode *root)
{
    for (int i = 0; i < NUM_TRIE_SIZE; i++)
    {
        if (root->children[i])
        {
            return false;
        }
    }
    return true;
}

// * Function to delete from name trie
struct NumTrieNode *numTrieDelete(struct NumTrieNode *root, char *key, int depth)
{
    // if root is null
    if (!root)
    {
        return NULL;
    }

    int len = strlen(key);

    // if we are at the last digit
    if (depth == len)
    {

        if (root->isEnd)
        {
            root->isEnd = false;
        }

        if (isNumEmpty(root))
        {
            free(root);
            root = NULL;
        }
        return root;
    }

    // recursive call
    int index;
    index = key[depth] - '0';

    root->children[index] = numTrieDelete(root->children[index], key, depth + 1);

    if (isNumEmpty(root) && root->isEnd == false)
    {
        free(root);
        root = NULL;
    }
    return root;
}
// --------------------------------------------------------------------------------------------------------------

// * Main function
int main()
{
    struct NameTrieNode *root = newNameTrieNode();
    struct NumTrieNode *rootn = newNumTrieNode();
    char p[MAX_NAME_SIZE];
    char s[MAX_NAME_SIZE] = "99";
    char i[MAX_NAME_SIZE] = "";
    char del[MAX_NAME_SIZE] = "9928376363";

    // nameTrieInsert(root, "shiv", 69420);
    // nameTrieInsert(root, "shivam", 70872592);
    // nameTrieInsert(root, "shivam bhagat", 7087662592);
    // nameTrieInsert(root, "shivam bpd", 592);
    // nameTrieInsert(root, i, 922389283);

    // root = NameTrieDelete(root, del, 0);

    // nameTrieSearch(root, s);

    numTrieInsert(rootn, "9928374626", "shivam");
    numTrieInsert(rootn, "9928376363", "shivam bhagat");
    numTrieInsert(rootn, "8828376363", "shivam bhagat");

    numTreeDisplay(rootn, p, 0);

    // numTrieSearch(rootn, i);

    // nameTreeDisplay(root, p, 0);

    // nameTrieSearch(root, s);
    rootn = numTrieDelete(rootn, del, 0);
    numTreeDisplay(rootn, p, 0);
    printf("\n");
    numTrieSearch(rootn, s);

    return 0;
}
// * End