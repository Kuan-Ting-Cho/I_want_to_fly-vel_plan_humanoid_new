#include <termio.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;
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

int *ControlButton()
{
  int *array = new int[2];
  array[0] = scanKeyboard();
  array[1] = scanKeyboard();
  return array;
}
// int* ControlButton()
//{
// int* array = new int[2];
// array[0] = scanKeyboard();
// cin >> array[1] ;
// return array;
//}
//
//
/*int main(int argc, char *argv[]) {
    

  while(1){
    int* arr=ControlButton();
    printf("\n%d\n",*arr);
    printf("%d\n",*(arr+1));
    delete[] arr;
  }
   
}*/

//ios::in | ios::out | ios::app |
int *convertToASCII(string s)
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

int main(int argc, char *argv[])
{
  int Previous_Line = 0;
  int Current_Line = 0;
  //string Line;
  string Last_Line;
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
    }
    cout << "Current_Line: " << Current_Line << " lines." << endl;
    cout << "Last_Line is: '" << Last_Line << "'" << endl;

    test.close();
    int *arr = convertToASCII(Last_Line);
    cout << "Last_Line ASCII is: '" << arr[0] << "' '" << arr[1] << "'" << endl;
    delete[] arr;
    Previous_Line = Current_Line = 0;
  }

  //test << "stackexchnange" << endl;
  return 0;
}
