/*
ICS 2301: Design and Analysis of Algorithms Assignment 1

Kepha Weru          SCT221-0218/2022
Keith Kihara        SCT221-0217/2022
Stephen Githua      SCT221-0668/2022

You are required to write a program in C programming language that compress texts data without
loosing the data. The program prompt a user to type some texts and it outputs the sizes of the
entered texts before and after compression. Use Huffman coding algorithm for text compression.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct Node **array;
};

struct Node* newNode(char data, unsigned freq) {
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node*) malloc(minHeap->capacity * sizeof(struct Node));
    return minHeap;
}

void swapNode(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct Node* extractMin(struct MinHeap* minHeap) {
    struct Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct Node* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(struct Node* root) {
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArray(arr, top);
    }
}

void calculateFrequency(char str[], int freq[]) {
    for (int i = 0; i < strlen(str); i++) {
        freq[str[i]]++;
    }
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct Node* root = buildHuffmanTree(data, freq, size);

    int arr[100], top = 0;
    printCodes(root, arr, top);
}

int main() {
    char str[100];
    printf("Enter some text: ");
    gets(str);

    int freq[256] = {0};
    calculateFrequency(str, freq);

    char data[256];
    int dataFreq[256], index = 0;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[index] = (char) i;
            dataFreq[index] = freq[i];
            index++;
        }
    }

    printf("Original size: %ld bytes\n", strlen(str) * sizeof(char));
    HuffmanCodes(data, dataFreq, index);
    printf("Compressed size: %d bytes\n", index * sizeof(char));

    return 0;
}
