


#include "comandos.h"
#include "defs_globales.h"
#include <time.h>

void contorno(float *v_contorno, uint16_t ip_inicial, uint16_t jp_inicial, Mat& im_ajuste, uint16_t ancho_screen, uint16_t alto_screen, Mat& im_control, uint16_t ancho_control, uint16_t alto_control, uint16_t *fp_vxajustes, uint16_t *fp_vyajustes)
{ 
    const double pi = 3.1415926535897;
      
    float fase, im, re;
    
    uint16_t i,j;             

    //---------------------------------------------------------        
    uint16_t x1,x2,x3,x4,y1,y2,y3,y4;
    uint16_t x,y;
    
    float fase_der_circ1, fase_abajo_circ1, fase_izq_circ2, fase_arr_circ2, fase_izq_circ3, fase_abajo_circ3, fase_arr_circ4, fase_der_circ4;
    float r;
    float xc1a, xc1b, xc2a, xc2b, xc3a, xc3b, xc4a, xc4b;
    float yc1a, yc1b, yc2a, yc2b, yc3a, yc3b, yc4a, yc4b;
    float mr_up, mr_down, br_up, br_down;
    float fase_rizq, fase_rder;
    
    char texto[50];

    x1=*(fp_vxajustes+1); x2=*(fp_vxajustes+2); x3=*(fp_vxajustes+3); x4=*(fp_vxajustes+4);  
    y1=*(fp_vyajustes+1); y2=*(fp_vyajustes+2); y3=*(fp_vyajustes+3); y4=*(fp_vyajustes+4); 


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


    mr_up = (yc3b-yc1a)/(xc3b-xc1a);
    mr_down = (yc2a-yc4b)/(xc2a-xc4b);
    br_up = yc3b-mr_up*xc3b;
    br_down = yc2a-mr_down*xc2a;


    im = ip_inicial-( y1-offset_comando*sin((90+OFFSET_FASE)*pi/180) );
    re = x1+offset_comando*cos((90+OFFSET_FASE)*pi/180)-jp_inicial;
    fase_der_circ1 = fasegrados(im,re);    
    im = ip_inicial-(y1-offset_comando*sin((180-OFFSET_FASE)*pi/180));
    re = x1+offset_comando*cos((180-OFFSET_FASE)*pi/180)-jp_inicial;
    fase_abajo_circ1 = fasegrados(im,re);
    
    im = ip_inicial-( y4-offset_comando*sin((180+OFFSET_FASE)*pi/180) );
    re = x4+offset_comando*cos((180+OFFSET_FASE)*pi/180)-jp_inicial;
    fase_arr_circ4 = fasegrados(im,re);    
    im = ip_inicial-(y4-offset_comando*sin((270-OFFSET_FASE)*pi/180));
    re = x4+offset_comando*cos((270-OFFSET_FASE)*pi/180)-jp_inicial;
    fase_der_circ4 = fasegrados(im,re);

    im = ip_inicial-( y2-offset_comando*sin((270+OFFSET_FASE)*pi/180) );
    re = x2+offset_comando*cos((270+OFFSET_FASE)*pi/180)-jp_inicial;
    fase_izq_circ2 = fasegrados(im,re);    
    im = ip_inicial-(y2-offset_comando*sin((360-OFFSET_FASE)*pi/180));
    re = x2+offset_comando*cos((360-OFFSET_FASE)*pi/180)-jp_inicial;
    fase_arr_circ2 = fasegrados(im,re);

    im = ip_inicial-( y3-offset_comando*sin((0+OFFSET_FASE)*pi/180) );
    re = x3+offset_comando*cos((0+OFFSET_FASE)*pi/180)-jp_inicial;
    fase_abajo_circ3 = fasegrados(im,re);    
    im = ip_inicial-(y3-offset_comando*sin((90-OFFSET_FASE)*pi/180));
    re = x3+offset_comando*cos((90-OFFSET_FASE)*pi/180)-jp_inicial;
    fase_izq_circ3 = fasegrados(im,re);    
    
    im = yc4a-yc1b; re = xc1b-xc4a;
    fase_rizq = fasegrados(im,re);
    im = yc2b-yc3a; re = xc3a-xc2b;
    fase_rder = fasegrados(im,re);
    
    

    
    
    double k;
    double R;    
    float fase_circulo;
    const float epsilon_circulo=2;
    float fase_aux;
    boolean seguir;
    uint16_t q=0;;

    for(fase=0; fase<=360.1; fase=fase+0.1){ 
        if ( (fase>=fase_abajo_circ3) && (fase<fase_izq_circ3) ) {    
            seguir=true;
            fase_circulo=0;
            while ( (seguir) && (fase_circulo<90) ) {
                x=x3+offset_comando*cos(fase_circulo*pi/180);
                y=y3-offset_comando*sin(fase_circulo*pi/180); 
                im=ip_inicial-y;
                re=x-jp_inicial;
                fase_aux=fasegrados(im,re);               
                if ((fase_aux>(fase-epsilon_circulo)) && (fase_aux<(fase+epsilon_circulo)) )
                    seguir=false;      
                fase_circulo=fase_circulo+0.1;  
            }  
            R = sqrt( (x-jp_inicial)*(x-jp_inicial)+(y-ip_inicial)*(y-ip_inicial) );    
        }
        else if ( (fase>=fase_izq_circ3) && (fase<fase_der_circ1) ) {    
            R = ip_inicial-br_up-mr_up*jp_inicial;
            R = R/( mr_up*cos(fase*pi/180)+sin(fase*pi/180) );   
        }         
        else if ( (fase>=fase_der_circ1) && (fase<fase_abajo_circ1) ) {
            seguir=true;
            fase_circulo=90;
            while ( (seguir) && (fase_circulo<180) ) {
                x=x1+offset_comando*cos(fase_circulo*pi/180);
                y=y1-offset_comando*sin(fase_circulo*pi/180); 
                im=ip_inicial-y;
                re=x-jp_inicial;
                fase_aux=fasegrados(im,re);               
                if ((fase_aux>(fase-epsilon_circulo)) && (fase_aux<(fase+epsilon_circulo)) )
                    seguir=false;
                
                fase_circulo=fase_circulo+0.01;               
            }   
            R = sqrt( (x-jp_inicial)*(x-jp_inicial)+(y-ip_inicial)*(y-ip_inicial) );
        }       
        else if ( (fase>=fase_abajo_circ1)&&(fase<fase_arr_circ4) ){
            k = sin(fase_rizq*pi/180)/cos(fase_rizq*pi/180);
            R = yc4a-k*jp_inicial+k*xc4a-ip_inicial;
            R = R/( k*cos(fase*pi/180)- sin(fase*pi/180) );     
        }
        else if ( (fase>=fase_arr_circ4) && (fase<fase_der_circ4) ) {    
            seguir=true;
            fase_circulo=180;
            while ( (seguir) && (fase_circulo<270) ) {
                x=x4+offset_comando*cos(fase_circulo*pi/180);
                y=y4-offset_comando*sin(fase_circulo*pi/180); 
                im=ip_inicial-y;
                re=x-jp_inicial;
                fase_aux=fasegrados(im,re);               
                if ((fase_aux>(fase-epsilon_circulo)) && (fase_aux<(fase+epsilon_circulo)) )
                    seguir=false;      
                fase_circulo=fase_circulo+0.1;  
            }  
            R = sqrt( (x-jp_inicial)*(x-jp_inicial)+(y-ip_inicial)*(y-ip_inicial) );   
        }
        else if ( (fase>=fase_der_circ4) && (fase<fase_izq_circ2) ) {    
            R = ip_inicial-br_down-mr_down*jp_inicial;
            R = R/( mr_down*cos(fase*pi/180)+sin(fase*pi/180) );   
        }         
        else if ( (fase>=fase_izq_circ2) && (fase<fase_arr_circ2) ) {    
            seguir=true;
            fase_circulo=270;
            while ( (seguir) && (fase_circulo<360) ) {
                x=x2+offset_comando*cos(fase_circulo*pi/180);
                y=y2-offset_comando*sin(fase_circulo*pi/180); 
                im=ip_inicial-y;
                re=x-jp_inicial;
                fase_aux=fasegrados(im,re);               
                if ((fase_aux>(fase-epsilon_circulo)) && (fase_aux<(fase+epsilon_circulo)) )
                    seguir=false;      
                fase_circulo=fase_circulo+0.1;  
            }  
            R = sqrt( (x-jp_inicial)*(x-jp_inicial)+(y-ip_inicial)*(y-ip_inicial) );   
        }         
        else if ( ( (fase>=fase_arr_circ2)&&(fase<=360) ) || (fase<fase_abajo_circ3)  ){
            k = sin(fase_rder*pi/180)/cos(fase_rder*pi/180);
            R = yc2b-k*jp_inicial+k*xc2b-ip_inicial;
            R = R/( k*cos(fase*pi/180)- sin(fase*pi/180) ); 
            
        }
        *(v_contorno+q)=R;
        q++;
    }

//--------------------------
float mrf1, mrf2, mrf3, mrf4, mrf5, mrf6;
float brf1, brf2, brf3, brf4, brf5, brf6;
float fase_rf1, fase_rf2, fase_rf3, fase_rf4, fase_rf5, fase_rf6;
float ri;
float xf1, xf2, xf3, xf4, xf5, xf6;
float yf1, yf2, yf3, yf4, yf5, yf6;
float fasep1, fasep2, fasep3, fasep4;
float fase1, fase2, fase3, fase4, fase5, fase6, fase7, fase8, faseaux;



for (i=0; i<alto_control; i++){
for (j=0; j<ancho_control; j++)
    im_control.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
}   
    
for (j=0; j<ancho_control; j++){
    im_control.at<Vec3b>(0, j) = Vec3b(255, 255, 0);
    im_control.at<Vec3b>(alto_control-1, j) = Vec3b(255, 255, 0);
}
for (i=0; i<alto_control; i++){
    im_control.at<Vec3b>(i, 0) = Vec3b(255, 255, 0);
    im_control.at<Vec3b>(i, ancho_control-1) = Vec3b(255, 255, 0);
} 

im = ip_inicial-*(fp_vyajustes+1);
re = *(fp_vxajustes+1)-jp_inicial;
fasep1=fasegrados(im, re);
im = ip_inicial-*(fp_vyajustes+2);
re = *(fp_vxajustes+2)-jp_inicial;
fasep2=fasegrados(im, re);
im = ip_inicial-*(fp_vyajustes+3);
re = *(fp_vxajustes+3)-jp_inicial;
fasep3=fasegrados(im, re);
im = ip_inicial-*(fp_vyajustes+4);
re = *(fp_vxajustes+4)-jp_inicial;
fasep4=fasegrados(im, re);    
fase1 = fasep3+20;
fase2 = fasep1-20;
fase3 = fasep1 + (fasep4-fasep1)/2;
fase4 = fasep4+20;
fase5 = fasep2-20;
if (fase5<0) fase5=fase5+360;       
fase6 = fasep3-abs(360-fasep2+fasep3)/2;
if (fase6<0) fase6=fase6+360;

R = *(  v_contorno+uint16_t(ceil(fase1*10)) );
xf1 = jp_inicial+R*cos(fase1*pi/180);
yf1 = ip_inicial-R*sin(fase1*pi/180); 
R = *(  v_contorno+uint16_t(ceil(fase2*10)) );
xf2 = jp_inicial+R*cos(fase2*pi/180);
yf2 = ip_inicial-R*sin(fase2*pi/180); 
R = *(  v_contorno+uint16_t(ceil(fase3*10)) );
xf3 = jp_inicial+R*cos(fase3*pi/180);
yf3 = ip_inicial-R*sin(fase3*pi/180); 
R = ip_inicial-br_down-mr_down*jp_inicial;
R = R/( mr_down*cos(fase4*pi/180)+sin(fase4*pi/180) );
xf4 = jp_inicial+R*cos(fase4*pi/180);
yf4 = ip_inicial-R*sin(fase4*pi/180); 
R = *(  v_contorno+uint16_t(ceil(fase5*10)) );
xf5 = jp_inicial+R*cos(fase5*pi/180);
yf5 = ip_inicial-R*sin(fase5*pi/180); 
R = *(  v_contorno+uint16_t(ceil(fase6*10)) );
xf6 = jp_inicial+R*cos(fase6*pi/180);
yf6 = ip_inicial-R*sin(fase6*pi/180); 
        
im = ip_inicial-yf1; re = xf1-jp_inicial;
fase_rf1 = fasegrados(im,re);
im = ip_inicial-yf2; re = xf2-jp_inicial;
fase_rf2 = fasegrados(im,re);
im = ip_inicial-yf3; re = xf3-jp_inicial;
fase_rf3 = fasegrados(im,re);
im = ip_inicial-yf4; re = xf4-jp_inicial;
fase_rf4 = fasegrados(im,re);
im = ip_inicial-yf5; re = xf5-jp_inicial;
fase_rf5 = fasegrados(im,re);
im = ip_inicial-yf6; re = xf6-jp_inicial;
fase_rf6 = fasegrados(im,re);

ri = sqrt( (xf1-jp_inicial)*(xf1-jp_inicial)+(yf1-ip_inicial)*(yf1-ip_inicial) );        
r=ri;
while(1){
    r = r+0.1;
    x = ancho_control/2+r*cos(fase_rf1*pi/180);
    y = alto_control/2-r*sin(fase_rf1*pi/180);
    if ( (x<0) || (x>ancho_control) || (y<0) || (y>alto_control) )
        break;
    else
        im_control.at<Vec3b>(y, x) = Vec3b(255, 255, 0);
}

ri = sqrt( (xf2-jp_inicial)*(xf2-jp_inicial)+(yf2-ip_inicial)*(yf2-ip_inicial) ); 
r = ri;
while(1){
    r = r+0.1;
    x = ancho_control/2+r*cos(fase_rf2*pi/180);
    y = alto_control/2-r*sin(fase_rf2*pi/180);
    if ( (x<0) || (x>ancho_control) || (y<0) || (y>alto_control) )
        break;
    else    
        im_control.at<Vec3b>(y,x) = Vec3b(255, 255, 0);
}

ri = sqrt( (xf3-jp_inicial)*(xf3-jp_inicial)+(yf3-ip_inicial)*(yf3-ip_inicial) ); 
r=ri;
while(1){
    r = r+0.1;
    x = ancho_control/2+r*cos(fase_rf3*pi/180);
    y = alto_control/2-r*sin(fase_rf3*pi/180);
    if ( (x<0) || (x>ancho_control) || (y<0) || (y>alto_control) )
        break;
    else      
        im_control.at<Vec3b>(y,x) = Vec3b(255, 255, 0);
}

ri = sqrt( (xf4-jp_inicial)*(xf4-jp_inicial)+(yf4-ip_inicial)*(yf4-ip_inicial) ); 
r = ri;
while(1){
    r = r+0.1;
    x = ancho_control/2+r*cos(fase_rf4*pi/180);
    y = alto_control/2-r*sin(fase_rf4*pi/180);
    if ( (x<0) || (x>ancho_control) || (y<0) || (y>alto_control) )
        break;
    else     
        im_control.at<Vec3b>(y,x) = Vec3b(255, 255, 0);
}

ri = sqrt( (xf5-jp_inicial)*(xf5-jp_inicial)+(yf5-ip_inicial)*(yf5-ip_inicial) ); 
r = ri;
while(1){
    r = r+0.1;
    x = ancho_control/2+r*cos(fase_rf5*pi/180);
    y = alto_control/2-r*sin(fase_rf5*pi/180);
    if ( (x<0) || (x>ancho_control) || (y<0) || (y>alto_control) )
        break;
    else 
        im_control.at<Vec3b>(y,x) = Vec3b(255, 255, 0);
}

ri = sqrt( (xf6-jp_inicial)*(xf6-jp_inicial)+(yf6-ip_inicial)*(yf6-ip_inicial) ); 
r = ri;
while(1){
    r = r+0.1;
    x = ancho_control/2+r*cos(fase_rf6*pi/180);
    y = alto_control/2-r*sin(fase_rf6*pi/180);
    if ( (x<0) || (x>ancho_control) || (y<0) || (y>alto_control) )
        break;
    else 
        im_control.at<Vec3b>(y,x) = Vec3b(255, 255, 0);
}


   
    for (r = 0; r<(yc4a-yc1b)/sin(fase_rizq*pi/180); r = r+0.1){
        x = xc4a+r*cos(fase_rizq*pi/180);
        y = yc4a-r*sin(fase_rizq*pi/180);
        im_control.at<Vec3b>(y-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }
    for (r = 0; r<(yc2b-yc3a)/sin(fase_rizq*pi/180); r = r+0.1){
        x = xc2b+r*cos(fase_rder*pi/180);
        y = yc2b-r*sin(fase_rder*pi/180);
        im_control.at<Vec3b>(y-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }
    for (x=xc1a; x<xc3b; x++){        
        im_control.at<Vec3b>(br_up+mr_up*x-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }     
    for (x=xc4b; x<xc2a; x++){        
        im_control.at<Vec3b>(br_down+mr_down*x-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }   
    for (fase=90+OFFSET_FASE; fase<(180-OFFSET_FASE); fase=fase+0.1){
        x=x1+offset_comando*cos(fase*pi/180);
        y=y1-offset_comando*sin(fase*pi/180);  
        im_control.at<Vec3b>(y-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }  
    for (fase=(180+OFFSET_FASE); fase<(270-OFFSET_FASE); fase=fase+0.1){
        x=x4+offset_comando*cos(fase*pi/180);
        y=y4-offset_comando*sin(fase*pi/180);        
        im_control.at<Vec3b>(y-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }  
    for (fase=(270+OFFSET_FASE); fase<(360-OFFSET_FASE); fase=fase+0.1){
        x=x2+offset_comando*cos(fase*pi/180);
        y=y2-offset_comando*sin(fase*pi/180);        
        im_control.at<Vec3b>(y-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }      
    for (fase=(0+OFFSET_FASE); fase<(90-OFFSET_FASE); fase=fase+0.1){
        x=x3+offset_comando*cos(fase*pi/180);
        y=y3-offset_comando*sin(fase*pi/180);        
        im_control.at<Vec3b>(y-ip_inicial+alto_control/2, x-jp_inicial+ancho_control/2) = Vec3b(255, 255, 0);
    }

//imwrite("im_control.jpg",im_control);

for (i=0; i<alto_control; i++){
    for (j=0; j<ancho_control; j++)
        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = im_control.at<Vec3b>(i,j);
}  

}

void dibujo_comando(boolean confirmado, float fase_comando, float distancia_comando, float *v_contorno, Mat& im_ajuste, 
        uint16_t ancho_screen, uint16_t alto_screen, float f1, float f2, float f3, float f4, float f5, float f6, 
        uint16_t jp_inicial, uint16_t ip_inicial )
{
    float im, re, fase, modulo, modulo_contorno;
    float imaux, reaux;
    uint16_t i,j;
    float R; 
    uint16_t x,y;
    char texto[20];
  
    for (i=0; i<alto_control; i++){
        for (j=0; j<ancho_control; j++){
            im = alto_control/2-i;
            re = j-ancho_control/2;
            fase = fasegrados(im,re);
            
            modulo = sqrt( im*im+re*re );
            modulo_contorno=*( v_contorno + uint16_t(ceil(fase*10)) );
          
            if ( (fase_comando>f1) && (fase_comando<f2) ){
                if ( (fase>(f1+0.5)) && (fase<f2) && (modulo>modulo_contorno) ){ 
                    if (confirmado)
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                    else
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                }
            }
            else if ( (fase_comando>f2) && (fase_comando<f3) ){
                if ( (fase>f2) && (fase<f3) && (modulo>modulo_contorno) ){ 
                    if (confirmado)
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                    else                    
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                }
            }
            else if ( (fase_comando>f3) && (fase_comando<f4) ){
                if ( (fase>f3) && (fase<f4) && (modulo>modulo_contorno) ){ 
                    if (confirmado)
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                    else                    
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                }
            }
            else if ( (fase_comando>f4) && (fase_comando<f5) ){
                if ( (fase>f4) && (fase<f5) && (modulo>modulo_contorno) ){ 
                    if (confirmado)
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                    else                    
                        im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                }
            } 
            else {
                if (f6>f5){
                    if ( (fase_comando>f5) && (fase_comando<f6) ){
                        if ( (fase>f5) && (fase<f6) && (modulo>modulo_contorno) ){   
                            if (confirmado)
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                            else                         
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                        }
                    } 
                    else if ( ( (fase_comando>f6) && (fase_comando<360) ) || (fase_comando<f1) ){
                        if ( ( ( (fase>f6) && (fase_comando<360) ) || (fase<f1) ) && (modulo>modulo_contorno) ){                
                            if (confirmado)
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                            else
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                        }
                    } 
                }
                else{
                    if ( ( (fase_comando>f5) && (fase_comando<360) ) || (fase_comando<f6) ){
                        if ( ( ((fase>f5) && (fase<360)) || (fase<f6) ) && (modulo>modulo_contorno) ){                
                            if (confirmado)
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                            else
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                        }
                    } 
                    else if ( (fase_comando>f6) && (fase_comando<f1) ){
                        if ( (fase>f6) && (fase<f1) && (modulo>modulo_contorno) ){
                            if (confirmado)
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(0, 255, 0);
                            else
                                im_ajuste.at<Vec3b>(i-alto_control/2+alto_screen/2+OFFSET_CONTROL, j-ancho_control/2+ancho_screen/2) = Vec3b(50, 50, 50);
                        }
                    }            
                }
            }
        }
    } 

}

void comandos(uint8_t forma_comando, float *v_contorno, Mat& im_control, boolean use_beep, uint16_t *fp_vxajustes, uint16_t *fp_vyajustes, Mat& im_ajuste, uint16_t ancho_screen, uint16_t alto_screen, uint16_t i_max_MAPA, uint16_t j_max_MAPA, uint16_t ip_inicial, uint16_t jp_inicial, float f_fps, SerialPort *serie_arduino  )
{
    
    const uint16_t ALTO_PLAFON = 220;
    const uint16_t ANCHO_PLAFON = 0.7*ancho_screen;
    const uint16_t Y1_PLAF = alto_screen/4;
    const uint16_t Y2_PLAF = alto_screen/4 + ALTO_PLAFON;
    const uint16_t X1_PLAF = ancho_screen/2-ANCHO_PLAFON/2;
    const uint16_t X2_PLAF = ancho_screen/2;
    const uint16_t X3_PLAF = ancho_screen/2+ANCHO_PLAFON/2;
    const uint16_t X0_PLAF = ancho_screen/2;
    const uint16_t Y0_PLAF = 0.8*alto_screen;

    uint16_t zmin;
  
    zmin=round(1.3*f_fps);
//            
    const double pi = 3.1415926535897;
    const uint8_t pmin=70;
  
    float pz;

    static uint8_t z1=0,z2=0,z3=0,z4=0,z5=0,z6=0,z7=0,z8=0;
    static uint16_t nz1=0, nz2=0, nz3=0, nz4=0, nz5=0, nz6=0, nz7=0, nz8=0;
    static uint16_t nite_old=0, nite=0;
    static uint8_t conta_centro=0;
    
    static uint16_t zi, zj;
    float dz;
    
    uint8_t wcuadro=100;
    
    
    char texto[50];
    
   // float fase1, fase2, fase3, fase4, fase5, fase6, fase7, fase8, faseaux;
    
    float fase, im, re;
    
    float distancia_movimiento;
    float dist_dizq1, dist_dizq2, dist_dder1, dist_dder2, dist_lizq, dist_lder, dist_sup, dist_inf;
    
    const uint16_t ang_diagonal=30;
    const uint16_t ang_lateral=40;
    const uint16_t ang_inf_sup=60;
    
    const uint8_t DIZQ1=10;
    const uint8_t DIZQ2=10;
    const uint8_t DDER1=10;
    const uint8_t DDER2=10;
    const uint8_t DSUP=10;
    const uint8_t DINF=10;    
    
    int i, j;
    
    static uint8_t comando_realizado, comando_realizado_old, comando_anterior, contador_no_movimiento, comando_movimiento_old, comando_movimiento;
        
    static boolean confirmo_comando=false;

    float fasep1, fasep2, fasep3, fasep4;
    float fase1, fase2, fase3, fase4, fase5, fase6, fase7, fase8, faseaux;
    
    float distancia_contorno;
      
    static boolean modo_off=false;
    static boolean modo_zapping=false;
    static clock_t t1,t2;
    
    im = ip_inicial-*(fp_vyajustes+1);
    re = *(fp_vxajustes+1)-jp_inicial;
    fasep1=fasegrados(im, re);
    im = ip_inicial-*(fp_vyajustes+2);
    re = *(fp_vxajustes+2)-jp_inicial;
    fasep2=fasegrados(im, re);
    im = ip_inicial-*(fp_vyajustes+3);
    re = *(fp_vxajustes+3)-jp_inicial;
    fasep3=fasegrados(im, re);
    im = ip_inicial-*(fp_vyajustes+4);
    re = *(fp_vxajustes+4)-jp_inicial;
    fasep4=fasegrados(im, re);    

    fase1 = fasep3+20;
    fase2 = fasep1-20;
    fase3 = fasep1 + (fasep4-fasep1)/2;
    fase4 = fasep4+20;
    fase5 = fasep2-20;
    if (fase5<0) fase5=fase5+360;       
    fase6 = fasep3-abs(360-fasep2+fasep3)/2;
    if (fase6<0) fase6=fase6+360;
    
    
    if (forma_comando==1){
        nite++;
        if (nite>50000) nite=0;
        
        
        im = ip_inicial-i_max_MAPA;
        re = j_max_MAPA-jp_inicial;
        fase = fasegrados(im, re);

        distancia_movimiento = sqrt( (j_max_MAPA-jp_inicial)*(j_max_MAPA-jp_inicial)+(i_max_MAPA-ip_inicial)*(i_max_MAPA-ip_inicial) );
        
        distancia_contorno = *(v_contorno+uint16_t(ceil(fase*10)));
        
        if ( (distancia_movimiento>distancia_contorno) && (fase>=fase1) && (fase<fase2) ) {

            if (nz1==0){
                nite_old=nite; nz1=1;
            }
            else
                nz1++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz1/(abs(nite-nite_old)+1);
            else
                pz=0;

            z1++;
            z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 

            if (pz>pmin) {
                confirmo_comando=true;
                nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0; 
                comando_realizado=1;
                comando_movimiento=1;
                contador_no_movimiento=0;   
            }
            else{
                confirmo_comando=false;
            }
            dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
            fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
        }
        else if ( (distancia_movimiento>distancia_contorno) && (fase>=fase2) && (fase<fase3) ) {

            z2++;
            z1=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 

            if (nz2==0){
                nite_old=nite; nz2=1;
            }
            else
                nz2++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz2/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z2>zmin){
                confirmo_comando=true;
                nz1=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0; 
                comando_realizado=2; comando_movimiento=2; contador_no_movimiento=0;
            }
            else{
                confirmo_comando=false;
            }  
            dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
            fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
        }
        else if ( (distancia_movimiento>distancia_contorno) && (fase>=fase3) && (fase<fase4) ) {
            z3++;
            z1=0; z2=0; z4=0; z5=0; z6=0; z7=0; z8=0; 

            if (nz3==0){
                nite_old=nite; nz3=1;
            }
            else
                nz3++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz3/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
                confirmo_comando=true;
                nz1=0; nz2=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0; 
                comando_realizado=3; comando_movimiento=3; contador_no_movimiento=0;
            }
            else{
                confirmo_comando=false;
            }   
            dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
            fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
        }
        else if ( (distancia_movimiento>distancia_contorno) && (fase>=fase4) && (fase<fase5) ) {
            
            z4++;

            if (nz4==0){
                nite_old=nite; nz4=1;
            }
            else
                nz4++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz4/(abs(nite-nite_old)+1);
            else
                pz=0;


            z1=0; z2=0; z3=0; z5=0; z6=0; z7=0; z8=0; 
            if (pz>pmin){
            //if (z4>zmin) {
                confirmo_comando=true;
                nz1=0; nz2=0; nz3=0; nz5=0; nz6=0; nz7=0; nz8=0;
                comando_realizado=4; comando_movimiento=4; contador_no_movimiento=0;
            }
            else{  
                confirmo_comando=false;
            }  
            dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
            fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
        }
        else
        {
            if (fase6>fase5){
                if ( (distancia_movimiento>distancia_contorno) && (fase>=fase5) && (fase<fase6) ) {
                                
                    z5++;
                    z1=0; z2=0; z3=0; z4=0; z6=0; z7=0; z8=0; 

                    if (nz5==0){
                        nite_old=nite; nz5=1;
                    }
                    else
                        nz5++;

                    if ((abs(nite-nite_old)+1)>zmin)
                        pz=100*nz5/(abs(nite-nite_old)+1);
                    else
                        pz=0;

                    if (pz>pmin){
                    //if (z5>zmin) {
                        confirmo_comando=true;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz6=0; nz7=0; nz8=0;
                        comando_realizado=5; comando_movimiento=5; contador_no_movimiento=0;
                    }
                    else{  
                        confirmo_comando=false;
                    } 
                    dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
                    fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
                } 
                else if ( (distancia_movimiento>distancia_contorno) && ( (fase>=fase6) || (fase<fase1) ) ) {
                    z6++;
                    z1=0; z2=0; z3=0; z4=0; z5=0; z7=0; z8=0;  

                    if (nz6==0){
                        nite_old=nite; nz6=1;
                    }
                    else
                        nz6++;

                    if ((abs(nite-nite_old)+1)>zmin)
                        pz=100*nz6/(abs(nite-nite_old)+1);
                    else
                        pz=0;

                    if (pz>pmin){
                    //if (z7>zmin) {
                        confirmo_comando=true;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz7=0; nz8=0;
                        comando_realizado=6; comando_movimiento=6; contador_no_movimiento=0;
                    }
                    else{
                        confirmo_comando=false;
                        //comando_realizado=0;
                        //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
                    }  
                    dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
                    fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
                }
                else {
                    comando_realizado=0;
                    
                    if (comando_realizado_old==0)
                        conta_centro++;
                    else
                        conta_centro=0;
                    
                    if (conta_centro==4){
                        conta_centro=0;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0;
                    }
                }
            }
            else{
                if ( (distancia_movimiento>distancia_contorno) && ( (fase>=fase5) || (fase<fase6) ) ) {
                                           
                    //comando_realizado=0;
                   // rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, alto_screen-wcuadro-20), Point(ancho_screen-20, alto_screen-20), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               
       
                    z5++;
                    z1=0; z2=0; z3=0; z4=0; z6=0; z7=0; z8=0; 

                    if (nz5==0){
                        nite_old=nite; nz5=1;
                    }
                    else
                        nz5++;

                    if ((abs(nite-nite_old)+1)>zmin)
                        pz=100*nz5/(abs(nite-nite_old)+1);
                    else
                        pz=0;

                    if (pz>pmin){
                    //if (z5>zmin) {
                        confirmo_comando=true;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz6=0; nz7=0; nz8=0;
                        comando_realizado=5; comando_movimiento=5; contador_no_movimiento=0;
                    }
                    else{
                        confirmo_comando=false;
                    } 
                    dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
                    fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
                } 
                else if ( (distancia_movimiento>distancia_contorno) && (fase>=fase6) && (fase<fase1) ) {
                        
                    //comando_realizado=0;
                   // rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, 20), Point(ancho_screen-20, 20+wcuadro), CV_RGB(255,255,0), 8);  // Dibujo rectángulo

                    z6++;
                    z1=0; z2=0; z3=0; z4=0; z5=0; z7=0; z8=0;  

                    if (nz6==0){
                        nite_old=nite; nz6=1;
                    }
                    else
                        nz6++;

                    if ((abs(nite-nite_old)+1)>zmin)
                        pz=100*nz6/(abs(nite-nite_old)+1);
                    else
                        pz=0;

                    if (pz>pmin){
                    //if (z7>zmin) {
                        confirmo_comando=true;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz7=0; nz8=0;
                        comando_realizado=6; comando_movimiento=6; contador_no_movimiento=0;
                    }
                    else{
                        confirmo_comando=false;
                        //comando_realizado=0;
                        //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
                    } 
                    dibujo_comando(confirmo_comando,fase,distancia_movimiento,v_contorno,im_ajuste,ancho_screen,alto_screen,
                    fase1,fase2,fase3,fase4,fase5,fase6,jp_inicial,ip_inicial);
                }  
                else {
                    comando_realizado=0;
                    
                    if (comando_realizado_old==0)
                        conta_centro++;
                    else
                        conta_centro=0;
                    
                    if (conta_centro==4){
                        conta_centro=0;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0;
                    }
                }
            }
        }
        
        
                           

//        uint16_t altura=500;
//        uint16_t ancho=500;
        
        uint16_t altura=10;
        uint16_t ancho=10;        
        switch(comando_realizado){
            case 1: 
                if ( (use_beep) && (comando_realizado!=comando_realizado_old)) { 
                    if (SetCursorPos(X2_PLAF,Y1_PLAF)){
                        mouse_event(MOUSEEVENTF_LEFTDOWN,X2_PLAF,Y1_PLAF,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP,X2_PLAF,Y1_PLAF,0,0);
                    }
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    waitKey(50);
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    
                    serie_arduino->writeSerialPort("1", 1); 
                    if (modo_off)
                        modo_off=false;
                    else
                        modo_off=true;
                    
                    modo_zapping=false;
                }
                
                break;
            case 2: 
                if ( (use_beep) && (comando_realizado!=comando_realizado_old)) {
                    if (SetCursorPos(X1_PLAF,Y1_PLAF)){
                        mouse_event(MOUSEEVENTF_LEFTDOWN,X1_PLAF,Y1_PLAF,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP,X1_PLAF,Y1_PLAF,0,0);
                    }
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    modo_zapping=false;
                    if (modo_off==false)
                        serie_arduino->writeSerialPort("2", 1);
                }              
                ; break;
            case 3: 
                if ( (use_beep) && (comando_realizado!=comando_realizado_old)) {
                    if (SetCursorPos(X1_PLAF,Y2_PLAF)){
                        mouse_event(MOUSEEVENTF_LEFTDOWN,X1_PLAF,Y2_PLAF,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP,X1_PLAF,Y2_PLAF,0,0);
                    }
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    modo_zapping=false;
                    if (modo_off==false)
                        serie_arduino->writeSerialPort("3", 1);
                }
                ; break;
            case 4: 
                if ( (use_beep) && (comando_realizado!=comando_realizado_old)) {
                    if (SetCursorPos(X2_PLAF,Y2_PLAF)){
                        mouse_event(MOUSEEVENTF_LEFTDOWN,X2_PLAF,Y2_PLAF,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP,X2_PLAF,Y2_PLAF,0,0);
                    }
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    if (modo_off==false){
                        serie_arduino->writeSerialPort("4", 1);
                        modo_zapping=true;
                        serie_arduino->writeSerialPort("6", 1);
                        waitKey(100);
                        serie_arduino->writeSerialPort("0", 1);
                        
                        t1 = clock();
                    }
                }               
                break;
            case 5: 
                if ( (use_beep) && (comando_realizado!=comando_realizado_old)) {
                    if (SetCursorPos(X3_PLAF,Y2_PLAF)){
                        mouse_event(MOUSEEVENTF_LEFTDOWN,X3_PLAF,Y2_PLAF,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP,X3_PLAF,Y2_PLAF,0,0);
                    }
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    modo_zapping=false;
                    if (modo_off==false){
                        serie_arduino->writeSerialPort("5", 1);
                        waitKey(100);
                        serie_arduino->writeSerialPort("0", 1);
                        waitKey(800);
                    }
                }
                break;
            case 6: 
                if ( (use_beep) && (comando_realizado!=comando_realizado_old)){ 
                    if (SetCursorPos(X3_PLAF,Y1_PLAF)){
                        mouse_event(MOUSEEVENTF_LEFTDOWN,X3_PLAF,Y1_PLAF,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP,X3_PLAF,Y1_PLAF,0,0);
                    }
                    Beep(FREQ_BEEP_COMANDO,TIME_BEEP_COMANDO);
                    modo_zapping=false;
                    if (modo_off==false){
                        serie_arduino->writeSerialPort("6", 1);
                        waitKey(100);
                        serie_arduino->writeSerialPort("0", 1);
                        waitKey(800);
                    }
                }               
                break;      
            default:{
                serie_arduino->writeSerialPort("0", 1);
                SetCursorPos(X0_PLAF,Y0_PLAF);}
        }
        
        


        comando_realizado_old=comando_realizado;
        
        
        if (modo_zapping==true){
            float dif;
            t2 = clock();
            dif = t2-t1;
            
            if (dif>4000){
                t1 = clock();
                serie_arduino->writeSerialPort("6", 1);
                waitKey(100);
                serie_arduino->writeSerialPort("0", 1);
                waitKey(800);
            }
        }
         
    }        
    else if (forma_comando==2){
        
        nite++;
        if (nite>50000) nite=0;

        im = ip_inicial-*(fp_vyajustes+1);
        re = *(fp_vxajustes+1)-jp_inicial;
        fase=fasegrados(im, re);
        fase3=fase-ang_diagonal+5;
        fase4=fase+5;

        im = ip_inicial-*(fp_vyajustes+2);
        re = *(fp_vxajustes+2)-jp_inicial;
        fase=fasegrados(im, re);
        fase7=fase-ang_diagonal+5;
        fase8=fase+5;
        if (fase7<0) fase7=fase+360;
        if (fase8>360) fase8=fase8-360;

        im = ip_inicial-*(fp_vyajustes+3);
        re = *(fp_vxajustes+3)-jp_inicial;
        fase=fasegrados(im, re);
        fase1=fase-5;
        fase2=fase+ang_diagonal-5;   
        if (fase1<0) fase1=fase+360;
        if (fase2>360) fase2=fase2-360;    

        im = ip_inicial-*(fp_vyajustes+4);
        re = *(fp_vxajustes+4)-jp_inicial;
        fase=fasegrados(im, re);
        fase5=fase-5;
        fase6=fase+ang_diagonal-5;    

        dist_dizq1 = sqrt( (*(fp_vxajustes+1)-jp_inicial)*(*(fp_vxajustes+1)-jp_inicial)+(*(fp_vyajustes+1)-ip_inicial)*(*(fp_vyajustes+1)-ip_inicial) );
        dist_dizq2 = sqrt( (*(fp_vxajustes+4)-jp_inicial)*(*(fp_vxajustes+4)-jp_inicial)+(*(fp_vyajustes+4)-ip_inicial)*(*(fp_vyajustes+4)-ip_inicial) );
        dist_dder1 = sqrt( (*(fp_vxajustes+3)-jp_inicial)*(*(fp_vxajustes+3)-jp_inicial)+(*(fp_vyajustes+3)-ip_inicial)*(*(fp_vyajustes+3)-ip_inicial) );
        dist_dder2 = sqrt( (*(fp_vxajustes+2)-jp_inicial)*(*(fp_vxajustes+2)-jp_inicial)+(*(fp_vyajustes+2)-ip_inicial)*(*(fp_vyajustes+2)-ip_inicial) );
        dist_lizq = abs( jp_inicial-*(fp_vxajustes+1)+jp_inicial-*(fp_vxajustes+4) )/2;   
        dist_lder = abs( jp_inicial-*(fp_vxajustes+3)+jp_inicial-*(fp_vxajustes+2) )/2;
        dist_sup = abs( ip_inicial-*(fp_vyajustes+1)+ip_inicial-*(fp_vyajustes+3) )/2;
        dist_inf = abs( ip_inicial-*(fp_vyajustes+4)+ip_inicial-*(fp_vyajustes+2) )/2;

        im = ip_inicial-i_max_MAPA;
        re = j_max_MAPA-jp_inicial;
        fase = fasegrados(im, re);

        distancia_movimiento = sqrt( (j_max_MAPA-jp_inicial)*(j_max_MAPA-jp_inicial)+(i_max_MAPA-ip_inicial)*(i_max_MAPA-ip_inicial) );
        
        sprintf(texto,"dist_dizq1 : %2.1f", dist_dizq1);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),120), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2); 
        sprintf(texto,"dist_dizq2 : %2.1f", dist_dizq2);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),150), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2); 
        sprintf(texto,"dist_dder1 : %2.1f", dist_dder1);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),180), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2); 
        sprintf(texto,"dist_dder2 : %2.1f", dist_dder2);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),210), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);  
        sprintf(texto,"dist_lizq : %2.1f", dist_lizq);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),240), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2); 
        sprintf(texto,"dist_lder : %2.1f", dist_lder);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),270), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);   
        sprintf(texto,"dist_sup : %2.1f", dist_sup);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),300), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);    
        sprintf(texto,"dist_inf : %2.1f", dist_inf);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),330), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);   
        //------------------------
        sprintf(texto,"fase1 : %2.1f", fase1);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),380), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);  
        sprintf(texto,"fase2 : %2.1f", fase2);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),410), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);   
        sprintf(texto,"fase3 : %2.1f", fase3);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),440), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);        
        sprintf(texto,"fase4 : %2.1f", fase4);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),470), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);      
        sprintf(texto,"fase5 : %2.1f", fase5);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),500), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);      
        sprintf(texto,"fase6 : %2.1f", fase6);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),530), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);  
        sprintf(texto,"fase7 : %2.1f", fase7);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),560), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);
        sprintf(texto,"fase8 : %2.1f", fase8);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),590), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);
        sprintf(texto,"distancia_movimiento : %2.1f", distancia_movimiento);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),620), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);   
        sprintf(texto,"fase : %2.1f", fase);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),650), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);           
    
        if ( (distancia_movimiento>dist_dder1) && (fase>=fase1) && (fase<fase2) ) {

            rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, 20), Point(ancho_screen-20, 20+wcuadro), CV_RGB(255,255,0), 8);  // Dibujo rectángulo

            if (nz1==0){
                nite_old=nite; nz1=1;
            }
            else
                nz1++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz1/(abs(nite-nite_old)+1);
            else
                pz=0;

            z1++;
            z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 

            if (pz>pmin) {
                nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0; 
                comando_realizado=1;
                comando_movimiento=1;
                contador_no_movimiento=0;   
            }
            else{
            }
        }
        else if ( (distancia_movimiento>dist_sup) && (fase>=fase2) && (fase<fase3) ) {

            rectangle(im_ajuste, Point(ancho_screen/2-wcuadro/2, 20), Point(ancho_screen/2+wcuadro/2, 20+wcuadro), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               
            //comando_realizado=0;
            z2++;
            z1=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 

            if (nz2==0){
                nite_old=nite; nz2=1;
            }
            else
                nz2++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz2/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z2>zmin){
                nz1=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0; 
                comando_realizado=2; comando_movimiento=2; contador_no_movimiento=0;
            }
            else{
            }   
        }
        else if ( (distancia_movimiento>dist_dizq1) && (fase>=fase3) && (fase<fase4) ) {

            rectangle(im_ajuste, Point(20, 20), Point(20+wcuadro, 20+wcuadro), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

            //comando_realizado=0;
            z3++;
            z1=0; z2=0; z4=0; z5=0; z6=0; z7=0; z8=0; 

            if (nz3==0){
                nite_old=nite; nz3=1;
            }
            else
                nz3++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz3/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z3>zmin) {
                nz1=0; nz2=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0; 
                comando_realizado=3; comando_movimiento=3; contador_no_movimiento=0;
            }
            else{
                //comando_realizado=0;
                //rectangle(im_ajuste,  Point(ancho_screen-50-10, alto_screen-50-10), Point(ancho_screen-10, alto_screen-10), CV_RGB(255,255,0), 8);  // Dibujo rectángulo 
            }   
        }
        else if ( (distancia_movimiento>dist_lder) && (fase>=fase4) && (fase<fase5) ) {
            //comando_realizado=0;
            rectangle(im_ajuste, Point(20, alto_screen/2-wcuadro/2), Point(20+wcuadro, alto_screen/2+wcuadro/2), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

            z4++;

            if (nz4==0){
                nite_old=nite; nz4=1;
            }
            else
                nz4++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz4/(abs(nite-nite_old)+1);
            else
                pz=0;


            z1=0; z2=0; z3=0; z5=0; z6=0; z7=0; z8=0; 
            if (pz>pmin){
            //if (z4>zmin) {
                nz1=0; nz2=0; nz3=0; nz5=0; nz6=0; nz7=0; nz8=0;
                comando_realizado=4; comando_movimiento=4; contador_no_movimiento=0;
            }
            else{  
            }   
        }
        else if ( (distancia_movimiento>dist_dizq2) && (fase>=fase5) && (fase<fase6) ) {
            //comando_realizado=0;
            rectangle(im_ajuste, Point(20, alto_screen-wcuadro-20), Point(20+wcuadro, alto_screen-20), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

            z5++;
            z1=0; z2=0; z3=0; z4=0; z6=0; z7=0; z8=0; 

            if (nz5==0){
                nite_old=nite; nz5=1;
            }
            else
                nz5++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz5/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z5>zmin) {
                nz1=0; nz2=0; nz3=0; nz4=0; nz6=0; nz7=0; nz8=0;
                comando_realizado=5; comando_movimiento=5; contador_no_movimiento=0;
            }
            else{  
            }   
        }                    
        else if ( (distancia_movimiento>dist_inf) && (fase>=fase6) && (fase<fase7) ) {
            //comando_realizado=0;
            rectangle(im_ajuste, Point(ancho_screen/2-wcuadro/2, alto_screen-wcuadro-20), Point(ancho_screen/2+wcuadro/2, alto_screen-20), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

            z6++;
            z1=0; z2=0; z3=0; z4=0; z5=0; z7=0; z8=0;

            if (nz6==0){
                nite_old=nite; nz6=1;
            }
            else
                nz6++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz6/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z6>zmin) {
                nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz7=0; nz8=0;
                comando_realizado=6; comando_movimiento=6; contador_no_movimiento=0;
            }
            else{
                //comando_realizado=0;
                //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
            }   
        }
        else
        {
            if (fase8>fase1){
                if ( (distancia_movimiento>dist_dder2) && (fase>=fase7) && (fase<fase8) ) {
            //comando_realizado=0;
            rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, alto_screen-wcuadro-20), Point(ancho_screen-20, alto_screen-20), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

            z7++;
            z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z8=0;  

            if (nz7==0){
                nite_old=nite; nz7=1;
            }
            else
                nz7++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz7/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z7>zmin) {
                nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz8=0;
                comando_realizado=7; comando_movimiento=7; contador_no_movimiento=0;
            }
            else{
                //comando_realizado=0;
                //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
            }   
        }
                else if ( (distancia_movimiento>dist_lizq) && ( (fase>=fase8) || (fase<fase1) ) ) {
                    //comando_realizado=0;
                    rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, alto_screen/2-wcuadro/2), Point(ancho_screen-20, alto_screen/2+wcuadro/2), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

                    z8++;
                    z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; 

                    if (nz8==0){
                        nite_old=nite; nz8=1;
                    }
                    else
                        nz8++;

                    if ((abs(nite-nite_old)+1)>zmin)
                        pz=100*nz8/(abs(nite-nite_old)+1);
                    else
                        pz=0;

                    if (pz>pmin){
                    //if (z8>zmin){
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; 
                        comando_realizado=8; comando_movimiento=8; contador_no_movimiento=0;

                    }
                    else{
                        //comando_realizado=0;
                        //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
                    }   
                } 
                else
                {
                    z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 
                    comando_realizado=0;

                    if (comando_realizado_old==0)
                        conta_centro++;

                    comando_realizado_old=comando_realizado;

                    if (conta_centro==4){
                        conta_centro=0;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0;
                    }

                    if (contador_no_movimiento<20)
                        contador_no_movimiento++;
                }
            }
            else{
                if ( (distancia_movimiento>dist_dder2) && ( (fase>=fase7) || (fase<fase8) ) ) {
            //comando_realizado=0;
            rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, alto_screen-wcuadro-20), Point(ancho_screen-20, alto_screen-20), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

            z7++;
            z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z8=0;  

            if (nz7==0){
                nite_old=nite; nz7=1;
            }
            else
                nz7++;

            if ((abs(nite-nite_old)+1)>zmin)
                pz=100*nz7/(abs(nite-nite_old)+1);
            else
                pz=0;

            if (pz>pmin){
            //if (z7>zmin) {
                nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz8=0;
                comando_realizado=7; comando_movimiento=7; contador_no_movimiento=0;
            }
            else{
                //comando_realizado=0;
                //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
            }   
        }
                else if ( (distancia_movimiento>dist_lizq) &&  (fase>=fase8) && (fase<fase1)  ) {
                    //comando_realizado=0;
                    rectangle(im_ajuste, Point(ancho_screen-wcuadro-20, alto_screen/2-wcuadro/2), Point(ancho_screen-20, alto_screen/2+wcuadro/2), CV_RGB(255,255,0), 8);  // Dibujo rectángulo               

                    z8++;
                    z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; 

                    if (nz8==0){
                        nite_old=nite; nz8=1;
                    }
                    else
                        nz8++;

                    if ((abs(nite-nite_old)+1)>zmin)
                        pz=100*nz8/(abs(nite-nite_old)+1);
                    else
                        pz=0;

                    if (pz>pmin){
                    //if (z8>zmin){
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; 
                        comando_realizado=8; comando_movimiento=8; contador_no_movimiento=0;

                    }
                    else{
                        //comando_realizado=0;
                        //rectangle(im_ajuste,  Point(ancho_screen-50-10, 30), Point(ancho_screen-10, 30+50), CV_RGB(255,255,0), 8);  // Dibujo rectángulo  
                    }   
                } 
                else
                {
                    z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 
                    comando_realizado=0;

                    if (comando_realizado_old==0)
                        conta_centro++;

                    comando_realizado_old=comando_realizado;

                    if (conta_centro==4){
                        conta_centro=0;
                        nz1=0; nz2=0; nz3=0; nz4=0; nz5=0; nz6=0; nz7=0; nz8=0;
                    }

                    if (contador_no_movimiento<20)
                        contador_no_movimiento++;
                }        
            }
        }

        uint16_t altura=500;
        uint16_t ancho=500;
        switch(comando_realizado){
            case 1: 
                serie_arduino->writeSerialPort("7", 1);
                for (i=1; i<altura; i++){
                    for (j=(ancho_screen-ancho); j<ancho_screen; j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
                ; break;
            case 2: 
                serie_arduino->writeSerialPort("8", 1);
                for (i=1; i<altura; i++){
                    for (j=(ancho_screen/2-ancho/2); j<(ancho_screen/2+ancho/2); j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
             //   z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 
                break;
            case 3: 
                serie_arduino->writeSerialPort("1", 1);
                for (i=1; i<altura; i++){
                    for (j=1; j<ancho; j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
                ; break;
            case 4: 
                serie_arduino->writeSerialPort("2", 1);
                for (i=(alto_screen/2-altura/2); i<(alto_screen/2+altura/2); i++){
                    for (j=1; j<ancho; j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
              //  z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 
                break;
            case 5: 
                serie_arduino->writeSerialPort("3", 1);
                for (i=(alto_screen-altura); i<(alto_screen); i++){
                    for (j=1; j<ancho; j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
                ; break;
            case 6: 
                serie_arduino->writeSerialPort("4", 1);
                for (i=(alto_screen-altura); i<(alto_screen); i++){
                    for (j=(ancho_screen/2-ancho/2); j<(ancho_screen/2+ancho/2); j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
              //  z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 
                break;
            case 7: 
                serie_arduino->writeSerialPort("5", 1);
                for (i=(alto_screen-altura); i<(alto_screen); i++){
                    for (j=(ancho_screen-ancho); j<ancho_screen; j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
                break;
            case 8: 
                serie_arduino->writeSerialPort("6", 1);
                for (i=(alto_screen/2-altura/2); i<(alto_screen/2+altura/2); i++){
                    for (j=(ancho_screen-ancho); j<ancho_screen; j++)
                        im_ajuste.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                }
              //  z1=0; z2=0; z3=0; z4=0; z5=0; z6=0; z7=0; z8=0; 
                break;      
            default:
                serie_arduino->writeSerialPort("0", 1);
        }

        sprintf(texto,"comando_realizado : %d", comando_realizado);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),850), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);  
        sprintf(texto,"pz : %2.1f", pz);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),880), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2); 
        sprintf(texto,"nz8 : %d", nz8);
        putText(im_ajuste, texto, Point(round(ancho_screen/2),910), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,255,0), 2);      
    }
    
}

float fasegrados(float im, float re){
    
    float fase;
    const double pi = 3.1415926535897;

    if ( (re==0) && (im>0) )  fase=pi/2;
    else if ( (re==0) && (im<0) ) fase = 3*pi/2;
    else if ( (im==0) && (re<0) ) fase = pi;
    else if ( (im==0) && (re>0) ) fase = 0;
    else if ( (im==0) && (re==0) ) fase = 0;
    else if ( (re>0) && (im>0)  ) fase = atan(im/re); // 1er cuadrante
    else if ( (re<0) && (im>0)  ) fase = atan(im/re)+pi; // 2do cuadrante
    else if ( (re<0) && (im<0)  ) { // 3er cuadrante
        fase = atan(im/re)-pi; 
        fase = 2*pi+fase; // hago positiva la fase
    }
    else if ( (re>0) && (im<0)  ) { // 4to cuadrante
        fase = atan(im/re); 
        fase = 2*pi+fase; // hago positiva la fase
    }
    fase=fase*180/pi;

    return fase;
}
    
