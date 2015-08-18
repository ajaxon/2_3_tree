//
//  main.cpp
//  project3
//
//  Created by Allen on 4/16/14.
//  Copyright (c) 2014 Allen. All rights reserved.
//

#include <iostream>
#include "ttTree.h"

int main(int argc, const char * argv[])
{
    
    ttTree mytree;
    mytree.ttTreeInsert(37);
     mytree.ttTreeInsert(50);
     mytree.ttTreeInsert(30);
     mytree.ttTreeInsert(39);
     mytree.ttTreeInsert(70);
     mytree.ttTreeInsert(37);
     mytree.ttTreeInsert(90);
     mytree.ttTreeInsert(10);
     mytree.ttTreeInsert(36);
     mytree.ttTreeInsert(20);
     mytree.ttTreeInsert(38);
     mytree.ttTreeInsert(40);
     mytree.ttTreeInsert(60);
     mytree.ttTreeInsert(80);
     mytree.ttTreeInsert(100);
     mytree.ttTreeInsert(35);
     mytree.ttTreeInsert(34);
     mytree.ttTreeInsert(33);
     mytree.ttTreeInsert(32);
    
    
    
  
    for(int i =0;i<2000;i++)
    {
        mytree.ttTreeInsert(i*10);
    }
    for(int i=1999; i>1;i--)
    {
        mytree.ttTreeDelete(i*10);
    }
    
    /*
    mytree.ttTreeInsert(10);//
    mytree.ttTreeInsert(20);
    mytree.ttTreeInsert(30);//
    mytree.ttTreeInsert(35);
    mytree.ttTreeInsert(36);
    mytree.ttTreeInsert(31);//
    mytree.ttTreeInsert(29);
    mytree.ttTreeInsert(11);
    mytree.ttTreeInsert(12);//
    mytree.ttTreeInsert(13);//
    mytree.ttTreeInsert(28);//
    mytree.ttTreeInsert(34);
    mytree.ttTreeInsert(27);//
    mytree.ttTreeInsert(14);
    mytree.ttTreeInsert(21);
    mytree.ttTreeInsert(15);
     mytree.ttTreeInsert(16);
     mytree.ttTreeInsert(32);
     mytree.ttTreeInsert(26);
    mytree.ttTreeInsert(23);
    mytree.ttTreeInsert(22);
    mytree.ttTreeInsert(33);
    mytree.ttTreeInsert(37);
    mytree.ttTreeInsert(38);
    mytree.ttTreeInsert(24);//
    mytree.ttTreeInsert(25);
    mytree.ttTreeInsert(1);//
  mytree.ttTreeInsert(2);//
    
    
    mytree.ttTreeDelete(28);
    mytree.ttTreeDelete(28);
    mytree.ttTreeDelete(10);
    mytree.ttTreeDelete(12);
    mytree.ttTreeDelete(27);
    mytree.ttTreeDelete(1);
     mytree.ttTreeDelete(30);
     mytree.ttTreeDelete(31);
     mytree.ttTreeDelete(2);
     mytree.ttTreeDelete(13);
     mytree.ttTreeDelete(24);
     mytree.ttTreeDelete(20);
     mytree.ttTreeDelete(35);
    mytree.ttTreeDelete(36);
     mytree.ttTreeDelete(29);
     mytree.ttTreeDelete(11);
     mytree.ttTreeDelete(32);
     mytree.ttTreeDelete(14);
     mytree.ttTreeDelete(21);
    mytree.ttTreeDelete(22);
    mytree.ttTreeDelete(33);
    mytree.ttTreeDelete(37);
    mytree.ttTreeDelete(16);
    mytree.ttTreeDelete(26);
    mytree.ttTreeDelete(23);
    mytree.ttTreeDelete(38);
    mytree.ttTreeDelete(25);
    */
    mytree.ttTreePrint();
    //mytree.postorder(mytree.root, 0);
    
    return 0;
}

