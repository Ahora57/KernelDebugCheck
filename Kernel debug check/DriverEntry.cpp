#include  "KernelDebugCheck.hpp"


VOID OnDriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);

	DbgPrint("[BAD BOB] Driver unload!\n");
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	if (!pDriverObject)
		return STATUS_FAILED_DRIVER_ENTRY;

	DbgPrint("[BAD BOB] Check hardware Breakpoint ->\t 0x%p", KDCheck::CheckHardwareBreakpoint());
	DbgPrint("[BAD BOB] Hypervisor debugger enable  ->\t 0x%p", KDCheck::HypDebugIsEnable());
	DbgPrint("[BAD BOB] Running under debug mode ->\t 0x%p", KDCheck::DebugModeIsEnable());
	DbgPrint("[BAD BOB] Debug mode informathion ->\t 0x%p", KDCheck::KernelDebugEnable());
	DbgPrint("[BAD BOB] Trigger debugger ->\t 0x%p", KDCheck::DebugTrigger());
	DbgPrint("[BAD BOB] Debug flag ->\t 0x%p", KDCheck::DebugFlagCheck());
	DbgPrint("[BAD BOB] STATUS disable kernel debugger ->\t 0x%p", KDCheck::DisableKernelDebug());

	pDriverObject->DriverUnload = &OnDriverUnload;
	return STATUS_SUCCESS;
}