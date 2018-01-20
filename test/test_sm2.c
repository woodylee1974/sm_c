/*
 * Copyright (C) 2007 Woody.Lee All rights reserved.
 */
#include <stdlib.h>
#include <stdio.h>
#include "c/statemachine.h"

enum {
    S_UNPLUGGED,
    S_INSERTED
};

enum {
    E_DEV_NOTIFY = 1
};

static int context = 1;

static
void mountLocalFS(void* c, TransitParam* tp)
{
    printf("mountLocalFS, ctx=%x, param1=%x, param2=%x\n", *(unsigned int*)c,
        (int)tp->param1,(int)tp->param2);
}

static
void umountLocalFS(void* c, TransitParam* tp)
{
    printf("umountLocalFS, ctx=%x, param1=%x, param2=%x\n", *(unsigned int*)c, (unsigned int)tp->param1,
        (unsigned int)tp->param2);
}

int main(int argc, const char* argv[])
{
    StateMachine* sm = SM_Create("USBDevice", S_UNPLUGGED);
    SM_AddTransit(sm, S_UNPLUGGED, E_DEV_NOTIFY, S_INSERTED, &context, umountLocalFS);
    SM_AddTransit(sm, S_INSERTED, E_DEV_NOTIFY, S_UNPLUGGED, &context, mountLocalFS);

    printf("initial state:%d\n", SM_GetState(sm));

    SM_UpdateState(sm, E_DEV_NOTIFY, (void*)1, (void*)0);
    printf("Current state:%d\n", SM_GetState(sm));

    SM_UpdateState(sm, E_DEV_NOTIFY, (void*)2, (void*)0);
    printf("Current state:%d\n", SM_GetState(sm));

    SM_Destroy(sm);

    return 0;
}
