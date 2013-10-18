#ifndef OCL_SOBEL_KERNEL_H
#define OCL_SOBEL_KERNEL_H
static const char *sobel_kernel =
"                                                                                                      \n"
"__constant sampler_t image_sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE;         \n"
"                                                                                                      \n"
"__kernel void sobel_filter_kernel(__read_only image2d_t iimage, __write_only image2d_t oimage,        \n"
"                                         __global float *filter_x_grad,                               \n"
"                                         __global float *filter_y_grad, int windowSize)               \n"
"{                                                                                                     \n"
"    unsigned int x = get_global_id(0);                                                                \n"
"    unsigned int y = get_global_id(1);                                                                \n"
"    int halfWindow = windowSize/2;                                                                    \n"
"    float4 pixelValue;                                                                                \n"
"    float gradientX = 0.0f;                                                                           \n"
"    float gradientY = 0.0f;                                                                           \n"
"    float computedFilter  = 0.0f;                                                                     \n"
"    int i, j, ifilter, jfilter;                                                                       \n"
"                                                                                                      \n"
"    for(i=-halfWindow, ifilter=0; i<=halfWindow; i++, ifilter++){                                     \n"
"       for(j=-halfWindow, jfilter=0; j<=halfWindow; j++, jfilter++){                                  \n"
"           pixelValue = read_imagef(iimage, image_sampler, (int2)(x+i, y+j));                         \n"
"           gradientX += filter_x_grad[ifilter*windowSize+jfilter]*pixelValue.x;                       \n"
"           gradientY += filter_y_grad[ifilter*windowSize+jfilter]*pixelValue.y;                       \n"
"       }                                                                                              \n"
"    }                                                                                                 \n"
"                                                                                                      \n"
"    computedFilter = sqrt(gradientX*gradientX + gradientY*gradientY);                                 \n"
"    write_imagef(oimage, (int2)(x, y), (float4)(computedFilter, 0.0, 0.0, 1.0);                       \n"
"}                                                                                                     \n"
"                                                                                                      \n"
"                                                                                                      \n";

#endif