void AddObject(Stack *stack, Object object)
{
    ObjectPile *newPile = malloc(sizeof(ObjectPile));
    object.rect = (SDL_Rect){stack->x + 10, stack->y + 5 + 10*stack->quantity, 30, 10};
    stack->quantity++;
    newPile->object = &object;
    newPile->next = stack->head;
    stack->head = newPile;
}

Object* creat_Object(char Name[50])
{
    Object *object = malloc(sizeof(Object));
    object->ID = 0;
    strcpy(object->Name, Name);
    return object;
}

