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

	//��ȡ��ǰ���̵�EPROCESS
	pCurPro = PsGetCurrentProcess();
	pPrevPro = pCurPro;
	do
	{
		//��ȡEPROCESS�Ľ�����
		pImageFileName = (PCHAR)pCurPro + 0x16C;
		//�Ƿ���Ҫ���صĽ���
		if (strcmp(pImageFileName, "CCCMaple.exe") == 0)
		{
			
			//�Խ��̽��ж�������
			pListEntry = (PLIST_ENTRY)((ULONG)pCurPro + 0xB8);
			pListEntry->Blink->Flink = pListEntry->Flink;
			pListEntry->Flink->Blink = pListEntry->Blink;
			DbgPrint("����%s���سɹ�\r\n", pImageFileName);
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
	//����ж�غ���
	
	driver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}
