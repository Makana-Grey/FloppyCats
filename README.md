# 🐾 Space Paws aka "Floppy Cats" 🐾
### This simple game like famous Floppy Bird but about Cats in space and with P2P multiplayer

![image](https://user-images.githubusercontent.com/116926286/226208029-636c4693-8d11-4af6-8e74-b377c1121ebd.png)

To build and run game you need:

1. Setup [Visual Studio to your Windows machine](https://visualstudio.microsoft.com/) with [C++ components](https://learn.microsoft.com/ru-ru/cpp/build/vscpp-step-0-installation?view=msvc-170)
2. Install [vcpkg](https://vcpkg.io/en/getting-started.html) and integrate it with *MSBuild/Visual Studio*
3. Install [NodeJS v18.14.2 for Windows too](https://nodejs.org/download/release/v18.14.2/) and [enable corepack for yarn](https://yarnpkg.com/getting-started/install)

This points are not required, it's just define how i develop.  
Below is the information about dependecies for every subproject. that you can use to build it for you enviroment.

> **Note**: Code of game is not cross platform and write for only Windows.

## Build **[🌐 IPv4resolver](https://github.com/Makana-Grey/FloppyCats/tree/master/IPv4resolver)**

It's first project that you need to build. It's uses in game as **STATIC** library.  
Use [🔷🔹☄️Boost.Asio🔷🔹☄️](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_asio.html) for define IPv4 by host name.   
In Visual Studio everything is set up so you just have to run the build.  
> **Note**: Build library for *Debug* and *Release* states.

## Build **[🎯 FloppyCatsOnlineAPI](https://github.com/Makana-Grey/FloppyCats/tree/master/FloppyCatsOnlineAPI)**

Run next commands:  
`yarn pre-start` - it's install all npm packets and set up secrets (if you have it) for testing via [Thunder Client](https://www.thunderclient.com/) production state of API. All configs of Thunder Client already defined and [must automaticaly integrate to your workspace](https://github.com/rangav/thunder-client-support#git-sync). 
  
`yarn start` - run API on *http://localhost:3000*

## Build **[👾 FloppyCatsOnline](https://github.com/Makana-Grey/FloppyCats/tree/master/FloppyCatsOnline)**
Use [🟢🟩💚SFML🟢🟩💚](https://www.sfml-dev.org/) for render game and [🔥Jsoncpp](https://github.com/open-source-parsers/jsoncpp), [🕸️IPv4resolver](https://github.com/Makana-Grey/FloppyCats/tree/master/IPv4resolver) and [🖧SFML Network](https://www.sfml-dev.org/tutorials/2.5/#network-module) for multiplayer mode.  
In [definition.hpp](https://github.com/Makana-Grey/FloppyCats/blob/master/FloppyCatsOnline/FloppyCatsOnline/definitions.hpp) API point set to *http://localhost:3000*  
Config set up to watch on *IPv4resolver/Debug* and *IPv4resolver/Release* to use [IPv4resolver](https://github.com/Makana-Grey/FloppyCats/tree/master/IPv4resolver)  
  
For static files like media and other data is set up [Post-Build hooks](https://learn.microsoft.com/en-us/visualstudio/ide/how-to-specify-build-events-csharp?view=vs-2022) that use standart Windows CMD commands to copy this files to output dirs.  

Gook luck 🍀

