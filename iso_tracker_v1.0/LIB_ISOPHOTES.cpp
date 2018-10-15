/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "LIB_ISOPHOTES.h"


void mapadecentros_completo( Mat& imCONV, float *fp_im_src, float *fp_MAPA, float *fp_FX, float *fp_FY, float *fp_FXX, float *fp_FYY, float *fp_FXY, 
     uint16_t wim, uint16_t him, float *fp_ph_gauss1, float *fp_ph_gauss2, float *fp_pd1, float *fp_pd1n, float *fp_pp, float *fp_ppn, float *fp_pd2, 
     uint16_t rmin, uint16_t rmax, uint16_t *fp_imax, uint16_t *fp_jmax, float *max_MAPA )
{

    uint8_t wkernel1=5;
    uint8_t wkernel2=7;
    //Mat imCONV(him, wim, CV_8UC1);
    
    conv2d_xcolumnafila_prueba( fp_im_src, fp_im_src, imCONV, wim, him, wkernel1, fp_ph_gauss1, fp_ph_gauss1 ); // Aplico filtro gaussiano
    conv2d_xcolumnafila_prueba( fp_im_src, fp_FX, imCONV, wim, him, wkernel2, fp_pd1n, fp_pp );
    conv2d_xcolumnafila_prueba( fp_im_src, fp_FY, imCONV, wim, him, wkernel2, fp_ppn, fp_pd1 );
    conv2d_xcolumnafila_prueba( fp_im_src, fp_FXX, imCONV, wim, him, wkernel2, fp_pd2, fp_pp );
    conv2d_xcolumnafila_prueba( fp_im_src, fp_FYY, imCONV, wim, him, wkernel2, fp_pp, fp_pd2 );
    conv2d_xcolumnafila_prueba( fp_FX, fp_FXY, imCONV, wim, him, wkernel2, fp_ppn, fp_pd1 );

    
    mapadecentros( fp_FX, fp_FY, fp_FXX, fp_FYY, fp_FXY, wim, him, rmin, rmax, fp_MAPA, imCONV, fp_imax, fp_jmax ); 
    conv2d_prueba(fp_MAPA, imCONV, wim, him, 9, fp_ph_gauss2);    
    
    findmax(fp_MAPA, wim, him, fp_imax, fp_jmax, max_MAPA);

}

void conv2d_prueba( float *fp_data, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel) {

    int i, j, ii, jj, px1, px2, px3;
    const uint8_t k_media_ventana=floor(wk/2);
    float max,min,aux1, aux2, resconv;
    
    float resconv_aux[him*wim];
    float *p_resconv_aux;
    p_resconv_aux=(float*)&resconv_aux;
    
    for ( i=0; i<him; i++) 
      for ( j=0; j<wim; j++) {
        px1=wim*i+j;
        *(p_resconv_aux+px1) = 0;  
      }
  
    
    max=0;
    for (i=k_media_ventana; i<(him-k_media_ventana); i++) {
        for (j=k_media_ventana; j<(wim-k_media_ventana); j++){
            px1=wim*i+j;
            resconv=0;
            for (ii=0; ii<wk; ii++){
                for (jj=0; jj<wk; jj++){
                        px2=wim*(i-k_media_ventana+ii)+j-k_media_ventana+jj;
                        px3=ii*wk+jj;
                        aux1=(*(fp_data+px2));
                        aux2=(*(fp_kernel+px3));
                        resconv=resconv+aux1*aux2;                       
                }
            }
            *(p_resconv_aux+px1) = resconv;   
            if (resconv>max) max=resconv;
        }
    } 
    
//    for (i=0; i<him; i++){
//        for (j=0; j<wim; j++){
//            px1=wim*i+j;
//            fp_im_dst.at<uchar>(i,j) = (*(p_resconv_aux+px1))*255/max;
//        }
//    }   
}



void conv2d_xcolumnafila_prueba( float *fp_im_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel_cols, float *fp_kernel_rows) {


  float resconv_aux[him*wim];
  //float resconv_aux2[him*wim];
  
  float *p_resconv_aux;
  //float *p_resconv_aux2;
  
  p_resconv_aux=(float*)&resconv_aux;
//  p_resconv_aux2=(float*)&resconv_aux2;
  
  
  int i,j,ii,jj,px1,px2;
  float max,min,aux1, aux2, resconv;

  const uint8_t kc_media_ventana=floor(wk/2);
  const uint8_t kf_media_ventana=floor(wk/2);
  const uint8_t wkernels=wk;
  const uint8_t OFFSETY=10;
  const uint8_t OFFSETX=10;
  
  
  for ( i=0; i<him; i++) 
      for ( j=0; j<wim; j++) {
        px1=wim*i+j;
        *(p_resconv_aux+px1) = 0; 
        //*(p_resconv_aux2+px1) = 0;   
      }
  



      
    
  //Convoluciono cada columna de la IMAGEN DE ENTRADA con kernel_columns: 
  
    for (i=0; i<him; i++) {
            for (j=kc_media_ventana; j<(wim-kc_media_ventana); j++){
                    px1=wim*i+j;
                    resconv=0;
                    for (jj=0; jj<wkernels; jj++){
                            px2=wim*i+j-kc_media_ventana+jj;
                            aux1=(*(fp_im_src+px2));
                            aux2=(*(fp_kernel_cols+jj));
                            resconv=resconv+aux1*aux2;
                    }				
                    //resconv1[i][j]=resconv;
                    *(p_resconv_aux+px1) = resconv;
            }
    }
 
  min=99999999; max=0;
    for (i=kf_media_ventana; i<him-kf_media_ventana; i++) {
        for (j=0; j<wim; j++){
            px1 = wim*i+j;
            resconv=0;
            for (ii=0; ii<wkernels; ii++){
                px2=wim*(i-kf_media_ventana+ii)+j;
                //aux1=resconv1[i-kf_media_ventana+ii][j];
                aux1 = *(p_resconv_aux+px2);
                aux2=(*(fp_kernel_rows+ii)); 
                resconv=resconv+aux1*aux2;		
             }

            if (resconv<min) min=resconv;
            if (resconv>max) max=resconv;
			
            *(fp_data_dst+px1)=resconv;
            
        }
    }

//    // Transformo para almacenar en imagen CV Mat
//    for (i= OFFSETY; i<(him-OFFSETY) ; i++) {
//        for ( j=OFFSETX; j<(wim-OFFSETX) ; j++){		
//            px1 = wim*i+j;
//          
//            aux1=(*(p_resconv_aux2+px1));
//            aux1=aux1-min;
//            aux1=255*aux1;
//            aux1=aux1/(max-min);	         			
//            fp_im_dst.at<uchar>(i,j) = aux1;
//            
//            fp_im_dst.at<uchar>(i,j) = 100;
//        }
//    }

//    // Transformo para almacenar en imagen CV Mat
//    for (i= 0; i<him ; i++) {
//        for ( j=0; j<wim ; j++){
//            
//            px1 = wim*i+j;
//          //  *(fp_im_dst+px1)=*(p_resconv_aux2+px1);
//            
//            if (  ( (j>=OFFSETX)&&(j<(wim-OFFSETX)) ) && ( (i>=OFFSETY)&&(i<(him-OFFSETY)))   )  {
//                
//
//                aux1=(*(fp_data_dst+px1));
//                aux1=aux1-min;
//                aux1=255*aux1;
//                aux1=aux1/(max-min);	         			
//                fp_im_dst.at<uchar>(i,j) = aux1;
//
//                //fp_im_dst.at<uchar>(i,j) = 100;
//            }
//            else
//                fp_im_dst.at<uchar>(i,j) = 0;
//        }
//    } 

  
      
}





void dibujo_cruz(Mat& fp_im, uint16_t wim, uint16_t him, uint16_t posx, uint16_t posy){

    uint16_t i, j, px, ilim1, ilim2, jlim1, jlim2;
    const uint8_t ancho_cruz=30;
    const uint8_t alto_cruz=30;
    int aux;
   
    aux = posy - ancho_cruz/2;
    if (aux>=0) ilim1=aux;
    else
        ilim1=0;   
    aux = posy + ancho_cruz/2;
    if (aux<him) ilim2=aux;
    else
        ilim2=him-1;
    aux = posx - ancho_cruz/2;
    if (aux>=0) jlim1=aux;
    else
        jlim1=0;
    aux = posx + ancho_cruz/2;
    if (aux<wim) jlim2=aux;
    else
        jlim2=wim-1;
    

    for (i=ilim1; i<ilim2; i++){
        fp_im.at<Vec3b>(i, posx) = Vec3b(0, 0, 255);
        if ( (posx-1)>=0 ) fp_im.at<Vec3b>(i, posx-1) = Vec3b(0, 0, 255);
        if ( (posx+1)<wim ) fp_im.at<Vec3b>(i, posx+1) = Vec3b(0, 0, 255);
    }
        
    for (j=jlim1; j<jlim2; j++){
        fp_im.at<Vec3b>(posy, j) = Vec3b(0, 0, 255); 
        if ( (posy-1)>=0 ) fp_im.at<Vec3b>(posy-1, j) = Vec3b(0, 0, 255);  
        if ( (posy+1)<him ) fp_im.at<Vec3b>(posy+1, j) = Vec3b(0, 0, 255);  
    }
}


void findmax( float *fp_data, uint16_t wim, uint16_t him, uint16_t *fp_imax, uint16_t *fp_jmax, float *fp_max ){
int i, j, px;
float max;

max=0;
    for (i=0; i<him; i++){
        for (j=0; j<wim; j++){
            px=wim*i+j;
            if (*(fp_data+px)>max){
                max = *(fp_data+px);
                *fp_imax=i;
                *fp_jmax=j;
            } 
        }
    }
*fp_max=max;
}


void conv2d( float *fp_data_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel) {

    int i, j, ii, jj, px1, px2, px3;
    const uint8_t k_media_ventana=floor(wk/2);
    float max,min,aux1, aux2, resconv;
    
    max=0;
    for (i=k_media_ventana; i<(him-k_media_ventana); i++) {
        for (j=k_media_ventana; j<(wim-k_media_ventana); j++){
            px1=wim*i+j;
            resconv=0;
            for (ii=0; ii<wk; ii++){
                for (jj=0; jj<wk; jj++){
                        px2=wim*(i-k_media_ventana+ii)+j-k_media_ventana+jj;
                        px3=ii*wk+jj;
                        aux1=(*(fp_data_src+px2));
                        aux2=(*(fp_kernel+px3));
                        resconv=resconv+aux1*aux2;                       
                }
            }
            *(fp_data_dst+px1) = resconv;   
            if (resconv>max) max=resconv;
        }
    } 
    
    for (i=0; i<him; i++){
        for (j=0; j<wim; j++){
            px1=wim*i+j;
            fp_im_dst.at<uchar>(i,j) = (*(fp_data_dst+px1))*255/max;
        }
    }   
}



//REGLAS DE VALIDACIÓN DE LA DETECCIÓN:
bool validacion(uint16_t imax, uint16_t jmax, float maxMAPA){
    static uint16_t jmax_old;
    static uint16_t imax_old;
    bool val=false;
    float d;
    
    //REGLA 1: MÁXIMO DEL MAPA POR ENCIMA DE UN UMBRAL.    
    //REGLA 2: distancia con punto anterior.
    
    d = sqrt( (imax-imax_old)*(imax-imax_old)+(jmax-jmax_old)*(jmax-jmax_old) );
    imax_old = imax;
    jmax_old = jmax;
    
    if ( (d<20) && (maxMAPA>0.5) )
        val=true;
    
    return val;
}


//wk es el ancho del kernel
//void conv2d( float *fp_data_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel) {
//
//    int i, j, ii, jj, px1, px2, px3;
//    const uint8_t k_media_ventana=floor(wk/2);
//    float max,min,aux1, aux2, resconv;
//    
//    max=0;
//    for (i=k_media_ventana; i<(him-k_media_ventana); i++) {
//        for (j=k_media_ventana; j<(wim-k_media_ventana); j++){
//            px1=wim*i+j;
//            resconv=0;
//            for (ii=0; ii<wk; ii++){
//                for (jj=0; jj<wk; jj++){
//                        px2=wim*(i-k_media_ventana+ii)+j-k_media_ventana+jj;
//                        px3=ii*wk+jj;
//                        aux1=(*(fp_data_src+px2));
//                        aux2=(*(fp_kernel+px3));
//                        resconv=resconv+aux1*aux2;                       
//                }
//            }
//            *(fp_data_dst+px1) = resconv;   
//            if (resconv>max) max=resconv;
//        }
//    } 
//    
//    for (i=0; i<him; i++){
//        for (j=0; j<wim; j++){
//            px1=wim*i+j;
//            fp_im_dst.at<uchar>(i,j) = (*(fp_data_dst+px1))*255/max;
//        }
//    }   
//
//
//
//
//
////void mat2negativo(float *fp_src_data, float *fp_dst_data, uint16_t wim, uint16_t him) {
////
////    int i, j, px;
////    
////    for (i=0; i<him; i++){
////        for (j=0; j<wim; j++){
////            px=wim*i+j;
////            *(fp_dst_data+px)=31-*(fp_src_data+px);
////        }
////    }   
////}
//}


//LEE IMAGEN RGB565 Y LA ALMACENA *PIM_OUT, FALTA DEPURAR (APARECEN ALGUNAS LÍNEAS SIN DATOS)
void frgb565_to_rgb(const char* pfilename, float* fpdata, Mat *pim_out){

    FILE *archivo; 
    const uint16_t H (pim_out->rows);
    const uint16_t W (pim_out->cols);
    const uint16_t HW = (pim_out->rows)*(pim_out->cols);
    
    int16_t datos[2*HW]; // si uso int no me lee todo el archivo, si uso int8_t muestra distorsión.
    int datos_r[HW];
    int datos_g[HW];
    int datos_b[HW];  
    int dataim[HW];
    int i, j, k;
    int g1, g2, px1,px2;

    for (i=1 ; i<2*HW ; i++) 
        datos[i]=0;
    
    //archivo = fopen("D:/PIC1.BMP","r");   
    archivo = fopen(pfilename,"r");
    
    if (archivo == NULL) {
       fputs ("File error",stderr); exit (1);
    }            
    else {
        i=1;
        i=fread(&datos,1,60200,archivo);
        //printf("VALOR DE i: %d :", i);
    }
    fclose(archivo);
    

    //......................................................................................................................................................
    //IMPORTANTE:
    // fread está leyendo de a 2 bytes. Por más que fread me devuelva 35571, está leyendo 320x80+32=25632 datos (datos de 16 bits, 71 BYTES de encabezado)
    //......................................................................................................................................................
    
   
    k=1;
    for (i=34; i<=(HW+32); i++) {    
        datos_b[k] = datos[i] & 0b11111; 
//        g1 = (datos[i] >> 5 ) & 0b111;
//        g2 = (datos[i+1] & 0b111) << 3;
//        datos_g[k] = g1+ g2;
//        datos_r[k] = (datos[i+1] >> 3 ) & 0b11111;
        k++;             
    }   
    
   
    for (i = 0; i<H ; i++) {
        for ( j=0; j<W ; j++){            
            px1 = W*i + j;
            px2 = W*(H - i)+j-W;
            dataim[px1] = datos_b[px2];
            *(fpdata+px1)=datos_b[px2];
        }
    }  
    
    
    for ( i = 0; i < pim_out->rows; i++) {
        for ( j = 0; j < pim_out->cols; j++) {
            px1 = W*i + j;
            pim_out->at<uchar>(i,j) = 255*dataim[px1]/31;          
          //  *(fpdata+px1)=datos_b[px1];
        }
    }   
    
}


void conv2d_xcolumnafila( float *fp_im_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel_cols, float *fp_kernel_rows, float *fp_resconv_aux ) {

  //float resconv1[him][wim];
  
  
  int i,j,ii,jj,px1,px2;
  float max,min,aux1, aux2, resconv;

  const uint8_t kc_media_ventana=floor(wk/2);
  const uint8_t kf_media_ventana=floor(wk/2);
  const uint8_t wkernels=wk;
  const uint8_t OFFSETY=10;
  const uint8_t OFFSETX=10;
  
  
  for ( i=0; i<him; i++) 
      for ( j=0; j<wim; j++) {
        px1=wim*i+j;
        *(fp_resconv_aux+px1) = 0;   
      }


      
    
  //Convoluciono cada columna de la IMAGEN DE ENTRADA con kernel_columns: 
  
    for (i=0; i<him; i++) {
            for (j=kc_media_ventana; j<(wim-kc_media_ventana); j++){
                    px1=wim*i+j;
                    resconv=0;
                    for (jj=0; jj<wkernels; jj++){
                            px2=wim*i+j-kc_media_ventana+jj;
                            aux1=(*(fp_im_src+px2));
                            aux2=(*(fp_kernel_cols+jj));
                            resconv=resconv+aux1*aux2;
                    }				
                    //resconv1[i][j]=resconv;
                    *(fp_resconv_aux+px1) = resconv;
            }
    }
 
  min=99999999; max=0;
    for (i=kf_media_ventana; i<him-kf_media_ventana; i++) {
        for (j=0; j<wim; j++){
            px1 = wim*i+j;
            resconv=0;
            for (ii=0; ii<wkernels; ii++){
                px2=wim*(i-kf_media_ventana+ii)+j;
                //aux1=resconv1[i-kf_media_ventana+ii][j];
                aux1 = *(fp_resconv_aux+px2);
                aux2=(*(fp_kernel_rows+ii)); 
                resconv=resconv+aux1*aux2;		
             }

            if (resconv<min) min=resconv;
            if (resconv>max) max=resconv;
			
            *(fp_data_dst+px1)=resconv;
            
            if ((i==75) && (j==300)){
                *(fp_data_dst+px1)=resconv;
            }
        }
    }

    // Transformo para almacenar en imagen CV Mat
    for (i= OFFSETY; i<(him-OFFSETY) ; i++) {
        for ( j=OFFSETX; j<(wim-OFFSETX) ; j++){		
            px1 = wim*i+j;
          
            aux1=(*(fp_data_dst+px1));
            aux1=aux1-min;
            aux1=255*aux1;
            aux1=aux1/(max-min);	         			
            fp_im_dst.at<uchar>(i,j) = aux1;
            //fp_im_dst.at(i,j)<uint8_t>= aux1;
        }
    }  
      
}




void mat2float(Mat& fp_im_src, float *fp_dst_data, uint16_t wim, uint16_t him) {

    int i, j, px;
    
    for (i=0; i<him; i++){
        for (j=0; j<wim; j++){
            px=wim*i+j;
            //*(fp_dst_data+px)=(float)(fp_im_src+px);           
            *(fp_dst_data+px) = fp_im_src.at<uchar>(i,j);        
            
           // fp_im.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
        }
    }
    
}
//void mat2float(Mat& fp_im_src, float *fp_data_dst) {
//    
//    int i,j,px;
//    const uint16_t him = (fp_im_src.rows);
//    const uint16_t wim = (fp_im_src.cols);
//    int aux;
//    float auxf;
//    
//    //px=123;
//    //*(fp_data_dst+px)=25;
//    for (i= 0; i<him ; i++) {
//        for ( j=0; j<wim ; j++){		
//            px = wim*i+j;
//           // (*(fp_data_dst+px))=25;
//            aux = fp_im_src.at<uchar>(i,j);
////            auxf = (float)aux;
////            (*(fp_data_dst+px)) = auxf;
//            
//            //(*(fp_data_dst+px)) = fp_im_src.at<uchar>(i,j);
//            (*(fp_data_dst+px)) = fp_im_src.at<uint8_t>(i,j);
//            
//            printf("%d", fp_im_src.at<uint8_t>(i,j));
//        }
//    }    
//}


void float2mat(float *fp_src_data, Mat& fp_im_dst, uint16_t wim, uint16_t him) {

    int i, j, px;
    
    for (i=0; i<him; i++){
        for (j=0; j<wim; j++){
            px=wim*i+j;
            fp_im_dst.at<uchar>(i,j) = *(fp_src_data+px);
        }
    }   
}




void mat2negativo(float *fp_src_data, float *fp_dst_data, uint16_t wim, uint16_t him) {

    int i, j, px;
    
    for (i=0; i<him; i++){
        for (j=0; j<wim; j++){
            px=wim*i+j;
            *(fp_dst_data+px)=31-*(fp_src_data+px);
        }
    }   
}

void matColor2negativo(Mat& fp_im_src, float *fp_dst_data, uint16_t wim, uint16_t him) {

    int i, j, px;
    Vec3b intensity;
    uchar blue, green, red;
    
    for (i=0; i<him; i++){
        for (j=0; j<wim; j++){
            px=wim*i+j;
            intensity = fp_im_src.at<Vec3b>(i, j);
            
            blue = intensity.val[0];
            green = intensity.val[1];
            red = intensity.val[2];
            *(fp_dst_data+px)=255 - float(red);
        }
    }
    
}





void mapadecentros( float *fp_FX, float *fp_FY, float *fp_FXX, float *fp_FYY, float *fp_FXY,  uint16_t wim, uint16_t him, uint16_t rmin, uint16_t rmax,
                    float *fp_MAPA, Mat& fp_im_mapa, uint16_t *fp_imax, uint16_t *fp_jmax )
{

    int i,j,px1,px2;
    float FX, FY, FXX, FYY, FXY;
    float FX2, FY2, FXX2, FYY2, FXY2;
    float QQ, Q1, Q2, Q3, Q4, Q5, curvedness;
    int DX, DY, MAGD, curvaturak;
    
    float aux_mapa;
    float max_mapa=0;
    float min_mapa=999999;
    
    float auxf;
    
    const uint8_t OFFSETY=10;
    const uint8_t OFFSETX=10;
    
    
    for (i=0; i<him; i++) {
        for (j=0; j<wim; j++){
            px1=wim*i+j;
            (*(fp_MAPA+px1))=0;
        }
    }


    for (i=OFFSETY; i<(him-OFFSETY); i++) {
      
	for (j=OFFSETX; j<(wim-OFFSETX); j++){
            px1=wim*i+j;

            FX=(*(fp_FX+px1)); 
            FX2= (*(fp_FX+px1))*(*(fp_FX+px1));
            FY=(*(fp_FY+px1)); 
            FY2= (*(fp_FY+px1))*(*(fp_FY+px1));
            FXX=(*(fp_FXX+px1)); 
            FXX2=(*(fp_FXX+px1))*(*(fp_FXX+px1));  
            FYY=(*(fp_FYY+px1)); 
            FYY2=(*(fp_FYY+px1))*(*(fp_FYY+px1));  
            FXY=(*(fp_FXY+px1)); 
            FXY2=(*(fp_FXY+px1))*(*(fp_FXY+px1)); 

            curvedness=100*( FXX2+2*FXY2+FYY2 );
            curvedness=sqrt( curvedness );

            Q1=FX2+FY2;
            Q3=FY2*FXX+FX2*FYY;
            Q3=Q3-2*FX*FXY*FY; 
            
            
            
			
            if (Q3==0) {
                    DX=0;
                    DY=0;
            }
            else {		
                auxf = -FX*Q1;
                auxf = auxf/Q3;
                DX = (int) auxf;
                
                auxf = -FY*Q1;
                auxf = auxf/Q3;
                DY = (int) auxf;
                
//                QQ=Q3/2;
//                DX=-FX*Q1; DY=-FY*Q1;
//
//                if (DX>0)
//                        DX=DX+abs(QQ);  // sumo denominador/2 para que redondear para arriba
//                else
//                        DX=DX-abs(QQ);
//
//                DX=DX/Q3;
//
//                if (DY>0)
//                        DY=DY+abs(QQ);
//                else
//                        DY=DY-abs(QQ);
//
//                DY=DY/Q3;	
            }
            


            MAGD=sqrt(DX*DX+DY*DY);
				
            if (Q3==0) curvaturak=0;
            else {
                    if (Q3>0) curvaturak=1;
                    else
                            curvaturak=-1;
            }
            
            //(*(fp_DX+px1))=DX;
            //(*(fp_DY+px1))=DY;
            //(*(fp_curvaturak+px1))=curvaturak;
            
            
           
//            if ((i<20) && (j<20))
//                printf("ck[%d,%d]:%d ", i,j, curvaturak);
            
            
            //(*(pcurvaturak+px1))=5;
            

            if  ( (DX!=0) || (DY!=0) ) {
                if ( (j+DX)>OFFSETX && (i+DY)>OFFSETY ){
                    if ( ((j+DX)<(wim-OFFSETX)) && ((i+DY)<(him-OFFSETY)) && (curvaturak<0) ){
                        if ( (MAGD>=rmin) && (MAGD<=rmax) ) {
                            px2=wim*(i+DY)+(j+DX);
                            (*(fp_MAPA+px2))=(*(fp_MAPA+px2))+abs(curvedness);

                            if ( (*(fp_MAPA+px2))>max_mapa ){ 
                                *fp_imax=i+DY;
                                *fp_jmax=j+DX;
                                max_mapa=(*(fp_MAPA+px2));
                            }

                            if ( (*(fp_MAPA+px2))<min_mapa ){
                                min_mapa=(*(fp_MAPA+px2));
                            }                             
                        }
                    }
                }		
            }	
	}
    }		

//    // Transformo para almacenar en imagen CV Mat	
//    for (i=OFFSETY; i<(him-OFFSETY); i++) {
//        for (j=OFFSETX; j<(wim-OFFSETX); j++){
//            px1=wim*i+j;
//            aux_mapa=*(fp_MAPA+px1);
//            if (aux_mapa!=0){
//                    if (max_mapa!=min_mapa){			
//                        aux_mapa=aux_mapa-min_mapa;
//                        aux_mapa=255*aux_mapa;
//                        aux_mapa=aux_mapa/(max_mapa-min_mapa);	
//                    }
//                    else{
//                        aux_mapa=255*aux_mapa/max_mapa;
//                    }
//                    //*(fp_img_ventana2+px1)=(uint8_t)aux_mapa;		
//            }
//             fp_im_mapa.at<uchar>(i,j) = aux_mapa;
//        }
//    }	    
}
