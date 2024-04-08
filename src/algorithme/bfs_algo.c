/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Pathfinding algorithme
*/

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "algorithme/bfs.h"
#include "my_alloc.h"
#include "amazed.h"
#include "map.h"
#include "my_macros.h"
#include "my.h"
#include "my_types.h"

static
int check_visited(map_t const *map, encountered_room_t *visited)
{
    if (map == NULL) {
        display_error("Unable to check map\n");
        return FALSE;
    }
    if (visited == NULL) {
        display_error("Unable to check visited\n");
        return FALSE;
    }
    while (visited != NULL) {
        if (my_strcmp(visited->map->name, map->name) == 0)
            return TRUE;
        visited = visited->next;
    }
    return FALSE;
}

static
int add_visited_room(encountered_room_t *visited, map_t *current_room)
{
    if (visited == NULL || current_room == NULL) {
        return display_error("Unable to retrieve the visited room\n");
    }
    if (visited->map == NULL) {
        visited->map = current_room;
        visited->next = NULL;
        return FAILURE;
    }
    while (visited->next != NULL) {
        visited = visited->next;
    }
    visited->next = malloc(sizeof(encountered_room_t));
    if (visited->next == NULL)
        return display_error("Unable to add visited room\n");
    visited->next->map = current_room;
    visited->next->next = NULL;
    return SUCCESS;
}

static
int add_room_to_queue(room_queue_t *queue, map_t *room)
{
    if (queue == NULL)
        return display_error("Unable to load queue\n");
    while (queue->next != NULL)
        queue = queue->next;
    if (queue->map == NULL) {
        queue->map = room;
        return SUCCESS;
    }
    queue->next = malloc(sizeof(room_queue_t));
    if (queue->next == NULL)
        return display_error("Unable to add another room to queue\n");
    queue->next->map = room;
    queue->next->next = NULL;
    return SUCCESS;
}

static
int check_linked_room(room_queue_t *queue,
    encountered_room_t *visited, char const *end_room)
{
    for (size_t i = 0; queue->map->link[i] != NULL; i += 1) {
        if (check_visited(queue->map->link[i], visited) == TRUE)
            continue;
        if (add_visited_room(visited, queue->map->link[i]) == FAILURE)
            return FAILURE;
        if (my_strcmp(queue->map->link[i]->name, end_room))
            return SUCCESS;
        add_room_to_queue(queue, queue->map->link[i]);
    }
    return FAILURE;
}

static
shortest_path_t *shortest_path(char const *start_room, char const *end_room,
    encountered_room_t *visited)
{
    shortest_path_t *shortest_path = malloc(sizeof(shortest_path_t));
    shortest_path_t *shortest_path_head = shortest_path;
    encountered_room_t *visited_head = visited;
    encountered_room_t *tmp = NULL;

    if (shortest_path == NULL)
        return NULL;
    while (visited != NULL) {
        if (visited->map == NULL) {
            visited = visited->next;
            continue;
        }
        if (my_strcmp(end_room, visited->map->name) == 0
            && shortest_path->room == NULL) {
            shortest_path->room = visited->map;
            visited->map = NULL;
            visited = visited_head;
            break;
        }
        visited = visited->next;
    }
    visited = visited_head;
    if (shortest_path->room == NULL || shortest_path->room->link == NULL) {
        display_error("Algorith couldn't find the end_room\n");
        return free(shortest_path), NULL;
    }
    for (size_t i = 0; shortest_path->room->link[i] != NULL; i += 1) {
        while (visited != NULL) {
            if (visited->map == shortest_path->room->link[i]) {
                shortest_path->next = malloc(sizeof(shortest_path_t));
                if (shortest_path->next == NULL)
                    return NULL;
                shortest_path = shortest_path->next;
                shortest_path->room = visited->map;
                shortest_path->next = NULL;
                visited->map = (visited->next == NULL) ? NULL : visited->next->map;
                tmp = visited->next;
                visited->next = (visited->next == NULL) ? NULL : visited->next->next;
                if (tmp != NULL)
                    free(tmp);
            }
            visited = visited->next;
        }
    }
    return shortest_path_head;
}

static
int execute_bfs(encountered_room_t *visited, room_queue_t *queue,
    char const *end_room, shortest_path_t **shortest_path)
{
    if (queue == NULL || queue->map 
            == NULL || queue->map->name == NULL
        || queue->map->link == NULL || visited == NULL || end_room == NULL)
        return display_error("Unable to access the room info\n");
    while (queue != NULL) {
        if (check_linked_room(queue, visited, end_room) == SUCCESS)
            return SUCCESS;
        queue = queue->next;
    }
    *shortes_path = retrieve_bfs_shortest_path();
    return FAILURE;
}

int get_shortest_path(map_t *map, const char *end_room, shortest_path_t **shortest_path)
{
    encountered_room_t *visited = NULL;
    room_queue_t *queue = NULL;

    if (end_room == NULL || map == NULL)
        return display_error("Struct null for algorithme\n");
    visited = malloc(sizeof(encountered_room_t));
    if (visited == NULL)
        return display_error("Unable to allocate visited memory\n");
    visited->map = map;
    visited->next = NULL;
    queue = malloc(sizeof(room_queue_t));
    if (queue == NULL) {
        free(visited);
        return display_error("Unable to allocate queue memory\n");
    }
    queue->map = map;
    queue->next = NULL;
    return execute_bfs(visited, queue, end_room, shortest_path);
}
