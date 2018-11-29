#include "dokladal.hpp"
#include <cstdint>



typedef struct Pixel_saved {
  uint8_t value;
  uint32_t location;
} Pixel_saved;

typedef struct OneDim_morph_return {
  uint8_t value;
  bool empty;
} OneDim_morph_return;


typedef std::deque<Pixel_saved> fifo;
typedef std::vector< std::deque< Pixel_saved > > fifo_array;

OneDim_morph_return OneDim_morph(const uint32_t rp,const uint32_t wp,const uint8_t F,const uint32_t se1,const uint32_t se2,const uint32_t N, fifo &sfifo){
//  std::cout << "init" << std::endl;

  if(!sfifo.empty()){
    //std::cout << "fifo: " << sfifo.size() << " back: " << unsigned(sfifo.back().value) << " F: " << unsigned(F) << std::endl;
    //std::cout << "fifo: "<< unsigned(sfifo.back().value) << " " << unsigned(F) << std::endl;
    while (sfifo.back().value <= F)  {
      sfifo.pop_back();
      if(sfifo.empty()){
        break;
      }
    };
    if(!sfifo.empty()){
      if((int)wp-(int)sfifo.front().location > (int)se1){
      //  std::cout << "pop front: " << unsigned(sfifo.front().location) << std::endl;
        sfifo.pop_front();
      };
    }
  }
  sfifo.push_back({F,rp});
//  std::cout << "fifo: " << sfifo.size() << " " << rp << " " << wp << std::endl;
//  std::cin.get();
  OneDim_morph_return ret;
  if(rp == std::min(N,wp+se2)){
    ret = {sfifo.front().value,false};
  }else{
    ret = {0,true};
  }
  return ret;
}

void dokladal(lti::channel8 &dst, const lti::channel8 &src, const int wsize){
  //init variables

    std::deque<uint8_t> in_stream;
    std::deque<uint8_t> out_stream;



    fifo hfifo;
    fifo_array vfifo_array;
    uint32_t N = src.columns();
    uint32_t M = src.rows();
    uint32_t se1,se2,se3,se4;
    se1 = se2 = se3 = se4 = (wsize-1)/2;

    const uint8_t PAD = 0;

  //mem allocation
    vfifo_array.resize(N);

  //input_stream
  for(uint32_t row=0; row<M; row++){
    for(uint32_t col=0; col<N; col++){
        in_stream.push_back(src[row][col]);
      }
    }


    uint32_t line_rd=1;
    uint32_t line_wr=1;
    uint8_t F;
    OneDim_morph_return dFx,dFy;
    F = 0;
    dFx=dFy={0,true};

    while(line_wr<=M){
      //std::cout << hfifo.front().location << std::endl;
      hfifo.clear();
      uint32_t col_rd = 0;
      uint32_t col_wr = 1;
      while(col_wr<=N){
        if(line_rd<=M){
          if(col_rd<N){
            F=in_stream.front();
            in_stream.pop_front();
            //std::cout << "F: " <<  unsigned(F) << std::endl;
          }else{
            F=PAD;
          }
          col_rd = std::min(col_rd+1,N);
          dFx = OneDim_morph(col_rd,col_wr,F,se1,se3,N,hfifo);
          //std::cout << "dim dFx: " << unsigned(dFx.value) << std::endl;
        }else{
          dFx = {PAD,false};
        }
        if(!dFx.empty){
          dFy = OneDim_morph(std::min(line_rd,M),line_wr,dFx.value,se2,se4,M,vfifo_array[col_wr-1]);
          if(!dFy.empty){
            out_stream.push_back(dFy.value);
          }
          col_wr+=1;
        }
      }
      line_rd+=1;
      if(!dFy.empty){
        line_wr+=1;
      }
    }

  for(uint32_t row=0; row<M; row++){
    for(uint32_t col=0; col<N; col++){
      dst[row][col] = out_stream.front();
      out_stream.pop_front();
    }
  }



}
