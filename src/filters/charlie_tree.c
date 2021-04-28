#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "charlie_tree.h"

Charlie* init_tree(Image* image, int threshold)
{
    Charlie* charlie = malloc(sizeof(Charlie));
    Node* root = malloc(sizeof(Node));
    charlie -> root = root;
    charlie -> pixels = malloc((image -> pixel_count) * sizeof(Pixel*));
    root -> threshold = threshold;
    root -> parent = NULL;
    root -> p_head = NULL;
    root -> p_tail = NULL;
    root -> head = NULL;
    root -> tail = NULL;
    root -> prev = NULL;
    root -> _next = NULL;
    root -> pixel_count = image -> pixel_count;
    for (int i = 0; i < image -> pixel_count; i++)
    {
        add_pixel(root, i, image -> pixels[i], charlie -> pixels, image->width, image->pixel_count);
    }
    init_leaf(root, image -> width, image -> pixel_count, charlie);
    return charlie;
}

void init_leaf(Node* node, int width, int pixel_count, Charlie* charlie)
{
    node -> threshold = get_smallest(node);
    Pixel* first = get_first(node);
    while (first)
    {
        Node* leaf = malloc(sizeof(Node));
        leaf -> parent = node;
        leaf -> threshold = node -> threshold + 1;
        leaf -> p_head = NULL;
        leaf -> p_tail = NULL;
        leaf -> head = NULL;
        leaf -> tail = NULL;
        leaf -> prev = NULL;
        leaf -> _next = NULL;
        leaf -> pixel_count = 0;

        if (node -> head == NULL)
        {
            node -> head = leaf;
        } else {
            node -> tail -> _next = leaf;
            leaf -> prev = node -> tail;
        }
        node -> tail = leaf;
        add_to_neighborhood(first, leaf, width, pixel_count, charlie);
        init_leaf(leaf, width, pixel_count, charlie);
        first = get_first(node);
    }
}

void add_to_neighborhood(Pixel* pixel, Node* node, int width, int pixel_count, Charlie* charlie)
{
    add_pixel2(node, pixel);
    if (pixel->rn == true)
    {
        Pixel* right = charlie -> pixels[(pixel -> index) + 1];
        if ((right -> node != node) && ((right -> value) >= (node -> threshold)))
        {
            add_to_neighborhood(right, node, width, pixel_count, charlie);
        }
    }
    if (pixel->ln == true)
    {
        Pixel* left = charlie -> pixels[(pixel -> index) - 1];
        if ((left -> node != node) && ((left -> value) >= (node -> threshold)))
        {
            add_to_neighborhood(left, node, width, pixel_count, charlie);
        }
    }
    if (pixel->bn == true)
    {
        Pixel* bottom = charlie -> pixels[(pixel -> index) + width];
        if ((bottom -> node != node) && ((bottom -> value) >= (node -> threshold)))
        {
            add_to_neighborhood(bottom, node, width, pixel_count, charlie);
        }
    }
    if (pixel->tn == true)
    {
        Pixel* top = charlie -> pixels[(pixel -> index) - width];
        if ((top -> node != node) && ((top -> value) >= (node -> threshold)))
        {
            add_to_neighborhood(top, node, width, pixel_count, charlie);
        }
    }
}

void add_pixel(Node* root, int index, int value, Pixel** pixels, int width, int pixel_count)
{
    Pixel* pixel = malloc(sizeof(Pixel));
    pixels[index] = pixel;
    pixel -> index = index;
    pixel -> value = value;
    pixel -> node = root;
    pixel -> _next = NULL;
    pixel -> rn = true;
    pixel -> ln = true;
    pixel -> bn = true;
    pixel -> tn = true;
    if (index == 0)
    {
        pixel -> ln = false;
        pixel -> tn = false;
    }
    else if (index==width-1)
    {
        pixel -> rn = false;
        pixel -> tn = false;
    }
    else if (index<width)
    {
        pixel -> tn = false;
    }
    else if (index == pixel_count-1)
    {
        pixel -> rn = false;
        pixel -> bn = false;
    }
    else if (index== pixel_count-width)
    {
        pixel -> ln = false;
        pixel -> bn = false;
    }
    else if (index>pixel_count-width)
    {
        pixel -> bn = false;
    }
    else if (index%width == 0)
    {
        pixel -> ln = false;
    }
    else if ((index+1)%width == 0)
    {
        pixel -> rn = false;
    }
    if (root -> p_head == NULL)
    {
        root -> p_head = pixel;
        pixel -> prev = NULL; 
    } else {
        root -> p_tail -> _next = pixel;
        pixel -> prev = root -> p_tail;
    }
    root -> p_tail = pixel;
}

void add_pixel2(Node* node, Pixel* pixel)
{
    if ((pixel -> _next) && (pixel -> prev))
    {
        pixel -> _next -> prev = pixel -> prev;
        pixel -> prev -> _next = pixel -> _next;
    }
    else if (pixel -> _next)
    {
        pixel -> node -> p_head = pixel -> _next;
        pixel -> _next -> prev = NULL;
    }
    else if (pixel -> prev)
    {
        pixel -> node -> p_tail = pixel -> prev;
        pixel -> prev -> _next = NULL;
    }
    else
    {
        pixel -> node -> p_head = NULL;
        pixel -> node -> p_tail = NULL;
    }

    if (node -> p_head == NULL)
    {
        node -> p_head = pixel;
        pixel -> prev = NULL; 
    }
    else
    {
        node -> p_tail -> _next = pixel;
        pixel -> prev = node -> p_tail;
    }
    node -> p_tail = pixel;
    node -> pixel_count += 1;
    pixel -> _next = NULL;
    pixel -> node = node;
}

int get_smallest(Node* node)
{
    Pixel* curr = node -> p_head;
    int smallest = 127;
    while (curr)
    {
        if (curr -> value < smallest)
        {
            smallest = curr -> value;
        }
        curr = curr -> _next;
    }
    return smallest;
}

Pixel* get_first(Node* node)
{
    Pixel* curr = node -> p_head;
    while (curr)
    {
        if (curr -> value > node -> threshold)
        {
            return curr;
        }
        curr = curr -> _next;
    }
    return NULL;
}

void destroy_leaf(Node* node)
{
    if (node -> head)
    {
        Node* curr = node -> head ->_next;
        Node* prev = node -> head;
        while (curr)
        {
            destroy_leaf(prev);
            prev = curr;
            curr = curr -> _next;
        }
        
        destroy_leaf(prev);
    }
    free(node);
}

void destroy_charlie(Charlie* charlie, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(charlie -> pixels[i]);
    }
    destroy_leaf(charlie -> root);
    free(charlie -> pixels);
    free(charlie);
}

void update_pixels(Node* node, int new_value)
{
    Pixel* curr = node -> p_head;
    while (curr)
    {
        curr -> value = new_value;
        curr = curr -> _next;
    }
    node -> threshold = new_value;
}

void recursive_area(Node* node, int a, int g, int threshold)
{
     if ((node->pixel_count <= a ) || ((node -> threshold) <= g))
    {
        update_pixels(node, threshold);
    }
    Node* curr = node -> head;
    while (curr)
    {
        recursive_area(curr, a, g, node->threshold);
        curr = curr -> _next;
    }
}

void recursive_delta(Node* node, float D, int parent_pixel_count)
{
    float d = (float)(parent_pixel_count - node->pixel_count) / (float)parent_pixel_count;
    if (d > D)
    {
        update_pixels(node, node -> parent -> threshold);
    }
    Node* curr = node -> head;
    while (curr)
    {
        recursive_delta(curr, D, node -> pixel_count);
        curr = curr -> _next;
    }
}

void save_image(Image* image, Charlie* charlie)
{
    for (int i = 0; i < image->pixel_count; i++)
    {
        image->pixels[i] = charlie -> pixels[i] -> value;
    }
}