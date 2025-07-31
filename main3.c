include <stdio.h>

int queue[100];
int front = -1, rear = -1;

int isFull() {
    return rear == 99;
}

int isEmpty() {
    return front == -1 || front > rear;
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full!\n");
        return;
    }

    if (front == -1)
        front = 0;

    queue[++rear] = value;
    printf("%d enqueued\n", value);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }

    int value = queue[front++];
    printf("%d dequeued\n", value);
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please enter 1-4.\n");
        }
    }

    return 0;
}
