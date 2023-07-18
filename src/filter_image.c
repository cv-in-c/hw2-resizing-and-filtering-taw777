#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{   
    // TODO
    int i, j, k;
    float s,v;
    s=0;
    for(i=0;i<im.w;i++){
        for(j=0;j<im.h;j++){
            for(k=0;k<im.c;k++){
            s = s + im.data[i + j*im.w + k*im.w*im.h];
            }
        }
    }
    for (i=0;i<im.w;i++){
        for (j=0;j<im.h;j++){
            for (k=0;k<im.c;k++){
            if (s != 0) {
            v = im.data[i + j*im.w + k*im.w*im.h] / s;
            }
            else {
            v = (float)1/ (im.w*im.h);
            }
            im.data[i + j*im.w + k*im.w*im.h] = v;
            }
        }
    }

    
}

image make_box_filter(int w)
{
    // TODO
    image new = make_image(w,w,1);
    int i;
    for(i=0;i<w*w*1;i++){
    new.data[i]=(float)1;
    }
    l1_normalize(new);
    return new;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
  assert(filter.c == im.c || filter.c == 1);
  image new = make_image(im.w, im.h, im.c);
  for (int x = 0; x < im.w; x++) {
    for (int y = 0; y < im.h; y++) {
      for (int c = 0; c < im.c; c++) {
        float q = 0;
        int fil;
        if (filter.c != 1) {
          fil = c;
        }
        else {
          fil = 0;
        }
        for (int filter_x = 0; filter_x < filter.w; filter_x++) {
          for (int filter_y = 0; filter_y < filter.h; filter_y++) {
            float value = filter.data[filter_x + filter_y*filter.w + filter.w*filter.h*fil];
            int fx = x - filter.w / 2 + filter_x;
            int fy = y - filter.h / 2 + filter_y;
            q += get_pixel(im, fx, fy, c) * value;
          }
        }
        new.data[x + y*im.w + c*im.w*im.h] = q;
      }
    }
  }
  if (!preserve) {
    image new2 = make_image(im.w, im.h, 1);
    for (int w = 0; w < im.w; w++) {
      for (int h = 0; h < im.h; h++) {
        float q = 0;
        for (int c = 0; c < im.c; c++) {
          q += new.data[w + h*im.w + im.w*im.h*c];
        }
        new2.data[w + h*im.w] = q;
      }
    }
    return new2;
  }
  else {
    return new;
  }
}

image make_highpass_filter()
{
    // TODO
  image new = make_box_filter(3);
  new.data[0] = 0;
  new.data[1] = -1;
  new.data[2] = 0;
  new.data[3] = -1;
  new.data[4] = 4;
  new.data[5] = -1;
  new.data[6] = 0;
  new.data[7] = -1;
  new.data[8] = 0;
    return new;
    
}

image make_sharpen_filter()
{
    // TODO
  image new = make_box_filter(3);
  new.data[0] = 0;
  new.data[1] = -1;
  new.data[2] = 0;
  new.data[3] = -1;
  new.data[4] = 5;
  new.data[5] = -1;
  new.data[6] = 0;
  new.data[7] = -1;
  new.data[8] = 0;
  return new;
}


image make_emboss_filter()
{
    // TODO
  image new = make_box_filter(3);
  new.data[0] = -2;
  new.data[1] = -1;
  new.data[2] = 0;
  new.data[3] = -1;
  new.data[4] = 1;
  new.data[5] = 1;
  new.data[6] = 0;
  new.data[7] = 1;
  new.data[8] = 2;
  return new;
    
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: Sharpen and emboss because we want to preserve colours

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: Yes clamping needs to be done to prevent colours going out of bounds

image make_gaussian_filter(float sigma)
{
    // TODO
    int s = (int)roundf(sigma * 6) + 1;
  int w;
  if (s % 2 != 0) {
    w = s;
  }
  else {
    w = s++;
  }
  image ret = make_box_filter(w);
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < w; y++) {
      int center = w / 2;
      float value = 1 / (sigma*sigma*2*M_PI);
      float power = -((x-center)*(x-center)+(y-center)*(y-center)) / (sigma*sigma*2);
      ret.data[x + y*w] = value * exp(power);
    }
  }
  l1_normalize(ret);
  return ret;
  
}

image add_image(image a, image b)
{
    // TODO

  assert(a.w == b.w && a.h == b.h && a.c == b.c);
  image ret = make_image(a.w, a.h, a.c);
  for (int x = 0; x < a.w; x++) {
    for (int y = 0; y < a.h; y++) {
      for (int c = 0; c < a.c; c++) {
        int pixel = x + y*a.w + c*a.w*a.h;
        ret.data[pixel] = a.data[pixel] + b.data[pixel];
      }
    }
  }
  return ret;
}

image sub_image(image a, image b)
{
    // TODO
  assert(a.w == b.w && a.h == b.h && a.c == b.c);
  image new = make_image(a.w, a.h, a.c);
  for (int x = 0; x < a.w; x++) {
    for (int y = 0; y < a.h; y++) {
      for (int c = 0; c < a.c; c++) {
        int pixel = x + y*a.w + c*a.w*a.h;
        new.data[pixel] = a.data[pixel] - b.data[pixel];
      }
    }
  }
  return new;
  
}
image make_gx_filter()
{
    // TODO
  image new = make_box_filter(3);
  new.data[0] = -1;
  new.data[1] = 0;
  new.data[2] = 1;
  new.data[3] = -2;
  new.data[4] = 0;
  new.data[5] = 2;
  new.data[6] = -1;
  new.data[7] = 0;
  new.data[8] = 1;
  return new;
}

image make_gy_filter()
{
    // TODO
  image new = make_box_filter(3);
  new.data[0] = -1;
  new.data[1] = -2;
  new.data[2] = -1;
  new.data[3] = 0;
  new.data[4] = 0;
  new.data[5] = 0;
  new.data[6] = 1;
  new.data[7] = 2;
  new.data[8] = 1;
  return new;
    
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
