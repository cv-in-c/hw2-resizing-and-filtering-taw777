#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    int a,b;
    a = round(x);
    b = round(y);
   /* int i,j;
    for (i=0;i<im.w;i++){                                           //first loop for the columns

        im.data[i*c]=im.data[i];    

        for (j=0;j<im.h*im.c;j++)                   
                im.data[j * im.w * c * i]=im.data[i * j * im.w];    //second loop for rows
          
    }*/
   /* int m,k,n,s,t;
    for (p=0;p<im.h)
    for (k=0;k<im.w*im.h*im.c;i++)
        m = k/c;
        n = (k+c)/c; 
        s = m * im.w;
        t = n * im.w;

            if (k-m <= n-k){
                if(k-m<=)
            }
            

            im.data[k]=im.data[m];
            else if (k-m>n-k)
            im.data[k]=im.data[n];


  */  return get_pixel(im , a , b ,c);
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    int i,j,k;
    float x_scale,y_scale,new_x,new_y;
    image new = make_image(w,h,im.c);
    for(i=0;i<w;i++)
        for(j=0;j<h;j++){ 
            for(k=0;k<im.c;k++){
             x_scale = (float)im.w/w;        //scaling factors in x and y
             y_scale = (float)im.h/h;
            
             new_x = x_scale*i + 0.5*x_scale - 0.5;
             new_y = y_scale*j + 0.5*y_scale - 0.5;
                
                new.data[i + j*w + k*h*w] = nn_interpolate(im,new_x,new_y,k);       //Assigning pixel value to the new coordinates
            }
        }    


    

    
    return new;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    float d1,d2,d3,d4,V1,V2,V3,V4;
    
    if(round(x)>x&&round(y)>y){
    d2 = (round(x)-x);
    d1 = (1-d2); 
    d4 = round(y)-y;
    d3 = 1-d4;
    V1 = get_pixel(im, (round(x)-1), (round(y)-1), c);
    V2 = get_pixel(im,  round(x),    (round(y)-1), c);
    V3 = get_pixel(im, (round(x)-1),  round(y),    c);
    V4 = get_pixel(im,  round(x),     round(y),    c);

    }
    if(round(x)<x&&round(y)>y){
    d1 = (x-round(x));
    d2 = (1-d1); 
    d4 = round(y)-y;
    d3 = 1-d4;
    V1 = get_pixel(im,  round(x),     (round(y)-1), c);
    V2 = get_pixel(im, (round(x)+1),  (round(y)-1), c);
    V3 = get_pixel(im,  round(x),      round(y),    c);
    V4 = get_pixel(im, (round(x)+1),   round(y),    c);

    }
    if(round(x)>x&&round(y)<y){
    d2 = (round(x)-x);
    d1 = (1-d2); 
    d3 = y-round(y);
    d4 = 1-d3;
    V1 = get_pixel(im, (round(x)-1),  round(y), c);
    V2 = get_pixel(im,  round(x),     round(y), c);
    V3 = get_pixel(im, (round(x)-1),  round(y)+1,    c);
    V4 = get_pixel(im,  round(x),     round(y)+1,    c);

    }
    if(round(x)<x&&round(y)<y){
    d1 = (x-round(x));
    d2 = (1-d1); 
    d3 = y-round(y);
    d4 = 1-d3;
    V1 = get_pixel(im,  round(x),      round(y), c);
    V2 = get_pixel(im, (round(x)+1),   round(y), c);
    V3 = get_pixel(im,  round(x),      round(y)+1,    c);
    V4 = get_pixel(im, (round(x)+1),   round(y)+1,    c);

    }
    float q1,q2,q;
    q1 = V1*d2 + V2*d1;
    q2 = V3*d2 + V4*d1;
    q = q1*d4 + q2*d3;

    return q;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    int i,j,k;
    float x_scale,y_scale,new_x,new_y;
    image new = make_image(w,h,im.c);
    for(i=0;i<w;i++)
        for(j=0;j<h;j++){ 
            for(k=0;k<im.c;k++){
             x_scale = (float)im.w/w;        //scaling factors in x and y
             y_scale = (float)im.h/h;
            
             new_x = x_scale*i + 0.5*x_scale - 0.5;
             new_y = y_scale*j + 0.5*y_scale - 0.5;
                
                new.data[i + j*w + k*h*w] = bilinear_interpolate(im,new_x,new_y,k);       //Assigning pixel value to the new coordinates
            }
        }    


    

    
    return new;
}

