#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// -------------------- Linked List for Normal Orders --------------------
typedef struct Node {
    int orderId;
    char item[50];
    struct Node* next;
} Node;

Node* head = NULL;

void addNormalOrder(int id, char* item) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->orderId = id;
    strcpy(temp->item, item);
    temp->next = NULL;

    if (head == NULL)
        head = temp;
    else {
        Node* p = head;
        while (p->next) p = p->next;
        p->next = temp;
    }

    printf("Normal order #%d added.\n", id);
}

void processNormalOrder() {
    if (head == NULL) {
        printf("No normal orders to process.\n");
        return;
    }
    Node* temp = head;
    printf("Processing normal order #%d: %s\n", temp->orderId, temp->item);
    head = head->next;
    free(temp);
}

void displayNormalOrders() {
    Node* temp = head;
    printf("\nNormal Orders:\n");
    while (temp) {
        printf("Order #%d: %s\n", temp->orderId, temp->item);
        temp = temp->next;
    }
}






// -------------------- Heap for Priority Orders --------------------
typedef struct {
    int orderId;
    int priority;
    char item[50];
} Order;

Order heap[MAX];
int size = 0;

void swap(Order* a, Order* b) {
    Order temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int index) {
    if (index <= 0) return;
    int parent = (index - 1) / 2;
    if (heap[index].priority > heap[parent].priority) {
        swap(&heap[index], &heap[parent]);
        heapifyUp(parent);
    }
}

void heapifyDown(int index) {
    int left = 2 * index + 1, right = 2 * index + 2, largest = index;
    if (left < size && heap[left].priority > heap[largest].priority) largest = left;
    if (right < size && heap[right].priority > heap[largest].priority) largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapifyDown(largest);
    }
}

void addPriorityOrder(int id, char* item, int priority) {
    Order o;
    o.orderId = id;
    o.priority = priority;
    strcpy(o.item, item);
    heap[size] = o;
    heapifyUp(size);
    size++;
    printf("Priority order #%d added with priority %d.\n", id, priority);
}

void processPriorityOrder() {
    if (size == 0) {
        printf("No priority orders to process.\n");
        return;
    }
    printf("Processing priority order #%d (%s) with priority %d\n",
           heap[0].orderId, heap[0].item, heap[0].priority);
    heap[0] = heap[--size];
    heapifyDown(0);
}

void displayPriorityOrders() {
    printf("\nPriority Orders:\n");
    for (int i = 0; i < size; i++) {
        printf("Order #%d: %s [Priority: %d]\n", heap[i].orderId, heap[i].item, heap[i].priority);
    }
}

// -------------------- Main Menu --------------------
int main() {
    int choice, id, priority;
    char item[50];

    while (1) {
        printf("\n--- E-Commerce Order Processing System ---\n");
        printf("1. Add Normal Order\n2. Process Normal Order\n3. Add Priority Order\n");
        printf("4. Process Priority Order\n5. Display All Orders\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Order ID and Item: ");
                scanf("%d %s", &id, item);
                addNormalOrder(id, item);
                break;
            case 2:
                processNormalOrder();
                break;
            case 3:
                printf("Enter Order ID, Item, and Priority: ");
                scanf("%d %s %d", &id, item, &priority);
                addPriorityOrder(id, item, priority);
                break;
            case 4:
                processPriorityOrder();
                break;
            case 5:
                displayPriorityOrders();
                displayNormalOrders();
                break;
            case 6:
                exit(0);
        }
    }
    return 0;
}






