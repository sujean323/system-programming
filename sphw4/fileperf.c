#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *source_file = fopen(argv[1], "r");//input
    FILE *dest_file = fopen(argv[2], "w");//output
    int num = atoi(argv[3]);
    int buffer_size = num;
    //假設一個字的最大長度是80個字母
    char word_buf[82];
    //word_buf已經用了多少個字母
    memset(word_buf, '0', 82);
    int buflen = 0;
    //在螢幕上已經列印到第幾個字母
    int linePos = 0; //already write in the line

    
    if (num == 0){ 
    //unbuffered
        setvbuf(source_file, NULL, _IONBF, 1024);
        setvbuf(dest_file, NULL, _IONBF, 1024);
    }
    else if (num == -1){ 
    //linebuffered
        setvbuf(source_file, NULL, _IONBF, 1024);
        setvbuf(dest_file, NULL, _IONBF, 1024);
    }
    else{ 
    //fullybuffered
    //根據man setvbuf 的解釋，系統會自動設定malloc然後設定buffer
    /*
    Except for unbuffered files, the buf argument should 
    point to a buffer at least size bytes long;  this
    buffer  will be used instead of the current buffer.  
    If the argument buf is NULL, only the mode is af‐
    fected; a new buffer will be allocated on the next read 
    or write operation.
    */
        
        //char *buf1 = (char *)malloc(buff_size);
        //char *buf2 = (char *)malloc(buff_size);
        setvbuf(source_file, NULL, _IOFBF, buffer_size);
        setvbuf(dest_file, NULL, _IOFBF, buffer_size);
    }

    while (1){
        int source_fileInt = getc(source_file);
        if (source_fileInt == EOF) break;
        unsigned char source_fileChar = (unsigned char)source_fileInt;
        if (source_fileChar == '\n') {
            fprintf(source_file, "%s\n", word_buf);
            //strcpy(word_buf, "\0");
            buflen=0;
            linePos=0;
        }
        else if (source_fileChar == ' '){
            if (linePos + buflen > 80){
                fprintf(dest_file, "\n");
                fprintf(dest_file, "%s", word_buf);
                //strcpy(word_buf, "\0");
                linePos = 0;
            }
            else{
                fprintf(dest_file, "%s", word_buf);
                //strcpy(word_buf, "\0");
                linePos += buflen+1;
            }
            buflen = 0;
        }
        else{
            word_buf[buflen++] = source_fileChar;
            word_buf[buflen] = '\0';
        }
    }
    return 0;
}
