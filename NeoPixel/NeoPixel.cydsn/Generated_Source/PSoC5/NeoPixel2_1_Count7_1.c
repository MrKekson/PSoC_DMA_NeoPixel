/*******************************************************************************
* File Name: NeoPixel2_1_Count7_1.c
* Version 1.0
*
* Description:
*  This file provides source code for the Count7 component's API.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NeoPixel2_1_Count7_1.h"
#include "CyLib.h"


uint8 NeoPixel2_1_Count7_1_initVar = 0u;


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the parameter editor
*  settings.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*  It is not necessary to call Count7_Init() because the Count7_Start() API
*  calls this function and is the preferred method to begin component
*  operation.
*
*******************************************************************************/
void NeoPixel2_1_Count7_1_Init(void) 
{
    /* Set the initial period value from parameter editor */
    NeoPixel2_1_Count7_1_PERIOD_REG = NeoPixel2_1_Count7_1_INITIAL_PERIOD;
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_Enable
********************************************************************************
*
* Summary:
*  Enables the software enable of the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*  It is not necessary to call Count7_Enable() because the Count7_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.
*  This API performs modification of auxiliary control register which is a
*  shared resource so it is required to disable interrupts until the
*  modification will complete.
*
*******************************************************************************/
void NeoPixel2_1_Count7_1_Enable(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    /* Set the counter start bit in auxiliary control. If routed enable
    * isn't used then this will immediately star the Count7 operation.
    */
    NeoPixel2_1_Count7_1_AUX_CONTROL_REG |= NeoPixel2_1_Count7_1_COUNTER_START;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  the counter. The first time the routine is executed, the period is set as
*  configured in the customizer. When called to restart the counter following a
*  Count7_Stop() call, the current period value is retained.
*
* Parameters:
*  None.
*
* Global Variables:
*  NeoPixel2_1_Count7_1_initVar - global variable.
*
* Return:
*  None.
*
*******************************************************************************/
void NeoPixel2_1_Count7_1_Start(void) 
{
    /* If not initialized then perform initialization */
    if(NeoPixel2_1_Count7_1_initVar == 0u)
    {
        NeoPixel2_1_Count7_1_Init();
        NeoPixel2_1_Count7_1_initVar = 1u;
    }

    /* Enable Count7 */
    NeoPixel2_1_Count7_1_Enable();
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_Stop
********************************************************************************
*
* Summary:
*  Disables the software enable of the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void NeoPixel2_1_Count7_1_Stop(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    /* Clear the counter start bit in auxiliary control. */
    NeoPixel2_1_Count7_1_AUX_CONTROL_REG &= (uint8) ~((uint8) NeoPixel2_1_Count7_1_COUNTER_START);

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_WriteCounter
********************************************************************************
*
* Summary:
*  This function writes the counter directly. The counter should be disabled
*  before calling this function.
*
* Parameters:
*  count - Value to be written to counter.
*
* Return:
*  None
*
*******************************************************************************/
void NeoPixel2_1_Count7_1_WriteCounter(uint8 count) 
{
    NeoPixel2_1_Count7_1_COUNT_REG = (count & NeoPixel2_1_Count7_1_COUNT_7BIT_MASK);
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_ReadCounter
********************************************************************************
*
* Summary:
*  This function reads the counter value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
uint8 NeoPixel2_1_Count7_1_ReadCounter(void) 
{
    return(NeoPixel2_1_Count7_1_COUNT_REG & NeoPixel2_1_Count7_1_COUNT_7BIT_MASK);
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_WritePeriod
********************************************************************************
*
* Summary:
*  This function writes the period register. The actual period is one greater
*  than the value in the period register since the counting sequence starts
*  with the period register and counts down to 0 inclusive. The period of the
*  counter output does not change until the counter is reloaded following the
*  terminal count value of 0 or due to a hardware load signal.
*
* Parameters:
*  period - Period value to be written.
*
* Return:
*  None
*
*******************************************************************************/
void NeoPixel2_1_Count7_1_WritePeriod(uint8 period) 
{
    NeoPixel2_1_Count7_1_PERIOD_REG = period;
}


/*******************************************************************************
* Function Name: NeoPixel2_1_Count7_1_ReadPeriod
********************************************************************************
*
* Summary:
*  This function reads the period register.
*
* Parameters:
*  None
*
* Return:
*  uint8 - Current period value.
*
*******************************************************************************/
uint8 NeoPixel2_1_Count7_1_ReadPeriod(void) 
{
    return(NeoPixel2_1_Count7_1_PERIOD_REG);
}


/* [] END OF FILE */
