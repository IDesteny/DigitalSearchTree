#pragma once // ��� �������������� ���������� ���������
#include <windows.h>
#include <tchar.h>

typedef struct _NODE
{
	CHAR data; // ������ ����
	struct _NODE *next; // ��������� �� ��������� ���� ������
	struct _NODE *down; // ��������� �� ���� ������� ������

} NODE, *PNODE;

// "������" �� �������������������� �������
typedef PVOID *DIGITAL_TREE;

// desc: �������� ������� ������
// ret: ������ ��������� ������

DIGITAL_TREE
DTCreate(
	VOID);

// desc: ���������� ����� ������
// prm-1: ������ ��������� ������
// prm-2: ������
// prm-3: ����� ������
// prm-4: ������������ (1 - ����������; 0 - ��������)
// ret: ������ ��������� ������� (0 - Success; 1 - Failure)

BOOL
DTInsert(
	DIGITAL_TREE dt,
	PCTSTR str,
	INT size,
	PBOOL uniq);

// desc: ����� ������
// prm-1: ������ ��������� ������
// prm-2: ������
// prm-3: ����� ������
// prm-4: ��������� ������ (1 - ������ �������, 0 - �� �������)
// ret: ������ ��������� ������� (0 - success; 1 - failure)

BOOL
DTFind(
	DIGITAL_TREE dt,
	PCTSTR str,
	INT size,
	PBOOL res);