//
//  ttTree.cpp
//  project3
//
//  Created by Allen on 4/16/14.
//  Copyright (c) 2014 Allen. All rights reserved.
//


//#include <iomanip> //just for testing 
#include "ttTree.h"
#include <algorithm>
node23 *previous_Sibling=NULL;

ttTree::ttTree()
{
    root = NULL;
    
}

bool ttTree::ttTreeInsert(int key)
{
    // Case 1 empty tree
    if(root==NULL)
    {
        root = new node23(key);
        return true;
    }
    // Check if key is already in tree
    if(search(key)) return false;
    
    return searchInsert(root, key);
    
    
    
}

bool ttTree::searchInsert(node23 *node, int key)
{
 
    if(node->isLeaf())
    {
        
        //Inserting into a 3 node
        if(node->isThreeTree())
        {
            // divide tree into two children and pass middle up to parent
            insert3Tree(node,key);
        }
        // Inserting into a 2 node
        else
        {
            node->insert2Tree(key);
        }  
        
    }
    else  //traverse tree to find correct leaf node
    {
        if(key < node->smallData)
        {
            searchInsert(node->leftChild, key);
        }
        else if(node->isThreeTree() && key > node->bigData)
        {
            searchInsert(node->rightChild, key);
        }
        else{
            searchInsert(node->middleChild, key);
        }
    }
    

    
    return true;
}




bool ttTree::search(int key)
{
    node23 *tmp = root;
    while(tmp != NULL)
    {
        if(tmp->smallData == key || tmp->bigData == key) return true;
        
        if(key < tmp->smallData) tmp=tmp->leftChild;
        else if(tmp->isThreeTree() && key > tmp->bigData)
        {
            tmp = tmp->rightChild;
        }
        else tmp = tmp->middleChild;
    }
    
    return false;
}
void ttTree::ttTreePrint()

{
    if (root==NULL) return;
    inorderTraverse(root);
    std::cout << std::endl;
    
}
bool ttTree::ttTreeDelete(int key)
{
    node23 *tmp = root;
    while(tmp != NULL)
    {
        if(key==0)
        {
            if(tmp->smallData == key) break;
        }
        else if(tmp->smallData == key || tmp->bigData == key) break;
        
        if(key < tmp->smallData) tmp=tmp->leftChild;
        else if(tmp->isThreeTree() && key > tmp->bigData)
        {
            tmp = tmp->rightChild;
        }
        else tmp = tmp->middleChild;
    }
    if(tmp==NULL) return false;
    node23 *N = tmp;
    if(!N->isLeaf())
    {
        //node23 *inorder find inorder successor and swap with leaf
        node23 *leafN = getInorderSuccessor(N,key);
        if(N->smallData == key)
        {
            N->smallData = leafN->smallData;
            leafN->smallData = key;
        }
        else{
            N->bigData = leafN->smallData;
            leafN->smallData = key;
        }
       
        N=leafN;
    
    }
    if(N->isThreeTree())
    {
        if(N->smallData==key){
        N->smallData = N->bigData;
        N->bigData = 0;
        return true;
        }else{
            N->bigData=0;
            return true;
        }
        
    }else{
        N->smallData = 0;
    }
    while(N->smallData==0)
    {
        //Case  1
        if(N==root)
        {
            
            if(N->leftChild!=NULL)
            {
                root=N->leftChild;
                root->parent=NULL;
            }else if(N->middleChild!=NULL)
            {
                root = N->middleChild;
                root->parent=NULL;
            }
            return true;
            //delete N ?
            
        }
        //Case 2 not the root and has siblimg with 2 keys
        
        else if (fixCase2(N))
        {
            return true;
        }
        // else case 3 siblings are single data
        else
        {
            
            N=fixCase3(N);
            
            
            
        }

            }
    
        return true;
}
node23* ttTree::fixCase3(node23 * N)
{
    node23* sibling=NULL;
    if(N->parent->isThreeTree())
    {
        
        if(N->parent->leftChild==N)
        {
            //situation 1
            sibling = N->parent->middleChild;
            sibling->bigData=sibling->smallData;
            sibling->smallData = sibling->parent->smallData;
            sibling->parent->smallData=sibling->parent->bigData;
            sibling->parent->leftChild=sibling;
            sibling->parent->middleChild=sibling->parent->rightChild;
            sibling->parent->rightChild= NULL;
            sibling->parent->bigData=0;
            
            if(!N->isLeaf())
            {
                sibling->rightChild=sibling->middleChild;
                sibling->middleChild=sibling->leftChild;
                sibling->leftChild = previous_Sibling;
                previous_Sibling->parent = sibling;
            }
        }
        else if (N->parent->middleChild==N)
        {
            
            
            sibling = N->parent->leftChild;
            sibling->bigData=sibling->parent->smallData;
            
            sibling->parent->smallData=sibling->parent->bigData;
            sibling->parent->leftChild=sibling;
            sibling->parent->middleChild=sibling->parent->rightChild;
            sibling->parent->rightChild= NULL;
            sibling->parent->bigData=0;
            
            
            if(!N->isLeaf())
            {
            sibling->rightChild=previous_Sibling;
            previous_Sibling->parent = sibling;
            }
            
                
         }
            // else n is  a right child
        else{
            
            
            sibling = N->parent->middleChild;
            sibling->bigData=sibling->parent->bigData;
         
            sibling->parent->rightChild= NULL;
            sibling->parent->bigData=0;
            
            if(!N->isLeaf())
            {
                sibling->rightChild = previous_Sibling;
                previous_Sibling->parent = sibling;
            }
            
                
            
        }
    }
    
        
    
    else  // parent is 2 tree
    {
        if(N->parent->leftChild==N)
        {
            sibling = N->parent->middleChild;
            
            sibling->bigData=sibling->smallData;
            sibling->smallData=sibling->parent->smallData;
            sibling->parent->smallData=0;
            sibling->parent->leftChild=NULL;
            
            if(!N->isLeaf())
            {
                sibling->rightChild=sibling->middleChild;
                sibling->middleChild=sibling->leftChild;
                sibling->leftChild=  previous_Sibling ;
                previous_Sibling->parent=sibling;//N->leftChild; // prev sibling
                
            }
            previous_Sibling=sibling;
        }
        else{   //deletin 20
            // pass sibling??
            sibling = N->parent->leftChild;
            sibling->bigData = sibling->parent->smallData;
            sibling->parent->smallData=0;
            sibling->parent->middleChild = 0;
            
            if(!N->isLeaf())
            {
                    sibling->rightChild=previous_Sibling;
                    previous_Sibling->parent = sibling;
                
            }
            
            previous_Sibling=sibling;
        }
        
        
    }
    
    
    
    return N->parent;
    
    
}

void ttTree::insert3Tree(node23 *node, int key,node23 *newLeftChild, node23 *newRightChild)
{
    node23 * p = NULL;
    
    node23 *nodeLC = node->leftChild;
    node23 *nodeMC = node->middleChild;
    node23 *nodeRC = node->rightChild;
    int x = 0;
    if(key < node->smallData)
    {
    x = 1;
    }else if(key > node->bigData)
        x =2;
    else x = 3;
    
    int values[3];
    values[0]=node->smallData;
    values[1]=node->bigData;
    values[2]=key;
    std::sort(values,values+3);
    
    // Case 1 no parent or is root node
    if(node->parent==NULL)
    {
        p = new node23;
        
    }
    else{
        p = node->parent;
    }
    bool leaf = node->isLeaf();
    //Replace this node with 2 nodes n1 and n2 with p as their parent
    int middle = values[1];
    node23 *n1 = new node23(values[0],p);
    node->nodeEdit(values[2],p); // changed bigdate to values[2]
    node23 *n2 = node;
    
    // if node is not a leaf before it was split n1 becomes parent of 2 leftmost children of node
    if(!leaf)
    {
        if(x==1)
        {
        newLeftChild->parent = n1;
        newRightChild->parent = n1;
            n1->leftChild = newLeftChild;
            n1->middleChild = newRightChild;
            n2->middleChild = nodeRC;
            n2->leftChild= nodeMC;
            nodeMC->parent = n2;
            nodeRC->parent = n2;
            
        }else if(x==2)
        {
            newLeftChild->parent = n2;
            newRightChild->parent = n2;
            n2->middleChild =newRightChild;
            n2->leftChild = newLeftChild;
            n1->leftChild = nodeLC;
            n1->middleChild = nodeMC;
            nodeLC->parent = n1;
            nodeMC->parent = n1;
            
        }else{
            n1->leftChild = nodeLC;
            nodeLC->parent =n1;
            n1->middleChild = newLeftChild;
            newLeftChild->parent=n1;
            n2->middleChild = nodeRC;
            nodeRC->parent = n2;
            n2->leftChild = newRightChild;
            newRightChild->parent=n2;
            
        }
    }
    
    // if p is new node
    if(p->leftChild==NULL)
    {
        p->smallData = middle;
        p->leftChild = n1;
        p->middleChild = n2; // should be n2
        root = p;
    }
    else if(!p->isThreeTree()){
        // Case parent is 2 node
        p->insert2Tree(middle,n1,n2);
    }
    
    // Case parent is 3 node
    else insert3Tree(p, middle,n1,n2);
    
}

void ttTree::inorderTraverse(node23 *node)
{
    
    if (node->isLeaf())
    {
        if(node->isThreeTree())
        {
            std::cout << "(" << node->smallData <<", "<< node->bigData << ")";
        }
        else std::cout <<"(" << node->smallData << ")";
    }
    
    
    
    else if(!node->isThreeTree())
    {
        std::cout << "(";
        inorderTraverse(node->leftChild);
        std::cout<<", "<< node->smallData<<", ";
        inorderTraverse(node->middleChild);
        std::cout << ")";
        
    }
    else
    {
        std::cout << "(";
        inorderTraverse(node->leftChild);
        std::cout << ", "<<node->smallData <<", ";
        inorderTraverse(node->middleChild);
        std::cout << ", "<<node->bigData <<", ";
        inorderTraverse(node->rightChild);
        std::cout << ")";
    }
    
}

node23* ttTree::getInorderSuccessor(node23 *node, int key)
{
    node23 *leaf = NULL;
    if(!node->isThreeTree())
    {
        leaf = node->middleChild;
    }
    else if(node->isThreeTree() && node->smallData == key)
    {
        leaf = node->middleChild;
    }
    else
    {
        leaf = node->rightChild;
    }
    
    while(!leaf->isLeaf())
    {
        leaf = leaf->leftChild;
    }
    return leaf;
}
// Method for testing tree visually
void ttTree::postorder(node23* p, int indent=0)
{
    if(p != NULL) {
        if (indent) {
            //std::cout << std::setw(indent) << ' ';
        }
        std::cout<< p->smallData;
        if(p->bigData>0)
        {
            std::cout<< "," << p->bigData;
        }
        std::cout<< "\n ";
        if(p->leftChild) postorder(p->leftChild, indent+6);
        if(p->middleChild) postorder(p->middleChild, indent+6);
        if(p->rightChild) postorder(p->rightChild, indent+6);
        
    }
}

bool ttTree::fixCase2(node23 *node)  // case when sibling is 3 tree
{
    node23 *parent = node->parent;

            if(parent->isThreeTree())
            {
                
                if(parent->leftChild==node)
                {
                    if(parent->middleChild->isThreeTree())
                    {
                        node->smallData = parent->smallData;
                        parent->smallData = parent->middleChild->smallData;
                        parent->middleChild->smallData = parent->middleChild->bigData;
                        parent->middleChild->bigData=0;
                        
                        if(!node->isLeaf())
                        {
                           
                            node->leftChild = previous_Sibling;
                            node->middleChild = parent->middleChild->leftChild; // correct
                            parent->middleChild->leftChild = parent->middleChild->middleChild;
                            parent->middleChild->middleChild = parent->middleChild->rightChild;
                            parent->middleChild->rightChild=NULL;
                            node->middleChild->parent = node;// added 27th 9:34 am
                        }
                        
                        
                        return true;
                    }
                }
                else if (parent->middleChild==node)
                {
                    
                    if(parent->leftChild->isThreeTree()) 
                    {
                        node->smallData = parent->smallData;
                        parent->smallData = parent->leftChild->bigData;
                        parent->leftChild->bigData=0;
                        // set three tree false
                        // must fix children if N is not leaf
                        
                        if(!node->isLeaf())
                        {
                            node->middleChild = node->leftChild;
                        node->leftChild = parent->leftChild->rightChild;
                            node->leftChild->parent = node->parent; // added 27th 9:42 am
                            parent->leftChild->rightChild=NULL;
                        }
                        
                        return true;
                    }else if(parent->rightChild->isThreeTree())
                    {
                        node->smallData = parent->bigData;
                        parent->bigData= parent->rightChild->smallData;
                        parent->rightChild->smallData=node->parent->rightChild->bigData;
                        parent->rightChild->bigData=0;
                        
                        if(!node->isLeaf())
                        {// CORRECT
                            // need to use previous sibling here for bc of multiple cases
                            node->leftChild=previous_Sibling;  // previous sibling?
                            node->middleChild = parent->rightChild->leftChild;
                            node->middleChild->parent = node;  // added 27th 9 45 am
                            parent->rightChild->leftChild=parent->rightChild->middleChild;
                            parent->rightChild->middleChild = parent->rightChild->rightChild;
                            parent->rightChild->rightChild=NULL;
                        }
                        return true;
                        // set rightchild false
                        
                    }
                }
                else{
                    if(parent->middleChild->isThreeTree()) 
                    {
                        node->smallData = parent->bigData;
                        parent->bigData = parent->middleChild->bigData;
                        parent->middleChild->bigData=0;
                        // set N->parent->middleChild threetree false

                        if(!node->isLeaf())
                        {
                            // CORRECT
                            node->middleChild = previous_Sibling;
                            node->leftChild = parent->middleChild->rightChild;
                            node->leftChild->parent = node ; // added 27th 945 am
                            parent->middleChild->rightChild = NULL;
                        }
                        return true;
                    }
                }
                
                
                
            }
            else  // parent is 2 tree
            {
                if(parent->leftChild==node)
                {
                    if(parent->middleChild->isThreeTree())
                    {
                        node->smallData = parent->smallData;
                        parent->smallData = parent->middleChild->smallData;
                        parent->middleChild->smallData = parent->middleChild->bigData;
                        parent->middleChild->bigData=0; //need new way to set to 2tree
                        if(!node->isLeaf())
                        {
                            /*
                            if(node->middleChild)
                            {
                                node->leftChild=node->middleChild;
                            }*/
                            node->leftChild = previous_Sibling;
                            node->middleChild = parent->middleChild->leftChild;
                            node->middleChild->parent = node;
                            parent->middleChild->leftChild=parent->middleChild->middleChild;
                            parent->middleChild->middleChild=parent->middleChild->rightChild;
                            parent->middleChild->rightChild=NULL;
                            
                        }
                        return true;
                        
                    }
                }
                else{
                    if(parent->leftChild->isThreeTree())
                    {
                        node->smallData = parent->smallData;
                        parent->smallData = parent->leftChild->bigData;
                        parent->leftChild->bigData=0;
                        // use previous sibling?
                        if(!node->isLeaf())
                        {
                            /* Maybe correct
                            if(node->leftChild) {
                            node->middleChild=node->leftChild;
                            } */
                            node->middleChild = previous_Sibling;
                            node->leftChild = parent->leftChild->rightChild;
                            node->leftChild->parent=node;
                            parent->leftChild->rightChild=NULL; // aded 27th 9 50
                            node->rightChild=NULL;
                            
                            
                            
                        }
                        parent->leftChild->rightChild=NULL;
                        return true;
                    }
                }
                
                
            }
            return false;
        }

