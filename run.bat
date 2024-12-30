@echo off

:: Compile the C++ code
g++ poll.cpp -o poll.exe

:: Check if the compilation was successful
if %errorlevel% equ 0 (
    echo Compilation successful. Running the program...
    :: Run the compiled program
    poll.exe
) else (
    echo Compilation failed. Please check the C++ code for errors.
)
