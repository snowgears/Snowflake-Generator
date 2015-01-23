//
//  snowflake.c
//  HW_4_Snowflakes
//
//  Created by Tanner Embry on 3/16/14.
//  Copyright (c) 2014 Tanner Embry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "snowflake.h"
#include <math.h>


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a ray structure                              //
//  Parameters:                                                    //
//            Starting point on the board (x,y)                    //
//            Angle of the line (angle)                            //
//                -Provided in degrees and converted to radians    //
//            Length of the line (length)                          //
//  Returns:                                                       //
//            Pointer to the ray that was created                  //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Ray *CreateRay(int x, int y, float angle, int length){
    Ray *pRay = NULL;
    pRay = malloc(sizeof(Ray));
    
    pRay->startX = x;
    pRay->startY = y;
    
    angle = angle + 90; //compensate to make it like unit circle
    pRay->angle = (PI * angle)/180;
    
    pRay->length = length;
    
    pRay->endX = x + length * cos(pRay->angle);
    pRay->endY = y + length * sin(pRay->angle);
    
    return pRay;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a node structure                             //
//  Parameters:                                                    //
//            Pointer to a ray structure (pRay)                    //
//  Returns:                                                       //
//            Pointer to the node that was created                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Node *CreateNode(Ray *pRay){
    Node *pNode = NULL;
    pNode= malloc(sizeof(Node));
    
    pNode->data = (void *)pRay;
    pNode->children[0] = NULL;
    pNode->children[1] = NULL;
    
    return pNode;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a tree structure                             //
//  Parameters:                                                    //
//            Pointer to a node structure (pParentNode)            //
//  Returns:                                                       //
//            Pointer to the tree that was created                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Tree *CreateTree(Node *pParentNode){
    Tree *pTree = NULL;
    pTree = malloc(sizeof(Tree));
    
    pTree->parentNode = pParentNode;
    
    return pTree;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Deconstructs a ray structure                         //
//  Parameters:                                                    //
//            Pointer to void (pVoid)                              //
//                -Converted to a Ray pointer when deallocating    //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int RemoveRay(void *pVoid){
    free((Ray *)pVoid);
    
    return 0;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Removes all nodes from the given parent node down    //
//                -Only called as a helper function for RemoveTree //
//  Parameters:                                                    //
//            Pointer to a node structure (pNode)                  //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int RecursiveNodeRemove(Node *pNode){

    RemoveRay(pNode->data);
    
    //node has no children
    if(pNode->children[0] == NULL && pNode->children[1] == NULL)
        return 0;
    
    if(pNode->children[0] != NULL)
        RecursiveNodeRemove(pNode->children[0]);
    if(pNode->children[1] != NULL)
        RecursiveNodeRemove(pNode->children[1]);
    
    return 0;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Deconstructs a tree structure                        //
//  Parameters:                                                    //
//            Pointer to a tree structure (pTree)                  //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int RemoveTree(Tree *pTree){
    RecursiveNodeRemove(pTree->parentNode);
    
    free(pTree);
    
    return 0;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Adds a child node to a given parent node             //
//  Parameters:                                                    //
//            Parent node to add child to (pParentNode)            //
//            Child node to be added to parent node (pChildNode)   //
//  Returns:                                                       //
//            0: Success                                           //
//            1: Failure                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int AddChildToNode(Node *pParentNode, Node *pChildNode){
    if(pParentNode->children[0] != NULL && pParentNode->children[1] != NULL)
        return 1;
    else if(pParentNode->children[0] == NULL)
        pParentNode->children[0] = pChildNode;
    else
        pParentNode->children[1] = pChildNode;
    
    return 0;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Clones the entire snowflake across the Y axis        //
//                -This method must be called before sibling       //
//                 method CloneTreeAcrossXAxis()                   //
//  Parameters:                                                    //
//            Pointer to a 2D snowflake array (pSnowflake)         //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int CloneTreeAcrossYAxis(snowflakeArray *pSnowflake){
    int x;
    int y;
    int clonedY;
    
    for(x=0; x < SNOWFLAKE_SIZE; x++){
        for(y=0; y < SNOWFLAKE_SIZE; y++){
            if((*pSnowflake)[x][y] == 1){
                clonedY = SNOWFLAKE_SIZE - y;
                (*pSnowflake)[x][clonedY] = 1;
            }
        }
    }
    
    return 0;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Clones the entire snowflake across the X axis        //
//                -This method must be called after sibling        //
//                 method CloneTreeAcrossYAxis()                   //
//  Parameters:                                                    //
//            Pointer to a 2D snowflake array (pSnowflake)         //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int CloneTreeAcrossXAxis(snowflakeArray *pSnowflake){
    int x;
    int y;
    int clonedX;
    
    for(x=0; x < SNOWFLAKE_SIZE; x++){
        for(y=0; y < SNOWFLAKE_SIZE; y++){
            if((*pSnowflake)[x][y] == 1){
                clonedX = SNOWFLAKE_SIZE - x;
                (*pSnowflake)[y][clonedX] = 1;
            }
        }
    }
    
    return 0;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Prints the snowflake out to the console              //
//  Parameters:                                                    //
//            Pointer to a 2D snowflake array (pSnowflake)         //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int PrintSnowflake(snowflakeArray *pSnowflake){
    int x;
    int y;
    
    
    CloneTreeAcrossXAxis(pSnowflake);
    CloneTreeAcrossYAxis(pSnowflake);
    
    //call cloning again just in case right corner was not cloned correctly
    CloneTreeAcrossXAxis(pSnowflake);
    CloneTreeAcrossYAxis(pSnowflake);
    

    printf("\n");
    for (x=1; x < SNOWFLAKE_SIZE; x++){
        for (y=1; y < SNOWFLAKE_SIZE; y++){
            if((*pSnowflake)[x][y] == 1)
                printf("%d ", 0);
            else
                printf("  ");
        }
        printf("\n");
    }
    return 0;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Returns a random integer between two values          //
//  Parameters:                                                    //
//            Minimum value (low)                                  //
//            Maximum value (high)                                 //
//  Returns:                                                       //
//            The random integer that was generated                //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int rand_mid(int low, int high) {
    return low+rand()%(high-low+1);
}


//////////////////////////////////////////////////////////////////////////
//  Function:                                                           //
//            Determines if a snowflake still has room to grow or not   //
//  Parameters:                                                         //
//            Pointer to Snowflake 2D array (pSnowflake)                //
//  Returns:                                                            //
//            0: Snowflake has no more room to grow                     //
//            1: Snowflake has room to grow                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

int SnowFlakeCanGrow(snowflakeArray *pSnowflake){
    int x;
    int y;
    
    for (x=0; x < SNOWFLAKE_SIZE; x++){
        if((*pSnowflake)[x][0] == 1)
            return 0;
        else if((*pSnowflake)[x][SNOWFLAKE_SIZE-1] == 1)
            return 0;
    }
    for (y=0; y < SNOWFLAKE_SIZE; y++){
        if((*pSnowflake)[0][y] == 1)
            return 0;
        else if((*pSnowflake)[SNOWFLAKE_SIZE-1][y] == 1)
            return 0;
    }
    
    return 1;
}


//////////////////////////////////////////////////////////////////////////
//  Function:                                                           //
//            Draws a ray by calling recursive helper method above      //
//  Parameters:                                                         //
//            Pointer to a Ray structure to draw (pRay)                 //    
//            Pointer to Snowflake 2D array (pSnowflake)                //
//  Returns:                                                            //
//            0: Line was drawn successfully                            //
//            1: Line was out of bounds of array and could not be drawn //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

int DrawRay(Ray *pRay, snowflakeArray *pSnowflake){
    //    int drewLine = DrawRayRecursiveHelper(pRay->startX, pRay->startY, pRay->angle, pRay->length, 0, pSnowflake);
    //
    //    return drewLine;

    int x0 = pRay->startX;
    int y0 = pRay->startY;
    
    int x1 = pRay->endX;
    int y1 = pRay->endY;
    
    //prevent from writing out of bounds of the snowflake
    if(x0 >= SNOWFLAKE_SIZE)
        x0 = SNOWFLAKE_SIZE - 1;
    else if(y0 >= SNOWFLAKE_SIZE)
        y0 = SNOWFLAKE_SIZE - 1;
    else if(x1 >= SNOWFLAKE_SIZE)
        x1 = SNOWFLAKE_SIZE - 1;
    else if(y1 >= SNOWFLAKE_SIZE)
        y1 = SNOWFLAKE_SIZE - 1;
    if(x0 < 0)
        x0 = 0;
    else if(y0 < 0)
        y0 = 0;
    else if(x1 < 0)
        x1 = 0;
    else if(y1 < 0)
        y1 = 0;
    
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    

    for(;;){
        (*pSnowflake)[x0][y0] = 1;
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
    
    printf("\n");
    
    return 0;
}


///////////////////////////////////////////////////////////////////////
//  Function:                                                        //
//            Returns the opposite angle (in degrees) of a given Ray //
//  Parameters:                                                      //
//            Ponter to a Ray structure (pRay)                       //
//  Returns:                                                         //
//            Opposite angle that was calculated                     //
//                                                                   //
///////////////////////////////////////////////////////////////////////

int GetOppositeAngle(Ray *pRay){
    int degreeAngle = pRay->angle * (180/PI);
    degreeAngle = degreeAngle - 90;
    
    //now we have our original angle in degrees, find opposite

   return 180 - degreeAngle;
    
}

///////////////////////////////////////////////////////////////////////
//  Function:                                                        //
//            Fills in snowflake array while recursively generating  //
//            nodes of the snowflake                                 //
//  Parameters:                                                      //
//            Parent node to start with (pNode)                      //
//                -This will be a node at the center of a 2D array   //
//  Returns:                                                         //
//            0: Success                                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

int RecursiveGrow(Node *pNode, snowflakeArray *pSnowflake){
    
    Node *pNewNode1;
    Node *pNewNode2;
    Ray *pRay;
    Ray *pNewRayLeft;
    Ray *pNewRayRight;
    int angleRay1;
    int rayLength;
    int oppositeAngle;
    

    //snowflake has no more room to grow
    if(SnowFlakeCanGrow(pSnowflake) == 0)
        return 0;
    
    pRay = (Ray *)pNode->data;

    angleRay1 = rand_mid(0, 180); //random angle on
    rayLength = rand_mid(1, SNOWFLAKE_SIZE/3);
    
    pNewRayLeft = CreateRay(pRay->endX, pRay->endY, angleRay1, rayLength);

    oppositeAngle = GetOppositeAngle(pNewRayLeft);
    pNewRayRight = CreateRay(pRay->endX, pRay->endY, oppositeAngle, rayLength);

    DrawRay(pNewRayLeft, pSnowflake);
    DrawRay(pNewRayRight, pSnowflake);
    
//    DrawRay(pNewRayOppositeBranch, pSnowflake);

    pNewNode1 = CreateNode(pNewRayLeft);
    pNewNode2 = CreateNode(pNewRayRight);
    
    AddChildToNode(pNode, pNewNode1);
    AddChildToNode(pNode, pNewNode2);
 
    RecursiveGrow(pNewNode1, pSnowflake);
    
    return 0;
}



