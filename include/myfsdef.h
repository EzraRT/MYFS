#ifndef __MYFSDEF_H__
#define __MYFSDEF_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#ifdef __LIB__MYFS__
#define MYFS_EXPORT __declspec(dllexport)
#else
#define MYFS_EXPORT __declspec(dllimport)
#endif // __LIB__MYFS__

#define MYFS_FNOACCESS 00
#define MYFS_FREAD 04
#define MYFS_FWRITE 02
#define MYFS_FEXEC 01

typedef struct {
    HANDLE hFile;
    size_t uid, gid;
    uint8_t owner, group, other;
} MYFILE, *MYFILE_HANDLE;

typedef struct {
    char name[80];
    size_t size, uid, gid;
    bool is_dir;
    SYSTEMTIME last_write;
    uint8_t owner, group, other;
} MYFILE_ATTRIBUTE;

typedef struct _link_node {
    void* data;
    struct _link_node* next;
} link_node;

/**
 * @brief insert data to the head of the list, return the new head
 * 
 * @param head 
 * @param data 
 * @return link_node* 
 */
MYFS_EXPORT link_node* insert_data(link_node* head, void* data);

/**
 * @brief push data to the tail of the list, return the head
 * 
 * @param head 
 * @param data 
 * @return link_node* 
 */
MYFS_EXPORT link_node* push_data(link_node* head, void* data);

/**
 * @brief delete the node from the list, return the new head
 * 
 * @param node 
 * @return link_node* 
 */
MYFS_EXPORT link_node* delete_node(link_node* node);

#endif // __MYFSDEF_H__