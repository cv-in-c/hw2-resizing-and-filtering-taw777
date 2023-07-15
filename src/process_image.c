#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    float pixel_value;
     if (x < 0){
        x = 0;
    }
    else if (x >= im.w){
        x = im.w-1;
    }
    if (y < 0){
        y = 0;
    }
    else if (y >= im.h){
        y = im.h-1;
    }
    if (c < 0){
        c = 0;
    }
    else if (c >= im.c){
        c = im.c-1; 
    }
    pixel_value =  im.data[x+(y*im.w)+(im.w*im.h*c)];
   
    

    return pixel_value;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    float pixel_value;

    pixel_value =  im.data[x+(y*im.w)+(im.w*im.h*c)];
    
    if (x < 0){
        return pixel_value;
    }
    else if (x >= im.w){
        return pixel_value;
    }
    if (y < 0){
        return pixel_value;
    }
    else if (y >= im.h){
        return pixel_value;
    }
    if (c < 0){
        return pixel_value;
    }
    else if (c >= im.c){
       return pixel_value; 
    }
    im.data[x+(y*im.w)+(im.w*im.h*c)] = v;
    
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    for (int i = 0;i<im.w*im.h*im.c;i++){
        copy.data[i] = im.data[i];
    }
    return copy;
}
//0.299 R' + 0.587 G' + .114 B'

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for (int i = 0; i < im.w*im.h; i++)
    gray.data[i] = im.data[i]*0.299 + im.data[i+im.h*im.w]*0.587 + im.data[i + (2*im.h*im.w)]*0.114;
    return gray;
}

void shift_image(image im, int c, float v)
{
    
    // TODO Fill this in

    for (int i=0; i<im.w*im.h; i++)
    im.data[i+(c*im.w*im.h)] += v;
}

void clamp_image(image im)
{
    for (int i = 0; i<im.w*im.h*im.c; i++)
    if (im.data[i]<0)
    im.data[i] = 0;
    else if (im.data[i]>1)
    im.data[i] = 1; 
       
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    for (int i=0; i<im.w*im.h; i++)
    {
        //Value V
       float R=im.data[i],G=im.data[i+im.w*im.h],B=im.data[i+2*im.w*im.h];
       float V = three_way_max(R,G,B);

       //Saturation S
       float m = three_way_min(R,G,B);

       float C = V-m;       //C is the difference between max and min.

       float S;

       if (R == 0 && G == 0 && B == 0)
       {
         S = 0;
       }
            else
            {
                 S = C/V;
            }

       //Hue H
       float H_temp,H;

        if (C==0)
        {
            H_temp = 0;
            
        }
           else if(V==R) 
            {
                H_temp = (G - B)/C;
            }
           else if(V==G)
            {
                H_temp = (B - R)/C +2;
            }
           else if(V==B) 
            {
                H_temp = (R - G)/C +4;
            }

        if (H_temp<0)
            H = (H_temp/6)+1;

            else
            H = (H_temp/6);

    im.data[i] = H;
    im.data[i+im.w*im.h] = S;
    im.data[i+im.w*im.h*2] = V;    

    }


}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    for (int i=0; i<im.h; i++)
    {
        for (int j=0; j<im.w; j++)
        {
            float   H = im.data[i*im.w+j], 
                    S = im.data[im.w*im.h+i*im.w+j],
                    V =im.data[2*im.w*im.h+i*im.w+j],
                    H_temp = H*6,
                    a = floor(H_temp),
                    f = H_temp - a,
                    C = V*S,
                    X = V*(1-S*f),
                    Y = V*(1-S*(1-f)),
                    m = V - C,
                    R,B,G;

            if (H_temp >= 0 && H_temp < 1)
            {
                R = V;
                G = Y;
                B = m;
            }
            else if (H_temp >= 1 && H_temp<2)
            {
                R = X;
                G = V;
                B = m;
            }
            else if (H_temp >= 2 && H_temp < 3)
            {
                R = m;
                G = V;
                B = Y;
            }
            else if (H_temp >= 3 && H_temp < 4)
            {
                R = m;
                G = X;
                B = V;
            }
            else if (H_temp >= 4 && H_temp < 5)
            {
                R = Y;
                G = m;
                B = V;
            }
            else
            {
                R = V;
                G = m;
                B = X;
            }

        im.data[i*im.w+j] = R;
        im.data[im.w*im.h+i*im.w+j] = G;
        im.data[2*im.w*im.h+i*im.w+j] = B;     

        }        
    }
}
