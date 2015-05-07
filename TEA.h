#ifndef TEA_h
#define TEA_h

#include <stdint.h>

/////////////////////////////////////////////////////////////////////
class TEA
{
  public:
    TEA();
    void TEAEncrypt (uint32_t* Data, int Loops=4);
    void TEADecrypt (uint32_t* Data, int Loops=4);

      
  protected:
				
  private:
};


#endif 

