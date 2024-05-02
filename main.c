#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 256
#define TRANS_SIZE 100

typedef struct Transaction
{
    int sender_id;
    int amount;
    int receiver_id;
    struct Transaction *leftChild;
    struct Transaction *rightChild;
} Transaction;

typedef struct Block
{
    Transaction *root;
    int nbTrans;
    char hashvalue[HASH_SIZE];
    struct Block *nextBlock;
} Block;

void separate();

int main()
{

    Transaction *tx2 = malloc(sizeof(Transaction));
    tx2->sender_id = 5;
    tx2->amount = 80;
    tx2->receiver_id = 9;
    tx2->leftChild = NULL;
    tx2->rightChild = NULL;

    Transaction *tx3 = malloc(sizeof(Transaction));
    tx3->sender_id = 2;
    tx3->amount = 90;
    tx3->receiver_id = 7;
    tx3->leftChild = NULL;
    tx3->rightChild = NULL;

    Transaction *tx1 = malloc(sizeof(Transaction));
    tx1->sender_id = 1;
    tx1->amount = 100;
    tx1->receiver_id = 3;
    tx1->leftChild = tx2;
    tx1->rightChild = tx3;

    printf("%d\n", tx1->amount);
    printf("%d\n", tx1->receiver_id);
    printf("%d\n", tx1->sender_id);
    printf("%x\n", tx1->rightChild);
    printf("%d\n", tx1->rightChild->amount);

    Block *block1 = malloc(sizeof(Block));

    block1->root = tx1;
    block1->nextBlock = NULL;

    separate();

    printf("%d\n", block1->root->amount);
    printf("%d\n", block1->root->sender_id);
    printf("%d\n", block1->root->receiver_id);

    return 0;
}

void separate()
{
    printf("\n#####################\n\n");
}