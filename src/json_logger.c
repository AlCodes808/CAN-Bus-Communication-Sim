#include "json_logger.h"
#include <stdio.h>
#include <time.h>

static FILE* json_file = NULL;
static int frame_count = 0;

void JSON_Init(const char* filename) {
    json_file = fopen(filename, "w");
    if (json_file) {
        fprintf(json_file, "{\n");
        fprintf(json_file, "  \"frames\": [\n");
        fflush(json_file);
    }
}

void JSON_LogFrame(const CANFrame* frame, const char* ecu_name) {
    if (!json_file) return;
    
    if (frame_count > 0) {
        fprintf(json_file, ",\n");
    }
    
    fprintf(json_file, "    {\n");
    fprintf(json_file, "      \"id\": \"0x%03X\",\n", frame->id);
    fprintf(json_file, "      \"ecu\": \"%s\",\n", ecu_name);
    fprintf(json_file, "      \"dlc\": %d,\n", frame->dlc);
    fprintf(json_file, "      \"data\": [");
    
    for (int i = 0; i < frame->dlc; i++) {
        fprintf(json_file, "%d", frame->data[i]);
        if (i < frame->dlc - 1) fprintf(json_file, ", ");
    }
    
    fprintf(json_file, "],\n");
    fprintf(json_file, "      \"timestamp\": %u\n", frame->timestamp);
    fprintf(json_file, "    }");
    
    frame_count++;
    fflush(json_file);
}

void JSON_LogStats(const CANBus* bus, ECUNode ecus[], int ecu_count) {
    if (!json_file) return;
    
    fprintf(json_file, "\n  ],\n");
    fprintf(json_file, "  \"statistics\": {\n");
    fprintf(json_file, "    \"total_frames\": %u,\n", bus->stats.total_frames);
    fprintf(json_file, "    \"collisions\": %u,\n", bus->stats.collisions);
    fprintf(json_file, "    \"errors\": %u,\n", bus->stats.errors);
    fprintf(json_file, "    \"dropped_frames\": %u,\n", bus->stats.dropped_frames);
    fprintf(json_file, "    \"bus_active\": %s\n", bus->bus_active ? "true" : "false");
    fprintf(json_file, "  },\n");
    
    fprintf(json_file, "  \"ecus\": [\n");
    for (int i = 0; i < ecu_count; i++) {
        fprintf(json_file, "    {\n");
        fprintf(json_file, "      \"name\": \"%s\",\n", ecus[i].name);
        fprintf(json_file, "      \"frames_sent\": %u,\n", ecus[i].frames_sent);
        fprintf(json_file, "      \"frames_received\": %u,\n", ecus[i].frames_received);
        fprintf(json_file, "      \"active\": %s\n", ecus[i].active ? "true" : "false");
        fprintf(json_file, "    }");
        if (i < ecu_count - 1) fprintf(json_file, ",");
        fprintf(json_file, "\n");
    }
    fprintf(json_file, "  ]\n");
    fprintf(json_file, "}\n");
    
    fflush(json_file);
}

void JSON_Close(void) {
    if (json_file) {
        fclose(json_file);
        json_file = NULL;
    }
    frame_count = 0;
}