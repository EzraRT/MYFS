#ifndef __MYFSAPI_H__
#define __MYFSAPI_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <myfsdef.h>

extern MYFS_EXPORT link_node* current_dir_attribute_head;

extern MYFS_EXPORT size_t uid, gid;

extern MYFS_EXPORT char current_dir_buffer[];

/**
 * @brief open a file and then return the file handle
 * 
 * @param filename 
 * @param mode should be one of "r", "w"
 * @return MYFILE_HANDLE - the file handle
 */
MYFILE_HANDLE MYFS_EXPORT myopen(const char* filename, char* mode);

/**
 * @brief close a file, every file handle should be closed after use
 * 
 * @param file 
 * @return bool - true if success, false if fail
 */
bool MYFS_EXPORT myclose(MYFILE_HANDLE file);

/**
 * @brief read data[s] from a file
 * 
 * @param file the file handle
 * @param buffer the buffer to store the data
 * @param size size of data to read
 * @return size_t - the number of bytes read
 */
size_t MYFS_EXPORT myread(MYFILE_HANDLE file, void* buffer, size_t size, size_t count);

/**
 * @brief write data[s] to a file
 * 
 * @param file the file handle
 * @param buffer the buffer which store the data
 * @param size size of data to write
 * @return size_t - the number of bytes written
 */
size_t MYFS_EXPORT mywrite(MYFILE_HANDLE file, void* buffer, size_t size, size_t count);

/**
 * @brief exec a file
 * 
 * @param file the ATTIBUTE of the file, you should at least have EXEC priviledge of this file
 * @param command command to pass to the file, could be NULL
 */
void MYFS_EXPORT myexec(const MYFILE_ATTIBUTE* file, const char* command);

/**
 * @brief change the current directory to the specified directory
 * 
 * @param path 
 */
void MYFS_EXPORT mychdir(const char* path);

/**
 * @brief get the file attribute of the specified file
 * 
 * @param path filename
 * @param attr where to store the attribute
 */
void MYFS_EXPORT mystat(const char* path, MYFILE_ATTIBUTE* attr);

/**
 * @brief make a directory
 * 
 * @param pathname 
 * @return bool - whether mkdir success
 */
bool MYFS_EXPORT mymkdir(const char* pathname);

/**
 * @brief refresh the current directory information
 * 
 */
void MYFS_EXPORT myrefresh_pwd();

/**
 * @brief get the privilege of the current user to the specified file
 * 
 * @param file the file to check
 * @return uint8_t - the privilege of the current user
 */
uint8_t MYFS_EXPORT grant_privilege(const MYFILE_ATTIBUTE* file);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MYFSAPI_H__