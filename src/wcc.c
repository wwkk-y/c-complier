# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define VERSION "1.0.0"

// 错误码枚举
typedef enum {
    SUCCESS = 0, 
    NULL_POINTER, // 空指针
    OUT_OF_MEMORY, // 内存分配失败
    INVALID_ARGUMENT, // 参数错误
    // ...
} ErrCode;

/** FuncResult ------------------------------------------------------------- */

// 函数返回值
typedef struct {
    char success; // 是否成功, 0 -> 不成功
    ErrCode err_code; // 错误码
    char* msg; // 错误信息
    void* data; // 返回信息
    int data_size; // data 所占大小
} FuncResult;

/**
 * 创建一个结构体, 只负责简单的赋值
 */
FuncResult* FuncResult_New(
    char success, 
    ErrCode err_code, 
    char* msg,
    void* data,
    int data_size    
){
    FuncResult* func_result = (FuncResult*)malloc(sizeof(FuncResult));
    func_result->success = success;
    func_result->err_code = err_code;
    func_result->msg = msg;
    func_result->data = data;
    func_result->data_size = data_size;

    return func_result;
}

/**
 * 生成一个错误信息
 * @param err_code 错误码
 * @param msg 错误信息
 * @return 生成的返回信息,使用完成后需要使用 FuncResult_Free 函数回收内存
 */
FuncResult* FuncResult_Err(ErrCode err_code, const char* msg){
    char* msg_copy = NULL;
    if(msg != NULL){
        int msg_len = strlen(msg);
        msg_copy = (char*)malloc(msg_len + 1);
        if(msg_copy == NULL){
            printf("[error] FuncResult_Err malloc NULL\n");
            exit(1);
        }

        strncpy(msg_copy, msg, msg_len + 1);
    }

    return FuncResult_New(0, err_code, msg_copy, NULL, 0);
}

/**
 * 生成一个正确信息
 * @param data 返回信息
 * @param data_size data 所占大小
 * @return 生成的返回信息,使用完成后需要使用 FuncResult_Free 函数回收内存
 */
FuncResult* FuncResult_Success(void* data, int data_size){
    char* data_copy = NULL;
    if(data != NULL && data_size > 0){
        char* data_copy = (char*)malloc(data_size);
        if(data_copy == NULL){
            printf("[error] FuncResult_Success malloc NULL\n");
            exit(1);
        }
        memcpy(data_copy, data, data_size);
    }

    return FuncResult_New(1, SUCCESS, NULL, data_copy, data_size);
}

/**
 * 对 FuncResult 进行内存回收, 包括 msg, data;
 * @param p_self 传入的 FuncResult 指针的地址, 回收成功后会把 FuncResult 指针设置为 NULL
 */
void FuncResult_Free(FuncResult** p_self){
    if(p_self == NULL || *p_self == NULL){
        printf("[error] FuncResult_Free(NULL)\n");
        exit(1);
    }

    FuncResult* self = *p_self;

    free(self->data);
    free(self->msg);

    free(self);

    *p_self = NULL;
}

/** FuncResult ------------------------------------------------------------- */

/**
 * 解析参数
 * 
 */
FuncResult* analysis(int argc, char** argv){

}


void help(){
    puts("usage:");
    puts("\t wcc -s [source]               complie source");
    puts("\t wcc -s [source] -o [target]   complie source to target");
    puts("\t wcc -h                     help");
    puts("\t wcc -v                     version");
    printf("press any key to continue ...");
    getchar();
}


/**
 * 初始化
 */
void init(){
    
}


int main(int argc, char** argv){
    init();

    // 解析参数
    char* source_file = NULL; // 源码文件
    char* target_file = "a.exe"; // 目标文件
    if(argc == 2 && strcmp("-v", argv[1]) == 0){ 
        // -v
        puts(VERSION);
    } else if (argc == 3 && strcmp("-s", argv[1]) == 0){
        // -s [source]
        source_file = argv[2];
    } else if (argc == 5 && strcmp("-s", argv[1]) == 0 && strcmp("-o", argv[3]) == 0){
        // -s [source] -o [target] 
        source_file = argv[2];
        target_file = argv[4];
    } else {
        help();
    }
    puts(source_file);
    puts(target_file);


    return 0;
}