#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //ť�� ������ ����

typedef char element; //charŸ���� elememt�� ������
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //element�� queue�迭
	int front, rear; //int�� ���� front, rear
}QueueType; //QueueType ����ü

/* �Լ����� ������Ÿ�� */
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
    printf("[----- [�̵���] [2019038027] -----]\n\n");
	QueueType *cQ = createQueue(); //������cQ�� createQueue()�� ���ϰ��� ����Ŵ
	element data; //element�� ���� data ����

	char command; //char�� ���� command ����

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = "); //����Է� �޽��� ���
		scanf(" %c", &command); //command�� �Է¹޴´�

		switch(command) {
		case 'i': case 'I': //command�� i�� I�� ���
			data = getElement(); //data�� getElement()�� ���ϰ� ����
			enQueue(cQ, data); //enQueue�Լ� ����
			break;  //break
		case 'd': case 'D': //command�� d�� D�� ���
			deQueue(cQ,&data); //deQueue�Լ� ����
			break;  //break
		case 'p': case 'P': //command�� p�� P�� ���
			printQ(cQ); //printQ�Լ� ����
			break;  //break
		case 'b': case 'B': //command�� b�� B�� ���
			debugQ(cQ); //debug�Լ� ����
			break;  //break
		case 'q': case 'Q': //command�� q�� Q�� ���
			break; //break
		default: //�ٸ����� �Է��������
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //Concentratiom �޽��� ���
			break; //break
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� �Էµ� �� ���� �ݺ�


	return 1;
}

/* ť�� �����ϴ� �Լ� */
QueueType *createQueue()
{
	QueueType *cQ; //QueueType�� ������ *cQ ����
	cQ = (QueueType *)malloc(sizeof(QueueType)); //QueueType�� ũ�⸸ŭ�� �޸𸮸� �Ҵ��Ͽ� �ּҸ� cQ�����Ϳ� ����
	cQ->front = 0; //cQ�� ����ü ��� front�� �����Ͽ� 0 ����
	cQ->rear = 0; //cQ�� ����ü ��� rear�� �����Ͽ� 0 ����
	return cQ; //cQ��ȯ
}

/* ť�� �����ϴ� �Լ� */
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //cQ�� NULL�̶�� 1��ȯ
    free(cQ); //cQ�� �Ҵ�� �޸� ����
    return 1; //1��ȯ
}

/* element(���)�� ��� �Լ� */
element getElement()
{
	element item; //elemeent�� ���� item ����
	printf("Input element = "); //element�Է� �޽��� ���
	scanf(" %c", &item); //item�� �Է¹޴´�
	return item; //item�� ��ȯ
}

/* ����ť�� empty���� Ȯ���ϴ� �Լ� */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){ //����ü ��� front�� rear�� ���ٸ�
		printf("Circular Queue is empty!"); //����ť�� ����ٴ� �޽��� ���
		return 1; //1��ȯ
	}
	else return 0; //�ƴ϶�� 0��ȯ
}

/* ����ť�� Full���� Ȯ���ϴ� �Լ� */
int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { //����ü ��� rear�� ����ĭ�� front�� ���ٸ�
		printf(" Circular Queue is full!"); //����ť�� full�̶�� �޽��� ���
		return 1; //1��ȯ
	}
	else return 0; //�ƴ϶�� 0��ȯ
}

/* ť�� ��Ҹ� �߰��ϴ� �Լ� */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return; //ť�� full�̶�� return
	else { //full�� �ƴ϶��
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear�� rear�� ���� ĭ�� ����
		cQ->queue[cQ->rear] = item; //queue�迭�� rear�� item ����
	}
}


void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return; //ť�� empty��� return
	else { //full�� �ƴ϶��
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //front�� front�� ���� ĭ�� ����
		*item = cQ->queue[cQ->front]; //queue�迭�� front�� ���� item�� �ִ´�
		return;
	}
}

/* ����ť�� ����ϴ� �Լ� */
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first�� first ���� ĭ�� ����
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last�� rear�� ���� ĭ�� ����

	printf("Circular Queue : ["); 

	i = first; //i�� first�� �� ����
	while(i != last){ //i�� last�� ���� �� ���� �ݺ�
		printf("%3c", cQ->queue[i]); //queue�迭 ���
		i = (i+1)%MAX_QUEUE_SIZE; //i�� ����ĭ ���� (i+1)

	}
	printf(" ]\n");
}

/* ť�� ������ϴ� �Լ� */
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //MAX_QUEUE_SIZE��ŭ �ݺ�
	{
		if(i == cQ->front) { //i�� front�� ������
			printf("  [%d] = front\n", i); //front ���
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //queue�迭 ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front�� rear ���
}


