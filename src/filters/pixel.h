#pragma once
#include "maxtree.h"

struct pixel;

typedef struct pixel Pixel;

struct pixel
{
    int index;
    int value;
    Node* node;
    Pixel* prev;
    Pixel* _next;
};
