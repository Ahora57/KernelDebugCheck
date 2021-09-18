#pragma once
#include "Struct.h"

EXTERN_C NTSTATUS NtQuerySystemInformation(
    SYSTEM_INFORMATION_CLASS SystemInformationClass,
    PVOID                    SystemInformation,
    ULONG                    SystemInformationLength,
    PULONG                   ReturnLength
);

EXTERN_C NTSTATUS NTAPI ZwSystemDebugControl(unsigned long ControlCode,
    void* InputBuffer,
    unsigned long InputBufferLength,
    void* OutputBuffer,
    unsigned long OutputBufferLength,
    unsigned long* pResultLength);
