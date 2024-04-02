#include "blocksList.hpp"

BlocksList::BlocksList()
{
    head = nullptr;
    tail = nullptr;
    destroyedBlocks = nullptr;
    size = 0;
}
BlocksList::~BlocksList()
{
    Node *current = head;
    while (current != tail)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    delete tail;
}
void BlocksList::insert(Block *block)
{
    Node *newNode = new Node;
    newNode->block = block;
    if (!head)
    {
        head = tail = newNode;
        head->prev = tail->next = tail->prev = head->next = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
    checkForMatches(Tail);
}
void BlocksList::insertAtHead(Block *block)
{
    Node *newNode = new Node;
    newNode->block = block;

    if (!head)
    {
        head = tail = newNode;
        head->prev = tail->next = tail->prev = head->next = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        tail->next = newNode;

        newNode->prev = tail;
        head = newNode;
    }
    size++;
    checkForMatches(Head);
}
int BlocksList::getSize()
{
    return size;
}

Node *BlocksList::getHead()
{
    return head;
}
Node *BlocksList::getTail()
{
    return tail;
}
void BlocksList::shift()
{
    if (head == nullptr)
    {
        return;
    }
    head = tail;
    tail = tail->prev;

    changePos();
}
void BlocksList::changePos()
{
    Node *current = head;
    Vector2D temp;
    Vector2D headPos = head->block->getPosition();
    do
    {
        temp = current->next->block->getPosition();
        current->block->setPosition({temp.getX(), temp.getY()});
        current = current->next;
    } while (current != tail);
    tail->block->setPosition({headPos.getX(), headPos.getY()});
}
void BlocksList::checkForMatches(Insertion insertion)
{
    if (size < NUMTOMATCH)
    {
        return;
    }
    int j = 1;
    switch (insertion)
    {
    case Head:
        if (checkColors(insertion) || checkTypes(insertion))
        {
            deleteMatch(Head);
            Block::decreaseMax(left);
        }

        break;
    case Tail:

        if (checkColors(insertion) || checkTypes(insertion))
        {
            deleteMatch(Tail);
            Block::decreaseMax(right);
        }
        break;
    }
    if (head == nullptr)
    {
        Block::resetMax();
    }
}
void BlocksList::render(RenderWindow *window)
{
    if (head == nullptr)
    {
        return;
    }
    Node *current = head;
    do
    {
        if (current == nullptr)
        {
            return;
        }
        current->block->render(window);
        current = current->next;
    } while (current != head);
}
int BlocksList::getmaxSize()
{
    return maxSize;
}
void BlocksList::setmaxSize(int size)
{
    maxSize = size;
}
void BlocksList::deleteList()
{
    if (head == nullptr)
    {
        return;
    }
    Node *current = head;
    while (current != tail)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    delete tail;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool BlocksList::checkColors(Insertion insertion)
{
    Node *current;
    switch (insertion)
    {
    case Head:

        current = head;
        break;
    case Tail:
        current = tail;
        break;
    default:
        break;
    }
    for (int i = 0; i < NUMTOMATCH - 1; i++)
    {
        switch (insertion)
        {
        case Head:
            if (current->block->getColor() != current->next->block->getColor())
            {
                return false;
            }
            current = current->next;

            break;
        case Tail:
            if (current->block->getColor() != current->prev->block->getColor())
            {

                return false;
            }
            current = current->prev;

            break;

        default:
            break;
        }
    }
    return true;
}
bool BlocksList::checkTypes(Insertion insertion)
{
    Node *current;
    switch (insertion)
    {
    case Head:

        current = head;
        break;
    case Tail:
        current = tail;
        break;
    default:
        break;
    }
    for (int i = 0; i < NUMTOMATCH - 1; i++)
    {
        switch (insertion)
        {
        case Head:
            if (current->block->getType() != current->next->block->getType())
            {
                return false;
            }
            current = current->next;

            break;
        case Tail:
            if (current->block->getType() != current->prev->block->getType())
            {

                return false;
            }
            current = current->prev;

            break;

        default:
            break;
        }
    }
    return true;
}

void BlocksList::deleteMatch(Insertion insertion)
{
    switch (insertion)
    {
    case Head:
        for (int i = 0; i < NUMTOMATCH; i++)
        {
            Node *temp = head;

            head = head->next;
            head->prev = tail;
            tail->next = head;
            if (temp == tail)
            {
                head = nullptr;
                tail = nullptr;
            }
            delete temp;
            size--;
        }
        break;
    case Tail:
        for (int i = 0; i < NUMTOMATCH; i++)
        {
            Node *temp = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            if (temp == head)
            {
                head = nullptr;
                tail = nullptr;
            }
            delete temp;
            size--;
        }
        break;
    }
}
