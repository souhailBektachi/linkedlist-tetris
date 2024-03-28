#pragma once
#include "block.hpp"
#include "renderWindow.hpp"
#include "enums.hpp"

struct Node
{
    Block *block;
    struct Node *next;
    struct Node *prev;
    Node() : next(nullptr), prev(nullptr) {}
};

class BlocksList
{
private:
    Node *head;
    Node *tail;
    int size;
    void changePos();
    int maxSize;

public:
    BlocksList();
    ~BlocksList();
    void insert(Block *block);
    void insertAtHead(Block *block);
    int getSize();
    Node *getHead();
    Node *getTail();
    void shift();
    void setmaxSize(int size);
    int getmaxSize();
    void render(RenderWindow *window);
    void deleteList();
    void checkForMatches(Insertion insertion);
    void deleteMatch(Insertion insertion);
};