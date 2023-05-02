// LeapSync - Copyright (c) 2023 Jacob Espy. See LICENSE.txt for more details. 
// Using the ViGEmClient library to connect with ViGemBus

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <cmath>
#include <utility>
#include <stdexcept>

#include <windows.h>

#include <ViGEm/Common.h>
#include <ViGEm/Client.h>

#include "gamepad.h"

constexpr double CIRCLE_DEADZONE = 0.13;

// Declare the driver, controller, and report
PVIGEM_CLIENT ds4Driver, &ds4Client = ds4Driver;
PVIGEM_TARGET ds4Controller;
DS4_REPORT_EX ds4Report;

std::unordered_map<std::string, DS4_BUTTONS> buttonMap;
std::unordered_map<std::string, DS4_BUTTONS> triggerMap;
std::unordered_map<std::string, DS4_DPAD_DIRECTIONS> direcMap;
std::unordered_map<std::string, DS4_SPECIAL_BUTTONS> specialMap;

void initVIGEM() {
    ds4Client = vigem_alloc();

    if (!VIGEM_SUCCESS(vigem_connect(ds4Client))) {
        std::cout << "[Error] Can't connect to Virtual Controller." << std::endl << std::flush;
        return;
    }
    ds4Controller = vigem_target_ds4_alloc();
    std::cout << "[DS4] Connected successfully." << std::endl << std::flush;

    if (!VIGEM_SUCCESS(vigem_target_add(ds4Client, ds4Controller))) {
        std::cout << "[Error] Couldn't add virtual DS4 device." << std::endl << std::flush;
        return;
    }
    std::cout << "[DS4] Added virtual DS4 device successfully." << std::endl << std::flush;

    DS4_REPORT_INIT_EX(&ds4Report);
}

void initButtonMaps() {
    buttonMap = {
        {"CIRCLE", DS4_BUTTON_CIRCLE},
        {"CROSS", DS4_BUTTON_CROSS},
        {"SHARE", DS4_BUTTON_SHARE},
        {"OPTIONS", DS4_BUTTON_OPTIONS},
        {"TRIANGLE", DS4_BUTTON_TRIANGLE},
        {"SQUARE", DS4_BUTTON_SQUARE},
        {"SHOULDER_LEFT", DS4_BUTTON_SHOULDER_LEFT},
        {"SHOULDER_RIGHT", DS4_BUTTON_SHOULDER_RIGHT}
    };

    triggerMap = {
        {"TRIGGER_RIGHT", DS4_BUTTON_TRIGGER_RIGHT},
        {"TRIGGER_LEFT", DS4_BUTTON_TRIGGER_LEFT}
    };

    direcMap = {
        {"DPAD_EAST", DS4_BUTTON_DPAD_EAST},
        {"DPAD_WEST", DS4_BUTTON_DPAD_WEST},
        {"DPAD_NORTH", DS4_BUTTON_DPAD_NORTH},
        {"DPAD_SOUTH", DS4_BUTTON_DPAD_SOUTH},

        // {"DPAD_NORTHEAST", DS4_BUTTON_DPAD_NORTHEAST},
        // {"DPAD_SOUTHEAST", DS4_BUTTON_DPAD_SOUTHEAST},
        // {"DPAD_SOUTHWEST", DS4_BUTTON_DPAD_SOUTHWEST},
        // {"DPAD_NORTHWEST", DS4_BUTTON_DPAD_NORTHWEST}
    };

    specialMap = {
        {"TOUCHPAD", DS4_SPECIAL_BUTTON_TOUCHPAD}
    };
}

std::pair<double, double> calculateXY(int x, int y, int state) {
    const float range = (state == 2) ? 150.0f : (state == 3) ? 90.0f : 1.0f;
    const float norm_x = x / range;
    const float norm_y = y / range;

    const float magnitude = std::sqrt(norm_x * norm_x + norm_y * norm_y);
    const float clamped_x = (magnitude > 1.0f) ? norm_x / magnitude : norm_x;
    const float clamped_y = (magnitude > 1.0f) ? norm_y / magnitude : norm_y;

    const int scaled_x = static_cast<int>((clamped_x + 1.0f) * 127.5f);
    const int scaled_y = static_cast<int>((clamped_y + 1.0f) * 127.5f);

    return std::make_pair(std::clamp(scaled_x, 1, 254), std::clamp(scaled_y, 1, 254));
}

void updateButton(const std::string& updateData, int updateState) {
    const auto bMap = buttonMap.find(updateData);
    const auto tMap = triggerMap.find(updateData);
    const auto dMap = direcMap.find(updateData);
    const auto sMap = specialMap.find(updateData);

    if (bMap != buttonMap.end()) {
        if (updateState == 0) {
            ds4Report.Report.wButtons |= bMap->second;
        } else {
            ds4Report.Report.wButtons &= ~bMap->second;
        }

        std::cout << "[DS4] Button data received from client:    (" << bMap->first << ", " << updateState << ")" << std::endl;
    }

    if (tMap != triggerMap.end()) {
        const bool isLeftTrigger = tMap->second == triggerMap.at("TRIGGER_LEFT");
        const bool isRightTrigger = tMap->second == triggerMap.at("TRIGGER_RIGHT");

        if (updateState == 0) {
            ds4Report.Report.bTriggerL = isLeftTrigger ? 255 : ds4Report.Report.bTriggerL;
            ds4Report.Report.bTriggerR = isRightTrigger ? 255 : ds4Report.Report.bTriggerR;
            ds4Report.Report.wButtons |= tMap->second;
        } else {
            ds4Report.Report.bTriggerL = isLeftTrigger ? 0 : ds4Report.Report.bTriggerL;
            ds4Report.Report.bTriggerR = isRightTrigger ? 0 : ds4Report.Report.bTriggerR;
            ds4Report.Report.wButtons &= ~tMap->second;
        }

        std::cout << "[DS4] Trigger data received from client:   (" << tMap->first << ", " << updateState << ")" << std::endl;
    }

    if (dMap != direcMap.end()) {
        ds4Report.Report.wButtons &= ~0xF;
        if (updateState == 0) {            
            ds4Report.Report.wButtons |= (USHORT)dMap->second;
        } else {
            ds4Report.Report.wButtons |= (USHORT)DS4_BUTTON_DPAD_NONE;
        }
        std::cout << "[DS4] DPad data received from client:      (" << dMap->first << ", " << updateState << ")" << std::endl;
    }

    if (sMap != specialMap.end()) {
        if (updateState == 0) {
            ds4Report.Report.bSpecial |= sMap->second;
        } else {
            ds4Report.Report.bSpecial &= ~sMap->second;
        }
        std::cout << "[DS4] Special data received from client:   (" << sMap->first << ", " << updateState << ")" << std::endl;
    }
}

void updateJoystick(const std::string& joystickData, int stick) {
    std::stringstream ss(joystickData);
    char c; // used to discard the '(' and ',' characters
    int x, y;

    ss >> c >> x >> c >> y >> c;

    const auto [result_x, result_y] = calculateXY(x, y, stick);

    if (stick == 2) {
        ds4Report.Report.bThumbLX = result_x;
        ds4Report.Report.bThumbLY = -result_y;
        std::cout << "[DS4] CirclePad data received from client: (" << result_x << ", " << -result_y << ")" << std::endl;
    } else {
        ds4Report.Report.bThumbRX = result_x;
        ds4Report.Report.bThumbRY = -result_y;
        std::cout << "[DS4] C-Stick data received from client:   (" << result_x << ", " << -result_y << ")" << std::endl;
    }
}

void updateTouchpad(const std::string& touchpadData) {
    std::stringstream ss(touchpadData);
    char c;
    int x, y;

    ss >> c >> x >> c >> y >> c;

    // Scale the 3DS resolution to the DS4 touchpad resolution (1920x943)
    int scaledX = (x * 1920) / 320;
    int scaledY = (y * 943) / 240 ;

    ds4Report.Report.sCurrentTouch.bIsUpTrackingNum1 = (false << 7);
    ds4Report.Report.sCurrentTouch.bTouchData1[0] = (scaledX & 0xFF); // Store the lower 8 bits of X
    ds4Report.Report.sCurrentTouch.bTouchData1[1] = ((scaledX >> 8) & 0x0F) | ((scaledY & 0x0F) << 4); // Store upper 4 bits of X and lower 4 bits of Y
    ds4Report.Report.sCurrentTouch.bTouchData1[2] = (scaledY >> 4) & 0xFF; // Store the upper 8 bits of Y
    
    // Release touch if coordinates are (0, 0)
    if (scaledX == 0 && scaledY == 0) {
        ds4Report.Report.sCurrentTouch.bIsUpTrackingNum1 = (true << 7);
    }

    std::cout << "[DS4] Touchpad data received from client: (" << scaledX << ", " << scaledY << ")" << std::endl;
}

void updateMotion(const std::string& motionData, int gyro) {
    std::stringstream ss(motionData);
    char c;
    int x, y, z;

    ss >> c >> x >> c >> y >> c >> z >> c;

    if (gyro == 5) {
        ds4Report.Report.wGyroX = -x;
        ds4Report.Report.wGyroY = z;
        ds4Report.Report.wGyroZ = y;
        // std::cout << "[DS4] Gyro data received from client: (" << -x << ", " << z << ", " << y << ")" << std::endl;

    } else {
        ds4Report.Report.wAccelX = x;
        ds4Report.Report.wAccelY = y;
        ds4Report.Report.wAccelZ = z;
        // std::cout << "[DS4] Accelerometer data received from client: (" << x << ", " << y << ", " << z << ")" << std::endl;
    }
}

void processInput() {
    if (!VIGEM_SUCCESS(vigem_target_ds4_update_ex(ds4Client, ds4Controller, ds4Report))) {
        std::cout << "[Error] Error when submitting report update to DS4." << std::endl << std::flush;
    }
}

void buttonHandler(const std::string& buttonData, int updateState) {
    updateButton(buttonData, updateState);
    processInput();
}

void joystickHandler(const std::string& joystickData, int stick) {
    updateJoystick(joystickData, stick);
    processInput();
}

void touchpadHandler(const std::string& touchpadData) {
    updateTouchpad(touchpadData);
    processInput();
}

void motionHandler(const std::string& motionData, int gyro) {
    updateMotion(motionData, gyro);
    processInput();
}

void gamepadSession() {
    initVIGEM();
    initButtonMaps();
}