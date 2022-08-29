#include "example_0.h"
#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <utility>

using ezli::call;

// 测试myls
void example_0()
{
    // 获取当前目录的目录流
    auto* dir_stream = call<opendir>(".");

    dirent* dir_item = nullptr;
    while ((dir_item = call<readdir>(dir_stream)) != nullptr)
    {
        std::cout << dir_item->d_name << "\n";
    }

    call<closedir>(dir_stream);
}

// 测试sysconf,pathconf,fpathconf
void example_0_1()
{
    // 数值限制-------------------
    std::cout << "页面大小:" << call<sysconf>(_SC_PAGE_SIZE) << "\n";

    std::cout << "相对路径名最大字节数:" << call<pathconf>(".", _PC_PATH_MAX) << "\n";
    std::cout << "最大文件名字节数:" << call<pathconf>(".", _PC_NAME_MAX) << "\n";

    // 选项----------------------
    // std::cout << "是否支持异步IO:" << call<pathconf>("~/base", _PC_ASYNC_IO) << "\n";
    // std::cout << "是否支持同步IO:" << call<pathconf>("~/base", _PC_SYNC_IO) << "\n";

    // 实际上，只要_POSIX_THREADS有定义，就可以用了
    // 否则需要sysconf来确定是否可用
    std::cout << "是否支持线程:" << call<sysconf>(_SC_THREADS) << "\n";
    std::cout << "POSIX版本:" << call<sysconf>(_SC_VERSION) << "\n";

    std::cout << "OPEN_MAX:" << call<sysconf>(_SC_OPEN_MAX) << "\n";

    auto val = call<sysconf>(_SC_ATEXIT_MAX);
    std::cout << "ATEXIT_MAX:" << val << "\n";
}

const char* print_file_type(mode_t file_mode)
{
    if (S_ISREG(file_mode))
        return "普通文件";

    if (S_ISDIR(file_mode))
        return "目录文件";

    if (S_ISCHR(file_mode))
        return "字符特殊文件";

    if (S_ISBLK(file_mode))
        return "块特殊文件";

    if (S_ISFIFO(file_mode))
        return "管道或FIFO";

    if (S_ISLNK(file_mode))
        return "符号链接";

    if (S_ISSOCK(file_mode))
        return "套接字";

    return "未知类型";
}

// 测试stat系列函数
void example_0_2()
{
    struct stat my_stat
    {
    };
    call<stat>("/home", &my_stat);

    std::cout << print_file_type(my_stat.st_mode) << "\n";

    // 注意一定要以0开头，这才表示八进制
    // 0644等同于S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    auto file_fd = call<creat>("./kaka.txt", 0644);

    call<fstat>(file_fd, &my_stat);

    std::cout << print_file_type(my_stat.st_mode) << "\n";

    // 测试是否设置 "设置用户ID" 和 "设置组ID" 位
    std::cout << (S_ISUID & my_stat.st_mode) << "\n";
    std::cout << (S_ISGID & my_stat.st_mode) << "\n";

    // 测试文件是否存在
    std::cout << call<access>("./kaka.txt", F_OK) << "\n";

    // mli::umask();

    call<close>(file_fd);
}

// 测试umask和chmod系函数
void example_0_3()
{
    call<umask>(0033);

    auto lolo_fd = call<creat>("./lolo.txt", 15125125277); // 由于umask，最后权限为0744

    struct stat my_stat
    {
    };

    call<fstat>(lolo_fd, &my_stat);

    std::cout << std::setbase(8);

    std::cout << "权限 : " << my_stat.st_mode << "\n";

    call<fchmod>(lolo_fd, 06444); // 为06444

    call<fstat>(lolo_fd, &my_stat);
    std::cout << "权限 : " << my_stat.st_mode << "\n";

    call<close>(lolo_fd);

    // stat.st_mode的八进制首两位表示文件的类型，第三位就是设置用户ID，设置组ID，以及粘着位，后面三位就是我们熟悉的所有者，所有组，其他的权限访问位了
    // 如106744即表示是一个常规文件，当程序执行该文件时，将有效用户ID，有效组ID设置为该文件的所属组和所属人，所有者拥有完全控制权限，所有组和其他拥有读取和执行权限。
}