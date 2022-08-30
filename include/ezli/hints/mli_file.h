#pragma once
#include <dirent.h> //目录项
#include <fcntl.h>  //文件控制
#include <unistd.h> //定义了符号常量

#include <sys/stat.h>
#include <sys/types.h>

namespace mli {

namespace io {

    /**
     * @brief C语言不支持重载，所以原本是一个变参函数，当创建新文件时才需要第三个参数mode。
     * open系统调用根据指定pathname，根据flags打开或创建文件，并返回这个文件的文件描述符
     * @param pathname 指定要操作的文件路径字符串
     * @param flags 它应该是O_开头的宏的组合，其中在O_RDONLY，O_WRONLY或O_RDWR(可能还包含O_EXEC和O_SEARCH)中必须选一个且只有一个。
     * 然后从其他的O_开头的宏或运算一个或多个(即可选的)。(O_RDONLY只读,O_WRONLY只写,O_RDWR读写)
     * @return int 返回新的最小未用文件描述符，如果出错，返回-1，并设置errno
     */
    int open(const char* pathname, int flags);

    /**
     * @brief C语言不支持重载，所以原本是一个变参函数，当创建新文件时才需要第三个参数mode。
     * open系统调用根据指定pathname，根据flags打开或创建文件，并返回这个文件的文件描述符
     * @param pathname 指定要操作的文件路径字符串
     * @param flags 它应该是O_开头的宏的组合，其中在O_RDONLY，O_WRONLY或O_RDWR(可能还包含O_EXEC和O_SEARCH)中必须选一个且只有一个。
     * 然后从其他的O_开头的宏或运算一个或多个(即可选的)。(O_RDONLY只读,O_WRONLY只写,O_RDWR读写)
     * @param mode 当使用O_CREAT(或者还有O_TMPFILE)时，必须指定该参数，该参数用于指定该新文件的访问权限位，它可以是一个八进制表示，如0644
     * @return int 返回新的最小未用文件描述符，如果出错，返回-1，并设置errno
     */
    int open(const char* pathname, int flags, mode_t mode);

    /**
     * @brief C语言不支持重载，所以原本是一个变参函数，当创建新文件时才需要第四个参数mode。
     * 1.当pathname指定绝对路径名，dirfd参数被忽略，此时openat函数就相当于open函数;
     * 2.当pathname指定相对路径名，dirfd则指出了相对路径名在文件系统中的开始地质。dirfd可以通过打开相对路径名所在的目录来获取；
     * 3.当pathname指定相对路径名，dirfd具有特殊值AT_FDCWD，此时，路径名在当前工作目录，此时openat函数就相当于open函数;
     *
     * @param dirfd 指定开始的目录，若pathname是绝对路径则忽略该参数，若是AT_FDCWD，则开始目录在当前工作目录
     * @param pathname 指定要操作的文件路径字符串
     * @param flags 它应该是O_开头的宏的组合，其中在O_RDONLY，O_WRONLY或O_RDWR(可能还包含O_EXEC和O_SEARCH)中必须选一个且只有一个。
     * 然后从其他的O_开头的宏或运算一个或多个(即可选的)。(O_RDONLY只读,O_WRONLY只写,O_RDWR读写)
     * @return int 返回新的最小未用文件描述符，如果出错，返回-1，并设置errno
     */
    int openat(int dirfd, const char* pathname, int flags);

    /**
     * @brief C语言不支持重载，所以原本是一个变参函数，当创建新文件时才需要第四个参数mode。
     * 1.当pathname指定绝对路径名，dirfd参数被忽略，此时openat函数就相当于open函数;
     * 2.当pathname指定相对路径名，dirfd则指出了相对路径名在文件系统中的开始地质。dirfd可以通过打开相对路径名所在的目录来获取；
     * 3.当pathname指定相对路径名，dirfd具有特殊值AT_FDCWD，此时，路径名在当前工作目录，此时openat函数就相当于open函数;
     *
     * @param dirfd 指定开始的目录，若pathname是绝对路径则忽略该参数，若是AT_FDCWD，则开始目录在当前工作目录
     * @param pathname 指定要操作的文件路径字符串
     * @param flags 它应该是O_开头的宏的组合，其中在O_RDONLY，O_WRONLY或O_RDWR(可能还包含O_EXEC和O_SEARCH)中必须选一个且只有一个。
     * 然后从其他的O_开头的宏或运算一个或多个(即可选的)。(O_RDONLY只读,O_WRONLY只写,O_RDWR读写)
     * @param mode 当使用O_CREAT(或者还有O_TMPFILE)时，必须指定该参数，该参数用于指定该新文件的访问权限位，它可以是一个八进制表示，如0644
     * @return int 返回新的最小未用文件描述符，如果出错，返回-1，并设置errno
     */
    int openat(int dirfd, const char* pathname, int flags, mode_t mode);

    /**
     * @brief 该函数等效于open(pathname, O_WRONLY|O_CREAT|O_TRUNC, mode)。
     * 注意，使用该函数创建的文件是只写的，如果你需要创建一个临时文件能够读写，使用
     * open(pathname, O_RDWR|O_CREAT|O_TRUNC, mode)
     *
     * @param pathname 要创建的文件的路径以及文件名
     * @param mode 该参数用于指定该新文件的访问权限位，它可以是一个八进制表示，如0644
     * @return int 返回新的最小未用文件描述符，如果出错，返回-1，并设置errno
     */
    int creat(const char* pathname, mode_t mode);

    /**
     * @brief 关闭指定文件描述符(fd)，并释放改进从加在该文件上的所有记录锁。如果
     * 该fd是最后一个引用打开文件的文件描述符，那么该打开文件的相关资源将被释放。
     *
     * @param fd 指定要关闭的文件描述符
     * @return int 成功则返回0，若出错返回-1，并设置errno
     */
    int close(int fd);

    /**
     * @brief 设置文件描述符(fd)所关联文件的偏移量，该函数仅将新偏移量记录于内核中，
     * 没有任何I/O操作，它影响之后的读写操作。
     *
     * @param fd 要设置偏移量的文件的文件描述符
     * @param offset 新偏移量，它可以比文件本身大小更大，这样会产生"空洞"，它并不会改变文件本身大小
     * @param where 它的可选值为SEEK_SET, SEEK_CUR, SEEK_END，用于指定offset的起点
     * @return off_t 若成功，返回结果偏移量(以字节为单位，从文件开始到当前偏移)，若出错，返回(off_t)-1，并设置errno
     */
    off_t lseek(int fd, off_t offset, int where);

    /**
     * @brief 尝试从指定文件描述符(fd)中读取count个字节到指定buf缓冲区中。若指定fd支持seeking，
     * 那么读取操作将从文件偏移开始，并且文件偏移将增加读取的字节数。如果文件偏移在或超过了文件尾。
     * 那么没有字节将被读取，并返回0。如果count大于SSIZE_MAX，结果由实现决定。
     *
     * @param fd 要读取的文件的文件描述符
     * @param buf 接受读取字节的缓冲区
     * @param count 要读取的字节数量
     * @return ssize_t 若成功，返回读取的字节数量(若返回0表示到达文件底部)，并且文件偏移移动该读取字节数量的距离
     * 该数量若比请求的字节数量少并不是一个错误，因为可能实际文件大小比请求字节少，或者它是一个管道(pipe)，或是一个
     * 终端(terminal)。如果发送错误，返回-1，并且设置errno，在这种情况下，文件位置是否改变没有规定。
     */
    ssize_t read(int fd, void* buf, size_t count);

    /**
     * @brief 将buf地址的count数量字节写入到fd关联的文件中。实际写入的字节数可能小于count，
     * 如磁盘被写满，或者遇到了 RLIMIT_FSIZE资源限制，或者调用在写入少于count字节后被信号处理程序打断。
     * 对于能seek的文件(即lseek能够使用的fd，如一个普通文件)，写操作从文件当前偏移量处开始，如果指定了
     * O_APPEND选项，则在每次写操作之前，将文件偏移量设置在文件的当前结尾处。在一次成功写之后，该文件
     * 偏移量增加实际写的字节数。如果count大于SSIZE_MAX，结果由实现决定。
     *
     * @param fd 要写入的文件的文件描述符
     * @param buf 指向写入内容的缓冲区
     * @param count 要写入的字节数量
     * @return ssize_t 若成功，返回写入的字节数。若出错，返回-1，并设置errno以指示错误。
     * 注意，成功的write()可能写入少于count的字节。如果是因为被信息处理程序打断，调用者
     * 可以再一次调用write()来写入剩余字节。
     */
    ssize_t write(int fd, const void* buf, size_t count);

    /**
     * @brief 从文件描述符fd在offset偏移(从文件开始的偏移)中读取count字节
     * 到buf开始位置，注意，文件自身偏移并不会改变。
     *
     * @param fd 要读取的文件的文件描述符，注意该fd必须是seekable
     * @param buf 接受读取字节的缓冲区
     * @param count 要读取的字节数量
     * @param offset 文件读取的偏移量(从文件开始位置的偏移)
     * @return ssize_t 若成功，返回读取的字节数量(若返回0表示到达文件底部)，如果发生错误，
     * 返回-1，并且设置errno。
     */
    ssize_t pread(int fd, void* buf, size_t count, off_t offset);

    /**
     * @brief 从buf开始位置写入count字节到文件描述符fd在offset偏移处(从文件开始的偏移)
     * ，注意，文件自身偏移并不会改变。
     *
     * @param fd 要写入的文件的文件描述符，注意该fd必须是seekable
     * @param buf 指向写入内容的缓冲区
     * @param count 要读取的字节数量
     * @param offset 文件写入的偏移量(从文件开始位置的偏移)
     * @return ssize_t 若成功，返回写入的字节数量，如果发生错误，返回-1，并且设置errno。
     */
    ssize_t pwrite(int fd, const void* buf, size_t count, off_t offset);

    /**
     * @brief 使用一个最小未使用的文件描述符创建一个oldfd文件描述符的拷贝。
     * 若成功返回，新fd和oldfd指向相同的文件表(file description)。使得它们共享文件偏移和
     * 文件状态标志(忘记了请看书)。例如：使用lseek改变oldfd的偏移，新fd也会被影响。
     * 注意，fd本身的标志并不共享(请回忆三张表的图)，新fd的close-on-exec标志被关闭。
     *
     * @param oldfd 要复制的文件描述符
     * @return int 若成功，返回新复制的文件描述符。若出错，返回-1，并设置errno
     */
    int dup(int oldfd);

    /**
     * @brief 使用newfd创建一个oldfd文件描述符的拷贝。若newfd已经被打开，则它将被关闭再拷贝，
     * 该步骤是原子操作，即先关闭newfd(如果之前打开着)，然后在newfd创建一个oldfd的拷贝，这很重要，
     * 因为分别调用close和dup可能导致竞争条件(race condition)。如果oldfd是非法值，则调用失败，
     * newfd不被关闭。如果oldfd是合法值，且oldfd = newfd，则该函数不做任何事，并返回newfd。
     *
     * @param oldfd 要拷贝的文件描述符
     * @param newfd 新的文件描述符，如果它正在被打开，则将会被先关闭，然后被oldfd拷贝
     * @return int 若成功，返回新复制的文件描述符。若出错，返回-1，并设置errno
     */
    int dup2(int oldfd, int newfd);

    /**
     * @brief 使得所有代处理的文件元数据和缓存文件数据的修改写入底层文件系统(磁盘)。
     * 人话：对所有文件的改变写入到磁盘
     */
    void sync();

    /**
     * @brief 该函数将fd指定文件的所有被修改的内核数据(即被修改的缓存页)写入(刷新)到磁盘中(或其他永久存储设备)。
     * 这样所有被更改的信息可以被保存即使系统崩溃或重启。调用线程将被阻塞直到写磁盘操作结束才返回。注意该函数
     * 与fdatasync的区别，该函数会同步更新文件的属性(看inode(7))，而fdatasync只更新文件的数据部分。
     *
     * @param fd 要将改变的数据写入磁盘的文件描述符
     * @return int 若成功，返回0，若失败返回-1，并设置errno
     */
    int fsync(int fd);

    /**
     * @brief 该函数将fd指定文件的所有被修改的内核数据(即被修改的缓存页)写入(刷新)到磁盘中(或其他永久存储设备)。
     * 这样所有被更改的信息可以被保存即使系统崩溃或重启。调用线程将被阻塞直到写磁盘操作结束才返回。注意该函数
     * 与fsync的区别，fdatasync只更新文件的数据部分。
     *
     * @param fd 要将改变的数据写入磁盘的文件描述符
     * @return int 若成功，返回0，若失败返回-1，并设置errno
     */
    int fdatasync(int fd);

    /**
     * @brief 该函数可以对已经打开的fd作各种操作(fcntl，file control)，操作类型取决于cmd，它是一个F_开头的宏，
     * 第三个参数的意义取决于cmd的值，大多数情况下第三个参数是一个int，而有些cmd并不需要第三个参数。
     * 如下说明一下，不要妄想使用该函数修改fd引用文件的访问模式，比如你不要想只读可以通过该函数改为可写。
     * 具体请看文档。
     *
     * @param fd 要进行指定操作的已经打开的fd
     * @param cmd 它是一个F_开头的宏，用于指定具体操作，详情看文档
     * @param arg 它与cmd的值有关系，有些cmd忽略第三个参数
     * @return int 若成功，其返回值取决于cmd的类型。若失败返回-1，并且设置errno
     */
    int fcntl(int fd, int cmd, int arg = 0);

    /**
     * @brief 使pathname指定的常规文件被截断到指定length的字节上。文件偏移不会改变。如果大小改变，该文件的字段st_ctime和st_mtime
     * 将被更新(分别是上一次状态修改时间和上一次修改时间)，并且设置用户ID和设置组ID模式位可能会被清除。
     * @param pathname 要截断的文件路径，该文件必须是可写的
     * @param length 截断的长度，若为0，表示清空文件
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int truncate(const char* pathname, off_t length);

    /**
     * @brief 使fd指定的常规文件被截断到指定length的字节上。文件偏移不会改变。如果大小改变，该文件的字段st_ctime和st_mtime
     * 将被更新(分别是上一次状态修改时间和上一次修改时间)，并且设置用户ID和设置组ID模式位可能会被清除。
     * @param fd 一个可写打开的文件描述符(读写，只写等等)
     * @param length 截断的长度，若为0，表示清空文件
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int ftruncate(int fd, off_t length);

} // namespace io

/* ioctl() */

namespace fs {
    /**
     * @brief 测试用户对某个文件的权限，注意该函数使用进程的实际用户ID和实际组ID进行测试(四步走)，而不是
     * 进程的有效用户ID和有效组ID。
     *
     * @param pathname 要测试文件的路径，如果指定的是符号链接，则对它进行解引用(即找到它引用的真实文件或目录)
     * @param mode 可以是F_OK，R_OK，W_OK，和X_OK，F_OK指定文件是否存在，后面三个就分别是读写执行
     * @return int 成功则返回0，当权限测试失败，或指定F_OK时文件不存在，或一些错误发生时，返回-1，并设置errno
     */
    int access(const char* pathname, int mode);

    /**
     * @brief 测试用户对某个文件的权限，当pathname参数为绝对路径，或dirfd时AT_FDCWD且pathname时相对路径时
     * 查找效果等同于access，否则pathname是相对于dirfd所指定目录的路径。
     *
     * @param dirfd 可以是目录的fd或AT_FDCWD
     * @param pathname 若为绝对路径，dirfd被忽略，否则是相对于dirfd的路径
     * @param mode 可以是F_OK，R_OK，W_OK，和X_OK，F_OK指定文件是否存在，后面三个就分别是读写执行
     * @param flags 可以是0，此时行为与access一致，若为AT_EACCESS，则使用进程有效用户ID和有效组ID进行测试
     * 可以选择或运算一个AT_SYMLINK_NOFOLLOW
     * @return int 成功则返回0，当权限测试失败，或指定F_OK时文件不存在，或一些错误发生时，返回-1，并设置errno
     */
    int faccessat(int dirfd, const char* pathname, int mode, int flags);

    /**
     * @brief 对调用进程设置创建屏蔽字，并返回之前的创建屏蔽字。创建屏蔽字应用于open，mkdir，或其他
     * 创建文件或目录并设置访问权限的系统调用上，规则是创建屏蔽字为1的位无论你新创建文件或目录其对应位是0还是1，最后结果都为0，
     * 如创建屏蔽字为0777，则不管你随后创建文件指定什么样的访问权限，最后新创建文件的访问权限均为0(即除了root外的用户不能进行任何操作)
     * 注意，使用fork创建的子进程将会继承父进程的创建屏蔽字(umask)
     *
     * @param mask 要设置的创建屏蔽字，如0222(使得该进程只能创建只读文件)
     * @return mode_t 之前的创建屏蔽字
     */
    mode_t umask(mode_t mask);

    /**
     * @brief  改变指定文件的模式位(模式位由文件权限位，set-user-ID，set-group-ID，粘着位构成)，chmod系函数的区别仅在于如何指定文件。
     * 为了改变一个文件的模式位，进程的有效用户ID必须等于文件的所有者ID，或者该进程必须具有root权限
     * @param file 指定文件路径，如果`file`参数指定的是一个符号链接，则对符号链接解引用找到原始文件并修改。
     * @param mode 通常可以用八进制数指定，也可以对特定宏进行或运算，通常指定4位，后三位与umask含义相同(即拥有者，所属组，其他)
     * 首位04表示在进程执行该文件时，将该文件所属用户ID设置到该进程有效用户ID中，02表示该文件所属组设置到进程有效用户组ID中
     * 01表示粘着位(限制删除标志，在unlink(2)中有描述)，如，06755表示，当进程执行该文件时，被设置有效用户ID，以及有效用户组ID
     * 并且所有者拥有读写执行的权限，所属组和其他拥有读取和执行权限。
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int chmod(const char* file, mode_t mode);

    /**
     * @brief  改变指定文件的模式位(模式位由文件权限位，set-user-ID，set-group-ID，粘着位构成)，chmod系函数的区别仅在于如何指定文件。
     * 为了改变一个文件的模式位，进程的有效用户ID必须等于文件的所有者ID，或者该进程必须具有root权限
     * @param fd 指定要改变文件的已经打开的fd
     * @param mode 通常可以用八进制数指定，也可以对特定宏进行或运算，通常指定4位，后三位与umask含义相同(即拥有者，所属组，其他)
     * 首位04表示在进程执行该文件时，将该文件所属用户ID设置到该进程有效用户ID中，02表示该文件所属组设置到进程有效用户组ID中
     * 01表示粘着位(限制删除标志，在unlink(2)中有描述)，如，06755表示，当进程执行该文件时，被设置有效用户ID，以及有效用户组ID
     * 并且所有者拥有读写执行的权限，所属组和其他拥有读取和执行权限。
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int fchmod(int fd, mode_t mode);

    /**
     * @brief 改变指定文件的模式位(模式位由文件权限位，set-user-ID，set-group-ID，粘着位构成)，chmod系函数的区别仅在于如何指定文件。
     * 为了改变一个文件的模式位，进程的有效用户ID必须等于文件的所有者ID，或者该进程必须具有root权限
     * @param dirfd 可以是目录的fd或AT_FDCWD
     * @param file 若为绝对路径，dirfd被忽略，否则是相对于dirfd的路径
     * @param mode 通常可以用八进制数指定，也可以对特定宏进行或运算，通常指定4位，后三位与umask含义相同(即拥有者，所属组，其他)
     * 首位04表示在进程执行该文件时，将该文件所属用户ID设置到该进程有效用户ID中，02表示该文件所属组设置到进程有效用户组ID中
     * 01表示粘着位(限制删除标志，在unlink(2)中有描述)，如，06755表示，当进程执行该文件时，被设置有效用户ID，以及有效用户组ID
     * 并且所有者拥有读写执行的权限，所属组和其他拥有读取和执行权限。
     * @param flag 可以为0或AT_SYMLINK_NOFOLLOW，后者表示，若指定了一个符号链接，那么不要对他解引用，而是对符号链接本身操作(当前标志未实现，看文档)
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int fchmodat(int dirfd, const char* file, mode_t mode, int flag);

    /**
     * @brief 更改文件的用户ID和组ID，如果两个参数owner或group参数任意一个是-1，则对应ID不变，该系列函数区别仅在于如何指定文件。
     * 根据不同的UNIX系统所需要的权限可能不同，有些UNIX需要root权限才能调用该系统调用。该系函数由非超级用户进程调用，则成功返回后，该文件
     * 设置用户ID和设置组ID位被清除
     *
     * @param pathname 文件路径，如果参数指定的是一个符号链接，则对符号链接解引用找到原始文件并修改，可使用lchown避免对符号链接解引用。
     * @param owner 新用户ID，若为-1则不改变
     * @param group 新组ID，若为-1则不变
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int chown(const char* pathname, uid_t owner, gid_t group);

    /**
     * @brief 更改文件的用户ID和组ID，如果两个参数owner或group参数任意一个是-1，则对应ID不变，该系列函数区别仅在于如何指定文件。
     * 根据不同的UNIX系统所需要的权限可能不同，有些UNIX需要root权限才能调用该系统调用。该系函数由非超级用户进程调用，则成功返回后，该文件
     * 设置用户ID和设置组ID位被清除
     *
     * @param fd 引用到指定文件的打开的文件描述符
     * @param owner 新用户ID，若为-1则不改变
     * @param group 新组ID，若为-1则不变
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int fchown(int fd, uid_t owner, gid_t group);

    /**
     * @brief 更改文件的用户ID和组ID，如果两个参数owner或group参数任意一个是-1，则对应ID不变，该系列函数区别仅在于如何指定文件。
     * 根据不同的UNIX系统所需要的权限可能不同，有些UNIX需要root权限才能调用该系统调用。该系函数由非超级用户进程调用，则成功返回后，该文件
     * 设置用户ID和设置组ID位被清除
     *
     * @param pathname 文件路径，如果参数指定的是一个符号链接，不解引用，而是对该符号链接操作
     * @param owner 新用户ID，若为-1则不改变
     * @param group 新组ID，若为-1则不变
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int lchown(const char* pathname, uid_t owner, gid_t group);

    /**
     * @brief 更改文件的用户ID和组ID，如果两个参数owner或group参数任意一个是-1，则对应ID不变，该系列函数区别仅在于如何指定文件。
     * 根据不同的UNIX系统所需要的权限可能不同，有些UNIX需要root权限才能调用该系统调用。该系函数由非超级用户进程调用，则成功返回后，该文件
     * 设置用户ID和设置组ID位被清除
     *
     * @param dirfd 可以是目录的fd或AT_FDCWD
     * @param pathname 若为绝对路径，dirfd被忽略，否则是相对于dirfd的路径
     * @param owner 新用户ID，若为-1则不改变
     * @param group 新组ID，若为-1则不变
     * @param flags 可以是0或AT_EMPTY_PATH(linux特定)，AT_SYMLINK_NOFOLLOW的或运算
     * @return int 若成功，返回0，若出错，返回-1，并设置errno
     */
    int fchownat(int dirfd, const char* pathname, uid_t owner, gid_t group, int flags);

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

    /**
     * @brief 打开指定目录名字的目录流(directory stream)，返回这个目录流的指针。该流位置在
     * 目录的第一个条目中。使用closedir关闭该目录流(或者可以说是目录块)
     *
     * @param dir_path 目录的名字
     * @return DIR* 返回目录流对象，若失败返回NULL，使用errno以获得更多错误信息
     */
    DIR* opendir(const char* dir_path);

    /**
     * @brief 关闭指定目录流，若成功同时也会关闭关联的底层的文件描述符(fd)。之后fd不再可用
     *
     * @param dir_stream 要关闭的目录流对象
     * @return int 若成功返回0，若失败返回-1，使用errno以获得更多错误信息
     */
    int closedir(DIR* dir_stream);

    /**
     * @brief 从目录流获取一个目录条目并返回，该目录条目是一个dirent结构体(目录项)。当到达目录流结尾或出现错误时
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
     * @brief 从oldpath指定的文件中创建一个新的目录项在newpath路径中，它也被称为硬链接，即不同的目录项但指向同一个i节点。
     * 注意，UNIX大多数实现上不支持目录硬链接，所以这里的oldpath必须是文件(具体原因请看笔记，unlink同理)。
     *
     * @param oldpath 已经存在的文件的路径，将从它生成新目录项(必须是文件)
     * @param newpath 新目录项所在路径
     * @return int 若成功返回0，若出错，返回-1并设置errno
     */
    int link(const char* oldpath, const char* newpath);

    /**
     * @brief 从olddirfd和oldpath指定的文件中创建一个新的目录项在newdirfd和newpath指定的路径中，它也被称为硬链接，
     * 即不同的目录项但指向同一个i节点。
     *
     * @param olddirfd 目录fd或特殊值AT_FDCWD
     * @param oldpath 若为相对路径，则相对于dirfd开始，若为绝对路径，则dirfd被忽略(必须是文件)
     * @param newdirfd 目录fd或特殊值AT_FDCWD
     * @param newpath 若为相对路径，则相对于dirfd开始，若为绝对路径，则dirfd被忽略
     * @param flags 可以是0，或者AT_SYMLINK_FOLLOW，即解引用符号链接，默认不解引用
     * @return int 若成功返回0，若出错，返回-1并设置errno
     */
    int linkat(int olddirfd, const char* oldpath, int newdirfd, const char* newpath, int flags);

    /**
     * @brief 删除pathname指定的*已存在的文件*的目录项，并使得其对应的i节点链接次数减1(原子操作)。
     * 如果链接次数为0，并且最后一个引用该文件的fd被关闭，该文件的i节点及其文件内容将被删除。
     * 如果该pathname指定的是符号链接，该链接被删除。如果指定的是socket, FIFO或设备，该名字将被删除，
     * 但是拥有这些东西的进程将可以继续使用它。
     *
     * @param pathname 要删除其目录项的*已存在的文件*的路径(必须是文件)
     * @return int 若成功返回0，若出错，返回-1并设置errno
     */
    int unlink(const char* pathname);

    /**
     * @brief 删除dirfd和pathname指定的*已存在的文件*的目录项，并使得其对应的i节点链接次数减1(原子操作)。
     * 如果链接次数为0，并且最后一个引用该文件的fd被关闭，该文件的i节点及其文件内容将被删除。
     * 如果该pathname指定的是符号链接，该链接被删除。如果指定的是socket, FIFO或设备，该名字将被删除，
     * 但是拥有这些东西的进程将可以继续使用它。如果flags指定为AT_REMOVEDIR，那么行为类似于rmdir。
     *
     * @param dirfd 目录fd或特殊值AT_FDCWD
     * @param pathname 若为相对路径，则相对于dirfd开始，若为绝对路径，则dirfd被忽略(必须是文件)
     * @param flags 可以为0或AT_REMOVEDIR，若为AT_REMOVEDIR，则行为类似于rmdir，可以删除目录
     * @return int 若成功返回0，若出错，返回-1并设置errno
     */
    int unlinkat(int dirfd, const char* pathname, int flags);

    /**
     * @brief 对于文件，它的行为类似于unlink；对于目录，它的行为类似于rmdir。
     * 如pathname指定的是文件，那么删除该文件的目录项，并使得其对应的i节点链接次数减1(原子操作)。
     * 如果链接次数为0，并且最后一个引用该文件的fd被关闭，该文件的i节点及其文件内容将被删除。
     * 如果该pathname指定的是符号链接，该链接被删除。如果指定的是socket, FIFO或设备，该名字将被删除，
     * 但是拥有这些东西的进程将可以继续使用它
     *
     * @param pathname 要删除的已经存在的文件的目录项或目录
     * @return int 若成功返回0，若出错，返回-1并设置errno
     */
    int remove(const char* pathname);

} // namespace fs

} // namespace mli