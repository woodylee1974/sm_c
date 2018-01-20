/*
 * Copyright (C) 2007 Woody.Lee All rights reserved.
 */
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTransitParam
{
    int st0;
    int st1;
    int evt;
    void* param1;
    void* param2;
}TransitParam;

struct tagStateMachine;
typedef struct tagStateMachine StateMachine;
typedef void (*SM_Handler)(void* ctx, TransitParam* tp);

/**
*
* @brief  This function create a state machine
* @param  name Given a name to a state machine for debugging purpose
* @param  initial_state Given a start state. Same as SM_StartState().
*
*/
StateMachine* SM_Create(const char* name, int initial_state);


/**
*
* @brief  This function set initial state of state machine
*
*/
void SM_StartState(StateMachine* sm, int start_state);


/**
*
* @brief  This function adds an arc between from_state and to_state.
* @param  st0  from_state
* @param  evt  the event that causes the state transition.
* @param  st1  to_state
* @param  ctx  context for state machine handler.
* @param  handler The function is called on this state transition.
*
*/
void SM_AddTransit(StateMachine* sm, int st0, int evt, int st1, void* ctx, SM_Handler handler);


/**
*
* @brief  This function forces state machine to update
* @param  evt  the event that emit to the state machine
* @param  param1 user parameter
* @param  param2 user parameter
*
*/
void SM_UpdateState(StateMachine* sm, int evt, void* param1, void* param2);


/**
*
* @brief  This function retrieve the state of state machine
*
*/
int SM_GetState(StateMachine* sm);


/**
*
* @brief  This function destroy state machine.
*
*/
void SM_Destroy(StateMachine* sm);


#ifdef __cplusplus
}
#endif

#endif /* STATEMACHINE_H */

