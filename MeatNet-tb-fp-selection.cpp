#include "MeatNet.h"

#include <stdio.h>
#include <iostream>

int main(){

    char cut_names[12][16] = { "Inside-Outside", "Round", "Top Sirloin", "Tenderloin", "Flap meat", "Striploin", "Rib eye", "Skirt meat", "Brisket", "Clod Chuck", "Shin", "Fat" }; 

    char directory[200];
    apfixed out[D_out], in[D_in];
    apfixed w01[D_in][H1],  w12[H1][H2], w23[H2][D_out];
    apfixed b01[H1], b12[H2], b23[D_out];

    int i, j, k;
    float t, out_real, out_py, tmp;

    cout << "Starting the program\n"; //Reading the paramters..."

    for(int cut=0;cut<12;cut++){

        cout << "Cut " << cut+1 << "/12...";

        FILE *fparam;
        sprintf(directory, "/home/daniel/Carnes/%s/best/params.txt", cut_names[cut]);
        fparam = fopen(directory,"r");
        if(fparam == NULL){
            cout << "Error opening the paramters file of " <<  cut_names[cut] << endl;
            return 0;
        }

        //Reading w01
        for(i=0;i<H1;i++){
            for(j=0;j<D_in;j++){
                fscanf(fparam,"%f ",&tmp);
                w01[j][i] = tmp;
            }
            fscanf(fparam,"\n");
        }

        //Reading b01
        for(i=0;i<H1;i++){
            fscanf(fparam,"%f\n",&tmp);
            b01[i] = tmp;
        }

        //Reading w12
        for(i=0;i<H2;i++){
            for(j=0;j<H1;j++){
                fscanf(fparam,"%f ",&tmp);
                w12[j][i] = tmp;
            }
            fscanf(fparam,"\n");
        }

        //Reading b12
        for(i=0;i<H2;i++){
            fscanf(fparam,"%f\n",&tmp);
            b12[i] = tmp;
        }

        //Reading w23
        for(i=0;i<D_out;i++){
            for(j=0;j<H2;j++){
                fscanf(fparam,"%f ",&tmp);
                w23[j][i] = tmp;
            }
            fscanf(fparam,"\n");
        }

        //Reading b23
        for(i=0;i<D_out;i++){
            fscanf(fparam,"%f\n",&tmp);
            b23[i] = tmp;
        }

        fclose(fparam);


        //cout << "OK\nOpening test file...";

        FILE *fin;
        sprintf(directory, "/home/daniel/Carnes/%s/best/test.txt", cut_names[cut]);
        fin = fopen(directory, "r");
        if(fin == NULL){
            cout << "Error opening the test file of " <<  cut_names[cut] << endl;
            return 0;
        }

        fscanf(fin,"# Time(s) TVC(norm) PredTVC(norm) Smoothed sensor readings (11 channels)\n");

        //cout << "OK\nOpening output file...";

        //Read fixed datatype details to include them in the output files names
	    int total_apfixed, int_apfixed;
	    sscanf(typeid(apfixed).name() , "8ap_fixedILi%dELi%dEL9ap_q_mode0EL9ap_o_mode0ELi0EE", &total_apfixed, &int_apfixed);
        
        FILE *fout;
        sprintf(directory, "/home/daniel/Carnes/%s/fixed-point-selection/%d-%d.txt", cut_names[cut], total_apfixed, int_apfixed);
        fout = fopen(directory, "w");
        if(fout == NULL){
            cout << "Error opening the output file of " <<  cut_names[cut] << endl;
            return 0;
        }

        fprintf(fout, "Time(s) TVC PyPredTVC HLSPredTVC\n");

        //cout << "OK\nStarting the test\n";

        for(k=1; k<=444; k++){
            //cout << "\t\Line " << k << "...";

            fscanf(fin, "%f %f %f ", &t, &out_real, &out_py);

            for(i=0;i<D_in;i++){
                fscanf(fin,"%f ", &tmp);
                in[i] = tmp;
            }
            fscanf(fin, "\n");


            MeatNet(in, w01, b01, w12, b12, w23, b23, out);

            fprintf(fout, "%f %f %f %f\n", t, out_real, out_py, float(out[0]));


            //cout << "TVC: pred_cpp: " << out[0] << " real: " << out_real << endl;

            //cout << "OK\n";
        }

        fclose(fin);
        fclose(fout);

        cout << "OK\n";
    }

    return 0;
}

