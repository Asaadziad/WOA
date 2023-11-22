#include "Dialouge.h"
#include "stdlib.h"

struct dialouge_t {
    int* label_ids;
    int labels_size;
    DialougeKind dialouge_kind;
    
};

DIALOUGE createDialouge(int* label_indexes,int labels_size,DialougeKind dialouge_kind){
    DIALOUGE d = (DIALOUGE)malloc(sizeof(*d));
    if(!d) return NULL;
    d->label_ids = label_indexes;
    d->labels_size = labels_size;
    d->dialouge_kind = dialouge_kind;
    return d;
}


int* getDialougeLabels(DIALOUGE dialouge){
    return dialouge->label_ids;
}

DialougeKind getDialougeKind(DIALOUGE dialouge){
    return dialouge->dialouge_kind;
}

int getLabelsSize(DIALOUGE dialouge){
    return dialouge->labels_size;
}

void destroyDialouge(DIALOUGE dialouge){
    free(dialouge->label_ids);
    free(dialouge);
}