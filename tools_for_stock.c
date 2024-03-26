int nbObjects = 0;

Bool addObject(Stack *stack, Object *object) {
    ObjectPile *newPile = malloc(sizeof(ObjectPile));

    int StackTopMargin = STACKHEIGHT * 0.05;
    int ObjectMargin = 20;
    int ObjectWidth = 80;
    int ObjectHeight = 30;
    int StackInLineMargin = (STACKWIDTH - (ObjectWidth + ObjectMargin) * 3 + ObjectMargin) / 2;

    int X = ((ObjectHeight + ObjectMargin) * stack->quantity);
    X = X / STACKHEIGHT;
    int pX = X * (ObjectWidth + ObjectMargin) + StackInLineMargin + stack->x;

    if (pX > (STACKWIDTH) + stack->x) {
        printf("coucou\n");
        return FALSE;
    }

    int Y = (ObjectHeight + ObjectMargin) * stack->quantity;
    Y = Y % STACKHEIGHT;
    Y = Y / (ObjectHeight + ObjectMargin);
    int pY = Y * (ObjectHeight + ObjectMargin) + StackTopMargin + stack->y;

    object->rect = (SDL_Rect) {pX, pY, ObjectWidth, ObjectHeight};

    stack->quantity++;
    newPile->object = object;
    newPile->next = stack->head;
    stack->head = newPile;

    return TRUE;
}

Object *creat_Object(char Name[50]) {
    Object *object = malloc(sizeof(Object));
    object->ID = nbObjects;
    nbObjects++;
    strcpy(object->Name, Name);
    object->r = 0;
    object->g = 0;
    object->b = 0;
    object->a = 255;
    for (int i = 0; i < (sizeof(color) / sizeof(color[0])); ++i) {
        if (strcmp(Name, color[i].text) == 0) {
            object->r = color[i].r;
            object->g = color[i].g;
            object->b = color[i].b;
            object->a = color[i].a;
        }
    }
    return object;
}

Bool popFirst(Stack *stack)
{
    if (stack->head == NULL)
        return FALSE;
    ObjectPile *newList = stack->head;
    newList = newList->next;
    free(stack->head);
    stack->head = newList;
    return TRUE;
}

int deleteObject(Stack stacks[], int ID) {
    Bool found = FALSE;
    Stack *stackModified = NULL;
    for (int i = 0; i < 6; i++) {
        if (found)
            break;
        ObjectPile *pile = stacks[i].head;
        ObjectPile *prev = NULL;
        while (stacks[i].head != NULL) {
            if (stacks[i].head->object->ID == ID) {
                if (prev == NULL) {
                    stacks[i].head = stacks[i].head->next;
                } else {
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
    while (stackModified->head != NULL) {

        int StackTopMargin = STACKHEIGHT * 0.05;
        int ObjectMargin = 20;
        int ObjectWidth = 80;
        int ObjectHeight = 30;
        int StackInLineMargin = (STACKWIDTH - (ObjectWidth + ObjectMargin) * 3 + ObjectMargin) / 2;

        int X = ((ObjectHeight + ObjectMargin) * quantity);
        X = X / STACKHEIGHT;
        int pX = X * (ObjectWidth + ObjectMargin) + StackInLineMargin + stackModified->x;

        if (pX > (STACKWIDTH - StackInLineMargin * 2) + stackModified->x) {
            return FALSE;
        }

        int Y = (ObjectHeight + ObjectMargin) * quantity;
        Y = Y % STACKHEIGHT;
        Y = Y / (ObjectHeight + ObjectMargin);
        int pY = Y * (ObjectHeight + ObjectMargin) + StackTopMargin + stackModified->y;

        stackModified->head->object->rect = (SDL_Rect) {pX,
                                                        pY, ObjectWidth, ObjectHeight};
        quantity++;
        stackModified->head = stackModified->head->next;
    }
    stackModified->head = pile;
    return 0;
}

int countObject(Stack stack[], char Name[50]) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        ObjectPile *pile = stack[i].head;
        while (stack[i].head != NULL) {
            if (strcmp(stack[i].head->object->Name, Name) == 0) {
                count++;
            }
            stack[i].head = stack[i].head->next;
        }
        stack[i].head = pile;
    }
    return count;
}

void creatText(Manager *manager, char text[1024], int indexColor, int quantity) {

    Text *newText = malloc(sizeof(Text));
    newText->next = manager->head;
    manager->head = newText;
    strcpy(newText->text, text);
    newText->quantity = quantity;
    newText->indexColor = indexColor;

    newText->surface_text = TTF_RenderText_Solid(manager->font, newText->text,
                                                 (SDL_Color) {color[indexColor].r, color[indexColor].g,
                                                              color[indexColor].b});
    newText->texture_text = SDL_CreateTextureFromSurface(manager->renderer, newText->surface_text);

    newText->renderQuad = (SDL_Rect) {manager->x + 20, manager->y + 50 + (manager->quantity * 25),
                                      newText->surface_text->w, 25};

    manager->quantity++;
}

void count(Manager *manager, Stack stack[], char name[]) {
    int count = countObject(stack, name);
    char text[1024];
    snprintf(text, sizeof(text), "%s : %d", name, count);

    int indexColor = 0;

    for (int i = 0; i < (sizeof(color) / sizeof(color[0])); ++i) {
        if (strcmp(name, color[i].text) == 0) {
            indexColor = i;
        }
    }
    creatText(manager, text, indexColor, count);
}

void sortManagerByLetter(Manager *manager, Text **head_ref) {
    Text *sorted = NULL;
    Text *current = *head_ref;
    while (current != NULL) {
        Text *next = current->next;
        Text **trail = &sorted;

        while (*trail != NULL && strcmp((*trail)->text, current->text) < 0) {
            trail = &((*trail)->next);
        }

        current->next = *trail;
        *trail = current;

        current = next;
    }

    *head_ref = sorted;

    Text *temp = *head_ref;
    int quantity = 0;
    while (temp != NULL) {
        temp->surface_text = TTF_RenderText_Solid(manager->font, temp->text,
                                                  (SDL_Color) {color[temp->indexColor].r, color[temp->indexColor].g,
                                                               color[temp->indexColor].b});
        temp->texture_text = SDL_CreateTextureFromSurface(manager->renderer, temp->surface_text);

        temp->renderQuad = (SDL_Rect) {manager->x + 20, manager->y + 50 + (quantity * 25),
                                       temp->surface_text->w, 25};
        quantity++;
        temp = temp->next;
    }
}

void sortManagerByQuantity(Manager *manager, Text **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Text *sorted = NULL;

    Text *current = *head;
    while (current != NULL) {
        Text *next = current->next;

        if (sorted == NULL || sorted->quantity >= current->quantity) {
            current->next = sorted;
            sorted = current;
        } else {
            Text *temp = sorted;
            while (temp->next != NULL && temp->next->quantity < current->quantity) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;

    Text *temp = *head;
    int quantity = 0;
    while (temp != NULL) {
        temp->surface_text = TTF_RenderText_Solid(manager->font, temp->text,
                                                  (SDL_Color) {color[temp->indexColor].r, color[temp->indexColor].g,
                                                               color[temp->indexColor].b});
        temp->texture_text = SDL_CreateTextureFromSurface(manager->renderer, temp->surface_text);

        temp->renderQuad = (SDL_Rect) {manager->x + 20, manager->y + 50 + (quantity * 25),
                                       temp->surface_text->w, 25};
        quantity++;
        temp = temp->next;
    }
}