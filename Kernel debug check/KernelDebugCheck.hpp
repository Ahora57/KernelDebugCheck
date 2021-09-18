#pragma once
#include "NtApiDef.h"

namespace KDCheck
{
	bool CheckHardwareBreakpoint()
	{
		/*
		Rootkits and Bootkits: Reversing Modern Malware and Next Generation Threats -> Festi botnet

		
		*/
		return __readdr(0) || __readdr(1) || __readdr(2) || __readdr(3);
	}

	DWORD DisableKernelDebug()
	{
		return NT_SUCCESS(KdDisableDebugger());
		
	// https://www.godeye.club/2021/06/03/002-mhyprot-insider-callbacks.html
		
	}

	bool HypDebugIsEnable()
	{
		//https://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/ex/sysinfo/hypervisor_query.htm


		SYSTEM_HYPERVISOR_QUERY_INFORMATION HypQueryInformathion{ -1 };
		ULONG retLenth = NULL;

		NtQuerySystemInformation(
			SystemHypervisorDetailInformation,
			&HypQueryInformathion,
			sizeof(SYSTEM_HYPERVISOR_QUERY_INFORMATION),
			&retLenth
		);

		return HypQueryInformathion.HypervisorDebuggingEnabled;
	}

	bool DebugModeIsEnable()
	{
		//https://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/ex/sysinfo/codeintegrity.htm
		


		SYSTEM_CODEINTEGRITY_INFORMATION sys_code_int_inform = { -1 };


		SYSTEM_CODEINTEGRITY_INFORMATION cInfo;
		cInfo.Length = sizeof(cInfo);//set size and it don't work without this

		NtQuerySystemInformation(
			SystemCodeIntegrityInformation,
			&cInfo,
			sizeof(cInfo),
			NULL
		);

		return cInfo.CodeIntegrityOptions & CODEINTEGRITY_OPTION_DEBUGMODE_ENABLED;
	}
	bool DebugFlagCheck()
	{
		SYSTEM_KERNEL_DEBUGGER_FLAGS flag_debugger{ 0 };

		NtQuerySystemInformation(
			SystemKernelDebuggerFlags,
			&flag_debugger,
			sizeof(flag_debugger),
			NULL
		);

		return flag_debugger.KernelDebuggerIgnoreUmExceptions;



	}

	bool KernelDebugEnable()
	{
		SYSTEM_KERNEL_DEBUGGER_INFORMATION kernel_debug_informathion{ -1 };
		NtQuerySystemInformation(
			SystemKernelDebuggerInformationEx,
			&kernel_debug_informathion,
			sizeof(kernel_debug_informathion),
			NULL
		);

		return
			kernel_debug_informathion.KernelDebuggerEnabled;

	}

	bool DebugTrigger()
	{

		/*
		https://pastebin.com/6kbt1Vka
		
		*/
		NTSTATUS status = ZwSystemDebugControl(SysDbgBreakPoint /* Anything but 0x1D */,
			0,
			0,
			0,
			0,
			0);

		return status != STATUS_DEBUGGER_INACTIVE;
	}
}