#include <MotorUnion.h>
#include <unistd.h>  /* UNIX standard function definitions */

using namespace std;
const int & Set_Velocity(MotorUnion& motor, int id, int mode, bool enable, int velocity );
const int Sync_Drive(MotorUnion& motor, int drive1_id, int drive2_id, int velocity, int  time);   //Synchronous drive
const int Drive(MotorUnion& motor, int drive1, int velocity, int  time); 
int  Leg_id( int id);                                                                                                                                                           //turn id into index




int main(int argc, char *argv[]){

MotorUnion motor_driver({0,6},{"Mx28","Mx28"});
   
Sync_Drive(motor_driver, 0, 6, 200, 2);

Drive(motor_driver, 0, 200, 2);
    
}
















const int &  Set_Velocity(MotorUnion& motor, int id, int mode, bool enable, int velocity){
    motor.SetAllMotorsOperatingMode(1);         //need to set mode on wizard 2.0 !!!!!!!!!!!!!!!!!!!!!!!!!!

     usleep(1000);
 
    motor.SetMotor_TorqueEnable(id, enable) ;
     usleep(1000);

    motor.SetMotor_Velocity(id,  velocity);
 
    usleep(1000);

     return motor.GetMotor_Velocity(id);
}

const int Sync_Drive(MotorUnion& motor, int driver1_id, int driver2_id, int velocity, int  time){

cout << "driver1 velocity is: "<< Set_Velocity(motor, Leg_id( driver1_id),1, 1, velocity )<<endl;
cout << "driver2 velocity is: "<<Set_Velocity(motor,Leg_id(driver2_id),1, 1,velocity)<<endl;
sleep(time);  
cout <<"driver1 velocity is: "<< Set_Velocity(motor, Leg_id( driver1_id),1, 1, 0)<<endl;
cout <<"driver2 velocity is: "<< Set_Velocity(motor,Leg_id( driver2_id),1, 1, 0)<<endl;
sleep(1);
motor.SetMotor_TorqueEnable(Leg_id( driver1_id),false ) ;
motor.SetMotor_TorqueEnable(Leg_id( driver2_id),false ) ;
}

const int Drive(MotorUnion& motor, int driver1_id, int velocity, int  time){

cout << "driver1 velocity is: "<< Set_Velocity(motor, Leg_id( driver1_id),1, 1, velocity )<<endl;
sleep(time); 
cout << "driver1 velocity is: "<< Set_Velocity(motor, Leg_id( driver1_id),1, 1, 0)<<endl;
sleep(1);
motor.SetMotor_TorqueEnable(Leg_id( driver1_id),false ) ;
}

int   Leg_id( int id){

    const int arr[]={0,6};
    const int n = sizeof(arr)/sizeof(arr[0]);
     int i = 0;
    while (i < n)
    {
        if (arr[i] == id) {
            id=i;
            return id;
            break;
        }
        i++;
    }
}

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

