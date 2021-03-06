#include "ap_fixed.h"

using namespace std;

#define D_in 11
#define H1 32
#define H2 12
#define D_out 1


typedef ap_fixed<8,4,AP_RND,AP_SAT> apfixed;


void MeatNet(apfixed in[D_in], 
             apfixed w01[D_in][H1],  apfixed b01[H1],
             apfixed w12[H1][H2],    apfixed b12[H2],
             apfixed w23[H2][D_out], apfixed b23[D_out],
             apfixed out[D_out]);
