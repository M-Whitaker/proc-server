#ifndef INCLUDE_PROC_SERVER_PROC_H_
#define INCLUDE_PROC_SERVER_PROC_H_

#include "proc-server/server.h"

#ifdef __linux__
#include <sys/sysinfo.h>
#include <errno.h>
#endif


#ifdef __linux__
#define SYS_UPTIME "uptime"
#define SYS_RAMSIZE "totalram"
#define SYS_LOADAVG "loads"
#endif

#ifdef __APPLE__
#define SYS_UPTIME "kern.boottime"
#define SYS_RAMSIZE "hw.memsize"
#define SYS_LOADAVG "vm.loadavg"
#endif

namespace procserver {

void get_system_info(procserver::SystemInfo *systeminfo,
                      const char* sysInfoValues[], size_t sysInfoValuesLength);

}  // namespace procserver

#endif  // INCLUDE_PROC_SERVER_PROC_H_
