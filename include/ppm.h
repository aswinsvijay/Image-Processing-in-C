typedef struct
{
    unsigned int rgb[3];
}PPMpx;

typedef struct
{
    int x, y;
    PPMpx *data;
}PPMimg;

PPMimg *readPPM(const char *filename);
void writePPM(const char *filename, PPMimg *img);