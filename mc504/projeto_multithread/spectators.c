#include "spectators.h"

void enter();
void leave();

void* f_spec (void *v) {
    int id = *(int*) v;

    return NULL;
}
