/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Cristian7
 *
 * Created on 18 de junio de 2018, 15:49
 */

//-----------------------------------
// PARA CONTROLAR PUERTO SERIE:
#include <iostream>
#include "SerialPort.h"
#include <stdio.h>
#include <string.h>
//-----------------------------------


/* 
 * File:   main.cpp
 * Author: Cristian
 *
 * Created on 28 de abril de 2015, 12:50
 */


#include<windows.h>


#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <stdlib.h>

#include <stdio.h>
#include <conio.h>
#include "dos.h"
#include <math.h>

#include <iostream>
#include <fstream>
#include <time.h>

#include "LIB_ISOPHOTES.h"
#include "defs.h"
#include "defs_globales.h"

#include "comandos.h"


using namespace std;
using namespace cv;

const uint16_t slider_contorno_max = 20;
int slider_contorno=10;
int slider_calibracion=1;



float v_contorno[3700];
float *pv_contorno;

boolean use_beep=true;
boolean modo_camara=true;



Mat im_ajuste(alto_screen,ancho_screen,CV_8UC3);


const uint16_t wframe_mostrar=638;
const uint16_t hframe_mostrar=200;

boolean tomar_pos=false;
uint16_t tmuestra=0;

uint16_t ip_inicial;
uint16_t jp_inicial;

uint16_t vectorx_ajustes[7];
uint16_t vectory_ajustes[7];

uint16_t *pvectorx, *pvectory;

uint16_t vectorx_ajustes2[7];
uint16_t vectory_ajustes2[7];
uint16_t *pvectorx2, *pvectory2;


    

void on_trackbar_calibracion( int, void* )
{
    if (slider_calibracion==0)
        usar_calibracion=false;
    
//    sprintf(texto,"slider_calibracion: %d", slider_calibracion );
//    putText(im_ajuste, texto, Point(ancho_screen/2-400,650), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2); 
//    imshow("ISO_TRACKER",im_ajuste);
//    waitKey(0);    
    
}

void on_trackbar_contorno( int, void* )
{
    const uint16_t max = 10;
    int aux_slider;
    
    aux_slider = slider_contorno*max/(slider_contorno_max/2)-max;
            
            //*max/slider_contorno_max
    
//    sprintf(texto,"vx+1 - vx+2: %d - %d", *(pvectorx+1),*(pvectorx+2));
//    putText(im_ajuste, texto, Point(ancho_screen/2-400,530), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);    
    
//    *(pvectorx+1)= *(pvectorx2+1) + slider_contorno*max/slider_contorno_max;
//    *(pvectorx+2) = *(pvectorx2+2) - slider_contorno*max/slider_contorno_max;
//    *(pvectorx+3)= *(pvectorx2+3) - slider_contorno*max/slider_contorno_max;
//    *(pvectorx+4)= *(pvectorx2+4) + slider_contorno*max/slider_contorno_max;
    
    *(pvectorx+1) = *(pvectorx2+1) - aux_slider;
    *(pvectorx+2) = *(pvectorx2+2) + aux_slider;
    *(pvectorx+3) = *(pvectorx2+3) + aux_slider;
    *(pvectorx+4) = *(pvectorx2+4) - aux_slider;
    
    *(pvectory+1) = *(pvectory2+1) - aux_slider;
    *(pvectory+2) = *(pvectory2+2) + aux_slider;
    *(pvectory+3) = *(pvectory2+3) - aux_slider;
    *(pvectory+4) = *(pvectory2+4) + aux_slider; 
    
//    *(pvectory2+1)= *(pvectory+1);
//    *(pvectory2+2)= *(pvectory+2);
//    *(pvectory2+3)= *(pvectory+3);
//    *(pvectory2+4)= *(pvectory+4);
      
//    sprintf(texto,"vx+1 - vx+2: %d - %d", *(pvectorx+1),*(pvectorx+2));
//    putText(im_ajuste, texto, Point(ancho_screen/2-400,560), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);
//
//    sprintf(texto,"slider contorno: %d", slider_contorno);
//    putText(im_ajuste, texto, Point(ancho_screen/2-400,590), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);
//  
//    sprintf(texto,"slider contorno max: %d", slider_contorno_max);
//    putText(im_ajuste, texto, Point(ancho_screen/2-400,620), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);
//    
//    sprintf(texto,"slider: %d", slider_contorno*max/slider_contorno_max );
//    putText(im_ajuste, texto, Point(ancho_screen/2-400,650), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);
//  
//    
//    imshow("ISO_TRACKER",im_ajuste);
//    waitKey(0);
    
    
    contorno(pv_contorno, ip_inicial, jp_inicial, im_ajuste, ancho_screen, alto_screen, im_control, ancho_control, alto_control, pvectorx, pvectory);     
    
//  alpha = (double) alpha_slider/alpha_slider_max ;
//  beta = ( 1.0 - alpha );
//  addWeighted( src1, alpha, src2, beta, 0.0, dst);
//  imshow( "Linear Blend", dst );
}



//////////////////////////////////////////////////////////////////
///TRACKBAR:
/// Global Variables
const int alpha_slider_max = 2;
int alpha_slider;
double alpha;
double beta;
/// Matrices to store images
Mat src1;
Mat src2;
Mat dst;
/**
 * @function on_trackbar
 * @brief Callback for trackbar
 */
void on_trackbar( int, void* )
{
  alpha = (double) alpha_slider/alpha_slider_max ;
  beta = ( 1.0 - alpha );
  addWeighted( src1, alpha, src2, beta, 0.0, dst);
  imshow( "Linear Blend", dst );
}
//////////////////////////////////////////////////////////////////

void delay(int secs) {
  for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}


void reset_imagen(Mat& im, uint16_t ancho, uint16_t alto){
uint16_t i,j;
    for (i=0; i<alto; i++){
        for (j=0; j<ancho; j++)
            im.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
    }    
}



int main(int argc, char** argv) {

uint16_t x1,x2,x3,x4,y1,y2,y3,y4;
uint16_t i1, i2, j1, j2, i_inicial_frame, j_inicial_frame;
    
    
    pv_contorno = (float*)&v_contorno;
    k=1;
    int q=1;
    
    r=255; g=0; b=0;

    uint8_t forma_comando;

    uint8_t ncuadros_fps=0;      
    
    double cam_fps, cam_brightness, cam_contrast, cam_saturation, cam_hue, cam_gain, cam_exposure, cam_gamma; 
   
    
    
 pvectorx2 = (uint16_t*)&vectorx_ajustes2;
pvectory2 = (uint16_t*)&vectory_ajustes2;


    VideoCapture cap(0);
   //CvCapture cap2(0);
    
    

                    
    pd1=(float*)&d1;
    pd2=(float*)&d2;
    pd1n=(float*)&d1n;
    pp=(float*)&p;
    ppn=(float*)&pn;
    ph_gauss1=(float*)&h_gauss1;
    ph_gauss2=(float*)&h_gauss2;
     
    arduino = new SerialPort(portName);
    //chequeo si se estableció la conexión con la placa Arduino:
    if (arduino->isConnected()){
        std::cout << "Conexion establecida con el puerto: " << portName << endl;
    }   
    


namedWindow("Ajustes", 1);
imshow("Ajustes", imread("D:/fondo_slider.jpg"));
char TrackbarName[50];
sprintf( TrackbarName, "Contorno " );
createTrackbar( TrackbarName, "Ajustes", &slider_contorno, slider_contorno_max, on_trackbar_contorno );
sprintf( TrackbarName, "Calibracion " );
createTrackbar( TrackbarName, "Ajustes", &slider_calibracion, 1, on_trackbar_calibracion );

//    cvNamedWindow("ventana1");
//    while(1){
//     printf("\n vol+:");           
//     arduino->writeSerialPort("2", 1);
//     waitKey(500);
//     arduino->writeSerialPort("0", 1); 
//     delay(4);
//     
//     printf("\n vol-:");           
//     arduino->writeSerialPort("3", 1);
//     waitKey(500);
//     arduino->writeSerialPort("0", 1);  
//     delay(4);
//     
//     printf("\n ch+:");         
//     arduino->writeSerialPort("6", 1);
//     waitKey(500);
//     arduino->writeSerialPort("0", 1);
//     delay(4);
//     
//     printf("\n ch-:");         
//     arduino->writeSerialPort("5", 1);
//     waitKey(500);
//     arduino->writeSerialPort("0", 1); 
//     delay(4);
//    }
    
    
    
    posx_mouse=ancho_screen/2;
    posy_mouse=alto_screen/2;
    rmin=6; rmax=10;
    //rmin=6; rmax=9;
    //rmin=5; rmax=8;
    
    if (modo_camara) {
        if(!cap.isOpened()) {
            printf("\nERROR: CAMARA NO DETECTADA!");
            printf("\n\n");
            return -1;
        }
        //cap.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.25);
       // cvSetCaptureProperty(cap2, CV_CAP_PROP_AUTO_EXPOSURE, 0.0);
        //cap.set(CV_CAP_PROP_BRIGHTNESS, 60);
        //cap.set(CV_CAP_PROP_BRIGHTNESS, 80);
        cap.set(CV_CAP_PROP_BRIGHTNESS, 90);
        cap.set(CV_CAP_PROP_GAIN,0);
        cap.set(CV_CAP_PROP_EXPOSURE, 0.20); //Or multiple other values here.
    }

    cvNamedWindow("ISO_TRACKER", CV_WINDOW_NORMAL);
    cvSetWindowProperty("ISO_TRACKER", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN); 
    reset_imagen(im_ajuste,ancho_screen,alto_screen);    
    sprintf(texto,"-DIRIJA LA MIRADA AL CENTRO DE LA PANTALLA-", fps);
    putText(im_ajuste, texto, Point(ancho_screen/2-400,530), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);
    
    dibujo_cruz(im_ajuste,ancho_screen,alto_screen,ancho_screen/2,alto_screen/2);

    uint16_t conta;
    tstart = clock();  
    tstart2 = tstart;
    while(1)
    {
          
        if (modo_camara) {
            cap >> frame;
            flip(frame, frame, +1);
        }
        else frame=imread("D:/capturas/comandos/0cap_centro.jpg");
        
        roi = frame.clone();  // Para evitar que los cambios en frame se vean reflejados en ROI
        roi = roi( Rect(xi_roi,yi_roi,w_roi,h_roi) ); // Selecciono región de interes 
        resize(roi, roi, Size(),escala_im,escala_im, INTER_CUBIC);
        rectangle(frame, Point(xi_roi, yi_roi), Point(xi_roi+w_roi, yi_roi+h_roi), CV_RGB(r,g,b), 3);  // Dibujo rectángulo 
        matColor2negativo(roi, pdataim, wimg, himg);

        mapadecentros_prueba( imCONV, pdataim, pMAPA, pFX, pFY, pFXX, pFYY, pFXY, wimg, himg, ph_gauss1, ph_gauss2, pd1, pd1n, pp, ppn, pd2, rmin, rmax, &i_max_MAPA, &j_max_MAPA, &max_MAPA);
               
        if  (abs(i_max_MAPA-i_max_MAPA_old)<=1) i_max_MAPA = i_max_MAPA_old;
        else
            i_max_MAPA_old = i_max_MAPA;
        if  (abs(j_max_MAPA-j_max_MAPA_old)<=1) j_max_MAPA = j_max_MAPA_old;
        else
            j_max_MAPA_old = j_max_MAPA;
              
        i_max_MAPA = i_max_MAPA/escala_im; j_max_MAPA = j_max_MAPA/escala_im;
        
        tend2 = clock();
        dif = tend2-tstart2;
        
        if (dif>1000){
            iniciar=true;
            tstart2 = clock(); 
        }
        if ( (dif>1000) && (iniciar) ){
            tstart2 = clock(); tomar_pos=true;
        }
        else
            tomar_pos=false;
     
        if (tomar_pos) {  
            cantidad_det=2;
            //cantidad_det=100;
            if (det==0) {
                icero = i_max_MAPA; jcero = j_max_MAPA;
                det=1;
                ip = icero; jp = jcero;        
            }
            else {
                distmax=8;
                dist = sqrt ( (i_max_MAPA-icero)*(i_max_MAPA-icero) + (j_max_MAPA-jcero)*(j_max_MAPA-jcero) );
                //if ( (d<10) && (max_MAPA>50) ) {
                if (dist<distmax) {    
                   det++;
                   ip = ip+i_max_MAPA; jp = jp+j_max_MAPA;
                }
                else{
                    det = 0; nodet++;
                }
            }
            if (det==cantidad_det) {                    
                ajustar=false;
                r=0; g=255; b=0;
                ip=ip/(cantidad_det); jp=jp/(cantidad_det);
                ip=round(ip)+yi_roi; jp=round(jp)+xi_roi;             
                if (use_beep) Beep(FREQ_BEEP_CAL,TIME_BEEP_CAL);               
                break;
            }
        } 
         
        sprintf(texto,"FPS: %.1f", fps);
        putText(frame, texto, Point(30,50), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);
              
        for (i = 0; i< 480; i++){
            for (j = 0 ; j < 640; j++){
                im_ajuste.at<Vec3b>(i,j+ancho_screen/2-320) = frame.at<Vec3b>( i, j);
            }
        }  
         
        imshow("ISO_TRACKER",im_ajuste);
        //if(waitKey(1) >= 0) break;
        tecla = waitKey(1);
        if ( (tecla == 27) || (tecla == 13) ) {  // tecla escape o enter
            salir_de_programa=true;
            return 0;
        }
            
        
        //--------------------------
        //waitKey(0);
//        sprintf(texto,"D:/capturas/cap%d.jpg",q);
//        imwrite(texto, frame );
//        q++;
        //--------------------------
 
        ncuadros_fps++;
        if (ncuadros_fps>=15){
            ncuadros_fps=0;
            tend = clock();
            dif = tend-tstart;
            fps = (1000*15)/dif;  
            tstart = clock();  
        }
    }
    
//-------------------------------------------------------------------------------------------------------------------------    
//-------------------------------------------------------------------------------------------------------------------------  
// 2) 
    

    
    ip_inicial=ip;
    jp_inicial=jp;
    
    delete pdataim;
    delete pdataim2;
    delete pFX;
    delete pFXX;
    delete pFY;
    delete pFYY;
    delete pFXY;
    delete pMAPA;
    delete pMAPA2;
    
    wimg = 200; 
    himg = 160;   

    w_roi = wimg ;
    h_roi = himg ;
    xi_roi = jp - wimg/2 ;
    yi_roi = ip - h_roi/2 ;   
    
      
    wimg=wimg*escala_im;
    himg=himg*escala_im;
   
    float *pdataim3 = new float[himg*wimg];
    float *pdataim4 = new float[himg*wimg];
    
    float *pFX2 = new float[himg*wimg];
    float *pFXX2 = new float[himg*wimg];
    float *pFY2 = new float[himg*wimg];
    float *pFYY2 = new float[himg*wimg];
    float *pFXY2 = new float[himg*wimg];
    float *pMAPA3 = new float[himg*wimg];
    float *pMAPA4 = new float[himg*wimg];
    float *presconv_aux2 = new float[himg*wimg];
      
    uint16_t i_max_MAPA2, j_max_MAPA2, i_max_MAPA2_old, j_max_MAPA2_old;
    
    imCONV.release();
    im_MAPA.release();
    Mat imCONV2(himg, wimg, CV_8UC1);
    Mat im_MAPA2(himg, wimg, CV_8UC1);
    
    uint16_t px;
    for (i=0; i<himg; i++){
        for (j=0; j<wimg; j++){
            px=wimg*i+j;          
            *(pFX2+px)=0; 
            *(pFXX2+px)=0; 
            *(pFY2+px)=0; 
            *(pFYY2+px)=0; 
            *(pFXY2+px)=0; 
            *(pMAPA3+px)=0; 
            *(pMAPA4+px)=0;
            *(presconv_aux2+px)=0; 
            im_MAPA2.at<uchar>(i,j) = 0;
            imCONV2.at<uchar>(i,j) = 0;      
        }
    }
    
        
    r=0; g=255; b=0;

    uint16_t k1=0;
    uint16_t k2=1;
    uint16_t k3=0;

    uint16_t detx[200];
    uint16_t dety[200];
       
    bool pos_valida=false;
    
    
              
                
    rmin_inicial=11;
    rmax_inicial=14;
    ajustar=false; 
    

    //rmin2=4; rmax2=7;
    
    //rmin2=6; rmax2=9;
    
    uint16_t nk1=0;
    uint16_t nk2=0;
    uint16_t nregion=1;

    
    pvectorx = (uint16_t*)&vectorx_ajustes;
    pvectory = (uint16_t*)&vectory_ajustes;
    
    for (i=0; i<=6; i++){
        vectorx_ajustes[i]=0; vectory_ajustes[i]=0;
    }
    
    
    i1 = 0;   // posición y donde comienzo a mostrar imagen de cámara    
    if ( ( ip_inicial + hframe_mostrar/2 )<480 )
        i2 = hframe_mostrar;
    else
        i2 = 480 - hframe_mostrar;
   
    j1 = ancho_screen/2 - wframe_mostrar/2;   // posición x donde comienzo a mostrar imagen de cámara
    j2 = ancho_screen/2 + wframe_mostrar/2;
    i_inicial_frame = ip_inicial-hframe_mostrar/2;        
    j_inicial_frame = 0;   
    

    det=0;
    ncuadros_fps=0;
    tstart = clock(); 
    tstart2 = tstart;
    while(1){
               
        reset_imagen(im_ajuste,ancho_screen,alto_screen);
        
        if (modo_camara) {
            cap >> frame;
            flip(frame, frame, +1);
        }
        else {
            switch(nregion){
                case 1: frame=imread("D:/capturas/comandos/1cap_arriba_izq.jpg"); 
                        //frame=imread("D:/capturas/comandos/3cap_arriba_der.jpg"); 
                        break;
                case 2: frame=imread("D:/capturas/comandos/2cap_abajo_der.jpg"); 
                        break;
                case 3: frame=imread("D:/capturas/comandos/3cap_arriba_der.jpg");   
                        break;
                case 4: frame=imread("D:/capturas/comandos/4cap_abajo_izq.jpg"); 
                        break;        
            }
        }

        switch(nregion){
            case 1: imagen_emoji=imread("D:/emoji1_100.png");
                    for (i = 0; i< 100; i++){
                        for (j = 0 ; j < 100; j++){
                            im_ajuste.at<Vec3b>(i+5, j+5) = imagen_emoji.at<Vec3b>(i,j);
                        }
                    }   
                    break;
            case 2: imagen_emoji=imread("D:/emoji4_100.jpg");
                    for (i = 0; i< 100; i++){
                        for (j = 0 ; j < 100; j++){
                            im_ajuste.at<Vec3b>(i+alto_screen-100-5, j+ancho_screen-100-5) = imagen_emoji.at<Vec3b>(i,j);
                        }
                    }                  
                    break;
            case 3: imagen_emoji=imread("D:/emoji2_100.jpg");
                    for (i = 0; i< 100; i++){
                        for (j = 0 ; j < 100; j++){
                            im_ajuste.at<Vec3b>(i+5, j+ancho_screen-100-5) = imagen_emoji.at<Vec3b>(i,j);
                        }
                    } 
                    break;
            case 4: imagen_emoji=imread("D:/emoji3_100.png");
                    for (i = 0; i< 100; i++){
                        for (j = 0 ; j < 100; j++){
                            im_ajuste.at<Vec3b>(i+alto_screen-100-5, j+5) = imagen_emoji.at<Vec3b>(i,j);
                        }
                    }                               
                    break;              
        }    
        
        roi = frame.clone();  // Para evitar que cambios en frame, se vean reflejados en ROI
        roi = roi( Rect(xi_roi,yi_roi,w_roi,h_roi) ); // Selecciono región de interes 
        resize(roi, roi, Size(),escala_im,escala_im, INTER_CUBIC);                   
        rectangle(frame, Point(xi_roi+10, yi_roi+10), Point(xi_roi+10+w_roi-20, yi_roi+10+h_roi-20), CV_RGB(r,g,b), 3);  // Dibujo rectángulo 
        matColor2negativo(roi, pdataim3, wimg, himg);
 
        mapadecentros_prueba( imCONV2, pdataim3, pMAPA3, pFX2, pFY2, pFXX2, pFYY2, pFXY2, wimg, himg, ph_gauss1, ph_gauss2, pd1, pd1n, pp, ppn, pd2, rmin, rmax, &i_max_MAPA2, &j_max_MAPA2, &max_MAPA);
                    
        pos_valida=validacion(i_max_MAPA2, j_max_MAPA2, max_MAPA);
        
        tend2 = clock();
        dif = tend2-tstart2;
        if ( (dif>1000) && (pos_valida) ){
            tstart2 = clock(); tomar_pos=true;
        }
        else
            tomar_pos=false;
             
        if (pos_valida){           
            i_max_MAPA = i_max_MAPA2/escala_im + yi_roi;
            j_max_MAPA = j_max_MAPA2/escala_im + xi_roi;
            if (tomar_pos) {  
                cantidad_det=2;
                //cantidad_det=10;
                if (det==0){
                    icero = i_max_MAPA; jcero = j_max_MAPA;
                    det=1;
                    ip = icero; jp = jcero;        
                }
                else {
                    distmax=8;
                    dist = sqrt ( (i_max_MAPA-icero)*(i_max_MAPA-icero) + (j_max_MAPA-jcero)*(j_max_MAPA-jcero) );
                    if (dist<distmax) {    
                       det++;
                       ip = ip+i_max_MAPA; jp = jp+j_max_MAPA;
                    }
                    else{
                        det=0; nodet++;
                    }
                }
                if (det==cantidad_det) {
                    det=0;
                    r=0; g=255; b=0;
                    ip=ip/(cantidad_det); jp=jp/(cantidad_det);              
                    ip=round(ip); jp=round(jp);
                    
                    switch(nregion){
                        case 1: if ( (jp<jp_inicial) && (ip<ip_inicial) )
                                    posicionok=true;
                                else
                                    posicionok=false;
                                break;
                        case 2: if ( (jp>jp_inicial) && (ip>ip_inicial) )
                                    posicionok=true;
                                else
                                    posicionok=false;
                                break;
                        case 3: if ( (jp>jp_inicial) && (ip<ip_inicial) )
                                    posicionok=true;
                                else
                                    posicionok=false;
                                break;
                        case 4: if ( (jp<jp_inicial) && (ip>ip_inicial) )
                                    posicionok=true;
                                else
                                    posicionok=false;
                                break;
                    }
                    
                    if (posicionok){
                        vectorx_ajustes[nregion]=jp;
                        vectory_ajustes[nregion]=ip;        
                        nregion++;

                        if (use_beep) Beep(FREQ_BEEP_CAL,TIME_BEEP_CAL);
                    }
                    else {
                        if (use_beep){
                            Beep(FREQ_BEEP_COMANDO,3*TIME_BEEP_COMANDO);
                        }
                    }

                        
                    //waitKey(0);
                }
            }       
            if  (abs(i_max_MAPA2-i_max_MAPA2_old)<=1) i_max_MAPA2 = i_max_MAPA2_old;
            else
                i_max_MAPA2_old = i_max_MAPA2;
            if  (abs(j_max_MAPA2-j_max_MAPA2_old)<=1) j_max_MAPA2 = j_max_MAPA2_old;
            else
                j_max_MAPA2_old = j_max_MAPA2;
                
            dibujo_cruz(frame,640,480,j_max_MAPA,i_max_MAPA);                            
        }
             
        sprintf(texto,"-SIGA EL EMOJI-", fps);      
        putText(im_ajuste, texto, Point(ancho_screen/2-120,hframe_mostrar+40), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);
        sprintf(texto,"(SIN MOVER LA CABEZA)", fps);
        putText(im_ajuste, texto, Point(ancho_screen/2-190,hframe_mostrar+70), FONT_HERSHEY_TRIPLEX, 1, CV_RGB(255,255,0), 2);

        circle(im_ajuste,  Point(ancho_screen/2, alto_screen/2), 8, CV_RGB(0,255,0), 2); 
        
        for (i=2; i<=nregion ;i++)
            circle(im_ajuste,  Point(vectorx_ajustes[i-1]-jp_inicial+ancho_screen/2, vectory_ajustes[i-1]-ip_inicial+alto_screen/2), 1, CV_RGB(255,255,0), 2);  // Dibujo rectángulo 
        
 if (usar_calibracion==false) nregion=5; 
        
        if (nregion==5) {         
            for (i=1; i<alto_screen; i++){
                for (j=1; j<ancho_screen; j++)
                    im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
            }            
            
            if (usar_calibracion==false){
                vectorx_ajustes[1] = jp_inicial-ancho_contorno/2;
                vectorx_ajustes[2] = jp_inicial+ancho_contorno/2;
                vectorx_ajustes[3] = vectorx_ajustes[2];
                vectorx_ajustes[4] = vectorx_ajustes[1];          
                vectory_ajustes[1] = ip_inicial-alto_contorno/2;
                vectory_ajustes[2] = ip_inicial+alto_contorno/2;
                vectory_ajustes[3] = vectory_ajustes[1];
                vectory_ajustes[4] = vectory_ajustes[2];
             }
            
                    
            x1=vectorx_ajustes[1]; x2=vectorx_ajustes[2]; 
            x3=vectorx_ajustes[3]; x4=vectorx_ajustes[4];          
            y1=vectory_ajustes[1]; y2=vectory_ajustes[2];
            y3=vectory_ajustes[3]; y4=vectory_ajustes[4];
            
            *(pvectorx2+1)= *(pvectorx+1);
            *(pvectorx2+2)= *(pvectorx+2);
            *(pvectorx2+3)= *(pvectorx+3);
            *(pvectorx2+4)= *(pvectorx+4);

            *(pvectory2+1)= *(pvectory+1);
            *(pvectory2+2)= *(pvectory+2);
            *(pvectory2+3)= *(pvectory+3);
            *(pvectory2+4)= *(pvectory+4);
           
    
            if ( (x1<jp_inicial) && (x4<jp_inicial) && (x3>jp_inicial) && (x2>jp_inicial) &&
                 (y1<ip_inicial) && (y3<ip_inicial) && (y4>ip_inicial) && (y2>ip_inicial) ) 
            {  
                imagen_emoji=imread("D:/mano_ok.png");
                for (i = 0; i< 320; i++){
                    for (j = 0 ; j < 320; j++){
                        im_ajuste.at<Vec3b>(i+alto_screen/2-170, j+ancho_screen/2-160) = imagen_emoji.at<Vec3b>(i,j);
                    }
                } 
                
                if (use_beep){
                    waitKey(300);
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    waitKey(100);
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                }
                
                sprintf(texto,"PERFECTO!");
                putText(im_ajuste, texto, Point(ancho_screen/2-180,alto_screen/4), FONT_HERSHEY_TRIPLEX, 2, CV_RGB(255,255,0), 2);         
            }
            else{
                sprintf(texto,"ERROR DE CALIBRACION...");
                putText(im_ajuste, texto, Point(ancho_screen/2-280,alto_screen/4), FONT_HERSHEY_TRIPLEX, 2, CV_RGB(255,0,0), 2);         
                imshow("ISO_TRACKER",im_ajuste);     
                waitKey(4000);
                return 0;
            }
            imshow("ISO_TRACKER",im_ajuste);        
            waitKey(1000);
            break;
        }
        
        sprintf(texto,"FPS: %.1f", fps);
        putText(frame, texto, Point(j_inicial_frame+5, i_inicial_frame+30), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);     
                
        for (i = i1; i< i2; i++){
            for (j = j1 ; j < j2; j++){
                im_ajuste.at<Vec3b>(i, j) = frame.at<Vec3b>( i-i1+i_inicial_frame, j-j1+j_inicial_frame);
            }
        }             
                
        imshow("ISO_TRACKER",im_ajuste); 
        
        tecla = waitKey(1);
        if ( (tecla == 27) || (tecla == 13) ) {  // tecla escape o enter
            salir_de_programa=true;
            return 0;
        }

        ncuadros_fps++;
        if (ncuadros_fps>=15){
            ncuadros_fps=0;
            tend = clock();
            dif = tend-tstart;
            fps = (1000*15)/dif;  
            tstart = clock();  
        }
   }    
    
//-------------------------------------------------------------------------------------------------------------------------    
//-------------------------------------------------------------------------------------------------------------------------  
// 3) 
    
    uint16_t x,y;
    float fase, im, re;
    
    float fase_der_circ1, fase_abajo_circ1, fase_izq_circ2, fase_arr_circ2, fase_izq_circ3, fase_abajo_circ3, fase_arr_circ4, fase_der_circ4;

    float r;

    float xc1a, xc1b, xc2a, xc2b, xc3a, xc3b, xc4a, xc4b;
    float yc1a, yc1b, yc2a, yc2b, yc3a, yc3b, yc4a, yc4b;
    float mr_up, mr_down, br_up, br_down;
    float fase_rizq, fase_rder;
    const double pi = 3.1415926535897;
    
    xc1a = x1+offset_comando*cos((90+OFFSET_FASE)*pi/180);
    yc1a = y1-offset_comando*sin((90+OFFSET_FASE)*pi/180);
    xc1b = x1+offset_comando*cos((180-OFFSET_FASE)*pi/180);
    yc1b = y1-offset_comando*sin((180-OFFSET_FASE)*pi/180);       

    xc4a = x4+offset_comando*cos((180+OFFSET_FASE)*pi/180);
    yc4a = y4-offset_comando*sin((180+OFFSET_FASE)*pi/180);
    xc4b = x4+offset_comando*cos((270-OFFSET_FASE)*pi/180);
    yc4b = y4-offset_comando*sin((270-OFFSET_FASE)*pi/180); 

    xc2a = x2+offset_comando*cos((270+OFFSET_FASE)*pi/180);
    yc2a = y2-offset_comando*sin((270+OFFSET_FASE)*pi/180);
    xc2b = x2+offset_comando*cos((360-OFFSET_FASE)*pi/180);
    yc2b = y2-offset_comando*sin((360-OFFSET_FASE)*pi/180); 

    xc3a = x3+offset_comando*cos((0+OFFSET_FASE)*pi/180);
    yc3a = y3-offset_comando*sin((0+OFFSET_FASE)*pi/180);
    xc3b = x3+offset_comando*cos((90-OFFSET_FASE)*pi/180);
    yc3b = y3-offset_comando*sin((90-OFFSET_FASE)*pi/180); 

          
//sprintf(texto,"xc3b - xc1a: %.1f - %.1f", xc3b, xc1a);
//putText(im_ajuste, texto, Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2); 
//sprintf(texto,"xc2a - xc4b: %.1f - %.1f", xc2a, xc4b);
//putText(im_ajuste, texto, Point(30, 60), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);  
// sprintf(texto,"im - re: %d - %d", im, re);
//putText(im_ajuste, texto, Point(30, 90), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);    
// imshow("ISO_TRACKER",im_ajuste);
//waitKey(0);             
    
    mr_up = (yc3b-yc1a)/(xc3b-xc1a);
    mr_down = (yc2a-yc4b)/(xc2a-xc4b);
    br_up = yc3b-mr_up*xc3b;
    br_down = yc2a-mr_down*xc2a;

    im = yc4a-yc1b;
    re = xc1b-xc4a;



    fase_rizq = fasegrados(im,re);
 


    im = yc2b-yc3a;
    re = xc3a-xc2b;
    fase_rder = fasegrados(im,re);
    

      
   
    i1 = 0;   // posición y donde comienzo a mostrar imagen de cámara
    if ( (ip_inicial+hframe_mostrar/2)<480 )
        i2 = hframe_mostrar;
    else
        i2 = 480 - hframe_mostrar;
    j1 = ancho_screen/2 - wframe_mostrar/2;   // posición x donde comienzo a mostrar imagen de cámara
    j2 = ancho_screen/2 + wframe_mostrar/2;  
    i_inicial_frame = ip_inicial-hframe_mostrar/2;        
    j_inicial_frame = 0;      
    

    uint16_t conta_ejemplo=0;
    uint8_t nejemplo=1;
    
    reset_imagen(im_ajuste,ancho_screen,alto_screen); 
    Mat imsimbolos;
    imsimbolos=imread("D:/control2.jpg");
   
    for (i=0; i<(hframe_mostrar); i++)
        for(j=0;j<ancho_screen;j++){
            im_ajuste.at<Vec3b>(i, j) = Vec3b(100,100,100);
        }
    
    for (i=0;i<400;i++)
        for(j=0;j<680;j++){
            im_ajuste.at<Vec3b>(i+alto_screen/2-200+OFFSET_CONTROL, j+ancho_screen/2-340) = imsimbolos.at<Vec3b>(i, j);
        }
    
    
    contorno(pv_contorno, ip_inicial, jp_inicial, im_ajuste, ancho_screen, alto_screen, im_control, ancho_control, alto_control, pvectorx, pvectory);     
    
    ncuadros_fps=0;
    tstart = clock();  
    


    while(1){
  
        if (modo_camara) {
            cap >> frame;
            flip(frame, frame, +1);
        }
        else {
            conta_ejemplo++;
            if (conta_ejemplo==40) {
                conta_ejemplo=0; nejemplo++;
            }
            if (nejemplo>5) nejemplo=1;
            switch(nejemplo){
                case 1: frame=imread("D:/capturas/comandos/comando_ej1.jpg"); break;
                case 2: frame=imread("D:/capturas/comandos/0cap_centro.jpg"); break;
                case 3: frame=imread("D:/capturas/comandos/comando_ej4.jpg"); break;
                case 4: frame=imread("D:/capturas/comandos/comando_ej3.jpg"); break;
                case 5:  frame=imread("D:/capturas/comandos/comando_ej2.jpg"); break;
            }            
        }
         
        for (i=0; i<alto_control; i++){
            for (j=0; j<ancho_control; j++)
                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = im_control.at<Vec3b>(i,j);
        }         
      
        roi = frame.clone();  // Para evitar que cambios en frame, se vean reflejados en ROI
        roi = roi( Rect(xi_roi,yi_roi,w_roi,h_roi) ); // Selecciono región de interes 
        resize(roi, roi, Size(),escala_im,escala_im, INTER_CUBIC);                    
        rectangle(frame, Point(xi_roi+10, yi_roi+10), Point(xi_roi+10+w_roi-20, yi_roi+10+h_roi-20), CV_RGB(r,g,b), 3);  // Dibujo rectángulo 
        matColor2negativo(roi, pdataim3, wimg, himg);

        mapadecentros_prueba( imCONV2, pdataim3, pMAPA3, pFX2, pFY2, pFXX2, pFYY2, pFXY2, wimg, himg, ph_gauss1, ph_gauss2, pd1, pd1n, pp, ppn, pd2, rmin, rmax, &i_max_MAPA, &j_max_MAPA, &max_MAPA);
   
        i_max_MAPA = i_max_MAPA/escala_im + yi_roi;
        j_max_MAPA = j_max_MAPA/escala_im + xi_roi;
                       
        pos_valida=validacion(i_max_MAPA, j_max_MAPA, max_MAPA);
        
        if (pos_valida){ 
            if  (abs(i_max_MAPA-i_max_MAPA_old)<=1) i_max_MAPA = i_max_MAPA_old;
            else
                i_max_MAPA_old = i_max_MAPA;
            if  (abs(j_max_MAPA-j_max_MAPA_old)<=1) j_max_MAPA = j_max_MAPA_old;
            else
                j_max_MAPA_old = j_max_MAPA;
                
            pvectorx=(uint16_t*)&vectorx_ajustes;
            pvectory=(uint16_t*)&vectory_ajustes;
            
            circle(im_ajuste,  Point(jp_inicial-jp_inicial+ancho_screen/2, ip_inicial-ip_inicial+alto_screen/2+OFFSET_CONTROL), 8, CV_RGB(0,255,0), 2);  
            
            forma_comando=1;          
            comando4( forma_comando, pv_contorno, im_control, use_beep, pvectorx, pvectory, im_ajuste, ancho_screen, alto_screen, i_max_MAPA, j_max_MAPA, ip_inicial, jp_inicial, fps, arduino );
            
            circle(im_ajuste,  Point(j_max_MAPA-jp_inicial+ancho_screen/2, i_max_MAPA-ip_inicial+alto_screen/2+OFFSET_CONTROL), 1, CV_RGB(255,0,0), 2);
            
            dibujo_cruz(frame,640,480,j_max_MAPA,i_max_MAPA);
        }
         
        sprintf(texto,"FPS: %.1f", fps);
        putText(frame, texto, Point(j_inicial_frame+5, i_inicial_frame+30), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);       
         
        if (forma_comando==1)
            for (i=1;i<=4;i++)
                circle(im_ajuste,  Point(vectorx_ajustes[i]-jp_inicial+ancho_screen/2, vectory_ajustes[i]-ip_inicial+alto_screen/2+OFFSET_CONTROL), 1, CV_RGB(255,255,0), 2);  // Dibujo rectángulo 
        
for (i = i1; i< i2; i++){
    for (j = j1 ; j < j2; j++){
        im_ajuste.at<Vec3b>(i, j) = frame.at<Vec3b>( i-i1+i_inicial_frame, j-j1+j_inicial_frame);
    }
}  
        
        imshow("ISO_TRACKER",im_ajuste);
        
        tecla = waitKey(1);
        if ( (tecla == 27) || (tecla == 13) ) {  // tecla escape o enter
            salir_de_programa=true;
            return 0;
        }
        
        ncuadros_fps++;
        if (ncuadros_fps>=15){
            ncuadros_fps=0;
            tend = clock();
            dif = tend-tstart;
            fps = (1000*15)/dif;  
            tstart = clock();  
        } 
   }
        
    waitKey(0);             
    return 0;
}



