#include <iostream>
using namespace std;

// 3

class Node
{
public:
    string data;
    Node *left;
    Node *right;

    Node(string d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

void printBook(Node *root, int diagonal)
{

    if (!root)
        return;

    for (int i = 0; i < diagonal; i++)
    {
        cout << '\t';
    }
    cout << root->data << endl;

    printBook(root->left, diagonal + 1);

    printBook(root->right, diagonal);
}

int main()
{

    string bookName;
    int noOfChapters;
    cout << "Enter Name of the book: ";
    cin >> bookName;
    cout << "Enter Number of Chapters in the book: ";
    cin >> noOfChapters;

    Node *root = new Node(bookName);

    string chapterName;
    int noOfSections;
    Node *prev = NULL;
    for (int i = 0; i < noOfChapters; i++)
    {
        cout << "Enter Name for chapter " << i + 1 << ": ";
        cin >> chapterName;
        cout << "Enter No of sections in chapter " << i + 1 << ": ";
        cin >> noOfSections;
        Node *curr = new Node(chapterName);
        if (prev == NULL)
        {
            root->left = curr;
        }
        else
        {
            prev->right = curr;
        }

        string sectionName;
        prev = NULL;
        for (int j = 0; j < noOfSections; j++)
        {
            cout << "Enter Name for section " << j + 1 << " chapter " << i + 1 << ": ";
            cin >> sectionName;
            Node *secNode = new Node(sectionName);
            if (prev == NULL)
            {
                curr->left = secNode;
            }
            else
            {
                prev->right = secNode;
            }
            prev = secNode;
        }

        prev = curr;
    }

    printBook(root, 0);
    cout << endl;

    return 0;
}