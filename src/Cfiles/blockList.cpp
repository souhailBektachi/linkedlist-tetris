#include "blocksList.hpp"
Node::~Node()
{
}
BlocksList::BlocksList()
{
    Block::resetMax();

    head = nullptr;
    tail = nullptr;

    size = 0;
    score = 0;
    shifted = false;
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
        head->nextType = head->prevType = head->nextColor = head->prevColor = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        tail->next = newNode;
        newNode->prev = tail;

        tail = newNode;
        assignNextPrevColor(tail);
        assignNextPrevType(tail);
    }
    size++;
    checkForMatches(Insertion::Tail);
}

void BlocksList::insertAtHead(Block *block)
{
    Node *newNode = new Node;
    newNode->block = block;

    if (!head)
    {
        head = tail = newNode;
        head->prev = tail->next = tail->prev = head->next = newNode;
        head->nextType = head->prevType = head->nextColor = head->prevColor = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        tail->next = newNode;

        newNode->prev = tail;
        head = newNode;
        assignNextPrevColor(head);
        assignNextPrevType(head);
    }
    size++;
    checkForMatches(Insertion::Head);
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

void BlocksList::deleteNode(Node *node)
{
    Node *temp = node;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    if (node == head)
    {
        head = head->next;
    }
    if (node == tail)
    {
        tail = tail->prev;
    }
    if (node == head && node == tail)
    {
        head = nullptr;
        tail = nullptr;
    }
    delete temp;

    size--;
}

void BlocksList::reassignBlocks()
{
    if (head == nullptr)
    {
        return;
    }
    Node *current = head;
    int j = POSINIT - ((size / 2) * 32);
    int i = 0;
    do
    {
        current->block->setPosition({float(j), current->block->getPosition().getY()});
        i++;
        j += 32;
        current = current->next;
    } while (current != head);
    Block::max[0] = head->block->getPosition().getX() - 32;
    Block::max[1] = tail->block->getPosition().getX() + 32;
}
Node *BlocksList::getprevType(Node *node)
{
    Node *current = node->prev;
    do
    {
        if (current->block->getType() == node->block->getType())
        {
            return current;
        }
        current = current->prev;
    } while (current != node);

    return node;
}
Node *BlocksList::getNextType(Node *node)
{
    Node *current = node->next;
    do
    {
        if (current->block->getType() == node->block->getType())
        {
            return current;
        }
        current = current->next;
    } while (current != node);
    return node;
}
Node *BlocksList::getprevColor(Node *node)
{
    Node *current = node->prev;
    do
    {
        if (current->block->getColor() == node->block->getColor())
        {
            return current;
        }
        current = current->prev;
    } while (current != node);

    return node;
}
Node *BlocksList::getNextColor(Node *node)
{
    Node *current = node->next;
    do
    {
        if (current->block->getColor() == node->block->getColor())
        {
            return current;
        }
        current = current->next;
    } while (current != node);
    return node;
}
void BlocksList::assignNextPrevColor(Node *node)
{
    node->prevColor = getprevColor(node);
    node->nextColor = getNextColor(node);
    if (node->prevColor != node)
    {
        node->prevColor->nextColor = node;
    }
    if (node->nextColor != node)
    {
        node->nextColor->prevColor = node;
    }
}
void BlocksList::assignNextPrevType(Node *node)
{
    node->prevType = getprevType(node);
    node->nextType = getNextType(node);
    if (node->prevType != node)
    {
        node->prevType->nextType = node;
    }
    if (node->nextType != node)
    {
        node->nextType->prevType = node;
    }
}
void BlocksList::setmaxSize(int size)
{
    maxSize = size;
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
        current->block->render(window);
        current = current->next;
    } while (current != head);
}
void BlocksList::deleteList()
{
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
int BlocksList::getmaxSize()
{
    return maxSize;
}

bool BlocksList::checkColors(Insertion insertion)
{
    Node *current;
    switch (insertion)
    {
    case Insertion::Head:
        current = head;
        for (int i = 0; i < NUMTOMATCH - 1; i++)
        {
            if (current->block->getColor() != current->next->block->getColor())
            {
                return false;
            }
            current = current->next;
        }
        return true;
        break;
    case Insertion::Tail:
        current = tail;
        for (int i = 0; i < NUMTOMATCH - 1; i++)
        {
            if (current->block->getColor() != current->prev->block->getColor())
            {
                return false;
            }
            current = current->prev;
        }
        return true;
        break;
    }
    return false;
}
bool BlocksList::checkTypes(Insertion insertion)
{
    Node *current;
    switch (insertion)
    {
    case Insertion::Head:
        current = head;
        for (int i = 0; i < NUMTOMATCH - 1; i++)
        {
            if (current->block->getType() != current->next->block->getType())
            {
                return false;
            }
            current = current->next;
        }
        return true;
        break;
    case Insertion::Tail:
        current = tail;
        for (int i = 0; i < NUMTOMATCH - 1; i++)
        {
            if (current->block->getType() != current->prev->block->getType())
            {
                return false;
            }
            current = current->prev;
        }
        return true;
        break;
    }
    return false;
}
void BlocksList::checkForMatches(Insertion insertion)
{
    if (size < NUMTOMATCH)
    {
        return;
    }
    switch (insertion)
    {
    case Insertion::Head:
        if (checkColors(insertion) || checkTypes(insertion))
        {
            deleteMatch(insertion);
        }
        break;
    case Insertion::Tail:
        if (checkColors(insertion) || checkTypes(insertion))
        {
            deleteMatch(insertion);
        }
        break;
    }
}
void BlocksList::deleteMatch(Insertion insertion)
{
    Node *current;
    Node *temp;
    switch (insertion)
    {
    case Insertion::Head:
        current = head;
        for (int i = 0; i < NUMTOMATCH; i++)
        {
            temp = current->next;
            deleteNode(current);
            current = temp;
        }

        Block::decreaseMax(Inserted::left);
        increaseScore(false);
        reassignTypesAndColors();
        break;
    case Insertion::Tail:
        current = tail;
        for (int i = 0; i < NUMTOMATCH; i++)
        {
            temp = current->prev;
            deleteNode(current);
            current = temp;
        }

        Block::decreaseMax(Inserted::right);
        increaseScore(false);
        reassignTypesAndColors();
        break;
    }
    reassignBlocks();
}
void BlocksList::checkForMatches()
{
    if (size < NUMTOMATCH)
    {
        return;
    }
    Node *current = head;
    do
    {
        if (checkColorsByNode(current) || checkTypesByNode(current))
        {
            deleteMatch(current);
            reassignBlocks();
            current = head;
        }
        current = current->next;

    } while (current != head);
}
void BlocksList::deleteMatch(Node *node)
{

    Node *current = node;
    Node *temp;
    for (int i = 0; i < NUMTOMATCH; i++)
    {
        temp = current->next;
        deleteNode(current);
        current = temp;
    }
    increaseScore(true);
    reassignTypesAndColors();
}
bool BlocksList::checkColorsByNode(Node *node)
{
    Node *current = node;
    for (int i = 0; i < NUMTOMATCH - 1; i++)
    {
        if (current->block->getColor() != current->next->block->getColor())
        {
            return false;
        }
        current = current->next;
    }
    return true;
}
bool BlocksList::checkTypesByNode(Node *node)
{
    Node *current = node;
    for (int i = 0; i < NUMTOMATCH - 1; i++)
    {
        if (current->block->getType() != current->next->block->getType())
        {
            return false;
        }
        current = current->next;
    }
    return true;
}
Node *BlocksList::getFirstColor(BlockColor color)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    Node *current = head;
    do
    {
        if (current->block->getColor() == color)
        {
            return current;
        }
        current = current->next;
    } while (current != head);
    return nullptr;
}
Node *BlocksList::getFirstType(BlockType type)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node *current = head;
    do
    {
        if (current->block->getType() == type)
        {
            return current;
        }
        current = current->next;
    } while (current != head);
    return nullptr;
}
void BlocksList::shift(ShiftType type, Block block)
{
    Node *current;
    Node *ini;
    BlockColor color = block.getColor();
    BlockType blockType = block.getType();
    BlockColor lastColor;
    BlockType lastType;
    switch (type)
    {
    case ShiftType::Type:

        ini = getFirstType(blockType);
        if (ini == nullptr)
        {
            return;
        }
        current = ini;
        lastType = ini->block->getType();
        lastColor = ini->block->getColor();
        do
        {
            current->block->changeColorType(current->nextType->block->getColor(), current->nextType->block->getType());
            current = current->nextType;

        } while (current != ini->prevType);
        ini->prevType->block->changeColorType(lastColor, lastType);
        break;
    case ShiftType::Color:
        ini = getFirstColor(color);
        if (ini == nullptr)
        {
            return;
        }
        current = ini;
        lastType = ini->block->getType();
        lastColor = ini->block->getColor();
        do
        {
            current->block->changeColorType(current->nextColor->block->getColor(), current->nextColor->block->getType());
            current = current->nextColor;

        } while (current != ini->prevColor);
        ini->prevColor->block->changeColorType(lastColor, lastType);
        break;
    }
    shifted = true;
    reassignTypesAndColors();

    checkForMatches();
}
void BlocksList::reassignTypesAndColors()
{
    if (head == nullptr)
    {
        return;
    }
    Node *current = head;
    do
    {
        assignNextPrevColor(current);
        assignNextPrevType(current);
        current = current->next;
    } while (current != head);
}
void BlocksList::increaseScore(bool useShift)
{
    if (head == nullptr)
    {
        return;
    }
    if (useShift || shifted)
    {
        score += 2;
        shifted = false;
    }
    else
    {
        score += 1;
    }
}
int BlocksList::getScore()
{
    return score;
}
void BlocksList::setScore(int score)
{
    this->score = score;
}

void BlocksList::saveList(const std::string &filename)
{
    if (head == nullptr)
    {
        std::cerr << "No blocks to save." << std::endl;
        return;
    }
    std::string filePath = "saves/" + filename;
    std::ofstream file(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
    if (file.is_open())
    {
        // Write score to file
        file.write(reinterpret_cast<const char *>(&score), sizeof(int));
        // Write state variables to file
        Node *current = head;
        do
        {
            BlockColor color = current->block->getColor();
            BlockType type = current->block->getType();
            file.write(reinterpret_cast<const char *>(&color), sizeof(BlockColor));
            file.write(reinterpret_cast<const char *>(&type), sizeof(BlockType));
            current = current->next;
        } while (current != head);
        file.close();
        std::cout << "BlocksList state saved successfully." << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

void BlocksList::loadList(const std::string &filename)
{
    Block::resetMax();
    std::string filePath = "saves/" + filename;
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        reset();

        file.read(reinterpret_cast<char *>(&score), sizeof(int));
        while (!file.eof())
        {
            BlockType type;
            BlockColor color;
            file.read(reinterpret_cast<char *>(&color), sizeof(BlockColor));
            file.read(reinterpret_cast<char *>(&type), sizeof(BlockType));
            Block *block = new Block(type, color, POSINIT, -32, 16, 16, nullptr);
            block->getTexture(type, color);
            block->move(RIGHT);
            insert(block);
        }
        file.close();
        std::cout << "BlocksList state loaded successfully." << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for reading." << std::endl;
    }
}
void BlocksList::reset()
{
    deleteList();
    score = 0;
    Block::resetMax();
    shifted = false;
}