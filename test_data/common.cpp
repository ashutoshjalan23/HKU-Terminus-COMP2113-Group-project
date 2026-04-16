#include<iostream>
#include "common.h"
#include<string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;


void clearLine(){
    cout<<"\033[2K";
}

