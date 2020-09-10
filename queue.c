#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return q;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    size_t len = strlen(s);
    /* TODO: What should you do if the q is NULL? */
    if (newh == NULL) {
        free(newh);
        return false;
    }
    char *value = malloc((len + 1) * sizeof(char));
    if (value == NULL) {
        free(newh);
        free(value);
        return false;
    }
    newh->value = value;
    strncpy(newh->value, s, len + 1);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    q->size++;
    if (q->size == 1) {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newt;
    size_t len = strlen(s);
    /* TODO: What should you do if the q is NULL? */
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL || q == NULL) {
        free(newt);
        return false;
    }
    char *value = malloc((len + 1) * sizeof(char));
    if (value == NULL) {
        free(newt);
        free(value);
        return false;
    }
    newt->value = value;
    newt->next = NULL;
    strncpy(newt->value, s, len + 1);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    q->size++;
    if (q->size == 1) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->size == 0)
        return false;
    q->size--;
    list_ele_t *tmp = q->head;
    if (bufsize != 0) {
        strncpy(sp, tmp->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size == 1)
        return;
    q->tail = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *next = NULL;
    list_ele_t *current = q->head;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    q->head = prev;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q)
        return;
    // q->head = insertionSortList(q->head);
    q->head = mergeSortList(q->head, 0, q->size - 1);
}

list_ele_t *mergeSortList(list_ele_t *start, int l_idx, int r_idx)
{
    if (r_idx <= l_idx)
        return start;
    list_ele_t *left, *right, *half;
    left = half = start;
    int mid = (l_idx + r_idx) / 2;
    for (int i = l_idx; i < mid; i++) {
        half = half->next;
    }
    right = half->next;
    half->next = NULL;
    left = mergeSortList(left, l_idx, mid);
    right = mergeSortList(right, mid + 1, r_idx);
    list_ele_t *merged = NULL;
    if (strcmp(left->value, right->value) <= 0) {
        merged = left;
        left = left->next;
    } else {
        merged = right;
        right = right->next;
    }
    start = merged;
    while (left && right) {
        if (strcmp(left->value, right->value) > 0) {
            merged->next = right;
            merged = merged->next;
            right = right->next;
        } else {
            merged->next = left;
            merged = merged->next;
            left = left->next;
        }
    }

    if (left) {
        merged->next = left;
    }
    if (right) {
        merged->next = right;
    }

    return start;
}