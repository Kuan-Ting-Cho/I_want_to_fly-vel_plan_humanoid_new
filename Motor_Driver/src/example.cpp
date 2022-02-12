#include <MotorUnion.h>
#include <unistd.h> /* UNIX standard function definitions */
#include <termio.h>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    MotorUnion motor_driver1({0, 2, 4, 6}, {"Mx28", "Mx28", "Mx28", "Mx28"}); //Mx106 Vmax 210  //Mx28  Vmax 230

    while (1)
    {
        cout << "-------------Press  SpeedMode( 1~3 ) && Command key( w(Go), s(Back), a(Left), d(Right) ,k(Keep moving) ) ----------------"
             << endl;

        int speed_mode = motor_driver1.scanKeyboard();
        int speed;
        int key;
        int time;

        switch (speed_mode)
        {
        case 49:
            speed = 77;
            key = motor_driver1.scanKeyboard();
            break;
        case 50:
            speed = 154;
            key = motor_driver1.scanKeyboard();
            break;
        case 51:
            speed = 230;
            key = motor_driver1.scanKeyboard();
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
            motor_driver1.KeepMoving(speed, key);
            break;
        case 100:
            motor_driver1.TurnRight(speed, key);
            break;
        case 97:
            motor_driver1.TurnLeft(speed, key);
            break;
        case 119:
            motor_driver1.GoStraight(speed, key);
            break;
        case 115:
            motor_driver1.GoBack(speed, key);
            break;
        default:
            cout << endl
                 << "No this direction." << endl;
            break;
        }
    }

    // motor_driver.Sync_Drive(0, 6, 210, 2);

    // motor_driver.Drive(0, 210, 2);
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
