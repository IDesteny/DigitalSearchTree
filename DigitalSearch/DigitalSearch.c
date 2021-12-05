#include "DigitalSearch.h"

DIGITAL_TREE
DTCreate(
	VOID)
{
	return calloc(1, sizeof(PNODE));
}

BOOL
DTInsert(
	DIGITAL_TREE dt,
	PCTSTR str,
	INT size,
	PBOOL uniq)
{
	PNODE rootTmp = *dt;
	INT i = 0; // Позиция в строке
	*uniq = FALSE;

	// Если дерево пустое
	if (!*dt)
	{
		*dt = calloc(1, sizeof(NODE));
		if (!*dt)
			return EXIT_FAILURE;

		*uniq = TRUE;
		(*(PNODE *)dt)->data = str[i++];
	}

	PNODE root = *dt;

	for (; i < size && rootTmp; ++i)
	{
		// Если данные узла совпадают с элементом строки
		if (rootTmp->data == str[i])
		{
			root = rootTmp;
			rootTmp = rootTmp->down; // На уровень ниже
		}
		else
		{
			// Проход по всему уровню
			while (rootTmp)
			{
				root = rootTmp;
				if (rootTmp->data == str[i])
				{
					rootTmp = rootTmp->down;
					break;
				}
				else if (!(rootTmp = rootTmp->next))
				{
					root->next = calloc(1, sizeof(NODE));
					if (!root->next)
						return EXIT_FAILURE;

					*uniq = TRUE;

					root = root->next;
					root->data = str[i];
				}
			}
		}
	}
	
	if (i >= size && root->down && (!root->down->next || root->down->next->data != INT_MAX))
	{
		root = root->down;
		rootTmp = root;

		while (rootTmp)
		{
			root = rootTmp;
			rootTmp = rootTmp->next;
		}

		root->next = calloc(1, sizeof(NODE));
		if (!root->next)
			return EXIT_FAILURE;

		root->next->data = INT_MAX;
		*uniq = TRUE;
	}

	for (; i < size; ++i)
	{
		root->down = calloc(1, sizeof(NODE));
		if (!root->down)
			return EXIT_FAILURE;

		root = root->down;
		root->data = str[i];

		if (!*uniq)
		{
			root->next = calloc(1, sizeof(NODE));
			if (!root->next)
				return EXIT_FAILURE;

			root->next->data = INT_MAX;
		}

		*uniq = TRUE;
	}

	return EXIT_SUCCESS;
}

BOOL
DTFind(
	DIGITAL_TREE dt,
	PCTSTR str,
	INT size,
	PBOOL res)
{
	PNODE root = *dt;
	*res = FALSE;

	for (INT i = 0; i < size; ++i)
	{
		if (!root)
			return EXIT_SUCCESS;

		if (root->data == str[i])
			root = root->down;
		else
		{
			while (TRUE)
			{
				if (root->data == str[i])
				{
					root = root->down;
					break;
				}
				else
				{
					root = root->next;
					if (!root)
						return EXIT_SUCCESS;
				}
			}
		}
	}

	if (root)
	{
		if (root->next && root->next->data == INT_MAX)
			*res = TRUE;
	}
	else
		*res = TRUE;

	return EXIT_SUCCESS;
}