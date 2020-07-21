# LithiumInjector

Free open-source injector made for **Counter-Strike: Global Offensive** game. It uses LoadLibrary method and bypasses Valve's LoadLibrary prevention system.

## Features
LithiumInjector restores original state of every possible function that Valve could use to detect LoadLibrary injection.

## Getting started

### Prerequisites
To compile this project you will need Microsoft Visual Studio 2019, platform toolset v142 and Windows SDK 10.0. If you don't have them, download them from [here](https://visualstudio.microsoft.com/) (SDK's are installed during the setup)

### Compiling
After downloading the source code from this repository, open **LithiumInjector.sln** in Microsoft Visual Studio 2019. Now change build configuration to `Release | x86` and press **Build solution**. You should receive `LithiumInjector.exe`.

### Usage
Start CS:GO and wait for it to load, then open LithiumInjector.exe and provice name of the DLL that you want to inject (Make sure that DLL is in the same folder as injector). Press `enter` and now your DLL should be succesfully injected.

## License

> Copyright (c) 2020 Nexo

This project is licensed under the [MIT License](https://opensource.org/licenses/mit-license.php) - see the [LICENSE](LICENSE) file for details.
