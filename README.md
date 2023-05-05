# LeapSyncServer

LeapSyncServer is a server program that receives data from LeapSync, a 3DS homebrew application, and emulates a DualShock4 controller. This allows you to use your 3DS as a controller for games on your PC that support DualShock4 input, including support for touchpad, gyroscope and accelerometer inputs from the 3DS.

## Requirements

To run LeapSyncServer, you need the following:

- The LeapSync homebrew application installed on your 3DS (see [LeapSync](https://github.com/Smoked-Fish/LeapSync) for details)
- ViGEmBus, a Windows driver for emulating virtual game controllers (download and install from [GitHub](https://github.com/ViGEm/ViGEmBus/releases))

## Installation

To install LeapSyncServer, follow these steps:

1. Go to the [releases section](https://github.com/Smoked-Fish/LeapSyncServer/releases) of this repository.
2. Download the latest compiled version of LeapSyncServer.
3. Run the LeapSyncServer executable to start the server.

Note that you will still need to install the requirements listed in the [Requirements](#requirements) section.

## Usage

Once you have have LeapSyncServer on your OC and installed LeapSync on your 3DS, you can use your 3DS as a controller for games on your PC that support DualShock4 input. To use LeapSyncServer, follow these steps:

1. Launch LeapSyncServer on your PC.
2. Launch LeapSync on your 3DS.
4. Start a game on your PC that supports DualShock4 input.
5. Use your 3DS as a controller for the game.

## Acknowledgements

The following tools were used in the creation of LeapSyncServer:

- UPX (Ultimate Packer for eXecutables): Used to compress the LeapSyncServer executable.
- ViGEmBus: A Windows driver for emulating virtual game controllers, used for creating the virtual DualShock4 controller.
- ViGEmClient: A library for interfacing with the ViGEmBus driver, used for communication between LeapSyncServer and the emulated controller.

A special thanks to the developers of these tools for their contribution to the software development community.

## License

LeapSyncServer is licensed under the MIT License. See [LICENSE](LICENSE) for details.
