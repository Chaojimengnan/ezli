#pragma once
#include <sys/stat.h> //文件状态

namespace mli {

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

} // namespace mli
