/**
* @file      UiHandlerThread.c
* @brief     File that contains the task code and supporting code for the UI
Thread for ESE516 Spring (Online) Edition
* @author    You! :)
* @date      2020-04-09

******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "UiHandlerThread/UiHandlerThread.h"

#include <errno.h>

#include "DistanceDriver/DistanceSensor.h"
#include "IMU/lsm6dso_reg.h"
#include "SerialConsole.h"
#include "WifiHandlerThread/WifiHandler.h"
#include "asf.h"
#include "gfx_mono.h"
#include "main.h"

/******************************************************************************
 * Defines
 ******************************************************************************/
#define BUTTON_PRESSES_MAX 16  ///< Number of maximum button presses to analize in one go

/******************************************************************************
 * Variables
 ******************************************************************************/
uiStateMachine_state uiState;         ///< Holds the current state of the UI
// struct GameDataPacket gamePacketIn;   ///< Holds the game packet to show
// struct GameDataPacket gamePacketOut;  ///< Holds the game packet to send back
volatile uint8_t red = 0;             ///< Holds the color of the red LEDs. Can be set by MQTT
volatile uint8_t green = 100;         ///< Holds the color of the green LEDs. Can be set by MQTT
volatile uint8_t blue = 50;           ///< Holds the color of the blue LEDs. Can be set by MQTT

uint8_t pressedKeys = 0;              ///< Variable to count how many presses the player has done
uint8_t keysToPress = 0;              ///< Variable that holds the number of new keypresses the user should do
bool playIsDone = false;              ///< Boolean flag to indicate if the player has finished moving.
                                      ///< Useful for COntrol to determine when to send back a play.
uint8_t buttons[BUTTON_PRESSES_MAX];  ///< Array to hold button presses
/******************************************************************************
 * Forward Declarations
 ******************************************************************************/

/******************************************************************************
 * Callback Functions
 ******************************************************************************/

/******************************************************************************
 * Task Function
 ******************************************************************************/

/**
 * @fn		void vUiHandlerTask( void *pvParameters )
 * @brief	STUDENT TO FILL THIS
 * @details 	student to fill this
 * @param[in]	Parameters passed when task is initialized. In this case we can ignore them!
 * @return		Should not return! This is a task defining function.
 * @note
 */
void vUiHandlerTask(void *pvParameters)
{
    // Do initialization code here
    SerialConsoleWriteString("UI Task Started!");
    uiState = UI_STATE_IGNORE_PRESSES;  // Initial state

    // Graphics Test - Students to uncomment to test out the OLED driver if you are using it! 
	/*
    gfx_mono_init();
    gfx_mono_draw_line(0, 0, 64, 48, GFX_PIXEL_SET);
    gfx_mono_draw_filled_circle(54, 24, 10, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string("ESE516",0,0, &sysfont);
	*/

    // Here we start the loop for the UI State Machine
    while (1) {
        switch (uiState) {
            case (UI_STATE_IGNORE_PRESSES): {
                // Ignore any presses until we receive a command from the control thread
                // to go to UI_STATE_SHOW_MOVES Will be changed by control with the
                // function void UiOrderShowMoves(struct GameDataPacket *packetIn) which
                // gets called when a valid MQTT Package comes in!
                break;
            }

            case (UI_STATE_SHOW_MOVES): {
                break;
            }

            case (UI_STATE_HANDLE_BUTTONS): {
                // This state should accept (gamePacketIn length + 1) moves from the
                // player (capped to maximum 19 + new move) The moves by the player
                // should be stored on "gamePacketOut". The keypresses that should count
                // are when the player RELEASES the button.

                // In this example, we return after only one button press!

                break;
            }

            default:  // In case of unforseen error, it is always good to sent state
                      // machine to an initial state.
                uiState = UI_STATE_HANDLE_BUTTONS;
                break;
        }

        // After execution, you can put a thread to sleep for some time.
        vTaskDelay(50);
    }
}

/******************************************************************************
 * Functions
 ******************************************************************************/
// void UiOrderShowMoves(struct GameDataPacket *packetIn)
// {
//     memcpy(&gamePacketIn, packetIn, sizeof(gamePacketIn));
//     uiState = UI_STATE_SHOW_MOVES;
//     playIsDone = false;  // Set play to false
// }
// 
// bool UiPlayIsDone(void)
// {
//     return playIsDone;
// }
// 
// struct GameDataPacket *UiGetGamePacketOut(void)
// {
//     return &gamePacketOut;
// }

/**
 int UIChangeColors(uint8_t r, uint8_t g, uint8_t b);
 * @brief	Changes the LED colors
 * @param [in]
 * @return
 * @note

*/
// void UIChangeColors(uint8_t r, uint8_t g, uint8_t b)
// {
//     red = r;
//     green = g;
//     blue = b;
// }
