int nbObjects = 0;

Bool addObject(Stack *stack, Object object)
{
    ObjectPile *newPile = malloc(sizeof(ObjectPile));

    int StackTopMargin = STACKHEIGHT * 0.05;
    int ObjectMargin = 20;
    int ObjectWidth = 100;
    int ObjectHeight = 30;
    int StackInLineMargin =(STACKWIDTH - (ObjectWidth + ObjectMargin) * 3 + ObjectMargin) / 2;

    int X = ((ObjectHeight + ObjectMargin) * stack->quantity);
    X = X / STACKHEIGHT;
    int pX = X * (ObjectWidth + ObjectMargin) + StackInLineMargin + stack->x;

    if (pX > (STACKWIDTH - StackInLineMargin*2) + stack->x)
    {
        return FALSE;
    }

    int Y = (ObjectHeight + ObjectMargin) * stack->quantity;
    Y = Y % STACKHEIGHT;
    Y = Y / (ObjectHeight + ObjectMargin);
    int pY = Y * (ObjectHeight + ObjectMargin) + StackTopMargin + stack->y;

    object.rect = (SDL_Rect){pX, pY, ObjectWidth, ObjectHeight};

    stack->quantity++;
    newPile->object = &object;
    newPile->next = stack->head;
    stack->head = newPile;

    return TRUE;
}

Object *creat_Object(char Name[50])
{
    Object *object = malloc(sizeof(Object));
    object->ID = nbObjects;
    nbObjects++;
    strcpy(object->Name, Name);
    return object;
}

int deleteObjectFromStack(Stack *stack, int ID)
{
    Bool found = FALSE;
    ObjectPile *pile = stack->head;
    ObjectPile *prev = NULL;
    Stack *stackModified = NULL;
    while (stack->head != NULL)
    {
        if (stack->head->object->ID == ID)
        {
            if (prev == NULL)
            {
                stack->head = stack->head->next;
            }
            else
            {
                prev->next = stack->head->next;
            }
            free(stack->head);
            found = TRUE;
        }
        prev = stack->head;
        stack->head = stack->head->next;
        if (found)
            break;
    }
    stack->head = pile;
    if (!found)
        return 1;

    ObjectPile *pile2 = stack->head;
    int quantity = 0;
    while (stack->head != NULL)
    {
        if (quantity < 5)
        {
            stack->head->object->rect = (SDL_Rect){stack->x + 80, stack->y + 20 + (40 * quantity), 100, 30};
        }
        else
        {
            stack->head->object->rect = (SDL_Rect){stack->x + 200, stack->y + 20 + (40 * (quantity - 5)), 100, 30};
        }
        
        quantity++;
        stack->head = stack->head->next;
    }
    stack->head = pile;

    return 0;
}

int deleteObject(Stack stacks[], int ID)
{
    Bool found = FALSE;
    Stack *stackModified = NULL;
    for (int i = 0; i < 6; i++)
    {
        if (found)
            break;
        ObjectPile *pile = stacks[i].head;
        ObjectPile *prev = NULL;
        while (stacks[i].head != NULL)
        {
            if (stacks[i].head->object->ID == ID)
            {
                if (prev == NULL)
                {
                    stacks[i].head = stacks[i].head->next;
                }
                else
                {
                    prev->next = stacks[i].head->next;
                }
                free(stacks[i].head);
                found = TRUE;
                stackModified = &stacks[i];
            }
            prev = stacks[i].head;
            stacks[i].head = stacks[i].head->next;
            if (found)
                break;
        }
        stacks[i].head = pile;
    }

    if (!found)
        return 1;

    ObjectPile *pile = stackModified->head;
    int quantity = 0;
    while (stackModified->head != NULL)
    {
        if (quantity < 5)
        {
            stackModified->head->object->rect = (SDL_Rect){stackModified->x + 80, stackModified->y + 20 + (40 * quantity), 100, 30};
        }
        else
        {
            stackModified->head->object->rect = (SDL_Rect){stackModified->x + 200, stackModified->y + 20 + (40 * (quantity - 5)), 100, 30};
        }
        
        quantity++;
        stackModified->head = stackModified->head->next;
    }
    stackModified->head = pile;
    return 0;
}
