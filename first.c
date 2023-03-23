#include <ntddk.h>
#include <stdlib.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path);

#pragma alloc_text(INIT, DriverEntry)

UNICODE_STRING randstr(unsigned int len) {
	UNICODE_STRING processName;
	//srand();
	int i;
	//str[++i] = '\0';
	return;
}
VOID HideProcess()
{
	PEPROCESS pCurPro = NULL, pPrevPro = NULL;
	PCHAR pImageFileName = NULL;
	PLIST_ENTRY pListEntry = NULL;

	//获取当前进程的EPROCESS
	pCurPro = PsGetCurrentProcess();
	pPrevPro = pCurPro;
	do
	{
		//获取EPROCESS的进程名
		pImageFileName = (PCHAR)pCurPro + 0x16C;
		//是否是要隐藏的进程
		if (strcmp(pImageFileName, "CCCMaple.exe") == 0)
		{
			
			//对进程进行断链操作
			pListEntry = (PLIST_ENTRY)((ULONG)pCurPro + 0xB8);
			pListEntry->Blink->Flink = pListEntry->Flink;
			pListEntry->Flink->Blink = pListEntry->Blink;
			DbgPrint("进程%s隐藏成功\r\n", pImageFileName);
		}
		pCurPro = (PEPROCESS)(*(PULONG)((ULONG)pCurPro + 0xB8) - 0xB8);
	} while (pCurPro != pPrevPro);
}

VOID DriverUnload(PDRIVER_OBJECT driver) {
	DbgPrint("first: Our driver is unloading...\r\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path) {
	DbgBreakPoint();
	DbgPrint("first: Hello, my salary!\r\n");
	//设置卸载函数
	
	driver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}
