#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 65
#define TRANS_SIZE 100

typedef struct Transaction
{
    char *peer1;
    char *data;
    char *peer2;
    struct Transaction *leftChild;
    struct Transaction *rightChild;
} Transaction;

typedef struct Block
{
    struct Transaction *root;
    int nbTrans;
    char *prevBlockHash;    //[HASH_SIZE];
    char *currentBlockHash; //[HASH_SIZE];
    struct Block *nextBlock;
} Block;

void separate();

void compute_block_hash(Block *block);
void hashchainBlockData(Block *block);

int main()
{

    Transaction *tx2 = malloc(sizeof(Transaction));
    tx2->peer1 = "5";
    tx2->data = "80";
    tx2->peer2 = "9";
    tx2->leftChild = NULL;
    tx2->rightChild = NULL;

    Transaction *tx3 = malloc(sizeof(Transaction));
    tx3->peer1 = "2";
    tx3->data = "90";
    tx3->peer2 = "7";
    tx3->leftChild = NULL;
    tx3->rightChild = NULL;

    Transaction *tx1 = malloc(sizeof(Transaction));
    tx1->peer1 = "1";
    tx1->data = "34";
    tx1->peer2 = "3";
    tx1->leftChild = tx2;
    tx1->rightChild = tx3;

    printf("%s\n", tx1->data);
    printf("%s\n", tx1->peer2);
    printf("%s\n", tx1->peer1);
    printf("%x\n", tx1->rightChild);
    printf("%d\n", tx1->rightChild->data);

    Block *block1 = malloc(sizeof(Block));

    block1->root = tx1;
    block1->nbTrans = 3;
    block1->nextBlock = NULL;

    separate();

    printf("%s\n", block1->root->data);
    printf("%s\n", block1->root->peer1);
    printf("%s\n", block1->root->peer2);

    // compute_block_hash(&block1);

    // separate();

    // printf("%d\n", block1->currentBlockHash);

    // separate();

    // printf("%d\n", block1->nextBlock->root->data);
    // printf("%d\n", block1->nextBlock->root->peer1);
    // printf("%d\n", block1->nextBlock->root->peer2);

    // char *x = chainBlockData(&block1);
    // printf("%s", x);

    hashchainBlockData(block1);

    Block *block2 = malloc(sizeof(Block));

    block2->root = tx1;
    block2->nbTrans = 3;
    block2->nextBlock = NULL;

    block2->prevBlockHash = block1->currentBlockHash; // TODO: This needs to be hashed

    block1->nextBlock = block2;

    // printf("\n%s\n", block1->currentBlockHash[1]);

    return 0;
}

void separate()
{
    printf("\n#####################\n\n");
}

void hashchainBlockData(Block *block)
{
    // Allocate memory for concatenated string
    size_t total_length = 0;

    total_length += strlen(block->root->data) + strlen(block->root->peer1) + strlen(block->root->peer2);
    total_length += strlen(block->root->rightChild->data) + strlen(block->root->rightChild->peer1) + strlen(block->root->rightChild->peer2);
    total_length += strlen(block->root->rightChild->data) + strlen(block->root->rightChild->peer1) + strlen(block->root->rightChild->peer2);

    char *concatenated_data = (char *)malloc((total_length + 1) * sizeof(char));

    // Concatenate data fields
    concatenated_data[0] = '\0'; // Ensure the string is initially empty
    strcat(concatenated_data, block->root->data);
    strcat(concatenated_data, block->root->peer1);
    strcat(concatenated_data, block->root->peer2);
    strcat(concatenated_data, block->root->leftChild->data);
    strcat(concatenated_data, block->root->leftChild->peer1);
    strcat(concatenated_data, block->root->leftChild->peer2);
    strcat(concatenated_data, block->root->rightChild->data);
    strcat(concatenated_data, block->root->rightChild->peer1);
    strcat(concatenated_data, block->root->rightChild->peer2);

    block->currentBlockHash = concatenated_data;

    printf("Concatenated Transaction Data: %s\n", concatenated_data);

    //! Hash the data
}

// Function to compute the hash value of a block
void compute_block_hash(Block *block)
{

    int block_size = 1000;
    // Concatenate block contents to compute hash
    char *block_data;
    block_data = chainBlockData(block);

    // // Compute SHA-256 hash
    // unsigned char hash[HASH_SIZE];

    // SHA256(block_data, sizeof(block_data), hash);

    // // Convert hash to string representation
    // for (int i = 0; i < HASH_SIZE; i++)
    // {
    //     sprintf(&block->currentBlockHash[i * 2], "%02x", hash[i]);
    // }

    // block->currentBlockHash[HASH_SIZE - 1] = '\0'; // Null-terminate the string

    block->currentBlockHash = block_data;
}
