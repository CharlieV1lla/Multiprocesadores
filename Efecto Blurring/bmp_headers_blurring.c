#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#define NUM_THREADS 800
#define SIZEM 1 //el tamanio de la mascara es SIZEM * 2 + 1

int main()
{
  FILE *image, *outputImage, *lecturas;
  image = fopen("4.bmp","rb");          //Imagen original a transformar
  outputImage = fopen("prueba4.bmp","wb");    //Imagen transformada
  long ancho;
  long alto;
  unsigned char r, g, b;               //Pixel
  unsigned char* ptr;

  unsigned char xx[54];
  long cuenta = 0, anchoR=0, altoR=0, anchoM=0, altoM=0;
  long sum;
  int iR, jR;
  for(int i=0; i<54; i++) {
    xx[i] = fgetc(image);
    fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
  }
  ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
  alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
  printf("largo img %li\n",alto);
  printf("ancho img %li\n",ancho);

  ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));
  omp_set_num_threads(NUM_THREADS);
    
  unsigned char foto[alto][ancho], fotoB[alto][ancho];
  unsigned char pixel;
  
    for(int i=0; i<alto;i++){
      for(int j=0; j<ancho;j++){
        b = fgetc(image);
        g = fgetc(image);
        r = fgetc(image);

        pixel = 0.21*r+0.72*g+0.07*b;
        foto[i][j]=pixel;
        fotoB[i][j]=pixel;
      }
    }

  anchoR=ancho/SIZEM;
  altoR=alto/SIZEM;
  anchoM=ancho%SIZEM;
  altoM=alto%SIZEM;

  int inicioX,inicioY,cierreX,cierreY,ladoX,ladoY;
  //casi toda la imagen se representa aquí
  for(int i=0;i<alto;i++){
    //iR=i*SIZEM;
    for(int j=0;j<ancho;j++){
      //jR=j*SIZEM;
      if(i<SIZEM){
        inicioX=0;
        cierreX=i+SIZEM;
        ladoX=i+SIZEM;
      } else if(i>=alto-SIZEM){
        inicioX=i-SIZEM;
        cierreX=alto;
        ladoX=alto-i+SIZEM;
      }else{
        inicioX=i-SIZEM;
        cierreX=i+SIZEM;
        ladoX=SIZEM*2+1;
      }
  
      if(j<SIZEM){
        inicioY=0;
        cierreY=j+SIZEM;
        ladoY=j+SIZEM;
      }else if(j>=ancho-SIZEM){
        inicioY=j-SIZEM;
        cierreY=ancho;
        ladoY=ancho-j+SIZEM;
      }else{
        inicioY=j-SIZEM;
        cierreY=j+SIZEM;
        ladoY=SIZEM*2+1;
      }
      sum=0;
      for(int x=inicioX;x<cierreX;x++){
        for(int y=inicioY;y<cierreY;y++){
          sum+=foto[x][y];
        }
      }
      sum=sum/(ladoX*ladoY);
      fotoB[i][j]=sum;
    }
  }
  
   
  //asignacion a imagen
  cuenta=0;
  for(int i=0; i<alto;i++){
    for(int j=0; j<ancho;j++){
      ptr[cuenta] = fotoB[i][j]; //b
      ptr[cuenta+1] = fotoB[i][j]; //g
      ptr[cuenta+2] = fotoB[i][j]; //r

      cuenta++;
    }
  }                     
  //Grises
  const double startTime = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for schedule(dynamic)
    for (int i = 0; i < alto*ancho; ++i) {
      fputc(ptr[i], outputImage);
      fputc(ptr[i+1], outputImage);
      fputc(ptr[i+2], outputImage);
    }
  }

  const double endTime = omp_get_wtime();
  free(ptr);
  fclose(image);
  fclose(outputImage);
  printf("Tiempo=%f", endTime-startTime);
  return 0;
}
