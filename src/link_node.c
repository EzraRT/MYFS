#include <myfsconfig.h>

#include <myfsdef.h>
#include <stdlib.h>

link_node* insert_data(link_node* head, void* data)
{
    link_node* node = (link_node*)malloc(sizeof(link_node));
    node->data = data;
    node->next = head;
    return node;
}

link_node* push_data(link_node* head, void* data)
{
    if (head == NULL) {
        return insert_data(head, data);
    }

    link_node *node = (link_node*)malloc(sizeof(link_node)), *cur = head;

    node->data = data;
    node->next = NULL;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = node;
    return head;
}

link_node* delete_node(link_node* node)
{
    link_node* next = node->next;
    if (node == NULL) {
        return NULL;
    }
    free(node);
    return next;
}
