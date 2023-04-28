// Binary constants that implement the escape characters used in slip encoding
#define SLIP_END ((uint8_t)(0xC0))
#define SLIP_ESC ((uint8_t)(0xDB))
#define SLIP_ESC_END ((uint8_t)(0xDC))
#define SLIP_ESC_ESC ((uint8_t)(0xDD))

// Binary constants for the gamepad button btate
#define SLIP_TRUE ((uint8_t)(0xC1))
#define SLIP_FALSE ((uint8_t)(0xC2))

// Binary constants for circle/cstick
#define SLIP_CIRCLE ((uint8_t)(0xC3))
#define SLIP_CSTICK ((uint8_t)(0xC4))

// Binary constants for gyroscope angular rate
#define SLIP_GYRO ((uint8_t)(0xC5))

// Binary constants for gamepad button inputs
#define DS_CIRCLE ((uint8_t)(0x00))
#define DS_CROSS ((uint8_t)(0x01))
#define DS_SHARE ((uint8_t)(0x02))
#define DS_OPTIONS ((uint8_t)(0x03))
#define DS_DPAD_EAST ((uint8_t)(0x04))
#define DS_DPAD_WEST ((uint8_t)(0x05))
#define DS_DPAD_NORTH ((uint8_t)(0x06))
#define DS_DPAD_SOUTH ((uint8_t)(0x07))
#define DS_TRIGGER_RIGHT ((uint8_t)(0x08))
#define DS_TRIGGER_LEFT ((uint8_t)(0x0B))
#define DS_TRIANGLE ((uint8_t)(0x0C))
#define DS_SQUARE ((uint8_t)(0x0E))
#define DS_SHOULDER_LEFT ((uint8_t)(0x0F))
#define DS_SHOULDER_RIGHT ((uint8_t)(0x10))
#define DS_TOUCHPAD ((uint8_t)(0x11))