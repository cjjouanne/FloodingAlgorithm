#pragma once
#include <stdbool.h>
#include "../imagelib/image.h"

struct pixel;

typedef struct pixel Pixel;

struct node;

typedef struct  node Node;

struct node
{
    int pixel_count;
    int threshold;

    /*Nodo padre correspondiente al árbol*/
    Node* parent;

    Pixel* p_head;
    Pixel* p_tail;

    /*Nodo cabeza y cola correspondiente a la lista ligada-nodos hijos*/
    Node* head;
    Node* tail;

    Node* prev;
    Node* _next;
};

struct pixel
{
    int index;
    int value;
    Node* node;
    Pixel* prev;
    Pixel* _next;
    bool rn;
    bool ln;
    bool bn;
    bool tn;
};

struct charlie;

typedef struct charlie Charlie;

struct charlie
{
    Node* root;
    Pixel** pixels;
};


Charlie* init_tree(Image* image, int threshold);
void init_leaf(Node* node, int width, int pixel_count, Charlie* charlie);
void add_to_neighborhood(Pixel* pixel, Node* node, int width, int pixel_count, Charlie* charlie);
void add_pixel(Node* root, int index, int value, Pixel** pixels, int width, int pixel_count);
void add_pixel2(Node* node, Pixel* pixel);
int get_smallest(Node* node);
Pixel* get_first(Node* node);
void destroy_leaf(Node* node);
void destroy_charlie(Charlie* charlie, int count);
void update_pixels(Node* node, int value);
void recursive_area(Node* node, int a, int g, int threshold);
void recursive_delta(Node* node, float D, int parent_pixel_count);
void save_image(Image* image, Charlie* charlie);
