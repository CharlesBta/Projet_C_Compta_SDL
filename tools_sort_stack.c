typedef struct element
{
    int indexStack;
    char name[50];
} element;

int indexStackToSort(element *sortedElements, char *name, int *indexFreeStack, int indexMainStack) {
    int index = -1;
    for(int i = 0; i < 5; i++)
    {
        if (strcmp(sortedElements[i].name, name) == 0)
        {
            index = sortedElements[i].indexStack;
            break;
        }
    }
    if (index == -1)
    {
        for(int i = 0; i < 5; i++)
        {
            if (sortedElements[i].indexStack == -1)
            {
                sortedElements[i].indexStack = *indexFreeStack;
                strcpy(sortedElements[i].name, name);
                index = sortedElements[i].indexStack;

                if (*indexFreeStack + 1 == indexMainStack)
                {
                    if(*indexFreeStack + 2 > 5)
                    {
                        printf("crash (3)\n");
                        return -1;
                    }
                    else
                    {
                        *indexFreeStack = *indexFreeStack + 2;
                    }
                }
                else
                {
                    if(*indexFreeStack + 1 > 5)
                    {
                        printf("crash (4)\n");
                        return -1;
                    }
                    else
                    {
                        *indexFreeStack = *indexFreeStack + 1;
                    }
                }
                break;
            }
        }
    }
    return index;
}


void *sort(arg *args) {
    Stack *stacks = args->stacks;
    int indexMainStack = args->indexMainStack;

    int firstIndexFreeStack = 0;
    if (indexMainStack == 0){
        firstIndexFreeStack = 1;
    }
    element sortedElements[5] = {{-1},{-1},{-1},{-1},{-1}};
    Stack mainStack = stacks[indexMainStack];
    for (ObjectPile *mainPile = mainStack.head; mainPile != NULL; mainPile = mainPile->next)
    {
        int index = indexStackToSort(sortedElements, mainPile->object->Name, &firstIndexFreeStack, indexMainStack);
        if (index > -1)
        {
            if (addObject(&stacks[index], mainPile->object) == FALSE)
            {
                printf("crash (1)\n");
                return NULL;
            }else
            {
                mainStack.quantity--;
                ObjectPile *newList = mainStack.head;
                newList = newList->next;
                mainStack.head = NULL;
                mainStack.head = newList;
            }
        }
        SDL_Delay(100);
    }
    for (int i = 0; i < 5; ++i) {
        if (sortedElements[i].indexStack != -1)
        {
            for (ObjectPile *pile = stacks[sortedElements[i].indexStack].head; pile != NULL; pile = pile->next)
            {
                if (addObject(&mainStack, pile->object) == FALSE)
                {
                    printf("crash (2)\n");
                    return NULL;
                }
                SDL_Delay(100);
            }
        }
    }
}
