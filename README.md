# 🏎️ Highway Racing

A 2D highway racing game developed in **C++ using SFML 3.0.0** as a semester project for the Programming Fundamentals (PF) course at FAST National University by: 
26L-0703 | Muhammad Hassnain Shahid
26L-0707 | Fatima Yasser
26L-0722 | Eman Aamir

The player controls a car driving along a three-lane highway, avoiding incoming traffic and road obstacles while trying to achieve the highest possible score.

## 🎮 Game Features

- **Main Menu:** Navigate through the game's main menu.
- **Three-Lane Highway:** Drive along a road with three traffic lanes.
- **Player Movement:** Move the player's car between lanes.
- **Enemy Traffic:** Avoid incoming vehicles that appear in different lanes.
- **Collision Detection:** Colliding with enemy vehicles or obstacles ends the game.
- **Scoring System:** Earn points by successfully avoiding traffic.
- **Pause System:** Pause and resume gameplay.
- **Instructions Screen:** View the game instructions before playing.
- **Game Over Screen:** View your final score and play again.
- **Sound Effects:** Enjoy background music and sound effects during gameplay.

## 🎯 Controls

| Key | Action |
|---|---|
| `←` / `A` | Move Left |
| `→` / `D` | Move Right |
| `P` | Pause / Resume |
| `R` | Restart Game |
| `M` | Return to Main Menu |
| `S` | Start Game |
| `I` | Open Instructions |
| `B` | Go Back |
| `ESC` | Exit Game |

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Graphics Library:** SFML 3.0.0
- **IDE:** Microsoft Visual Studio 2022
- **Platform:** Windows
- **Architecture:** x64

## ⚙️ SFML Configuration (Visual Studio 2022)

This project uses **SFML 3.0.0**, which must be configured manually in Visual Studio before compiling the source code.

### 1. Download and Extract SFML

1. Download SFML 3.0.0 for Visual Studio (VC17), 64-bit.
2. Extract the downloaded folder to a location on your computer.
3. Locate the extracted SFML directory.

### 2. Configure Project Properties

Open the project in Visual Studio 2022.

Select **All Configurations** and **x64** in Project Properties.

Configure the following directories:

**C/C++ → General → Additional Include Directories**

Add the path to:

```
SFML-3.0.0/include
```

**Linker → General → Additional Library Directories**

Add the path to:

```text
SFML-3.0.0/lib
```

**Linker → Input → Additional Dependencies**

For Debug configuration, add:

```text
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib
sfml-audio-d.lib
```

For Release configuration, add:

```text
sfml-graphics.lib
sfml-window.lib
sfml-system.lib
sfml-audio.lib
```
Replace the directory paths with the actual location where SFML has been extracted on your computer.

### 3. Copy Required DLL Files

SFML requires runtime DLL files to execute the game.

1. Open the SFML `bin` folder.
2. Copy the required DLL files for the selected configuration.
3. Paste them into the executable's output directory.

For example:

```
ProjectFolder/x64/Debug/
```
For Release builds, use the corresponding Release DLLs.

### 4. Build and Run the Project

1. Open the `.sln` solution file in Visual Studio 2022.
2. Select the desired configuration (Debug or Release).
3. Select the x64 platform.
4. Ensure SFML is configured correctly.
5. Build the solution using **Build → Build Solution**.
6. Run the game using **Local Windows Debugger**.

**Note:** SFML 3.0.0 and its required runtime DLLs must be available for successful compilation and execution.
