#pragma once
#include <stdbool.h>
#include "../imagelib/image.h"

struct pixel;

typedef struct pixel Pixel;

struct node;

typedef struct  node Node;

struct node
{
    int id;
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
};

struct charlie;

typedef struct charlie Charlie;

struct charlie
{
    Node* root;
    Pixel** pixels;
    int node_count;
};


Charlie* init_tree(Image* image, int threshold);
void init_leaf(Node* node, int width, int pixel_count, Charlie* charlie);
void add_to_neighborhood(Pixel* pixel, Node* node, int width, int pixel_count, Charlie* charlie);
void add_pixel(Node* root, int index, int value, Pixel** pixels);
void add_pixel2(Node* node, Pixel* pixel);
int get_smallest(Node* node);
bool node_ready(Node* node);
Pixel* get_first(Node* node);
void destroy_leaf(Node* node);
void destroy_charlie(Charlie* charlie, int count);
void recursive_inform(Node* node, int depth);
int count_pixels(Node* node);
int count_recursive(Node* node);
void update_pixels(Node* node, int value);
void area_filter(Node* node, int a, int g);
void delta_filter(Node* node, float D, int parent_pixel_count, int node_pixel_count);
void recursive_area(Node* node, int a, int g);
void recursive_delta(Node* node, float D, int parent_pixel_count, int node_pixel_count);
void save_image(Image* image, Charlie* charlie);
