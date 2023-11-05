// * PROJECT  -  PHONE DIRECTORY USING TRIE DATA STRUCTURE
// * Group 43

// * Imports
#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include <stdbool.h> // for using boolean data type
#include <string.h>  // for performing string operations

// * Macros
#define NAME_TRIE_SIZE 27 // 26 alphabets and 1 blank space
#define NUM_TRIE_SIZE 10  // 10 numbers
#define MAX_NAME_SIZE 40  // max length for name

// ------------------------------------------- Name trie --------------------------------------------------------

// * Defining struct for Name Trie Node
struct NameTrieNode
{
    struct NameTrieNode *children[NAME_TRIE_SIZE];
    bool isEnd;
    long long int number;
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
            printf("Invalid String Entered\n");
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
void nameTrieDisplay(struct NameTrieNode *root, char *str, int level)
{
    // Printing when end is found
    if (root->isEnd)
    {
        char temp[MAX_NAME_SIZE];
        strncpy(temp, str, level);
        temp[level] = '\0';

        int len = strlen(temp);
        temp[0] = temp[0] - ' ';
        for (int i = 1; i < len; i++)
        {
            if (temp[i - 1] == ' ')
            {
                temp[i] = temp[i] - ' ';
            }
        }
        printf("%s", temp);
        for (int i = len; i < MAX_NAME_SIZE; i++)
        {
            printf(" ");
        }
        printf(": %lld\n", root->number);
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
            nameTrieDisplay(root->children[i], str, level + 1);
        }
    }
}

// * Function to insert in the name trie
void nameTrieInsert(struct NameTrieNode *root, char *key, long long int phoneNo)
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
            index = key[i] - 'a';
        }
        if (root->children[index] == NULL)
        {
            printf("No Results Found.\n");
            return;
        }

        root = root->children[index];
    }

    nameTrieDisplay(root, key, length);
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
void numTrieDisplay(struct NumTrieNode *root, char *num, int level)
{
    // Printing when end is found
    if (root->isEnd)
    {
        char key[10];
        strcpy(key, num);
        char temp[MAX_NAME_SIZE];
        strcpy(temp, root->name);
        int len = strlen(temp);
        temp[0] = temp[0] - ' ';
        for (int i = 1; i < len; i++)
        {
            if (temp[i - 1] == ' ')
            {
                temp[i] = temp[i] - ' ';
            }
        }
        printf("\n%s", temp);
        for (int i = len; i < MAX_NAME_SIZE; i++)
        {
            printf(" ");
        }
        printf(": %s\n", key);
    }

    int i;

    // Recursively printing for similar search results
    for (i = 0; i < NUM_TRIE_SIZE; i++)
    {
        if (root->children[i] != NULL)
        {
            num[level] = i + '0';
            numTrieDisplay(root->children[i], num, level + 1);
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

    numTrieDisplay(root, key, length);
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

// * global variables needed for main function
char name_input[MAX_NAME_SIZE];
char num_input[10];

// * Main function
int main()
{
    struct NameTrieNode *root = newNameTrieNode();
    struct NumTrieNode *rootn = newNumTrieNode();
    char dis[1] = "";
    FILE *ptr;
    ptr = fopen("sample_data.txt", "r");
    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    int i = 1;
    while (!feof(ptr))
    {
        if (i % 2 == 1)
        {
            fscanf(ptr, " %[^\n]", name_input);
        }

        else
        {
            fscanf(ptr, " %s", num_input);
            numTrieInsert(rootn, num_input, name_input);
            long long int num1_input = strtoll(num_input, NULL, 0);
            nameTrieInsert(root, name_input, num1_input);
        }
        i++;
    }
    while (true)
    {
        printf("\n\nWELCOME TO YOUR PHONE DIRECTORY\n\n");
        printf("press 1 to create a new contact\n");
        printf("press 2 to see all your contacts\n");
        printf("press 3 to search for a contact\n");
        printf("press 4 to delete a contact\n");
        printf("press 5 to exit the directory\n");
        printf("\nEnter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
            printf("\n");
            printf("Enter contact name : ");
            size_t buff = 32;
            char name[MAX_NAME_SIZE];
            // Use %[^\n] to read all characters until a newline
            if (scanf(" %[^\n]", name) != 1)
            {
                fprintf(stderr, "Error reading input.\n");
                return 1;
            }
            printf("Enter contact number : ");
            char num[10];
            scanf("%s", num);
            numTrieInsert(rootn, num, name);
            long long int num1;
            // Using strtoll to convert string input to long long integer
            num1 = strtoll(num, NULL, 0);
            nameTrieInsert(root, name, num1);
            break;
        }
        case 2:
        {
            printf("\n");
            nameTrieDisplay(root, dis, 0);
            break;
        }
        case 3:
        {
            printf("\n");
            printf("Enter 1 to search for a Contact Number \n");
            printf("Enter 2 to search for a Contact Name \n");
            int s;
            printf("\nEnter your choice : ");
            scanf("%d", &s);
            if (s == 1)
            {
                char num[NUM_TRIE_SIZE];
                printf("Enter Contact Number : ");
                scanf("%s", num);
                numTrieSearch(rootn, num);
            }
            else if (s == 2)
            {
                char name[MAX_NAME_SIZE];
                printf("Enter Contact Name : ");
                scanf("%s", name);
                nameTrieSearch(root, name);
            }
            else
            {
                printf("Invalid Choice\n");
            }
            break;
        }
        case 4:
        {
            printf("Enter 1 to delete a Contact Number : ");
            printf("Enter 2 to delete a Contact Name : ");
            int s;
            scanf("%d", &s);
            if (s == 1)
            {
                char num[NUM_TRIE_SIZE];
                printf("Enter Contact Number :\n");
                scanf("%s", num);
                rootn = numTrieDelete(rootn, num, 0);
            }
            else if (s == 2)
            {
                char name[MAX_NAME_SIZE];
                printf("Enter Contact Name :\n");
                scanf("%s", name);
                root = NameTrieDelete(root, name, 0);
            }
            else
            {
                printf("Invalid Choice\n");
            }
            printf("Contact Deleted Successfully\n");
            break;
        }
        case 5:
        {
            exit(0);
        }
        }
    }
}
// * End