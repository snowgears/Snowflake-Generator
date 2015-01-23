//
//  main.c
//  HW_4_Snowflakes
//
//  Created by Tanner Embry on 3/16/14.
//  Copyright (c) 2014 Tanner Embry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snowflake.h"

int main(int argc, const char * argv[])
{
    srand(time(NULL)); //seed random number using the time
    
    snowflakeArray *pSnowflake;
    pSnowflake = calloc(SNOWFLAKE_SIZE * SNOWFLAKE_SIZE, sizeof(int));

    
    Ray *pSnowflakeCenter = CreateRay((SNOWFLAKE_SIZE / 2), (SNOWFLAKE_SIZE / 2), 0, 0);
    Node *pCenterNode = CreateNode(pSnowflakeCenter);
    Tree *nodeTree = CreateTree(pCenterNode);
    
    
    RecursiveGrow(pCenterNode, pSnowflake);
    
    
    PrintSnowflake(pSnowflake);

    
    RemoveTree(nodeTree);
    free(pSnowflake);
}