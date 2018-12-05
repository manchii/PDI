#include "vectorized.hpp"
#include <cstdint>
#include <immintrin.h>

void print256_num_1(__m256i var){
    uint8_t *val = (uint8_t*) &var;
    printf("Numerical: %x%x%x%x %x%x%x%x %x%x%x%x %x%x%x%x %x%x%x%x %x%x%x%x %x%x%x%x %x%x%x%x \n",
           val[0], val[1], val[2], val[3], val[4], val[5],
           val[6], val[7],val[8], val[9], val[10], val[11], val[12], val[13],
           val[14], val[15],val[16], val[17], val[18], val[19], val[20], val[21],
           val[22], val[23],val[24], val[25], val[26], val[27], val[28], val[29],
           val[30], val[31]);
}

uint8_t One_Dim_Hor(const lti::channel8 &src,const int row,const int col,const int32_t width,const int se_mid_len){
  uint8_t max = src[row][col];

  for(int a=col-se_mid_len; a<col+se_mid_len; a++){
    uint8_t value=max;
    if(a >= 0 && a < width) value = src[row][a];
    max=std::max(value,max);
  }
  return max;
}
uint8_t One_Dim_Ver(const lti::channel8 &src,const int row,const int col, const int32_t height,const int se_mid_len){
  uint8_t max = src[row][col];
  for(int32_t b=row-se_mid_len; b<row+se_mid_len; b++){
      uint8_t value=max;
      if( b >= 0 && b < height) value = src[b][col];
      max=std::max(value,max);
  }
  return max;
}

void non_vectorized_max_filter(lti::channel8 &dst, const lti::channel8 &src,const int32_t height,const int32_t width,const int se_mid_len){
  // Pass horizontal filter
  lti::channel8 aux(height,width);
    for(int row=0; row<height; row++){
        for(int col=0; col<width; col++){
            aux[row][col] = One_Dim_Hor(src,row,col,width,se_mid_len);
        }
    }
  //  Pass vertical filter
    for(int row=0; row<height; row++){
        for(int col=0; col<width; col++){
            dst[row][col] = One_Dim_Ver(aux,row,col,height,se_mid_len);
        }
    }
}


__m256i inner_vector_max(const __m256i local_256, const int se_mid_len){
  //shift left <<16
  __m256i copy_shift = _mm256_alignr_epi8(local_256, _mm256_permute2x128_si256(local_256, local_256, _MM_SHUFFLE(0, 0, 2, 0)), 16-2);
  //max operate 1
  __m256i max_inner = _mm256_max_epu8(local_256,copy_shift);
  //shift left <<8 && max operate 2
  copy_shift = _mm256_alignr_epi8(local_256, _mm256_permute2x128_si256(local_256, local_256, _MM_SHUFFLE(0, 0, 2, 0)), 16-1);
  max_inner = _mm256_max_epu8(max_inner,copy_shift);
  //shift left >>8 && max operate 3
  copy_shift = _mm256_alignr_epi8(_mm256_permute2x128_si256(local_256, local_256, _MM_SHUFFLE(2, 0, 0, 1)), local_256, 1);
  max_inner = _mm256_max_epu8(max_inner,copy_shift);
  //shift left >>16 && max operate 4
  copy_shift = _mm256_alignr_epi8(_mm256_permute2x128_si256(local_256, local_256, _MM_SHUFFLE(2, 0, 0, 1)), local_256, 2);
  max_inner = _mm256_max_epu8(max_inner,copy_shift);
  return max_inner;
}

__m256i wrapped_max(const __m256i local_256, const __m256i last_local_256, const int se_mid_len){
  __m256i wrapped = _mm256_permute2x128_si256 (local_256, last_local_256, 0x03);
  wrapped = inner_vector_max(wrapped,se_mid_len);
  wrapped = _mm256_permute2x128_si256 (wrapped, wrapped, 0x23);
  //clean with mask
  return _mm256_and_si256(wrapped,_mm256_setr_epi32(0xFFFF,0,0,0,0,0,0,0xFFFF0000));
}

__m256i inner_max(const __m256i local_256, const int se_mid_len){
  return _mm256_and_si256(inner_vector_max(local_256,se_mid_len), _mm256_setr_epi32(0xFFFF0000,-1,-1,-1,-1,-1,-1,0x0000FFFF));
}

__m256i corner_right_max(const __m256i local_256, const int se_mid_len){
   //shift left <<16
   __m256i copy_shift = _mm256_alignr_epi8(local_256, _mm256_set1_epi32(0),14); // <<128 >>8*14
   //max operate 1
   __m256i max_corner_left = _mm256_max_epu8(local_256,copy_shift);
   //shift right <<8 && max operate 2
   copy_shift = _mm256_alignr_epi8(local_256, _mm256_set1_epi32(0),15); // <<128 >>8*15
   max_corner_left = _mm256_max_epu8(max_corner_left,copy_shift);
   //shift right >>8 && max operate 3
   copy_shift = _mm256_alignr_epi8(local_256, _mm256_set1_epi32(0),17); // <<128 >>8*17
   max_corner_left = _mm256_max_epu8(max_corner_left,copy_shift);
   //clean with mask
   return _mm256_and_si256(max_corner_left, _mm256_setr_epi32(0,0,0,0,0,0,0,0xFFFF0000));
 }

__m256i corner_left_max(const __m256i local_256, const int se_mid_len){
   //shift left <<8
   __m256i copy_shift = _mm256_alignr_epi8(local_256, _mm256_set1_epi32(0),15); // <<128 >>8*15
   //max operate 1
   __m256i max_corner_left = _mm256_max_epu8(local_256,copy_shift);
   //shift right >>8 && max operate 2
   copy_shift = _mm256_alignr_epi8(local_256, _mm256_set1_epi32(0),17); // <<128 >>8*17
   max_corner_left = _mm256_max_epu8(max_corner_left,copy_shift);
   //shift right >>16 && max operate 3
   copy_shift = _mm256_alignr_epi8(local_256, _mm256_set1_epi32(0),18); // <<128 >>8*18
   max_corner_left = _mm256_max_epu8(max_corner_left,copy_shift);
   //clean with mask
   return _mm256_and_si256(max_corner_left, _mm256_setr_epi32(0xFFFF,0,0,0,0,0,0,0));
 }

void One_Dim_Hor_Vectorized(lti::vector<uint8_t> &dst, const lti::vector<uint8_t> &src, const int32_t width, const int se_mid_len){
  __m256i local_256, last_local_256, max_container,tmp;
  int *src_base_image = (int *) src.data();
  int *dst_base_image = (int *) dst.data();
  int column_idx=0;

  enum State {CORNER_LEFT,INNER,WRAPPED,CORNER_RIGHT};
  State operation = CORNER_LEFT;

  __m256i vindex = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
  while(column_idx < width){
    switch (operation) {
      case CORNER_LEFT:
        local_256 = _mm256_i32gather_epi32(src_base_image, vindex, 4); // MEM[base+(vdindex)*4]
        max_container = corner_left_max(local_256,se_mid_len);
        column_idx += se_mid_len;
        operation = INNER;

        break;
      case INNER:
        max_container = _mm256_or_si256(max_container, inner_max(local_256,se_mid_len));
        column_idx += 32-(se_mid_len*2);
        operation = WRAPPED;
        operation = (column_idx<(width-2))? WRAPPED : CORNER_RIGHT;
        break;
      case WRAPPED:
        last_local_256=local_256;
        vindex = _mm256_add_epi32(vindex, _mm256_set1_epi32(8)); //vector index + 8*ones
        local_256 = _mm256_i32gather_epi32(src_base_image, vindex, 4); // MEM[base+(vdindex)*4]
        tmp = wrapped_max(local_256,last_local_256,se_mid_len);
        max_container= _mm256_blendv_epi8(max_container, tmp, _mm256_setr_epi32(0, 0, 0, 0, 0, 0, 0,0x80800000));
        _mm256_maskstore_epi32(dst_base_image+((column_idx-30)/4),_mm256_set1_epi32(0x80000000),max_container);
        max_container = _mm256_set1_epi32(0);
        max_container = _mm256_blendv_epi8(max_container, tmp, _mm256_setr_epi32(0x8080, 0, 0, 0, 0, 0, 0, 0));
        column_idx += (se_mid_len*2);
        operation = INNER;
        break;
      case CORNER_RIGHT:
        max_container=_mm256_or_si256(max_container,corner_right_max(local_256,se_mid_len));
        column_idx += se_mid_len;
        _mm256_maskstore_epi32(dst_base_image+((column_idx-30)/4),_mm256_set1_epi32(0x80000000),max_container);
    }
  }
}




void vectorized_max_filter(lti::channel8 &dst, const lti::channel8 &src,const int32_t height,const int32_t width,const int se_mid_len){

  lti::channel8 aux(height,width);

  for(int row = 0; row< height; row++){
    One_Dim_Hor_Vectorized(aux.getRow(row),src.getRow(row),width,se_mid_len);
  }

  aux.transpose();
  dst.transpose();
  for(int row = 0; row< width; row++){
    One_Dim_Hor_Vectorized(dst.getRow(row),aux.getRow(row),height,se_mid_len);
  }
  dst.transpose();
}

void max_sep_filter(lti::channel8 &dst, const lti::channel8 &src, const int wsize){
  int32_t width = src.columns();
  int32_t height = src.rows();
  int se_mid_len = (wsize-1)/2;
  bool support=true;
  if(!support || wsize!=5){
    non_vectorized_max_filter(dst,src,height,width,se_mid_len);
  }else{
    vectorized_max_filter(dst,src,height,width,se_mid_len);
  }
}
