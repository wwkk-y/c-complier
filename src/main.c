# include <stdio.h>
# include <string.h>



int main(int argc, char** argv){
    // 第一个参数为文件名
    --argc;
    ++argv;

    // 解析参数
    if(argc == 0){
        printf("no input file!");
        return;
    }    

    printf("hello world");
    // getchar();
    return 0;
}