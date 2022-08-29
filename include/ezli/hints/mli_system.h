#pragma once
#include <dirent.h>   //目录项
#include <sys/stat.h> //文件状态

namespace mli {

/**
 * @brief 在指定目录名字打开一个目录流(directory stream)，返回这个目录流的指针。该流位置在
 * 目录的第一个条目中。使用closedir关闭该目录流
 *
 * @param dir_path 目录的名字
 * @return DIR* 返回目录流对象，若失败返回NULL，使用errno以获得更多错误信息
 */
DIR* opendir(const char* dir_path);

/**
 * @brief 关闭指定目录流，若成功同时也会关闭关联的底层的文件描述符(fd)。之后文件流不再可用
 *
 * @param dir_stream 要关闭的目录流对象
 * @return int 若成功返回0，若失败返回-1，使用errno以获得更多错误信息
 */
int closedir(DIR* dir_stream);

/**
 * @brief 从目录流获取一个目录条目并返回，该目录条目是一个dirent结构体。当到达目录流结尾或出现错误时
 * 返回NULL，使用errno来判断是出错还是到达结尾。
 *
 * @param dir_stream 要从中获取一个目录条目的目录流
 * @return dirent* 若成功，返回这个目录条目结构体指针，若失败返回NULL，若到达目录流结尾也返回NULL
 */
dirent* readdir(DIR* dir_stream);
/**
 * @brief 改变调用进程的工作目录，工作目录是相对路径查找的起点(不以/开头即为相对路径)。
 * 随后通过fork创建的子进程将继承父进程的当前工作目录
 *
 * @param path 新的工作目录
 * @return int 若成功返回0，若失败返回-1，使用errno以获得更多错误信息
 */
int chdir(const char* path);

/**
 * @brief 在运行时获取系统配置信息，如是否支持某个选项或限制，大部分限制数值和选项可在unistd.h和limits.h中编译期获取。
 *
 * @param name 它应该是一个_SC_开头的宏
 * @return long 若出现错误，返回-1，并设置errno以指示错误类型，
 * 若指定限制值是不确定的，则返回-1，而errno不设置。
 * 若指定选项不支持，则返回-1，而errno不设置。
 * 否则当前指定选项或限制值返回正数(>0)
 */
long sysconf(int name);

/**
 * @brief 获取指定文件的配置值，该函数使用文件路径字符串来指定文件。大部分限制数值和选项可在unistd.h和limits.h中编译期获取。
 *
 * @param path 指定文件的路径字符串
 * @param name 它应该是一个_PC_开头的宏，它必须与指定文件类型兼容，如_PC_MAX_INPUT则指定文件必须是一个终端
 * @return long 若出现错误，返回-1，并设置errno以指示错误类型，
 * 若指定限制值是不确定的，则返回-1，而errno不设置。
 * 若指定选项不支持，则返回-1，而errno不设置。
 * 否则当前指定选项或限制值返回正数(>0)
 */
long pathconf(const char* path, int name);

/**
 * @brief 获取指定文件的配置值，该函数使用一个打开的文件描述符来指定文件。大部分限制数值和选项可在unistd.h和limits.h中编译期获取。
 *
 * @param fd 指定文件的打开的文件描述符
 * @param name 它应该是一个_PC_开头的宏，它必须与指定文件类型兼容，如_PC_MAX_INPUT则指定文件必须是一个终端
 * @return long 若出现错误，返回-1，并设置errno以指示错误类型，
 * 若指定限制值是不确定的，则返回-1，而errno不设置。
 * 若指定选项不支持，则返回-1，而errno不设置。
 * 否则当前指定选项或限制值返回正数(>0)
 */
long fpathconf(int fd, int name);

/**
 * @brief 从pathname指定的文件获取信息，并存放在statbuf指定的结构体中，
 * 文件本身不需要权限，但是pathname中的所有目录都需要执行(搜索)权限。stat与
 * lstat区别在于，当路径名指定一个符号链接，那么stat返回符号链接指向文件的信息，
 * 而lstat返回符号链接本身的信息。
 *
 * @param pathname 要获取信息的文件路径名
 * @param statbuf 用于接受pathname指定文件信息的结构体
 * @return int 若成功返回0，若出错，返回-1并设置errno
 */
int stat(const char* pathname, struct stat* statbuf);

/**
 * @brief 从fd指定的文件获取信息，并存放在statbuf指定的结构体中，
 * 与stat不同，fstat使用fd指定一个文件，而stat使用路径字符串。
 *
 * @param fd 要获取信息的文件fd
 * @param statbuf 用于接受fd指定文件信息的结构体
 * @return int 若成功返回0，若出错，返回-1并设置errno
 */
int fstat(int fd, struct stat* statbuf);

/**
 * @brief 从pathname指定的文件获取信息，并存放在statbuf指定的结构体中，
 * 文件本身不需要权限，但是pathname中的所有目录都需要执行(搜索)权限。stat与
 * lstat区别在于，当路径名指定一个符号链接，那么stat返回符号链接指向文件的信息，
 * 而lstat返回符号链接本身的信息。
 *
 * @param pathname 要获取信息的文件路径名
 * @param statbuf 用于接受pathname指定文件信息的结构体
 * @return int 若成功返回0，若出错，返回-1并设置errno
 */
int lstat(const char* pathname, struct stat* statbuf);

/**
 * @brief 获取从dirfd开始，pathname指定的文件信息，并存放在statbuf指定的结构体中，
 * 根据flags不同，行为会有不同变化。当pathname是一个绝对路径时，dirfd被忽略。
 * 当pathname是一个相对路径时，pathname被解释为相对于dirfd的路径。dirfd可以为特殊值
 * AT_FDCWD，表示当前工作目录。
 *
 * @param dirfd 目录fd或特殊值AT_FDCWD
 * @param pathname 若为相对路径，则相对于dirfd开始，若为绝对路径，则dirfd被忽略
 * @param statbuf 用于接收指定文件信息的结构体
 * @param flags 它可以0，或者AT_开头宏的组合(目前只有AT_SYMLINK_NOFOLLOW)
 * @return int 若成功返回0，若出错，返回-1并设置errno
 */
int fstatat(int dirfd, const char* pathname,
    struct stat* statbuf, int flags);

} // namespace mli
