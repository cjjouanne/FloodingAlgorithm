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
    charlie -> node_count = 1;
    root -> threshold = threshold;
    root -> id = charlie -> node_count;
    root -> parent = NULL;
    root -> p_head = NULL;
    root -> p_tail = NULL;
    root -> head = NULL;
    root -> tail = NULL;
    root -> prev = NULL;
    root -> _next = NULL;
    charlie -> node_count += 1;

    for (int i = 0; i < image -> pixel_count; i++)
    {
        add_pixel(root, i, image -> pixels[i], charlie -> pixels);
    }

    init_leaf(root, image -> width, image -> pixel_count, charlie);

    return charlie;
}

void init_leaf(Node* node, int width, int pixel_count, Charlie* charlie)
{
    int smallest = get_smallest(node);
    if (node -> threshold < smallest) {
        node -> threshold = smallest;
    }
    bool ready = node_ready(node);
    while (ready)
    {
        Pixel* first = get_first(node);
        if (first)
        {

        }
        Node* leaf = malloc(sizeof(Node));
        leaf -> parent = node;
        leaf -> threshold = node -> threshold + 1;
        leaf -> id = charlie -> node_count;
        leaf -> p_head = NULL;
        leaf -> p_tail = NULL;
        leaf -> head = NULL;
        leaf -> tail = NULL;
        leaf -> prev = NULL;
        leaf -> _next = NULL;
        charlie -> node_count += 1;

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
        ready = node_ready(node);
    }
}

void add_to_neighborhood(Pixel* pixel, Node* node, int width, int pixel_count, Charlie* charlie)
{
    if ((pixel -> node -> id != node -> id) && ((pixel -> value) >= (node -> threshold)))
    {
        add_pixel2(node, pixel);
    }
    if (pixel -> index < width)
    {
        if (pixel -> index == 0)
        {
            Pixel* right = charlie -> pixels[(pixel -> index) + 1];
            if ((right -> node -> id != node -> id) && ((right -> value) >= (node -> threshold)))
            {
                add_to_neighborhood(right, node, width, pixel_count, charlie);
            }
        }
        else if (pixel -> index == width -1)
        {
            Pixel* left = charlie -> pixels[(pixel -> index) - 1];
            if ((left -> node != node) && ((left -> value) >= (node -> threshold)))
            {
                add_to_neighborhood(left, node, width, pixel_count, charlie);
            }
        }
        else
        {
            Pixel* right = charlie -> pixels[(pixel -> index) + 1];
            Pixel* left = charlie ->pixels[(pixel -> index) - 1];
            if ((right -> node -> id != node -> id) && (right -> value) >= node -> threshold)
            {
                add_to_neighborhood(right, node, width, pixel_count, charlie);
            }
            if ((left -> node -> id != node -> id) && (left -> value) >= node -> threshold)
            {
                add_to_neighborhood(left, node, width, pixel_count, charlie);
            }
        }
        Pixel* bottom = charlie -> pixels[(pixel -> index) + width];
        if ((bottom -> node -> id != node -> id) && (bottom -> value) >= node -> threshold)
        {
            add_to_neighborhood(bottom, node, width, pixel_count, charlie);
        }
    }
    else if (pixel -> index >= pixel_count - width)
    {
        if (pixel -> index == pixel_count - width)
        {
            Pixel* right = charlie -> pixels[(pixel -> index) + 1];
            if ((right -> node -> id != node -> id) && (right -> value) >= node -> threshold)
            {
                add_to_neighborhood(right, node, width, pixel_count, charlie);
            }
        }
        else if (pixel -> index == pixel_count - 1)
        {
            Pixel* left = charlie -> pixels[(pixel -> index) - 1];
            if ((left -> node -> id != node -> id) && (left -> value) >= node -> threshold)
            {
                add_to_neighborhood(left, node, width, pixel_count, charlie);
            }
        }
        else
        {
            Pixel* right = charlie -> pixels[(pixel -> index) + 1];
            Pixel* left = charlie -> pixels[(pixel -> index) - 1];
            if ((right -> node -> id != node -> id) && (right -> value) >= node -> threshold)
            {
                add_to_neighborhood(right, node, width, pixel_count, charlie);
            }
            if ((left -> node -> id != node -> id) && (left -> value) >= node -> threshold)
            {
                add_to_neighborhood(left, node, width, pixel_count, charlie);
            }
        }
        Pixel* top = charlie -> pixels[(pixel -> index) - width];
        if ((top -> node -> id != node -> id) && (top -> value) >= node -> threshold)
        {
            add_to_neighborhood(top, node, width, pixel_count, charlie);
        }
    }
    else
    {
        Pixel* top = charlie -> pixels[(pixel -> index) - width];
        Pixel* bottom = charlie -> pixels[(pixel -> index) + width];
        if ((bottom -> node -> id != node -> id) && (bottom -> value) >= node -> threshold)
        {
            add_to_neighborhood(bottom, node, width, pixel_count, charlie);
        }
        if ((top -> node -> id != node -> id) && (top -> value) >= node -> threshold)
        {
            add_to_neighborhood(top, node, width, pixel_count, charlie);
        }
        if (((pixel -> index)) % width == 0)
        {
            Pixel* right = charlie -> pixels[(pixel -> index) + 1];
            if ((right -> node -> id != node -> id) && (right -> value) >= node -> threshold)
            {
                add_to_neighborhood(right, node, width, pixel_count, charlie);
            }
        }
        else if (((pixel -> index) +1) % width == 0)
        {
            Pixel* left = charlie -> pixels[(pixel -> index) - 1];
            if ((left -> node -> id != node -> id) && (left -> value) >= node -> threshold)
            {
                add_to_neighborhood(left, node, width, pixel_count, charlie);
            }
        }
        else
        {
            Pixel* right = charlie -> pixels[(pixel -> index) + 1];
            Pixel* left = charlie -> pixels[(pixel -> index) - 1];
            if ((right -> node -> id != node -> id) && (right -> value) >= node -> threshold)
            {
                add_to_neighborhood(right, node, width, pixel_count, charlie);
            }
            if ((left -> node -> id != node -> id) && (left -> value) >= node -> threshold)
            {
                add_to_neighborhood(left, node, width, pixel_count, charlie);
            }
        }
    }
}

void add_pixel(Node* root, int index, int value, Pixel** pixels)
{
    Pixel* pixel = malloc(sizeof(Pixel));
    pixels[index] = pixel;
    pixel -> index = index;
    pixel -> value = value;
    pixel -> node = root;
    pixel -> _next = NULL; 
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

bool node_ready(Node* node)
{
    Pixel* curr = node -> p_head;
    while (curr)
    {
        if (curr -> value > node -> threshold)
        {
            return true;
        }
        curr = curr -> _next;
    }
    return NULL;
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
    if ((node ->_next) && (node -> prev)) 
    {
        node -> _next -> prev = node -> prev;
        node -> prev -> _next = node -> _next;
    }
    else if (node -> _next)
    {
        node -> parent -> head = node -> _next;
        node -> _next -> prev = NULL;
    }
    else if (node -> prev)
    {
        node -> parent -> tail = node -> prev;
        node -> prev -> _next = NULL;
    }
    else if (node -> parent)
    {
        node -> parent -> head = NULL;
        node -> parent -> tail = NULL;
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

void recursive_inform(Node* node, int depth)
{
    int count = count_pixels(node);
    for (int i = 0; i < depth; i++)
    {
        printf(" ");
    }
    printf("%i:%i:%i\n", node -> id, node->threshold,count);
    Node *curr = node -> head;
    while (curr)
    {
        recursive_inform(curr, depth + 1);
        curr = curr -> _next;
    }
}

int count_pixels(Node* node)
{
    int count = 0;
    Pixel* curr = node -> p_head;
    while (curr)
    {
        count += 1;
        curr = curr -> _next;
    }
    return count;
}

int count_recursive(Node* node)
{
    int count = count_pixels(node);
    Node* curr = node -> head;
    while (curr)
    {
        count += count_recursive(curr);
        curr = curr -> _next;
    }
    return count;
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

void area_filter(Node* node, int a, int g)
{
    int count = count_recursive(node);
    if ((count <= a ) || ((node -> threshold) <= g))
    {
        if (node -> parent)
        {
            update_pixels(node, node -> parent -> threshold);
        }
        else
        {
            update_pixels(node, 0);
        }
    }
}

void delta_filter(Node* node, float D, int parent_pixel_count, int node_pixel_count)
{
    if (node -> parent)
    {
        float d = (float)(parent_pixel_count - node_pixel_count) / (float)parent_pixel_count;
        if (d > D)
        {
            update_pixels(node, node -> parent -> threshold);
        }
    }
}

void recursive_area(Node* node, int a, int g)
{
    area_filter(node, a, g);
    Node* curr = node -> head;
    while (curr)
    {
        recursive_area(curr, a, g);
        curr = curr -> _next;
    }
}

void recursive_delta(Node* node, float D, int parent_pixel_count, int node_pixel_count)
{
    delta_filter(node, D, parent_pixel_count, node_pixel_count);
    Node* curr = node -> head;
    while (curr)
    {
        int count = count_recursive(curr);
        recursive_delta(curr, D, node_pixel_count, count);
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