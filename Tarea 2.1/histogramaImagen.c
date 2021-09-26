#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputHist1, *outputHist2, *outputHist3, *outputHist4, *lecturas;
    image = fopen("1.bmp","rb");          //Imagen original a transformar
    outputHist1 = fopen("histogramaR.txt","wb");    //Imagen transformada
    outputHist2 = fopen("histogramaG.txt","wb");    //Imagen transformada
    outputHist3 = fopen("histogramaB.txt","wb");    //Imagen transformada
    outputHist4 = fopen("histogramaGrises.txt","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned int r, g, b;               //Pixel

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    int rV[256], gV[256], bV[256], grisV[256];
    
    for(int i=0; i<256;i++){
        rV[i]=0;
        gV[i]=0;
        bV[i]=0;
        grisV[i]=0;
    }


    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;

      rV[r]++;
      gV[g]++;
      bV[b]++;
      grisV[pixel]++;
    }                                        //Grises

    for(int i = 0; i<256; i++){
        fprintf(outputHist1, " %d\t %d\t \n", i, rV[i]);
        fprintf(outputHist2, " %d\t %d\t \n", i, gV[i]);
        fprintf(outputHist3, " %d\t %d\t \n", i, bV[i]);
        fprintf(outputHist4, " %d\t %d\t \n", i, grisV[i]);
    }




    fclose(image);
    fclose(outputHist1);
    fclose(outputHist2);
    fclose(outputHist3);
    fclose(outputHist4);
    return 0;
}
