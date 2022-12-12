#ifndef IS_NODE

#include "Secret.h"
#include <Keyboard.h>

void slash()
{
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('7');
    Keyboard.releaseAll();
}

void colon()
{
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('.');
    Keyboard.releaseAll();
}

void quote()
{
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('2');
    Keyboard.releaseAll();
}

void inputNIP()
{
    Keyboard.write(' ');
    delay(1000);
    Keyboard.print(Secret::NIP);
    Keyboard.write(KEY_RETURN);
}

void inputPath(String path)
{

    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '/' || path[i] == '\\')
            slash();
        else if (path[i] == ':')
            colon();
        else if (path[i] == '"')
            quote();
        else
            Keyboard.print(path[i]);
    }
}

void runPython()
{
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(1000);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.print("cmd");
    Keyboard.write(KEY_RETURN);
    delay(1000);
    inputPath("python3 \"C:/Users/Esteban/Documents/Proyectos/RemoteDesktop/RemoteDesktop.py\" & exit");
    Keyboard.write(KEY_RETURN);
}

#endif