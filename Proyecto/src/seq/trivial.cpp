#include "trivial.hpp"
#include <cstdint>

void maxFilterTrivial(lti::channel8 &dst, const lti::channel8 &src, const int wsize)
{

    int width = src.columns();
    int height = src.rows();
    int se_mid_len = (wsize-1)/2;

    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            uint8_t max = src[j][i];

            for(int a=i-se_mid_len; a<i+se_mid_len; a++)
            {
                for(int32_t b=j-se_mid_len; b<j+se_mid_len; b++)
                {
                    uint8_t value=max;
                    if(a >= 0 && a < width && b >= 0 && b < height)
                        value = src[b][a];
                    if(value > max)
                        max = value;
                }
            }
            dst[j][i] = max;
        }
    }

}
