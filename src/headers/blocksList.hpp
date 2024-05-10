#pragma once
#include "block.hpp"
#include "renderWindow.hpp"
#include <fstream>
#include <sys/stat.h>

#include "enums.hpp"
using namespace std;

struct Node
{
    Block *block;
    struct Node *next;
    struct Node *prev;
    struct Node *nextType;
    struct Node *prevType;
    struct Node *nextColor;
    struct Node *prevColor;
    Node() : next(nullptr), prev(nullptr), nextType(nullptr), prevType(nullptr), nextColor(nullptr), prevColor(nullptr) {}
    ~Node();
};

class BlocksList
{
private:
    Node *head;
    Node *tail;
    int size;
    int score;
    bool shifted;
    int maxSize;

public:
    BlocksList();
    ~BlocksList();
    void insert(Block *block);
    void insertAtHead(Block *block);
    int getSize();
    Node *getHead();
    Node *getTail();
    void shift(ShiftType type, Block block);
    void setmaxSize(int size);
    int getmaxSize();
    void render(RenderWindow *window);
    void deleteList();
    void checkForMatches(Insertion insertion);
    void deleteMatch(Insertion insertion);
    bool checkColors(Insertion insertion);
    bool checkTypes(Insertion insertion);
    void deleteNode(Node *node);
    void checkForMatches();
    void reassignBlocks();
    Node *getprevType(Node *node);
    Node *getNextType(Node *node);
    Node *getprevColor(Node *node);
    Node *getNextColor(Node *node);
    void assignNextPrevColor(Node *node);
    void assignNextPrevType(Node *node);
    void deleteMatch(Node *node);
    bool checkColorsByNode(Node *node);
    bool checkTypesByNode(Node *node);
    Node *getFirstColor(BlockColor color);
    Node *getFirstType(BlockType type);
    void reassignTypesAndColors();
    void increaseScore(bool useShift);
    int getScore();
    void setScore(int score);
    void saveList(const std::string &filename);
    void loadList(const std::string &filename);
    void SaveLoadHighscore();
    void reset();
};
