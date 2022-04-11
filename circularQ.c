#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐의 사이즈 정의

typedef char element; //char타입을 elememt라 재정의
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //element형 queue배열
	int front, rear; //int형 변수 front, rear
}QueueType; //QueueType 구조체

/* 함수들의 프로토타입 */
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
    printf("[----- [이동현] [2019038027] -----]\n\n");
	QueueType *cQ = createQueue(); //포인터cQ가 createQueue()의 리턴값을 가리킴
	element data; //element형 변수 data 선언

	char command; //char형 변수 command 선언

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = "); //명령입력 메시지 출력
		scanf(" %c", &command); //command를 입력받는다

		switch(command) {
		case 'i': case 'I': //command가 i나 I일 경우
			data = getElement(); //data에 getElement()의 리턴값 저장
			enQueue(cQ, data); //enQueue함수 실행
			break;  //break
		case 'd': case 'D': //command가 d나 D일 경우
			deQueue(cQ,&data); //deQueue함수 실행
			break;  //break
		case 'p': case 'P': //command가 p나 P일 경우
			printQ(cQ); //printQ함수 실행
			break;  //break
		case 'b': case 'B': //command가 b나 B일 경우
			debugQ(cQ); //debug함수 실행
			break;  //break
		case 'q': case 'Q': //command가 q나 Q일 경우
			break; //break
		default: //다른값을 입력했을경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //Concentratiom 메시지 출력
			break; //break
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될 때 까지 반복


	return 1;
}

/* 큐룰 생성하는 함수 */
QueueType *createQueue()
{
	QueueType *cQ; //QueueType형 포인터 *cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); //QueueType의 크기만큼의 메모리를 할당하여 주소를 cQ포인터에 저장
	cQ->front = 0; //cQ로 구조체 멤버 front에 접근하여 0 저장
	cQ->rear = 0; //cQ로 구조체 멤버 rear에 접근하여 0 저장
	return cQ; //cQ반환
}

/* 큐를 해제하는 함수 */
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //cQ가 NULL이라면 1반환
    free(cQ); //cQ에 할당된 메모리 해제
    return 1; //1반환
}

/* element(요소)를 얻는 함수 */
element getElement()
{
	element item; //elemeent형 변수 item 선언
	printf("Input element = "); //element입력 메시지 출력
	scanf(" %c", &item); //item을 입력받는다
	return item; //item값 반환
}

/* 원형큐가 empty인지 확인하는 함수 */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){ //구조체 멤버 front와 rear가 같다면
		printf("Circular Queue is empty!"); //원형큐가 비었다는 메시지 출력
		return 1; //1반환
	}
	else return 0; //아니라면 0반환
}

/* 원형큐가 Full인지 확인하는 함수 */
int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { //구조체 멤버 rear의 다음칸이 front와 같다면
		printf(" Circular Queue is full!"); //원형큐가 full이라는 메시지 출력
		return 1; //1반환
	}
	else return 0; //아니라면 0반환
}

/* 큐에 요소를 추가하는 함수 */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return; //큐가 full이라면 return
	else { //full이 아니라면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear에 rear의 다음 칸을 저장
		cQ->queue[cQ->rear] = item; //queue배열의 rear에 item 저장
	}
}


void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return; //큐가 empty라면 return
	else { //full이 아니라면
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //front에 front의 다음 칸을 저장
		*item = cQ->queue[cQ->front]; //queue배열의 front의 값을 item에 넣는다
		return;
	}
}

/* 원형큐를 출력하는 함수 */
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first에 first 다음 칸을 저장
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last에 rear의 다음 칸을 저장

	printf("Circular Queue : ["); 

	i = first; //i에 first의 값 저장
	while(i != last){ //i가 last와 같을 때 까지 반복
		printf("%3c", cQ->queue[i]); //queue배열 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i에 다음칸 저장 (i+1)

	}
	printf(" ]\n");
}

/* 큐를 디버그하는 함수 */
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //MAX_QUEUE_SIZE만큼 반복
	{
		if(i == cQ->front) { //i가 front와 같을때
			printf("  [%d] = front\n", i); //front 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //queue배열 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear 출력
}


