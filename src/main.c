# include <stdio.h>
# include <string.h>

# define VERSION "1.0.0"

// 描述用户输入参数
typedef struct InputArg {
    char error;
    char* error_msg;
    char* source_file;
    char* target_file;
} InputArg;

/**
 * 生成一个结构体
 * @return 生成的
 */
InputArg* New_Input_Arg(){
    InputArg* input_arg = (InputArg*) malloc (sizeof(InputArg));
    if(input_arg == NULL){
        return NULL;
    }

    input_arg->error = 0;
    input_arg->error_msg = NULL;
    input_arg->source_file = NULL;
    input_arg->target_file = NULL;
}



/**
 * 解析参数
 * 
 */
InputArg analysis(int argc, char** argv){

}


void help(){
    puts("usage: [-c source] [-o target]");

}


/**
 * 初始化
 */
void init(){
    
}


int main(int argc, char** argv){
    init();

    if(argc == 0){
        help();
        return;
    }    

    // 解析参数



    return 0;
}