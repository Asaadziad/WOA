#ifndef DIALOUGE_H
#define DIALOUGE_H

typedef enum {
    SWORD_DIALOUGE,
    AXE_DIALOUGE,
} DialougeKind;

typedef struct dialouge_t* DIALOUGE;

DIALOUGE createDialouge(int* label_indexes,int labels_size,DialougeKind dialouge_kind);
void destroyDialouge(DIALOUGE dialouge);

int* getDialougeLabels(DIALOUGE dialouge);
DialougeKind getDialougeKind(DIALOUGE dialouge);
int getLabelsSize(DIALOUGE dialouge);

#endif