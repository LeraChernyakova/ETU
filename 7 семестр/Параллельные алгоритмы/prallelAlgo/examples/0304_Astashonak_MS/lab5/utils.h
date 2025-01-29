//
// Created by mikeasta on 01/12/23.
//
#pragma once

#include <iostream>
#include <string>
#include <CL/cl.h>
#include <sstream>

// Custom std::to_string() realization
template<typename T>
std::string to_string(T value) {
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

// Log message
void log(const std::string& message) {
    std::cout << message << std::endl;
}

// Log device info
void log_device_info(cl_device_id device_lo_log) {
    log("Device Stats:");

    // Get device name
    char device_name[128];
    clGetDeviceInfo(device_lo_log, CL_DEVICE_NAME, 128, &device_name, nullptr);
    log("Name: " + to_string(device_name));

    // Get device type
    cl_device_type device_type;
    clGetDeviceInfo(device_lo_log, CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, nullptr);

    switch (device_type) {
        case CL_DEVICE_TYPE_CPU: log("Type: CPU"); break;
        case CL_DEVICE_TYPE_GPU: log("Type: GPU"); break;
        default: log("Type: Unknown"); break;
    }
}
