#include "ppm.h"
#include<stdio.h>
#include<stdlib.h>

PPMimg *readPPM(const char *filename)
{
    char line[10];
    PPMimg *img;
    FILE *f;
    int c, rgb_comp_color;
    f = fopen(filename, "rb");

    fgets(line, sizeof(line), f);
    if (line[0] != 'P' || line[1] != '3')
    {
        fprintf(stderr, "Invalid image format (must be 'P3')\n");
        exit(1);
    }
    img = (PPMimg *)malloc(sizeof(PPMimg));
    if (!img)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    c = getc(f);
    while (c == '#')
    {
        while (getc(f) != '\n') ;
        c = getc(f);
    }
    ungetc(c, f);
    if (fscanf(f, "%d %d", &img->x, &img->y) != 2)
    {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
        exit(1);
    }
    if (fscanf(f, "%d", &rgb_comp_color) != 1)
    {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
        exit(1);
    }
    if (rgb_comp_color!= 255)
    {
        fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
        exit(1);
    }

    while (fgetc(f) != '\n') ;
    img->data = (PPMpx*)malloc(img->x * img->y * sizeof(PPMpx));

    if (!img)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
  
    for(int i=0;i<img->x;i++)
        for(int j=0;j<img->y;j++)
            fscanf(f,"%d %d %d ",&img->data[i*(img->y)+j].rgb[0],&img->data[i*(img->y)+j].rgb[1],&img->data[i*(img->y)+j].rgb[2]);
  
    fclose(f);
    return img;
}

void writePPM(const char *filename, PPMimg *img)
{
    FILE *f;
    f = fopen(filename, "w");
    if (!f)
    {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n",img->x,img->y);
    fprintf(f, "%d\n",255);

    for(int i=0;i<img->x;i++)
    {
        for(int j=0;j<img->y;j++)
        {
            fprintf(f,"%d ",img->data[i*(img->y)+j].rgb[0]);
            fprintf(f,"%d ",img->data[i*(img->y)+j].rgb[1]);
            fprintf(f,"%d ",img->data[i*(img->y)+j].rgb[2]);
        }
        if(i%6==0)
            fprintf(f,"\n");
    }
    fclose(f);
}