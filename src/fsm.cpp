#include "fsm.h"

//****************************************************************************//
// Global variables
//****************************************************************************//
uint8_t  ActState;

const FSM_STATE_TABLE StateTable [NR_STATES][NR_EVENTS] =
{
  FSM_calculateIntensityAndEnergy, UVCMETERING, FSM_refreshDisplay, UVCMETERING, FSM_resetEnergy, UVCMETERING, FSM_moveToSetting, WAVELENSETTING, NULL, UVCMETERING,
  NULL, WAVELENSETTING, NULL, WAVELENSETTING, FSM_waveLengthIncrement, WAVELENSETTING, FSM_moveToMetering, UVCMETERING, FSM_waveLengthIncrement, WAVELENSETTING
};


//****************************************************************************//
// Initialize state machine
//****************************************************************************//
void FSM_Init (void)
{
  ActState = UVCMETERING;
}


//****************************************************************************//
// Event function "timeToCalc"
//****************************************************************************//
void FSM_timeToCalc (void)
{
  if (StateTable[ActState][TIMETOCALC].ptrFunct != NULL)
    StateTable[ActState][TIMETOCALC].ptrFunct();

  ActState = StateTable[ActState][TIMETOCALC].NextState;
}


//****************************************************************************//
// Event function "timeToRefresh"
//****************************************************************************//
void FSM_timeToRefresh (void)
{
  if (StateTable[ActState][TIMETOREFRESH].ptrFunct != NULL)
    StateTable[ActState][TIMETOREFRESH].ptrFunct();

  ActState = StateTable[ActState][TIMETOREFRESH].NextState;
}


//****************************************************************************//
// Event function "singleClick"
//****************************************************************************//
void FSM_singleClick (void)
{
  if (StateTable[ActState][SINGLECLICK].ptrFunct != NULL)
    StateTable[ActState][SINGLECLICK].ptrFunct();

  ActState = StateTable[ActState][SINGLECLICK].NextState;
}


//****************************************************************************//
// Event function "doubleClick"
//****************************************************************************//
void FSM_doubleClick (void)
{
  if (StateTable[ActState][DOUBLECLICK].ptrFunct != NULL)
    StateTable[ActState][DOUBLECLICK].ptrFunct();

  ActState = StateTable[ActState][DOUBLECLICK].NextState;
}


//****************************************************************************//
// Event function "longPress"
//****************************************************************************//
void FSM_longPress (void)
{
  if (StateTable[ActState][LONGPRESS].ptrFunct != NULL)
    StateTable[ActState][LONGPRESS].ptrFunct();

  ActState = StateTable[ActState][LONGPRESS].NextState;
}


//****************************************************************************//
