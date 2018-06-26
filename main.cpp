#include <iostream>
#include <cstdio>
using namespace std;

struct Queue
{
	int data;
	Queue *link;
};

void Enqueue(Queue **front, Queue **rear, int data) // ť ���� �Լ�
{
	Queue *new_queue = new Queue;
	if (*rear == NULL) { // ���� ť�� ����ִٸ� ����
		*rear = new_queue;
		*front = new_queue;
		new_queue->data = data;
		new_queue->link = NULL;
	}
	else if (new_queue == NULL) { // ���� ť�� ���� á�ٸ� ����
		cout << "Enqueue Error !" << endl;
	}
	else { // ť ���� ������ ����
		(*rear)->link = new_queue;
		new_queue->data = data;
		new_queue->link = NULL;
		*rear = new_queue;
	}
}

void Dequeue(Queue **front) // ť ���� �Լ�
{
	if (*front == NULL) { // ���� ť�� ����ִٸ� ����
		cout << "Dequeue Error !" << endl;
	}
	else {
		Queue *temp = *front;
		*front = (*front)->link;
		delete temp;
	}
}

void ASCIItoINT(Queue **front) // ť ���尪(�ƽ�Ű�ڵ� -> ����) ��ȯ �Լ�
{
	Queue *search_ptr = *front;
	for (; search_ptr; search_ptr = search_ptr->link) {
		if ((search_ptr->data >= 48) && (search_ptr->data <= 57)) {
			search_ptr->data = search_ptr->data - 48;
		}
	}
}

void Search_queue(Queue **front) // ť Ž�� �Լ�
{
	Queue *search_ptr = *front; // Ž���� ������ ����1
	for (; search_ptr; search_ptr = search_ptr->link) { // front ��ġ���� ������ Ž�� ����
		if ((search_ptr->data == 43 || search_ptr->data == 45 || search_ptr->data == 42 || search_ptr->data == 47)) { // ������ üũ
			Queue *search_ptr2 = search_ptr->link; // Ž���� ������ ����2
			Queue *search_ptr3 = search_ptr2->link; // Ž���� ������ ����3
			if ((search_ptr2->data < 42 || search_ptr2->data > 48) && (search_ptr3->data < 40 || search_ptr3->data > 48)) { // �ǿ����� üũ
				switch (search_ptr->data) {
				case 43: { // (+)
					search_ptr->data = search_ptr2->data + search_ptr3->data;
					search_ptr->link = search_ptr3->link;
					Dequeue(&search_ptr2);
					Dequeue(&search_ptr3); // EX) + 2 8 �� ��� + �ڸ��� ��忡 ������ ���� �� 2 8 ��� �޸��Ҵ� ����
					break;
				}
				case 45: { // (-)
					search_ptr->data = search_ptr2->data - search_ptr3->data;
					search_ptr->link = search_ptr3->link;
					Dequeue(&search_ptr2);
					Dequeue(&search_ptr3);
					break;
				}
				case 42: { // (*)
					search_ptr->data = search_ptr2->data * search_ptr3->data;
					search_ptr->link = search_ptr3->link;
					Dequeue(&search_ptr2);
					Dequeue(&search_ptr3);
					break;
				}
				case 47: { // (/)
					search_ptr->data = search_ptr2->data / search_ptr3->data;
					search_ptr->link = search_ptr3->link;
					Dequeue(&search_ptr2);
					Dequeue(&search_ptr3);
					break;
				}
				}
			}
		}
	}
}

void main()
{
	Queue *rear = NULL;
	Queue *front = NULL;

	//	Enqueue(&front, &rear, 10);
	//	Dequeue(&front);

	char *ary = "-+*9+28*+4863"; // -+*9+28*+4863(������)�� �����Ϳ� ����

	for (int i = 0; i < (int)strlen(ary); i++) // �����͸� Ž���Ͽ� �� ���� ť�� ��� ����.
		Enqueue(&front, &rear, ary[i]);

	ASCIItoINT(&front); // ť ���尪(�ƽ�Ű�ڵ� -> ����) ��ȯ �Լ� ȣ��
	Search_queue(&front);
	Search_queue(&front);
	Search_queue(&front);
	Search_queue(&front); // ť Ž�� �Լ� ȣ��(Ž�� �� ����)

	cout << "������ <-+*9+28*+4863> ��� ��� : ";
	for (; front; front = front->link) // ť ����� ���
		printf("%d ", front->data);

	cout << endl;
}