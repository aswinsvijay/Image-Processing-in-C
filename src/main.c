#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ppm.h"
#include"transformations.h"

int main(int argc,char *argv[])
{
    char *inname,*outname,*opt;
    inname  = argv[1];
    outname = argv[2];
    opt     = argv[3]+4;

    PPMimg *img = readPPM(inname);

    if(!strcmp(opt,"interactive"))
    {
        char ch;
        while(1)
        {
            printf("0. Exit\n1. Greyscale\n2. Colour invert\n3. Change Saturation\n");
            printf("Enter choice:");
            scanf(" %c",&ch);
            printf("%d\n",(int)ch);
            switch(ch)
            {
                case '1' : printf("Converting...\n");
                           greyscale(img);
                           printf("Writing...\n");
                           writePPM(outname,img);
                           break;
                case '2' : printf("Converting...\n");
                           invert(img);
                           printf("Writing...\n");
                           writePPM(outname,img);
                           break;
                case '3' : saturation(img);
                           printf("Converting...\n");
                           printf("Writing...\n");
                           writePPM(outname,img);
                           break;
                case '0' : exit(0);
                default  : printf("Wrong option\n");
            }
        }
    }
    else
    {
        for(int i=0 ; opt[i]!='\0' ; i++)
        {
            switch(opt[i])
            {
                case '1' : greyscale(img);
                           break;
                case '2' : invert(img);
                           break;
                case '3' : saturation(img);
                           break;
                default  : printf("Wrong option given, exiting...\n");
                           return(0);
            }
        }
        writePPM(outname,img);
    }
    return 0;
}
