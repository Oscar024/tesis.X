#include "cny70.h"

int getCNY70Value(void)
{
    if(RB0 == 1 && RB1 == 1 && RB2 == 0 && RB3 == 1 && RB4 == 1)
        return 0;
    else if(RB0 == 1 && RB1 == 0 && RB2 == 1 && RB3 == 1 && RB4 == 1)
        return -1;
    else if(RB0 == 0 && RB1 == 1 && RB2 == 1 && RB3 == 1 && RB4 == 1)
        return -2;
    else if(RB0 == 1 && RB1 == 1 && RB2 == 1 && RB3 == 0 && RB4 == 1)
        return 1;
    else if(RB0 == 1 && RB1 == 1 && RB2 == 1 && RB3 == 1 && RB4 == 0)
        return 2;
    else if(RB0 == 1 && RB1 == 1 && RB2 == 1 && RB3 == 0 && RB4 == 0)
        return 2;
    else if(RB0 == 0 && RB1 == 0 && RB2 == 1 && RB3 == 1 && RB4 == 1)
        return -2;
    else if(RB0 == 1 && RB1 == 0 && RB2 == 0 && RB3 == 1 && RB4 == 1)
        return -1;
    else if(RB0 == 1 && RB1 == 1 && RB2 == 0 && RB3 == 0 && RB4 == 1)
        return 1;
    else
        return 0;
//     if(RB0 == 0 && RB1 == 0 && RB2 == 1 && RB3 == 0 && RB4 == 0)
//        return 0;
//    else if(RB0 == 0 && RB1 == 1 && RB2 == 0 && RB3 == 0 && RB4 == 0)
//        return -1;
//    else if(RB0 == 1 && RB1 == 0 && RB2 == 0 && RB3 == 0 && RB4 == 0)
//        return -2;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 0 && RB3 == 1 && RB4 == 0)
//        return 1;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 0 && RB3 == 0 && RB4 == 1)
//        return 2;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 0 && RB3 == 1 && RB4 == 1)
//        return 2;
//    else if(RB0 == 1 && RB1 == 1 && RB2 == 0 && RB3 == 0 && RB4 == 0)
//        return -2;
//    else if(RB0 == 0 && RB1 == 1 && RB2 == 1 && RB3 == 0 && RB4 == 0)
//        return -1;
//    else if(RB0 == 0 && RB1 == 0 && RB2 == 1 && RB3 == 1 && RB4 == 0)
//        return 1;
//    else
//        return 0;
}

