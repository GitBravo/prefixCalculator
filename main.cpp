#include <iostream>
#include <cstdio>
using namespace std;

struct Queue
{
	int data;
	Queue *link;
};

void Enqueue(Queue **front, Queue **rear, int data) // 큐 삽입 함수
{
	Queue *new_queue = new Queue;
	if (*rear == NULL) { // 만약 큐가 비어있다면 삽입
		*rear = new_queue;
		*front = new_queue;
		new_queue->data = data;
		new_queue->link = NULL;
	}
	else if (new_queue == NULL) { // 만약 큐가 가득 찼다면 에러
		cout << "Enqueue Error !" << endl;
	}
	else { // 큐 삽입 가능한 상태
		(*rear)->link = new_queue;
		new_queue->data = data;
		new_queue->link = NULL;
		*rear = new_queue;
	}
}

void Dequeue(Queue **front) // 큐 삭제 함수
{
	if (*front == NULL) { // 만약 큐가 비어있다면 에러
		cout << "Dequeue Error !" << endl;
	}
	else {
		Queue *temp = *front;
		*front = (*front)->link;
		delete temp;
	}
}

void ASCIItoINT(Queue **front) // 큐 저장값(아스키코드 -> 정수) 변환 함수
{
	Queue *search_ptr = *front;
	for (; search_ptr; search_ptr = search_ptr->link) {
		if ((search_ptr->data >= 48) && (search_ptr->data <= 57)) {
			search_ptr->data = search_ptr->data - 48;
		}
	}
}

void Search_queue(Queue **front) // 큐 탐색 함수
{
	Queue *search_ptr = *front; // 탐색용 포인터 선언1
	for (; search_ptr; search_ptr = search_ptr->link) { // front 위치에서 데이터 탐색 시작
		if ((search_ptr->data == 43 || search_ptr->data == 45 || search_ptr->data == 42 || search_ptr->data == 47)) { // 연산자 체크
			Queue *search_ptr2 = search_ptr->link; // 탐색용 포인터 선언2
			Queue *search_ptr3 = search_ptr2->link; // 탐색용 포인터 선언3
			if ((search_ptr2->data < 42 || search_ptr2->data > 48) && (search_ptr3->data < 40 || search_ptr3->data > 48)) { // 피연산자 체크
				switch (search_ptr->data) {
				case 43: { // (+)
					search_ptr->data = search_ptr2->data + search_ptr3->data;
					search_ptr->link = search_ptr3->link;
					Dequeue(&search_ptr2);
					Dequeue(&search_ptr3); // EX) + 2 8 일 경우 + 자리의 노드에 연산결과 삽입 후 2 8 노드 메모리할당 해제
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

	char *ary = "-+*9+28*+4863"; // -+*9+28*+4863(전위식)을 포인터에 저장

	for (int i = 0; i < (int)strlen(ary); i++) // 포인터를 탐색하여 그 값을 큐에 모두 저장.
		Enqueue(&front, &rear, ary[i]);

	ASCIItoINT(&front); // 큐 저장값(아스키코드 -> 정수) 변환 함수 호출
	Search_queue(&front);
	Search_queue(&front);
	Search_queue(&front);
	Search_queue(&front); // 큐 탐색 함수 호출(탐색 및 연산)

	cout << "전위식 <-+*9+28*+4863> 계산 결과 : ";
	for (; front; front = front->link) // 큐 결과값 출력
		printf("%d ", front->data);

	cout << endl;
}