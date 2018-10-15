/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LIB_ISOPHOTES.h
 * Author: Cristian
 *
 * Created on 2 de julio de 2018, 16:03
 */

#include <stdint.h> 

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


#ifndef LIB_ISOPHOTES_H
#define LIB_ISOPHOTES_H

void conv2d_prueba( float *fp_data, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel);

void mapadecentros_prueba( Mat& imCONV, float *fp_im_src, float *fp_MAPA, float *fp_FX, float *fp_FY, float *fp_FXX, float *fp_FYY, float *fp_FXY, 
     uint16_t wim, uint16_t him, float *fp_ph_gauss1, float *fp_ph_gauss2, float *fp_pd1, float *fp_pd1n, float *fp_pp, float *fp_ppn, float *fp_pd2, 
     uint16_t rmin, uint16_t rmax, uint16_t *fp_imax, uint16_t *fp_jmax, float *max_MAPA  );

void conv2d_xcolumnafila_prueba( float *fp_im_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel_cols, float *fp_kernel_rows);


//void mapadecentros2( float *pdataim, float *pMAPA, float *pFX, float *pFY, float *pFXX, float *pFYY, float *pFXY, uint16_t wimg, uint16_t himg, float *ph_gauss1, float *ph_gauss2, float *pd1, float *pd1n, float *pp, float *ppn, float *pd2, float *rmin, rmax, &i_max_MAPA, &j_max_MAPA);


void dibujo_cruz(Mat& fp_im, uint16_t wim, uint16_t him, uint16_t posx, uint16_t posy);

void conv2d( float *fp_data_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel);

void findmax( float *fp_data, uint16_t wim, uint16_t him, uint16_t *fp_imax, uint16_t *fp_jmax, float *fp_max );
    
//void delay(int secs);
    
    
bool validacion(uint16_t imax, uint16_t jmax, float maxMAPA);


void findmax( float *fp_data, uint16_t wim, uint16_t him, uint16_t *fp_imax, uint16_t *fp_jmax, float *fp_max);


void frgb565_to_rgb(const char* pfilename, float* fpdata, Mat *pim_out);
void conv2d_xcolumnafila( float *fp_im_src, float *fp_data_dst, Mat& fp_im_dst, uint16_t wim, uint16_t him, uint8_t wk, float *fp_kernel_cols, float *fp_kernel_rows, float *fp_resconv_aux );

void mat2float(Mat& fp_im_src, float *fp_dst_data, uint16_t wim, uint16_t him);
void mat2negativo(float *fp_src_data, float *fp_dst_data, uint16_t wim, uint16_t him);

void matColor2negativo(Mat& fp_im_src, float *fp_dst_data, uint16_t wim, uint16_t him);

void float2mat(float *fp_src_data, Mat& fp_im_dst, uint16_t wim, uint16_t him);

void mapadecentros( float *fp_FX, float *fp_FY, float *fp_FXX, float *fp_FYY, float *fp_FXY,  uint16_t wim, uint16_t him, uint16_t rmin, uint16_t rmax,
                    float *fp_MAPA, Mat& fp_im_mapa, uint16_t *fp_imax, uint16_t *fp_jmax );



#endif /* LIB_ISOPHOTES_H */

