//
//  ttTree.h
//  project3
//
//  Created by Allen on 4/16/14.
//  Copyright (c) 2014 Allen. All rights reserved.
//

#ifndef __project3__ttTree__
#define __project3__ttTree__

#include <iostream>
#include "node23.h"
class ttTree{

public:
    node23 * root;
    ttTree();
    
    bool searchInsert(node23* node, int key);
    bool ttTreeInsert(int key);
    bool ttTreeDelete(int key);
    node23* getInorderSuccessor(node23 *node,int key);
    void ttTreePrint();
    void postorder(node23*,int);
    
    bool search(int key);
    void insert2tree(int key);
    void insert3Tree(node23 *node, int key,node23 *lc = NULL, node23 *rc = NULL);
    
    void inorderTraverse(node23 *root);
    
    bool fixCase2(node23* node);
    node23* fixCase3(node23* node);

};
#endif /* defined(__project3__ttTree__) */
