#ifndef INCLUDE_PROC_SERVER_SERVER_H_
#define INCLUDE_PROC_SERVER_SERVER_H_

#include "../protofiles/build/systeminfo.pb.h"

namespace procserver {

void SetSystemInfoDetails(procserver::SystemInfo *systeminfo);

}  // namespace procserver

#endif  // INCLUDE_PROC_SERVER_SERVER_H_
