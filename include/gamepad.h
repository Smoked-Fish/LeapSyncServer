// LeapSync - Copyright (c) 2023 Jacob Espy. See LICENSE.txt for more details. 
// Using the ViGEmClient library to connect with ViGemBus

#include <unordered_map>
#include <string>
#include <utility>
#include <ViGEm/Common.h>
#include <ViGEm/Client.h>

/// Initializes the ViGEm connection and virtual gamepad.
void initVIGEM();

/// Initializes the button maps for button, trigger, dpad, and special inputs.
void initButtonMaps();

/// Updates the directional keys list with the given key and state,
/// and returns the current direction of the D-pad.
/// @param key The key to add or remove from the list.
/// @param updateState 0 to add the key, 1 to remove the key.
/// @return The current direction of the D-pad.
USHORT updateDPadList(USHORT key, int updateState);

/// Calculates the scaled and clamped x and y values for joystick input.
/// @param x The raw x-axis value.
/// @param y The raw y-axis value.
/// @param state The current state of the joystick.
/// @return A std::pair containing the scaled and clamped x and y values.
std::pair<double, double> calculateXY(int x, int y, int state);

/// Updates the button state of the virtual gamepad.
/// @param updateData The button identifier.
/// @param updateState The new state of the button (0: pressed, 1: released).
void updateButton(const std::string& updateData, int updateState);

/// Updates the joystick state of the virtual gamepad.
/// @param joystickData The joystick data string in the format "(x,y)".
/// @param stick The stick identifier (2: left stick, 3: right stick).
void updateJoystick(const std::string& joystickData, int stick);

/// Updates the touchpad state of the virtual gamepad.
/// @param touchData The touchpad data string in the format "(x,y)".
void updateTouchpad(const std::string& touchpadData);

/// Updates the motion data of the virtual gamepad.
/// @param motionData The motion data string in the format "(x,y,z)".
/// @param gyro The motion identifier (5: gyro, 6: accel).
void updateMotion(const std::string& motionData, int gyro);

/// Processes the input updates and sends them to the virtual gamepad.
void processInput();

/// Handles button updates for the virtual gamepad.
/// @param buttonData The button identifier.
/// @param updateState The new state of the button (0: pressed, 1: released).
void buttonHandler(const std::string& buttonData, int updateState);

/// Handles joystick updates for the virtual gamepad.
/// @param joystickData The joystick data string in the format "(x,y)".
/// @param stick The stick identifier (2: left stick, 3: right stick).
void joystickHandler(const std::string& joystickData, int stick);

/// Handles touchpad updates for the virtual gamepad.
/// @param joystickData The touchpad data string in the format "(x,y)".
void touchpadHandler(const std::string& touchData);

/// Handles gyro updates for the virtual gamepad.
/// @param motionData The motion data string in the format "(x,y,z)".
/// @param gyro The motion identifier (5: gyro, 6: accel).
void motionHandler(const std::string& motionData, int gyro);

/// Initializes the virtual gamepad session.
void gamepadSession();