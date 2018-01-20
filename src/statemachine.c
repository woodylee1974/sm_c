/*
 * Copyright (C) 2007 Woody.Lee All rights reserved.
 */
#include "c/statemachine.h"
#include <stdlib.h>
#include <stdio.h>

struct tagTransit;
typedef struct tagTransit Transit;

#define _DEBUG_SM

#ifdef _DEBUG_SM
#define SM_DBG(format, args...) fprintf(stderr, format, args)
#else
#define SM_DBG(format, args...)
#endif

struct tagTransit
{
    int st0;
    int st1;
    int evt;
    void* ctx;
    SM_Handler handler;
    Transit* next;
};

struct tagStateMachine
{
    const char* name;
    Transit*    head;
    int         current;
};

StateMachine* SM_Create(const char* name, int initial_state)
{
    StateMachine* sm = (StateMachine*)malloc(sizeof(StateMachine));
    if (sm == NULL) {
        return NULL;
    }
    sm->name = name;
    sm->head = NULL;
    sm->current = initial_state;
    return sm;
}

void SM_StartState(StateMachine* sm, int start_state)
{
    sm->current = start_state;
}

void SM_AddTransit(StateMachine* sm, int st0, int evt, int st1, void* ctx, SM_Handler handler)
{
    Transit* transit = (Transit*)malloc(sizeof(Transit));
    if (transit == NULL) {
        fprintf(stderr, "No memory to add transit.\n");
        return;
    }
    transit->st0 = st0;
    transit->st1 = st1;
    transit->evt = evt;
    transit->ctx = ctx;
    transit->handler = handler;
    transit->next = sm->head;
    sm->head = transit;
}

void SM_UpdateState(StateMachine* sm, int evt, void* param1, void* param2)
{
    Transit* transit;

    for (transit = sm->head; transit; transit = transit->next) {
        if ((transit->st0 == sm->current) && (transit->evt == evt)) {
            if (transit->handler != NULL) {
                TransitParam transit_param;
                transit_param.st0 = sm->current;
                transit_param.st1 = transit->st1;
                transit_param.evt = evt;
                transit_param.param1 = param1;
                transit_param.param2 = param2;
                transit->handler(transit->ctx, &transit_param);
                SM_DBG("[%s]:[%d] ----%d-----> [%d]\n", sm->name, sm->current, evt, transit_param.st1);
                sm->current = transit_param.st1;
                return;
            }
        }
    }
    SM_DBG("[%s]:[%d] ----%d-----> [undefined]\n", sm->name, sm->current, evt);
}

int SM_GetState(StateMachine* sm)
{
    return sm->current;
}

void SM_Destroy(StateMachine* sm)
{
    Transit* transit = sm->head, *next;

    while (transit) {
        next = transit->next;
        free(transit);
        transit = next;
    }
    free(sm);
}




