#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define CRT_SECURE_NO_WARNINGS

#define MAX_STACK_SIZE 10 //���� ������ ����
#define MAX_EXPRESSION_SIZE 20 //expression ������ ����

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence; //������ ��Ī�� precedence�� ����

char infixExp[MAX_EXPRESSION_SIZE]; //infixExp �迭 ����
char postfixExp[MAX_EXPRESSION_SIZE]; //postfixExp �迭 ����
char postfixStack[MAX_STACK_SIZE]; //postfixStack �迭 ����
int evalStack[MAX_STACK_SIZE]; //evalStack �迭 ����

int postfixStackTop = -1; //postfixStackTop -1�� �ʱ�ȭ
int evalStackTop = -1;    //evackStackTop -1�� �ʱ�ȭ1

int evalResult = 0; //evalResult 0���� �ʱ�ȭ

/* �Լ����� ������Ÿ�� */
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    printf("[----- [�̵���] [2019038027] -----]\n\n");
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command); //��ɾ �Է¹޴´�

		switch(command) {
		case 'i': case 'I': //command�� i�� I�� ��
			getInfix();     //getInfix �Լ� ����
			break;  //break
		case 'p': case 'P': //command�� p�� P�� ��
			toPostfix();    //toPostfix �Լ� ����
			break;  //break
		case 'e': case 'E': //command�� e�� E�� ��
			evaluation();   //evaluation �Լ� ����
			break;  //break
		case 'd': case 'D': //command�� d�� D�� ��
			debug();    //debug �Լ� ����
			break;  //break
		case 'r': case 'R': //command�� r�̳� R�� ��
			reset();    //reset �Լ� ����
			break;  //break
		case 'q': case 'Q': //command�� q�� Q�� ��
			break;  //break
		default: //�ٸ����� �Է� ���� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //concentration �޽��� ���
			break;  //break
		}

	}while(command != 'q' && command != 'Q');   //q�� Q�� �Էµ� �� ���� �ݺ�

	return 1;


}

/* postfix push �Լ� */
void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //postfixStack�迭�� postfixStackTop ����ĭ�� x�� ����
}

/* postfix pop �Լ� */
char postfixPop()
{
	char x;
    if(postfixStackTop == -1) //postfixStack�� -1�̶��
        return '\0'; //'\0' ����
    else {  //�ƴ϶��
    	x = postfixStack[postfixStackTop--]; //x�� postfixStackTop�� ���� �ְ� postfixStackTop�� �ϳ� ���ҽ�Ų��
    }
    return x; //x ����
}

/* eval push �Լ� */
void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //evalStack �迭�� evalStackTop ����ĭ�� x�� ����
}

/* eval pop �Լ� */
int evalPop()
{
    if(evalStackTop == -1) //evalStackTop�� -1�̶��
        return -1; //-1 ����
    else    //�ƴ϶��
        return evalStack[evalStackTop--];   //evalStack�迭�� evalStackTop�� ��ȯ�ϰ� evalStackTop�� �ϳ� ���ҽ�Ų��
}

/*
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */

/* infix �� ��� �Լ� */
void getInfix()
{
    printf("Type the expression >>> "); //expression�� Ÿ���� ����� �޽��� ���
    scanf("%s",infixExp);   //infixExp�� �Է¹޴´�
}

/* Token�� ��� �Լ� */
precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen; //symbol�� '(' �̶�� 0 ����
	case ')' : return rparen; //symbol�� ')' �̶�� 9 ����
	case '+' : return plus;   //symbol�� '+' �̶�� 5 ����
	case '-' : return minus;  //symbol�� '-' �̶�� 4 ����
	case '/' : return divide; //symbol�� '/' �̶�� 6 ����
	case '*' : return times;  //symbol�� '*' �̶�� 7 ����
	default : return operand; //���� case�� ���ٸ� 1���� 
	}
}

/* priority�� ��� �Լ� */
precedence getPriority(char x)
{
	return getToken(x); //getToken�Լ��� ���ϰ� ����
}

/* �����ϳ��� ���޹޾�, postfixExp�� �߰� */

/* ���ڿ� �̾���̴� �Լ� */
void charCat(char* c)
{
	if (postfixExp == '\0') //postfixExp�� '\0'�ϰ��
		strncpy(postfixExp, c, 1); //c�� postfixExp�� 1��ŭ�� ����
	else //�ƴ϶��
		strncat(postfixExp, c, 1); //c�� postfixExp�ڷ� 1��ŭ �̾���δ�
}

/*
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */


void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp; //infixExp�� ����Ű�� ������ exp ����
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0') //���ڿ��� ������ �ݺ�
	{
		if(getPriority(*exp) == operand) //infixExp�� 1�̶��
		{
			x = *exp;   //infixExp�� x�� ����
        	charCat(&x); //charCat�Լ� ����
		}
        else if(getPriority(*exp) == lparen) { //infixExp�� 0�̶��

        	postfixPush(*exp);  //postfixPush�Լ� ����
        }
        else if(getPriority(*exp) == rparen) //infixexp�� 9���
        {
        	while((x = postfixPop()) != '(') { //'('�� ���ö����� �ݺ�
        		charCat(&x); //charCat�Լ� ����
        	}
        }
        else //�ƴ϶��
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //postfixStack�Լ��� postfixStacktop�� infixExp���� ���������� �ݺ�
            {
            	x = postfixPop(); //x�� postfixPop�Լ� ���� �� ����
            	charCat(&x); //charCat�Լ� ����
            }
            postfixPush(*exp); //postfixPush�Լ� ����
        }
        exp++; //exp 1����
	}

    while(postfixStackTop != -1) //postfixStackTop�� -1�� �ƴ϶�� �ݺ�
    {
    	x = postfixPop(); //x�� psotfixPop�Լ� ���� �� ����
    	charCat(&x); //charCat�Լ� ����
    }

}

/* ����� �Լ� */
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //infixExp ���
	printf("postExp =  %s\n", postfixExp); //postfixExp ���
	printf("eval result = %d\n", evalResult); //evalResult���

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);    //postfixStack�迭 ���

	printf("\n");

}

/* ���� �Լ� */
void reset()
{
	infixExp[0] = '\0';     //infixExp[0]�� '\0' ����
	postfixExp[0] = '\0';   //postfixExp[0]�� '\0' ����

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //postfixStack �迭 ���� '\0' ����
         
	postfixStackTop = -1;   //postfixStackTop�� -1 ����
	evalStackTop = -1;      //evalStackTop�� -1 ����
	evalResult = 0;         //evalResult�� 0 ����
}

/* ����ϴ� �Լ� */
void evaluation()
{
	int opr1, opr2, i;  //������ ���� opr1, opr2, i ����

	int length = strlen(postfixExp); //length�� postfixexp�� ���� ����
	char symbol; //char�� ���� symbol ����
	evalStackTop = -1;  //evalStackTop�� -1 ����

	for(i = 0; i < length; i++) //postfixexp�� ���̸�ŭ �ݺ�
	{
		symbol = postfixExp[i]; //symbol�� postfixexp[i] ����
		if(getToken(symbol) == operand) { //symbol�� 1�̶��
			evalPush(symbol - '0'); //evalPush�Լ� ����
		}
		else { //�ƴ϶��
			opr2 = evalPop(); //opr2�� evalpop�Լ��� ���ϰ� ����
			opr1 = evalPop(); //opr1�� evalpop�Լ��� ���ϰ� ����
			switch(getToken(symbol)) {
			    case plus: evalPush(opr1 + opr2); break; //opr1�� opr2�� ���� �� evalPush�Լ� ����
			    case minus: evalPush(opr1 - opr2); break; //opr1�� opr2�� �� �� evalPush�Լ� ����
			    case times: evalPush(opr1 * opr2); break; //opr1�� opr2�� ���� �� evalPush�Լ� ����
			    case divide: evalPush(opr1 / opr2); break; //op1�� opr2�� ���� �� evalPush�Լ� ����
			    default: break; //���� case�� ���ٸ� break
			}
		}
	}
	evalResult = evalPop(); //evalPop�Լ��� ���ϰ��� evalResult�� ����
}

