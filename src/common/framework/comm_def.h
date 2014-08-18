/**
 *  @file   comm_def.h
 *  @brief   包含常用系统头文件,各服务间公共的常量、宏与数据结构定义
 *  @author   stanjiang
 *  @date   2014-08-11
*/

#ifndef _COMM_DEF_H_
#define _COMM_DEF_H_

#include <stdint.h>
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <assert.h>
#include <getopt.h>
#include <libgen.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <queue>


extern "C" 
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
};

typedef long long  int64_t;
typedef unsigned long long  uint64_t;
typedef unsigned int uint32_t;


#define ROUNDUP(n, width) (((n) + (width) - 1) & ~((width) - 1))

#define ROUNDDOWN(n, width) ((n) & ~(-width))

// UP(A/B) = int((A+B-1)/B)
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define UNUSE_ARG(arg) ((void)arg)

#endif // _COMM_DEF_H_

