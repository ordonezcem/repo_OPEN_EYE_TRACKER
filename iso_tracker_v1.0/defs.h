/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "defs_globales.h"
/* 
 * File:   definiciones.h
 * Author: Cristian
 *
 * Created on 4 de septiembre de 2018, 12:03
 */

#ifndef DEFINICIONES_H
#define DEFINICIONES_H


int ancho_screen = GetSystemMetrics(SM_CXSCREEN);
int alto_screen = GetSystemMetrics(SM_CYSCREEN); 


    Mat im_control(alto_control,ancho_control,CV_8UC3);

    const uint16_t WFRAME = 640;
    const uint16_t HFRAME = 480;    
    uint16_t wimg_i = 200;  // en cap1.jpg la pupila tiene un diametro de 64
    uint16_t himg_i = 250;  // en cap1.jpg la pupila tiene un diametro de 31

    float escala_im=0.5; 
    

    uint16_t w_roi = wimg_i ;
    uint16_t h_roi = himg_i ;
    uint16_t xi_roi = WFRAME/2 - wimg_i/2 + 1;
    uint16_t yi_roi = HFRAME/2 - h_roi/2 + 45;

    uint16_t wimg = wimg_i*escala_im;
    uint16_t himg = himg_i*escala_im;
    
    float p[7] = { 0.004711, 0.069321, 0.245410, 0.361117, 0.245410, 0.069321, 0.004711 };
    float pn[7] = { -0.004711, -0.069321, -0.245410, -0.361117, -0.245410, -0.069321, -0.004711 };
    float d1[7] = { 0.018708, 0.125376, 0.193091, 0.000000, -0.193091, -0.125376, -0.018708 };
    float d1n[7] = { -0.018708, -0.125376, -0.193091, 0.000000, 0.193091, 0.125376, 0.018708 };
    float d2[7] = { 0.055336, 0.137778, -0.056554, -0.273118, -0.056554,  0.137778,  0.055336 };
    
    float h_gauss1[5] = { 0.160945,	0.218261,	0.241587,	0.218261,	0.160945 };    

    float h_gauss2[81] = {
                    0.0034,    0.0039,    0.0043,    0.0045,    0.0046,    0.0045,    0.0043,    0.0039,    0.0034,
                    0.0039,    0.0044,    0.0049,    0.0052,    0.0053,    0.0052,    0.0049,    0.0044,    0.0039,
                    0.0043,    0.0049,    0.0054,    0.0058,    0.0059,    0.0058,    0.0054,    0.0049,    0.0043,
                    0.0045,    0.0052,    0.0058,    0.0061,    0.0062,    0.0061,    0.0058,    0.0052,    0.0045,
                    0.0046,    0.0053,    0.0059,    0.0062,    0.0064,    0.0062,    0.0059,    0.0053,    0.0046,
                    0.0045,    0.0052,    0.0058,    0.0061,    0.0062,    0.0061,    0.0058,    0.0052,    0.0045,
                    0.0043,    0.0049,    0.0054,    0.0058,    0.0059,    0.0058,    0.0054,    0.0049,    0.0043,
                    0.0039,    0.0044,    0.0049,    0.0052,    0.0053,    0.0052,    0.0049,    0.0044,    0.0039,
                    0.0034,    0.0039,    0.0043,    0.0045,    0.0046,    0.0045,    0.0043,    0.0039,    0.0034 
    };
      
    
    Mat imCONV(himg, wimg, CV_8UC1);
    Mat im_MAPA(himg, wimg, CV_8UC1);
    Mat frame;
    Mat roi;
    Mat imagen_emoji;

   
  
    float *pdataim = new float[himg*wimg];
    float *pdataim2 = new float[himg*wimg];

    float *pFX = new float[himg*wimg];
    float *pFXX = new float[himg*wimg];
    float *pFY = new float[himg*wimg];
    float *pFYY = new float[himg*wimg];
    float *pFXY = new float[himg*wimg];
    float *pMAPA = new float[himg*wimg];
    float *pMAPA2 = new float[himg*wimg];
    
    float *presconv_aux = new float[himg*wimg];
    
 
    float *pd1, *pd2;
    float *pd1n;
    float *ppn;
    float *pp;
    float *ph_gauss1, *ph_gauss2;
 
    
    int i, j, c, px1, px2;
    uint16_t i_max_MAPA,  j_max_MAPA, i_max_MAPA_old, j_max_MAPA_old, rmin, rmax, rmin2, rmax2;
    float auxf;
    char filename[200];
    char nventana[50];
         

 
    clock_t tstart, tstart2, tend, tend2;
    float dif, fps=20;
    char texto[50];
    char ventana[50];

    int k=1;
    
    float escala=3.5;
    

    uint16_t nsamples=63;
    
    uint16_t detecciones[10];
    

    uint8_t r, g, b;
    
    uint16_t icero; 
    uint16_t jcero;
    
    uint16_t det=0, nodet=0, rmin_inicial, rmax_inicial, cambio_radios=0;
    float dist;
    bool ajustar=true;
    float max_MAPA, max_ajuste;
    float ip,jp;

    float distmax;
    uint16_t cantidad_det;
  
    
    boolean mover_mouse=false;
    boolean mover_izquierda=false;
    boolean mover_derecha=false;
    boolean mover_arriba=false;
    boolean mover_abajo=false;
    
    uint8_t nmovimiento=0;

    uint16_t posx_mouse, posy_mouse;
    
    
    char incomingData[10];
    char* portName = "\\\\.\\COM4";
    
    //Arduino SerialPort object
    SerialPort *arduino;
    
    uint16_t ancho_contorno=18, alto_contorno = ancho_contorno*11/16;
    //uint16_t ancho_contorno=60, alto_contorno = ancho_contorno*9/16;
    
    boolean posicionok;
    
    boolean usar_calibracion=true;
    
    boolean iniciar=false;
    boolean salir_de_programa=false;
    int tecla;

#endif /* DEFINICIONES_H */

