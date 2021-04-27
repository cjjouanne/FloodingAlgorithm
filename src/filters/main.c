#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "../imagelib/image.h"

#include "charlie_tree.h"


int main(int argc, char** argv)
{
    // Revisamos los argumentos
    
    pthread_attr_t atr;
    size_t size = 19391577;
    pthread_attr_setstacksize(&atr, size);
    

    if(argc < 4) {
        printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
        return 1;
    }

    // Cargamos la imagen original desde el archivo
    Image* image = img_png_read_from_file(argv[1]);

    /* ------------- POR IMPLEMENTAR -------------- */
    /* Aqui debes crear el MaxTree de la imagen.    */
    Charlie* charlie = init_tree(image, 0);
    // recursive_inform(charlie->root, 0);
    
    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(image->pixel_count, sizeof(int))
    };

    // Filtramos el arbol y lo guardamos en la imagen, segun el filtro que corresponda
    if (! strcmp("delta", argv[3]))
    {
        // Filtro DELTA
        float max_delta = atof(argv[4]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro delta y     */
        int count = count_recursive(charlie->root);
        recursive_delta(charlie->root, max_delta, image->pixel_count, count);
        /* guardar la imagen filtrada en new_img.       */
        save_image(new_img, charlie);

    }
    else if (! strcmp("area", argv[3]))
    {
        // Filtro AREA-COLOR
        int min_area = atoi(argv[4]);
        int threshold = atoi(argv[5]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro de area y   */
        printf("AREA FILTER IS RUNNING\n");
        recursive_area(charlie->root, min_area, threshold);
        /* guardar la imagen filtrada en new_img.       */
        printf("UPDATING CHANGES\n");
        save_image(new_img, charlie);

    }

    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    printf("Listo!\n");

    // Liberamos los recursos
    destroy_charlie(charlie, image -> pixel_count);
    img_png_destroy(image);
    img_png_destroy(new_img);

    // Terminamos exitosamente
    return 0;
}