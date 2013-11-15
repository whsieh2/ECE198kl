#include <stdio.h>
#include <stdlib.h>

/* This is the image sructure. TotalRows and TotalCols are the number of pixels in the height and the
 width of the image; par is the array of pixels. In this problem, all pixels are either balck (0) or white (255).
 */
struct pgmimage{
    char type[4];
    int TotalRows,TotalCols;
    int maxval;
    int *par;
};

typedef struct pgmimage pgmimage;

/* newImage creates a new pgmimage of size r x c. Does not initialize it.
 printImage write the image to a file
 DO NOT MODIFY THESE FUNCTIONS. */
pgmimage * newImage(int c, int r, int m);
void printImage(pgmimage * img, FILE * fd);

/* fill_black takes a pointer to a pgm image of size TotalRows x TotalCols 
 and puts a black (length x length) square with top-left corner at (row, col) 
 */
void fill_black(pgmimage* img, int row, int col, int TotalRows, int TotalCols, int length);

/* sierpinski takes a pointer to a pgm image of size TotalRows x TotalCols, 
 and the parameters row, col, and length which indicate that this function draws a (length x length) 
 part of the carpet with top left corner at (row, col). 
 In drawing this part of the carpet, sierpinski may call itself (recursively) to draw 9
 smaller carpets.
 */
void sierpinski(pgmimage* img, int row, int col, int TotalRows, int TotalCols, int length);


int main(int argc, char **argv){
    
    pgmimage *image = NULL;
    FILE* fptr = fopen("carpet.pgm","w");
    int TotalRows,TotalCols,max;
    
    TotalRows = atoi(argv[1]);
    TotalCols = atoi(argv[1]);
    max = 255;
    
    image = newImage(TotalCols, TotalRows, max);
    
    
    /* main sierpinski call, length begins equal to the length of a side */
    sierpinski(image,0,0,TotalRows,TotalCols,TotalRows);
    
    printImage(image,fptr);
    
    return 0;
}

void fill_black(pgmimage* img, int row, int col, int TotalRows, int TotalCols, int length){
/* Add your implementation */
    
}

void sierpinski(pgmimage* img, int row, int col, int TotalRows, int TotalCols, int length){
/* Add your implementation */
    
}

pgmimage* newImage(int c, int r, int m)
{
    pgmimage* im;
    im = (pgmimage *)malloc(sizeof(pgmimage));
    if (im!=NULL) {
        im ->type[0] = 'P';
        im ->type[1] = 'G';
        im ->type[2] = 'M';
        im ->type[3] = '\0';
        im ->TotalRows = r; // *im.TotalRows = r;
        im ->TotalCols = c;
        im ->maxval = m;
        im ->par = (int *)malloc(c*r*sizeof(int));
        if (im->par==NULL)
            exit(-1);
    }
    return im;
}

void printImage(pgmimage * im, FILE * fd)
{
    int row,col,i;
    
    /* Print header */
    fprintf(fd, "P2\n%d %d\n%d\n",  im->TotalCols, im->TotalRows, im->maxval);
    int size = im->TotalRows * im-> TotalCols;
    /* Print pixels */
    for(i = 0; i < size;i++){
        fprintf(fd, " %d ", im->par[i]);
    }
    fprintf(fd, "\n");
}
