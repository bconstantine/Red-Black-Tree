#include <iostream>
using namespace std;

struct treeNode 
{
    int value;
    treeNode* left;
    treeNode* right;
    bool isBlack;
    treeNode* parent; //essential for checking rotation
};

//if child right node of head, not rotating right
treeNode* rightRotation(treeNode* up, treeNode* down)
{
    //no change color done here, will be done manually
    down->parent = up->parent;
    up->parent = down;
    up->right = down->left;
    if (down->left != NULL)
    {
        down->left->parent = up;
    }
    down->left = up;
    return down;
}

//if child left node of head, not rotating left
treeNode* leftRotation(treeNode* up, treeNode* down)
{
    //no change color done here, will be done manually
    down->parent = up->parent;
    up->parent = down;
    up->left = down->right;
    if (down->right != NULL)
    {
        down->right->parent = up;
    }
    down->right = up;
    return down;
}

void printColor(treeNode* head)
{
    if (head != NULL)
    {
        cout << head->value << "_";
        if (head->isBlack)
        {
            cout << "b";
        }
        else
        {
            cout << "r";
        }
        cout << "(";
        printColor(head->left);
        cout << ")";
        cout << "(";
        printColor(head->right);
        cout << ")";
    }
}

int main()
{
    treeNode* head = NULL;
    char command;
    int value; 
    treeNode* traverseNode = NULL; 
    while (cin >> command)
    {
        if (command == 'I')
        {
            cin >> value;
            treeNode* newNode = new treeNode;
            newNode->value = value;
            newNode->right = NULL;
            newNode->left = NULL;
            newNode->isBlack = false;
            newNode->parent = NULL; //if head, parent always NULL; 
            treeNode* prevNode = NULL; 
            if (head == NULL)
            {
                head = newNode;
            }
            else
            {
                traverseNode = head; 
                //check for the 
                while (traverseNode != NULL)
                {
                    
                    if (traverseNode->left != NULL && traverseNode->right != NULL)
                    {
                        if (!traverseNode->left->isBlack && !traverseNode->right->isBlack)
                        {
                            traverseNode->left->isBlack = true;
                            traverseNode->right->isBlack = true;
                            traverseNode->isBlack = false;
                        }
                    }
                    if (traverseNode->parent != NULL && !(traverseNode->parent->isBlack) && !(traverseNode->isBlack))
                    {
                        //do rotation here;
                        bool lowerConnection = false; //true if right connection
                        bool upperConnection = false; //true if right connection
                        treeNode* lowerParent = traverseNode->parent;
                        treeNode* upperParent = lowerParent->parent; //must be exist and not root
                        bool isHead = (upperParent == head);

                        if (lowerParent->value < traverseNode->value)
                        {
                            lowerConnection = true;
                        }
                        if (upperParent->value < lowerParent->value)
                        {
                            upperConnection = true;
                        }

                        if (lowerConnection)
                        {
                            if (upperConnection)
                            {
                                //connection is RR
                                upperParent->isBlack = false;
                                traverseNode->isBlack = false;
                                traverseNode = rightRotation(upperParent, lowerParent);
                                traverseNode->isBlack = true;
                            }
                            else
                            {
                                //connection is LR
                                upperParent->isBlack = false;
                                lowerParent->isBlack = false;
                                traverseNode->isBlack = true;
                                traverseNode = rightRotation(lowerParent, traverseNode);
                                traverseNode = leftRotation(upperParent, traverseNode);
                            }
                        }
                        else
                        {
                            if (upperConnection)
                            {
                                //connection is RL
                                upperParent->isBlack = false;
                                lowerParent->isBlack = false;
                                traverseNode->isBlack = true;
                                traverseNode = leftRotation(lowerParent, traverseNode);
                                traverseNode = rightRotation(upperParent, traverseNode);
                            }
                            else
                            {
                                //connection is LL
                                upperParent->isBlack = false;
                                traverseNode->isBlack = false;
                                traverseNode = leftRotation(upperParent, lowerParent);
                                traverseNode->isBlack = true;
                            }
                        }

                        if (isHead)
                        {
                            head = traverseNode; 
                        }
                        else
                        {
                            if (traverseNode->parent->value < traverseNode->value)
                            {
                                traverseNode->parent->right = traverseNode;
                            }
                            else
                            {
                                traverseNode->parent->left = traverseNode;
                            }
                        }
                    }
                    //no need to check up parent of traverseNode
                    if (value > traverseNode->value)
                    {
                        if (traverseNode->right == NULL)
                        {
                            prevNode = traverseNode; 
                        }
                        traverseNode = traverseNode->right;
                        
                        
                    }
                    else
                    {
                        if (traverseNode->left == NULL)
                        {
                            prevNode = traverseNode;
                        }
                        traverseNode = traverseNode->left;
                        
                    }
                }
                
                //traverseNode now NULL; 
                if (prevNode->value < newNode->value)
                {
                    prevNode->right = newNode;
                }
                else
                {
                    prevNode->left = newNode; 
                }
                newNode->parent = prevNode; 
                traverseNode = newNode; 
                //traverse back to up
                while (traverseNode != head)
                {
                    if (traverseNode->parent != NULL && !(traverseNode->parent->isBlack) && !(traverseNode->isBlack))
                    {
                        //do rotation here;
                        bool lowerConnection = false; //true if right connection
                        bool upperConnection = false; //true if right connection
                        treeNode* lowerParent = traverseNode->parent;
                        treeNode* upperParent = lowerParent->parent; //must be exist and not root
                        bool isHead = (upperParent == head);
                        if (lowerParent->value < traverseNode->value)
                        {
                            lowerConnection = true;
                        }
                        if (upperParent->value < lowerParent->value)
                        {
                            upperConnection = true;
                        }

                        if (lowerConnection)
                        {
                            if (upperConnection)
                            {
                                //connection is RR
                                upperParent->isBlack = false;
                                traverseNode->isBlack = false;
                                traverseNode = rightRotation(upperParent, lowerParent);
                                traverseNode->isBlack = true;
                            }
                            else
                            {
                                //connection is LR
                                upperParent->isBlack = false;
                                lowerParent->isBlack = false;
                                traverseNode->isBlack = true;
                                traverseNode = rightRotation(lowerParent, traverseNode);
                                traverseNode = leftRotation(upperParent, traverseNode);
                            }
                        }
                        else
                        {
                            if (upperConnection)
                            {
                                //connection is RL
                                upperParent->isBlack = false;
                                lowerParent->isBlack = false;
                                traverseNode->isBlack = true;
                                traverseNode = leftRotation(lowerParent, traverseNode);
                                traverseNode = rightRotation(upperParent, traverseNode);
                            }
                            else
                            {
                                //connection is LL
                                upperParent->isBlack = false;
                                traverseNode->isBlack = false;
                                traverseNode = leftRotation(upperParent, lowerParent);
                                traverseNode->isBlack = true;
                            }
                        }

                        if (isHead)
                        {
                            head = traverseNode;
                        }
                        else
                        {
                            if (traverseNode->parent->value < traverseNode->value)
                            {
                                traverseNode->parent->right = traverseNode;
                            }
                            else
                            {
                                traverseNode->parent->left = traverseNode;
                            }
                        }
                    }
                    else
                    {
                        break; 
                    }
                }
            }
            head->isBlack = true;
        }
        else
        {
            printColor(head);
            cout << "\n";
        }
    }
}