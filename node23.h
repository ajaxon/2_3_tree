//
//  node23.h
//  project3
//
//  Created by Allen on 4/19/14.
//  Copyright (c) 2014 Allen. All rights reserved.
//

#ifndef __project3__node23__
#define __project3__node23__

#include <iostream>

class node23{
    
public:
    
    node23 *leftChild;
    node23 *middleChild;
    node23 *rightChild;
    
    node23 *parent;
    
    int smallData;
    int bigData;
    
    node23(int data, node23 *parent = NULL);
    void nodeEdit(int data, node23 *parent=NULL);
    
    node23();
    
    bool dataFull;
    
    bool isLeaf();
    bool isThreeTree();
    
    void insert2Tree(int key,node23 *leftChild = NULL, node23 *rightChild=NULL);
    void insert3Tree(int key, node23 *root,node23 *lc = NULL, node23 *rc = NULL);
};

#endif /* defined(__project3__node23__) */
