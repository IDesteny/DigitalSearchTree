#pragma once // Для предотвращения повторного включения
#include <windows.h>
#include <tchar.h>

typedef struct _NODE
{
	CHAR data; // Символ узла
	struct _NODE *next; // Указатель на следующий узел уровня
	struct _NODE *down; // Указатель на узел нижнего уровня

} NODE, *PNODE;

// "Защита" от несанкционированного доступа
typedef PVOID *DIGITAL_TREE;

// desc: Создание пустого дерева
// ret: Объект цифрового дерева

DIGITAL_TREE
DTCreate(
	VOID);

// desc: Добавление новой строки
// prm-1: Объект цифрового дерева
// prm-2: Строка
// prm-3: Длина строки
// prm-4: Уникальность (1 - Уникальное; 0 - Дубликат)
// ret: Статус отработки функции (0 - Success; 1 - Failure)

BOOL
DTInsert(
	DIGITAL_TREE dt,
	PCTSTR str,
	INT size,
	PBOOL uniq);

// desc: Поиск строки
// prm-1: Объект цифрового дерева
// prm-2: Строка
// prm-3: Длина строки
// prm-4: Результат поиска (1 - Строка найдена, 0 - Не найдена)
// ret: Статус отработки функции (0 - success; 1 - failure)

BOOL
DTFind(
	DIGITAL_TREE dt,
	PCTSTR str,
	INT size,
	PBOOL res);