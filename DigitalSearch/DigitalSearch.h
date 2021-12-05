#pragma once
#include <windows.h>
#include <tchar.h>

typedef struct _NODE
{
	INT data;
	struct _NODE *next;
	struct _NODE *down;

} NODE, *PNODE;

typedef PVOID *DIGITAL_TREE;

DIGITAL_TREE
DTCreate(
	VOID);

BOOL
DTInsert(
	DIGITAL_TREE dt,
	PINT data,
	INT size,
	PBOOL unique);

BOOL
DTFind(
	DIGITAL_TREE dt,
	PINT data,
	INT size,
	PBOOL res);