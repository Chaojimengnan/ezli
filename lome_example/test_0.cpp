#include <iostream>
#include <unistd.h>

constexpr auto BUFFSIZE = 4096;

// 从标准输入读取数据，然后输出到标准输出中
// 在bash中可以使用>和<来指定输出的地方和输入的地方
// 若不指定则默认在终端中
void test_0()
{
    ssize_t read_count = 0;
    char buffer[BUFFSIZE] = { 0 };

    while ((read_count = read(STDIN_FILENO, buffer, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buffer, read_count) != read_count)
        {
            std::cerr << "写入错误!\n";
        }
    }
    if (read_count < 0)
        std::cerr << "read error!\n";
}

/**
 * @brief 打印当前进程的用户ID和组ID
 *
 */
void test_1()
{
    std::cout << getuid() << "," << getgid() << "\n";
}

#include <fcntl.h>

int main()
{
    // test_0();
    test_1();
    return 0;
}