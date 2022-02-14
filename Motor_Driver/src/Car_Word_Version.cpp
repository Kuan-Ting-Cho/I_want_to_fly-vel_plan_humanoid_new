#include <iostream>
#include <unistd.h> /* UNIX standard function definitions */
#include <termio.h>
#include <stdio.h>
#include <fstream>
using namespace std;
int *ConvertToASCII(string s)
{
    int a;
    int *array = new int[s.length()];
    for (int i = 0; i < s.length(); i++)
    {
        a = s[i];
        array[i] = a;
    }
    return array;
}
int scanKeyboard()
{

    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(STDIN_FILENO, &stored_settings); //获得stdin 输入
    new_settings = stored_settings;            //
    new_settings.c_lflag &= (~ICANON);         //
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(STDIN_FILENO, &stored_settings); //获得stdin 输入
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings); //

    in = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &stored_settings);
    return in;
}

int main(int argc, char *argv[])
{
    int Previous_Line = 0;
    int Current_Line = 0;
    //int No_Line = 0;
    int Stop_Key = 0;
    string Line = "QQ";
    string Last_Line = "No any command.";
    ifstream test;

    while (Previous_Line == Current_Line)
    {
        test.open("test.txt");
        while (Previous_Line == Current_Line)
        {
            while (test.peek() != EOF)
            {
                getline(test, Last_Line);
                Current_Line++;
            }
            if (Current_Line == 0) //if no command in test.txt
            {
                Current_Line++;
            }
        }
        cout << endl
             << "Current_Line: " << Current_Line << " lines." << endl;
        cout << "Last_Line is: '" << Last_Line << "'" << endl;

        test.close();
        int *Command = ConvertToASCII(Last_Line);
        cout << "Last_Line ASCII is: '" << Command[0] << "' '" << Command[1] << "'" << endl;

        if (Command[0] == 112 && Stop_Key == 0)
        {
            cout << endl
                 << "Stop." << endl;
            sleep(5);
            Stop_Key = 1;
        }
        else if (Last_Line != Line)
        {
            cout << "-------------Press  SpeedMode( 1~3 ) && Command key( w(Go), s(Back), a(Left), d(Right) ,k(Keep moving) ) ----------------"
                 << endl;
            Stop_Key = 0;
            int speed_mode = Command[0];
            int speed;
            int key;
            int time;

            switch (speed_mode)
            {
            case 49:
                speed = 77;
                key = Command[1];
                break;
            case 50:
                speed = 154;
                key = Command[1];
                break;
            case 51:
                speed = 230;
                key = Command[1];
                break;
            default:
                speed = 0;
                key = 0;
                cout << endl
                     << "No this mode." << endl;
                break;
            }

            switch (key)
            {
            case 0:
                break;
            case 107:
                cout << endl
                     << "keepmoving." << endl;
                sleep(5);
                break;
            case 100:
                cout << endl
                     << "turnright." << endl;
                sleep(5);
                break;
            case 97:
                cout << endl
                     << "turnleft." << endl;
                sleep(5);
                break;
            case 119:
                cout << endl
                     << "gostraight" << endl;
                sleep(5);
                break;
            case 115:
                cout << endl
                     << "goback" << endl;
                sleep(5);
                break;
            default:
                cout << endl
                     << "No this direction." << endl;
                break;
            }
        }
        delete[] Command;
        Line = Last_Line;
        Previous_Line = Current_Line = 0;
    }
}
