# C 语言编译器

## 本项目编码规范

> 每个人的编码习惯都有可能不同, 前后风格保持一致即可, 此处的编码规范仅适用于本项目

### 命名规范

命名应该符合使用时的表达的意思, 如果不能准确的表达, 应当在定义变量时注释说明

- 变量: 小写开头, 下划线分割单词, 例如 `num`, `total_num`
- 常量: 全大写, 下划线分割单词, 例如 `MAX_LENGTH`, `MIN_SIZE`
- 结构体: 使用大驼峰命名, 除非特殊情况尽可能使用 `typedef`, 例如:
 
``` c
typedef struct PersonComputer {
    // ...
} PersonComputer;
```

- 函数: 下划线分割单词, 为了与变量区分, 大写开头, 例如 `New_Node`, `Delete_All`
    - 特殊情况: 对于某个结构体的专用函数, 使用 `结构体名 + 函数` 命名, 例如:

```c
LinkList* LinkList_New();
LinkList* LinkList_Insert(int val);
void LinkList_Free(LinkList** p_self);
```

### 注释规范

- 定义函数时使用如下格式的注释说明功能

```c
/**
 * 描述函数的功能
 * @param arg1 说明参数 arg1 的含义
 * @return 说明返回值
 */
int Some_Func(int arg1){
    // ...
}
```

- 声明变量/常量时, 如果不能见名知意, 使用注释说明


```c
int var_tag; // 某某标志位
```

### 错误处理

由于 C 语言没有提供错误处理机制, 这里我们定义一个结构体做为每个函数的通用返回值来传达错误信息

> 可能这里使用全局变量会更方便, 但我体会过前期使用全局变量使用的有多爽, 后期维护时就有多难受, 所以我极力反对使用全局变量, 我宁愿写代码时更麻烦一点也不愿意使用全局变量

- 返回值结构体

```c
typedef struct {
    char success; // 是否成功, 0 -> 不成功
    ErrCode err_code; // 错误码
    char* msg; // 错误信息
    void* data; // 返回信息
    int data_size; // data 所占大小
} FuncResult;
```

- 定义一些常见错误码枚举值

```c
typedef enum {
    SUCCESS = 0, 
    NULL_POINTER, // 空指针
    OUT_OF_MEMORY, // 内存分配失败
    INVALID_ARGUMENT, // 参数错误
    // ...
} ErrCode;
```

- 相关函数

```c
/**
 * 生成一个错误信息
 * @param err_code 错误码
 * @param msg 错误信息
 * @return 生成的返回信息,使用完成后需要使用 FuncResult_Free 函数回收内存
 */
FuncResult* FuncResult_Err(ErrCode err_code, const char* msg);

/**
 * 生成一个正确信息
 * @param data 返回信息
 * @param data_size data 所占大小
 * @return 生成的返回信息,使用完成后需要使用 FuncResult_Free 函数回收内存
 */
FuncResult* FuncResult_Success(void* data, int data_size);

/**
 * 对 FuncResult 进行内存回收, 包括 msg, data;
 * @param p_self 传入的 FuncResult 指针的地址, 回收成功后会把 FuncResult 指针设置为 NULL
 */
void FuncResult_Free(FuncResult** p_self);
```

- 定义函数时可以这么写

``` c
FuncResult* Some_Func(){
    // ...
    if(...){ // ... 如果发生了某些错误
        return FuncResult_Err(NULL_POINTER, "空指针异常");
    }
    int result = 1; // 返回值
    // ... 业务处理
    return FuncResult_Success(&result, sizeof(result));
}
```

- 调用函数完成后进行错误处理

```c
FuncResult* result = Some_Func();
if(!(result->success)){
    // ... 错误处理
}
int* data = (int*)(result->data);
// ... 业务处理
// 回收
FuncResult_Free(&result);
```

#### 总结

使用这样的错误处理方式有一定的问题:

- 增加内存管理的负担, 每次使用完 `FuncResult` 都需要手动调用 `FuncResult_Free` 释放。
- 为了兼容不同类型, 我把 `data` 设置成了一个 `void` 指针, 使用时需要进行类型转换, 容易引入类型不安全的问题。

但是我认为它的优点是大于缺点的:

- 错误处理更加规范和一致。通过 err_code 和 msg 提供详细的错误信息，有助于调试和维护。
- 避免了使用全局变量，减少了全局变量带来的潜在维护问题和线程安全问题。
- 通过 `data` 和 `data_size` 可以灵活地返回不同类型和大小的数据。

只要能够正确规范的使用, 我相信这样是能节省开发时间的
