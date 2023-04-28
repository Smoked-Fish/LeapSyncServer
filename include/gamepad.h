#include <unordered_map>
#include <string>
#include <utility>
#include <ViGEm/Common.h>
#include <ViGEm/Client.h>

/// Initializes the ViGEm connection and virtual gamepad.
void initVIGEM();

/// Initializes the button maps for button, trigger, dpad, and special inputs.
void initButtonMaps();

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
/// @param updateJoystick The joystick data string in the format "(x,y)".
/// @param stick The stick identifier (2: left stick, 3: right stick).
void updateJoystick(const std::string& updateJoystick, int stick);

/// Updates the gyro state of the virtual gamepad.
/// @param gyroData The gyro data string in the format "(x,y,z)".
void updateGyro(const std::string& gyroData);

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

/// Handles gyro updates for the virtual gamepad.
/// @param gyroData The gyro data string in the format "(x,y,z)".
void gyroHandler(const std::string& gyroData);

/// Initializes the virtual gamepad session.
void gamepadSession();