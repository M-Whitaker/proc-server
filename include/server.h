#ifndef SERVER_H
#define SERVER_H

#include "../protofiles/build/systeminfo.pb.h"

namespace procserver {

void SetSystemInfoDetails(procserver::SystemInfo *systeminfo);

} // namespace procserver

#endif // SERVER_H
