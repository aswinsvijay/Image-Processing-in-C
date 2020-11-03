Image Processing in C
=====================

This repository contains code for Image Processing using C. Images are edited using simple matrix transformations. The input is required to be an image in .ppm(P3) format.

**Usage:**  
make build - Compile the code.  
make test_n  - Setting the nth test image as input to program.  
make prepare - Read input and output filenames from user.  
make run_xyz - Run the transformations numbered x, y, z in succession.  

1. Greyscale
2. Colour Inversion  
eg: make run_12 will greyscale first and then colour inversion.  

make run_interactive - Run the program in interactive mode.  
make clean - Cleanup the environment.  