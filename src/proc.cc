#include "proc-server/proc.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <iostream>

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#endif

namespace procserver {

#ifdef __linux__
void get_system_info(procserver::SystemInfo *systeminfo,
                      const char* sysInfoValues[], size_t sysInfoValuesLength) {
  struct sysinfo sys_info;
  if (sysinfo(&sys_info) != 0) {
    perror("sysinfo");
  }
  printf("Getting value for uptime...\n");
  systeminfo->set_uptime(sys_info.uptime);
  printf("%ld\n", sys_info.uptime);
  printf("Getting value for totalram...\n");
  systeminfo->set_totalram(sys_info.totalram);
  printf("%lu\n", sys_info.totalram);
}
#endif

#ifdef __APPLE__
void get_system_info(procserver::SystemInfo *systeminfo,
                      const char* sysInfoValues[], size_t sysInfoValuesLength) {
  for (size_t i = 0; i < sysInfoValuesLength; i++) {
    printf("Getting value for %s...\n", sysInfoValues[i]);

    size_t size;
    sysctlbyname(sysInfoValues[i], NULL, &size, NULL, 0);

    if (strcmp(sysInfoValues[i], "kern.boottime") == 0) {
        int64_t *buffer = reinterpret_cast<int64_t*>(malloc(size));
        sysctlbyname(sysInfoValues[i], buffer, &size, NULL, 0);
        time_t curr_time;
        time(&curr_time);
        printf("%lld\n", curr_time - *buffer);
        systeminfo->set_uptime(curr_time - *buffer);
        free(buffer);
    } else if (strcmp(sysInfoValues[i], "vm.loadavg") == 0) {
        struct loadavg *buffer = (struct loadavg*)malloc(size);
        sysctlbyname(sysInfoValues[i], buffer, &size, NULL, 0);
        printf("{%u %u %u}\n",
                buffer->ldavg[0], buffer->ldavg[1], buffer->ldavg[2]);
        free(buffer);
    } else {
        int64_t *buffer = reinterpret_cast<int64_t*>(malloc(size));
        sysctlbyname(sysInfoValues[i], buffer, &size, NULL, 0);
        printf("%lld\n", *buffer);
        systeminfo->set_totalram(*buffer);
        free(buffer);
    }
  }
}
#endif

}  // namespace procserver

#ifdef PDEBUG
int main() {
  const char* sysctlvalues[] = {"kern.boottime", "hw.memsize", "vm.loadavg"};
  procserver::get_system_info(sysctlvalues,
                              sizeof(sysctlvalues) / sizeof(sysctlvalues[0]));
}
#endif  // PDEBUG
