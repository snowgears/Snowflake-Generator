//
//  snowflake.h
//  HW_4_Snowflakes
//
//  Created by Tanner Embry on 3/16/14.
//  Copyright (c) 2014 Tanner Embry. All rights reserved.
//

///////////////////////
//     Constants     //
///////////////////////

#define SNOWFLAKE_SIZE  51
#define PI              3.14159265358979323846264338327950288419716939937510582


////////////////////////
//  Type Definitions  //
////////////////////////

typedef int snowflakeArray[SNOWFLAKE_SIZE][SNOWFLAKE_SIZE];

typedef struct{
    int startX;
    int startY;
    float angle;
    int length;
    int endX;
    int endY;
}Ray;

typedef struct{
    void *data;
    struct Node * children[2];
}Node;

typedef struct{
    Node *parentNode;
    
    //TODO function pointer
}Tree;


///////////////////////
//     Functions     //
///////////////////////

Ray *CreateRay(int x, int y, float angle, int length);

Node *CreateNode(Ray *pRay);

Tree *CreateTree(Node *pParentNode);

int RecursiveGrow(Node *pNode, snowflakeArray *pSnowflake);

int PrintSnowflake(snowflakeArray *pSnowflake);

int RemoveTree(Tree *pTree);
