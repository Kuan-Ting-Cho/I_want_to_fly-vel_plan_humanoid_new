#include <MotorUnion.h>
#include <unistd.h> /* UNIX standard function definitions */
#include <stdio.h>
#include <fstream>
using namespace std;
// int *ConvertToASCII(string s)
// {
//     int a;
//     int *array = new int[s.length()];
//     for (int i = 0; i < s.length(); i++)
//     {
//         a = s[i];
//         array[i] = a;
//     }
//     return array;
// }

int main(int argc, char *argv[])
{
    MotorUnion motor_driver1({0, 2, 4, 6}, {"Mx28", "Mx28", "Mx28", "Mx28"}); //Mx106 Vmax 210  //Mx28  Vmax 230
    int Previous_Line = 0;                                                    //initialize
    int Current_Line = 0;                                                     //initialize
    int Stop_Key = 0;                                                         //initialize
    string Line = "QQ";                                                       //initialize
    string Last_Line = "No any command.";                                     //initialize
    ifstream test;
    while (Previous_Line == Current_Line)
    {
        test.open("/home/potter/I_want_to_fly-vel_plan_humanoid_new/Motor_Driver/src/test.txt");
        while (Previous_Line == Current_Line)
        {
            while (test.peek() != EOF)
            {
                getline(test, Last_Line); //find Last_Line
                Current_Line++;
            }
            if (Current_Line == 0) //if no command in test.txt
            {
                Current_Line++;
            }
        }
        // cout << endl
        //      << "Current_Line: " << Current_Line << " lines." << endl;
        // cout << "Last_Line is: '" << Last_Line << "'" << endl;

        test.close();
        int *Command = motor_driver1.ConvertToASCII(Last_Line);
        // cout << "Last_Line ASCII is: '" << Command[0] << "' '" << Command[1] << "'" << endl;

        if (Command[0] == 112 && Stop_Key == 0) //Press 'p' && Have yet to stop
        {
            motor_driver1.Stop();
            Stop_Key = 1; //Car is stop
        }
        else if (Last_Line != Line)
        {
            cout << "-------------------------------------" << endl;
            Stop_Key = 0; //Car will move
            int speed_mode = Command[0];
            int speed;
            int Angle;
            int key;
            int time;

            switch (speed_mode)
            {
            case 99:
                speed = 210;
                Angle = Command[1];
                motor_driver1.Change_angle(Angle, speed);
                key = 0;
                break;
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
                cout << "No this mode." << endl;
                break;
            }

            switch (key)
            {
            case 0:
                break;
            case 100:
                motor_driver1.TurnRight(speed);
                break;
            case 97:
                motor_driver1.TurnLeft(speed);
                break;
            case 119:
                motor_driver1.GoStraight(speed);
                break;
            case 115:
                motor_driver1.GoBack(speed);
                break;
            default:
                cout << "No this direction." << endl;
                break;
            }
        }
        delete[] Command;
        Line = Last_Line;                 //record Line = Last_Line
        Previous_Line = Current_Line = 0; //reset to initial
    }
}
// int *ControlButton()
// {
//     int *array = new int[2];
//     array[0] = scanKeyboard();
//     array[1] = scanKeyboard();
//     //printf("%d\n",array);
//     return array;
// }

//////////////////code using MotorUnion.h/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// MotorUnion motor_driver({0,6},{"Mx28","Mx28"});
//  motor_driver.SetAllMotorsOperatingMode(1);         //need to set mode on wizard 2.0 !!!!!!!!!!!!!!!!!!!!!!!!!!
//  usleep(1000);

// motor_driver.SetMotor_TorqueEnable(0, true) ;
//  usleep(1000);
// motor_driver.SetMotor_TorqueEnable(1, true) ;
//  usleep(1000);
// motor_driver.SetMotor_Velocity(0,  200);
// usleep(5000);
// motor_driver.SetMotor_Velocity(1,  200);
// sleep(2);
//  motor_driver.SetMotor_Velocity(0, 0);
//  usleep(5000);
// motor_driver.SetMotor_Velocity(1, 0);
// sleep(3);
// motor_driver.SetMotor_TorqueEnable(0,false ) ;
// motor_driver.SetMotor_TorqueEnable(1,false ) ;
