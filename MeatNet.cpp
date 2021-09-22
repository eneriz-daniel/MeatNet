#include "MeatNet.h"

apfixed ReLU(apfixed x);

apfixed ReLU(apfixed x){
	if(x>0) return x;
    else return 0; //ReLU
}

void MeatNet(apfixed in[D_in], 
             apfixed w01[D_in][H1],  apfixed b01[H1],
             apfixed w12[H1][H2],    apfixed b12[H2],
             apfixed w23[H2][D_out], apfixed b23[D_out],
             apfixed out[D_out]){
    
    int i,j;

    apfixed tmp, inter1[H1], inter2[H2];

    Layer01Ext: for(i=0;i<H1;i++){
        tmp = b01[i];
        Layer01Int: for(j=0;j<D_in;j++){
            tmp += w01[j][i]*in[j];
        }
        inter1[i] = ReLU(tmp);
    }

    Layer12Ext: for(i=0;i<H2;i++){
        tmp = b12[i];
        Layer12Int: for(j=0;j<H1;j++){
            tmp += w12[j][i]*inter1[j];
        }
        inter2[i] = ReLU(tmp);
    }

    Layer23Ext: for(i=0;i<D_out;i++){
        tmp = b23[i];
        Layer23Int: for(j=0;j<H2;j++){
            tmp += w23[j][i]*inter2[j];
        }
        out[i] = ReLU(tmp);
    }
}
