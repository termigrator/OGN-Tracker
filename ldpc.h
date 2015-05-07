#ifndef __LDPC_H__
#define __LDPC_H__

#include <stdint.h>
#include <stdlib.h>

#include "bitcount.h"

class LDPC
{
  public:
    LDPC();
    void LDPC_Encode(const uint32_t *Data, uint32_t *Parity, const uint32_t ParityGen[48][5]);
    void LDPC_EncodeBlock(const uint32_t *Data, uint32_t *Parity);
};

#endif // of __LDPC_H__
