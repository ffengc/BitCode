
#pragma once

#include <iostream>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <cassert>
#include <string>
#include "Log.hpp"
#include <unistd.h>


//这些都可以随便写，只要保证我们这个路径是可以有访问权限的就行了
#define PATH_NAME "/home/yufc"
#define PROJ_ID 0x66
#define SHM_SIZE 4096 //共享内存的大小，最好是页（PAGE: 4096）的整数倍
