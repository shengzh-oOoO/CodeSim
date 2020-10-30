#include <iostream>
#include <cstring>
#include <cassert>
#include <list>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
int FILENAME_MAXLEN = 100
int N_GRAM_K = 20
int WINNOWING_SIZE = 10
bool debug_option = 0;
class CodeFile{
    char filename[FILENAME_MAXLEN];
    list<char> hashwindow;
    vector<long> hashlist;
    vector<long> result;
    void init(char *f){
        strcpy(filename,f);
    }
    long RSHash(){
        long b = 378551;
        long a = 63689;
        long hash = 0;
        assert(hashwindow.size() == N_GRAM_K);
        list<char>::iterator i;
        for (i = hashwindow.begin(); i != hashwindow.end(); i++){
            hash = hash * a + (long) (*i);
            a = a * b;
        }
        return hash;
    }
    void CreateHashList(){
        char ch;
        FILE *fid = fopen(filename,"r");
        while(EOF!=(ch= fgetc(fid))){
            if (hashwindow.size() < N_GRAM_K){
                hashwindow.push_back(ch);
            }
            else{
                hashlist.push_back(RSHash());

                hashwindow.pop_front();
                hashwindow.push_back(ch);
            }
        }
    }
    void Winnowing(){
        list<long> win;
        vector<long>::iterator h;
        long before = LONG_LONG_MAX;
        for (h = hashlist.begin(); h != hashlist.end(); h++){
            if (win.size() < WINNOWING_SIZE){
                win.push_back(*h);
            }
            else{
                list<long>::iterator i;
                long min = LONG_LONG_MAX;
                for (i = win.begin(); i != win.end(); i++){
                    if(*i < min) min = *i;
                }
                if(min !=  before){
                    before = min;
                    result.push_back(min);
                }
                win.pop_front();
                win.push_back(*h);
            }
        }
    }
};


int main(int argc, char ** argv){
    CodeFile cfile1,cfile2;
    cfile1.init(argv[1]);
    cfile2.init(argv[2]);
    cfile1.CreateHashList();
    cfile2.CreateHashList();
    cfile1.Winnowing();
    cfile2.Winnowing();

    sort(cfile1.result.begin(), cfile1.result.end());
    sort(cfile2.result.begin(), cfile2.result.end());

    int i = 0, j = 0;
    int same_cnt = 0;
    while(i < cfile1.result.size() && j < cfile2.result.size()){
        if(cfile1.result[i] == cfile2.result[j]){
            i++;
            j++;
            same_cnt ++;
        }
        else if(cfile1.result[i] > cfile2.result[j]){
            j++;
        }
        else if(cfile1.result[i] < cfile2.result[j]){
            i++;
        }
    }
    double IoU = (double)same_cnt/(double)(cfile1.result.size() + cfile2.result.size() - same_cnt);
    printf("%0.1f\n",IoU * 100);
    return 0;
}
