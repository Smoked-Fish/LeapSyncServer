# LeapSyncServer

LeapSyncServer is a server program that receives data from LeapSync, a 3DS homebrew application, and emulates a DualShock4 controller. This allows you to use your 3DS as a controller for games on your PC that support DualShock4 input.

## Requirements

To run LeapSyncServer, you need the following:

- The LeapSync homebrew application installed on your 3DS (see [LeapSync](https://github.com/Smoked-Fish/LeapSync) for details)
- ViGEmBus, a Windows driver for emulating virtual game controllers (download and install from [GitHub](https://github.com/ViGEm/ViGEmBus/releases))

## Installation

To install LeapSyncServer, follow these steps:

1. Go to the [releases section](https://github.com/your-username/leapsyncserver/releases) of this repository.
2. Download the latest compiled version of LeapSyncServer.
3. Run the LeapSyncServer executable to start the server.

Note that you will still need to install the requirements listed in the [Requirements](#requirements) section.
 <!-- and configure the server as described in the [Usage](#usage) section. -->

## Usage

Once LeapSyncServer is running and connected to LeapSync on your 3DS, you can use your 3DS as a DualShock4 controller for games on your PC that support DualShock4 input. To disconnect, simply close LeapSync on your 3DS or stop LeapSyncServer on your PC.

<!-- ## Configuration

You can configure LeapSyncServer by editing the `config.ini` file in the repository directory. The following options are available:

- `port`: the port number that LeapSyncServer listens on for incoming connections (default is `49500`)
- `debug`: whether to enable debug output (default is `false`) -->

<!-- ## Troubleshooting

If you encounter any issues with LeapSyncServer, try the following:

- Make sure that your DualShock4 controller is connected to your PC and supported by the SCPToolkit driver (Windows only) or the ds4drv driver (macOS and Linux).
- Make sure that you have installed all the required Python packages by running `pip install -r requirements.txt` in the repository directory.
- Make sure that your 3DS is connected to the same network as your PC and that you have entered the correct IP address in LeapSync.
- Try running LeapSyncServer with the `--debug` option to enable debug output. -->

## License

LeapSyncServer is licensed under the MIT License. See [LICENSE](LICENSE) for details.