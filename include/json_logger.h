#ifndef JSON_LOGGER_H
#define JSON_LOGGER_H

#include "can_frame.h"
#include "can_bus.h"
#include "ecu_node.h"

void JSON_Init(const char* filename);
void JSON_LogFrame(const CANFrame* frame, const char* ecu_name);
void JSON_LogStats(const CANBus* bus, ECUNode ecus[], int ecu_count);
void JSON_Close(void);

#endif