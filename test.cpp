#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;

char buffer[1024]={0};
char input[1024]={0};
float result[10]={0};
int len = 0;

void PrintFinalResult(){
    float f_result = 0;
    for (int i = 0; i < len; i++){
        f_result = f_result + result[i];
        printf("%0.1f\n",result[i]);
    }
    f_result = f_result / float(len);
    printf("%0.1f\n",f_result);
}
void Shell(char* str){
    FILE *fp;
    fp=popen(str,"r");
    memset(buffer,0,sizeof(buffer));
    fread(buffer,1,sizeof(buffer),fp);
    pclose(fp);
}
int main(int argc, char **argv){
    memset(input,0,sizeof(input));
    sprintf(input,"./text_moss %s %s", argv[1], argv[2]);
    Shell(input);
    result[len++] = atof(buffer);

    memset(input,0,sizeof(input));
    Shell((char *)"mktemp 1.s.XXXX");
    char sfile1[128] = {0};
    strcpy(sfile1, buffer);
    for (int i = 0 ;i < 128 ;i++){
        if (sfile1[i] == '\n'){
            sfile1[i] = 0;
            break;
        }
    }
    memset(input,0,sizeof(input));
    Shell((char *)"mktemp 2.s.XXXX");
    char sfile2[128] = {0};
    strcpy(sfile2, buffer);
    for (int i = 0 ;i < 128 ;i++){
        if (sfile2[i] == '\n'){
            sfile2[i] = 0;
            break;
        }
    }

    memset(input,0,sizeof(input));
    sprintf(input,"g++ -S %s -o %s", argv[1], sfile1);
    Shell(input);

    memset(input,0,sizeof(input));
    sprintf(input,"g++ -S %s -o %s", argv[2], sfile2);
    Shell(input);
    
    memset(input,0,sizeof(input));
    sprintf(input,"./assembly_moss %s %s", sfile1, sfile2);
    Shell(input);
    result[len++] = atof(buffer);

    memset(input,0,sizeof(input));
    sprintf(input,"rm %s", sfile1);
    Shell(input);
    memset(input,0,sizeof(input));
    sprintf(input,"rm %s", sfile2);
    Shell(input);


    PrintFinalResult();
    return 0;    
}