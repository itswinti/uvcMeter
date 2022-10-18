#ifndef FSM_H
#define FSM_H

#include <stdio.h>

//****************************************************************************//
// State table typedef
//****************************************************************************//
typedef struct
{
  void (*ptrFunct) (void);
  uint8_t NextState;
} FSM_STATE_TABLE;

extern uint8_t ActState;


#define NR_EVENTS 5
#define TIMETOCALC  0
#define TIMETOREFRESH  1
#define SINGLECLICK  2
#define DOUBLECLICK  3
#define LONGPRESS  4

#define NR_STATES 2
#define UVCMETERING  0
#define WAVELENSETTING  1


//****************************************************************************//
// Function prototypes
//****************************************************************************//
// Initialize state machine
void FSM_Init (void);

// Event function "timeToCalc"
void FSM_timeToCalc (void);

// Event function "timeToRefresh"
void FSM_timeToRefresh (void);

// Event function "singleClick"
void FSM_singleClick (void);

// Event function "doubleClick"
void FSM_doubleClick (void);

// Event function "longPress"
void FSM_longPress (void);

// Transition function "calculateIntensityAndEnergy"
void FSM_calculateIntensityAndEnergy (void);

// Transition function "refreshDisplay"
void FSM_refreshDisplay (void);

// Transition function "resetEnergy"
void FSM_resetEnergy (void);

// Transition function "moveToSetting"
void FSM_moveToSetting (void);

// Transition function "waveLengthIncrement"
void FSM_waveLengthIncrement (void);

// Transition function "moveToMetering"
void FSM_moveToMetering (void);


//****************************************************************************//

#endif /* FSM_H */

//****************************************************************************//
