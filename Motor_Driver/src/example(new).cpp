#include <MotorUnion.h>
#include <MIT_MotorUnion.h>
#include <unistd.h>  /* UNIX standard function definitions */

#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>

vector<vector<float>> csv2cmds(string filename){
    fstream file;
    string line;
    vector<vector<float>> motion;

    file.open(filename);
    while (getline(file, line))  //讀檔讀到換行
        {
            vector<float> cmd;
            istringstream templine(line); // string 轉換成 stream
            string data;
            while (getline( templine, data,',')) //讀檔讀到逗號
            {

                float x = atof(data.c_str());
                cmd.push_back(x);  //string 轉換成數字
            }
            motion.push_back(cmd);
        }
    file.close();
    return motion;
}
vector<float> motor_bias = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    
                          // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    
                          // 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 

                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    
                          // 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 

                             0.588,  0,  -0.23,  -0.84,  -0.78,   0,  0,  0,  0,  0,    
                          // 30,     31,   32,      33,     34,    35, 36, 37, 38, 39,

                             0,  0,  0.44,  -0.1167,  0.456,  0,  0,  0,  0,  0,    
                          // 40, 41,   42,       43,     44, 45, 46, 47, 48, 49,    
};  

// --------------- main() ---------------
int main(int argc, char *argv[]){
    
    // ----- MotorUnion物件宣告處 ----- //
    
    // MIT_MotorUnion right_leg( { 32, 33, 34 } ); // 3  
    MIT_MotorUnion left_leg( { 42, 43, 44 } );  // 4

    // MIT_MotorUnion motor_driver({1}, "/dev/ttyUSB0"); // The port of motor is known
    // MIT_MotorUnion motor_driver({1}); // Auto find the port of motor
    // MotorUnion dynamixel_leg({31,35}, {"Pro100,Pro20"} ); // 5
    // MotorUnion dynamixel_leg({41}, {"Pro100"} ); // 5

    // ----- HT03基本設定 ----- //  
    // right_leg.GetModuleFirmwareVersion();    // Get firmware version
    // usleep(1000);
    left_leg.GetModuleFirmwareVersion();    // Get firmware version
    usleep(1000);

    // right_leg.SetMotor_TorqueEnable(right_leg.Get_MotorIndex(30), true);
    // usleep(1000);
    // right_leg.SetMotor_TorqueEnable(right_leg.Get_MotorIndex(32), true);
    // usleep(1000);
    // right_leg.SetMotor_TorqueEnable(right_leg.Get_MotorIndex(33), true);
    // // usleep(1000);
    // right_leg.SetMotor_TorqueEnable(right_leg.Get_MotorIndex(34), true);
    // usleep(1000);

    // left_leg.SetMotor_TorqueEnable(left_leg.Get_MotorIndex(40), true);
    // usleep(1000);
    left_leg.SetMotor_TorqueEnable(left_leg.Get_MotorIndex(42), true);
    usleep(1000);
    left_leg.SetMotor_TorqueEnable(left_leg.Get_MotorIndex(43), true);
    usleep(1000);
    left_leg.SetMotor_TorqueEnable(left_leg.Get_MotorIndex(44), true);
    usleep(1000);

    // ----- Dynamixel Motor基本設定 ----- //
    // dynamixel_leg.SetAllMotorsOperatingMode(3);
    // dynamixel_leg.SetAllMotorsTorqueEnable(true); 
    // usleep(5000);
    // SendParameter(index, mode, position, time, torque, kp, kd)
    // right_leg.SendParameter(right_leg.Get_MotorIndex(33), 0, -1.64, 5, 0, 100, 0.2);
    // usleep(1000);
    // dynamixel_leg.GetMotor_ID(0);
    // dynamixel_leg.SetMotor_Angle(0,0);
    // usleep(5000000);
    vector<vector<float>> motion = csv2cmds("0120_forward_cmd_Haitai_L.csv"); //0120_forward_cmd_Haitai_L
    
    for(int i=0; i<motion.size(); i++){
        switch( int(motion[i][0]) ){
            
            // case 3: // Right leg command(HT03)
            // {
            //     // SendParameter(index, mode, position(rads), time, torque, kp, kd)
            //     int id = motion[i][1];
            //     // cout << motion[i][3] << endl;
            //     right_leg.SendParameter(right_leg.Get_MotorIndex(id), 
            //                             motion[i][2],  // mode 0:到定點,1:連續動作
            //                             motion[i][3] + motor_bias[id],  // position(+-6.28 rads)
            //                             motion[i][4],  // time(sec)
            //                             motion[i][5],  // torque
            //                             motion[i][6],  // kp
            //                             motion[i][7]); // kd
            //     cout << id << motion[i][3] + motor_bias[id] << endl;
            //     break;
            // }

            case 4: // Left leg command(HT03)
            {
                int id = motion[i][1];
                left_leg.SendParameter(left_leg.Get_MotorIndex(id), 
                                        motion[i][2],  // mode 0:到定點,1:連續動作
                                        motion[i][3] + motor_bias[id],  // position(+-6.28 rads)
                                        motion[i][4],  // time(sec)
                                        motion[i][5],  // torque
                                        motion[i][6],  // kp
                                        motion[i][7]); // kd
                cout << id << motion[i][3] + motor_bias[id] << endl;
                break;
            }

            // case 5: // Leg dynamixel command
            // {
            //     // SetMotor_Angle(id,angle(+-180 degree));
            //     int id = motion[i][1];
            //     int idx;
            //     if( id== 31 ) idx =0;
            //     // else if (id==35) idx =1;
            //     {    dynamixel_leg.SetMotor_AngleandVelocity(idx, 
            //                                                 motion[i][2], 
            //                                                 motion[i][3]);
            //     }
            //     break;
            // }
            case 100: // Delay command
            {
                usleep(motion[i][1]/2);
                break;
            }
        }
        usleep(5000);
    }

    // printf("Generated encrypted packet: ");
    // for(int i = 0; i < 16; i++){
    //     printf("%x ", motor_driver.pre_cmd[i]);
    // }
    // printf("\r\n");
    return 0;
}
