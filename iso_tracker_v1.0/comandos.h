
#include <stdint.h> 

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "SerialPort.h"

using namespace std;
using namespace cv;


#ifndef COMANDOS_H
#define COMANDOS_H


void dibujo_comando(boolean confirmado, float fase_comando, float distancia_comando, float *v_contorno, 
     Mat& im_ajuste, uint16_t ancho_screen, uint16_t alto_screen, float f1, float f2, float f3, float f4, 
        float f5, float f6, uint16_t jp_inicial, uint16_t ip_inicial );
void contorno(float *v_contorno, uint16_t ip_inicial, uint16_t jp_inicial, Mat& im_ajuste, uint16_t ancho_screen, uint16_t alto_screen, Mat& im_control, uint16_t ancho_control, uint16_t alto_control, uint16_t *fp_vxajustes, uint16_t *fp_vyajustes);
void comandos(uint8_t forma_comando,  float *v_contorno, Mat& im_control, boolean use_beep, uint16_t *fp_vxajustes, uint16_t *fp_vyajustes, Mat& im_ajuste, uint16_t ancho_screen, uint16_t alto_screen, uint16_t i_max_MAPA, uint16_t j_max_MAPA, uint16_t ip_inicial, uint16_t jp_inicial, float f_fps, SerialPort *serie_arduino  );

float fasegrados(float im, float re);


#endif