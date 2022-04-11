#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define CRT_SECURE_NO_WARNINGS

#define MAX_STACK_SIZE 10 //스택 사이즈 정의
#define MAX_EXPRESSION_SIZE 20 //expression 사이즈 정의

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence; //열거형 별칭을 precedence로 정의

char infixExp[MAX_EXPRESSION_SIZE]; //infixExp 배열 선언
char postfixExp[MAX_EXPRESSION_SIZE]; //postfixExp 배열 선언
char postfixStack[MAX_STACK_SIZE]; //postfixStack 배열 선언
int evalStack[MAX_STACK_SIZE]; //evalStack 배열 선언

int postfixStackTop = -1; //postfixStackTop -1로 초기화
int evalStackTop = -1;    //evackStackTop -1로 초기화1

int evalResult = 0; //evalResult 0으로 초기화

/* 함수들의 프로토타입 */
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
    printf("[----- [이동현] [2019038027] -----]\n\n");
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command); //명령어를 입력받는다

		switch(command) {
		case 'i': case 'I': //command가 i나 I일 때
			getInfix();     //getInfix 함수 실행
			break;  //break
		case 'p': case 'P': //command가 p나 P일 때
			toPostfix();    //toPostfix 함수 실행
			break;  //break
		case 'e': case 'E': //command가 e나 E일 때
			evaluation();   //evaluation 함수 실행
			break;  //break
		case 'd': case 'D': //command가 d나 D일 때
			debug();    //debug 함수 실행
			break;  //break
		case 'r': case 'R': //command가 r이나 R일 때
			reset();    //reset 함수 실행
			break;  //break
		case 'q': case 'Q': //command가 q나 Q일 때
			break;  //break
		default: //다른값을 입력 했을 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //concentration 메시지 출력
			break;  //break
		}

	}while(command != 'q' && command != 'Q');   //q나 Q가 입력될 때 까지 반복

	return 1;


}

/* postfix push 함수 */
void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //postfixStack배열의 postfixStackTop 다음칸에 x를 저장
}

/* postfix pop 함수 */
char postfixPop()
{
	char x;
    if(postfixStackTop == -1) //postfixStack이 -1이라면
        return '\0'; //'\0' 리턴
    else {  //아니라면
    	x = postfixStack[postfixStackTop--]; //x에 postfixStackTop의 값을 넣고 postfixStackTop을 하나 감소시킨다
    }
    return x; //x 리턴
}

/* eval push 함수 */
void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //evalStack 배열의 evalStackTop 다음칸에 x를 저장
}

/* eval pop 함수 */
int evalPop()
{
    if(evalStackTop == -1) //evalStackTop이 -1이라면
        return -1; //-1 리턴
    else    //아니라면
        return evalStack[evalStackTop--];   //evalStack배열의 evalStackTop을 반환하고 evalStackTop을 하나 감소시킨다
}

/*
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

/* infix 를 얻는 함수 */
void getInfix()
{
    printf("Type the expression >>> "); //expression의 타입을 고르라는 메시지 출력
    scanf("%s",infixExp);   //infixExp를 입력받는다
}

/* Token을 얻는 함수 */
precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen; //symbol이 '(' 이라면 0 리턴
	case ')' : return rparen; //symbol이 ')' 이라면 9 리턴
	case '+' : return plus;   //symbol이 '+' 이라면 5 리턴
	case '-' : return minus;  //symbol이 '-' 이라면 4 리턴
	case '/' : return divide; //symbol이 '/' 이라면 6 리턴
	case '*' : return times;  //symbol이 '*' 이라면 7 리턴
	default : return operand; //위의 case에 없다면 1리턴 
	}
}

/* priority를 얻는 함수 */
precedence getPriority(char x)
{
	return getToken(x); //getToken함수의 리턴값 리턴
}

/* 문자하나를 전달받아, postfixExp에 추가 */

/* 문자열 이어붙이는 함수 */
void charCat(char* c)
{
	if (postfixExp == '\0') //postfixExp가 '\0'일경우
		strncpy(postfixExp, c, 1); //c를 postfixExp로 1만큼만 복사
	else //아니라면
		strncat(postfixExp, c, 1); //c를 postfixExp뒤로 1만큼 이어붙인다
}

/*
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */


void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp; //infixExp를 가리키는 포인터 exp 선언
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') //문자열의 끝까지 반복
	{
		if(getPriority(*exp) == operand) //infixExp가 1이라면
		{
			x = *exp;   //infixExp를 x에 저장
        	charCat(&x); //charCat함수 실행
		}
        else if(getPriority(*exp) == lparen) { //infixExp가 0이라면

        	postfixPush(*exp);  //postfixPush함수 실행
        }
        else if(getPriority(*exp) == rparen) //infixexp가 9라면
        {
        	while((x = postfixPop()) != '(') { //'('가 나올때까지 반복
        		charCat(&x); //charCat함수 실행
        	}
        }
        else //아니라면
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //postfixStack함수의 postfixStacktop이 infixExp보다 작을떄까지 반복
            {
            	x = postfixPop(); //x에 postfixPop함수 리턴 값 저장
            	charCat(&x); //charCat함수 실행
            }
            postfixPush(*exp); //postfixPush함수 실행
        }
        exp++; //exp 1증가
	}

    while(postfixStackTop != -1) //postfixStackTop이 -1이 아니라면 반복
    {
    	x = postfixPop(); //x에 psotfixPop함수 리턴 값 저장
    	charCat(&x); //charCat함수 실행
    }

}

/* 디버그 함수 */
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //infixExp 출력
	printf("postExp =  %s\n", postfixExp); //postfixExp 출력
	printf("eval result = %d\n", evalResult); //evalResult출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);    //postfixStack배열 출력

	printf("\n");

}

/* 리셋 함수 */
void reset()
{
	infixExp[0] = '\0';     //infixExp[0]에 '\0' 저장
	postfixExp[0] = '\0';   //postfixExp[0]에 '\0' 저장

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //postfixStack 배열 전부 '\0' 저장
         
	postfixStackTop = -1;   //postfixStackTop에 -1 저장
	evalStackTop = -1;      //evalStackTop에 -1 저장
	evalResult = 0;         //evalResult에 0 저장
}

/* 계산하는 함수 */
void evaluation()
{
	int opr1, opr2, i;  //정수형 변수 opr1, opr2, i 선언

	int length = strlen(postfixExp); //length에 postfixexp의 길이 저장
	char symbol; //char형 변수 symbol 선언
	evalStackTop = -1;  //evalStackTop에 -1 저장

	for(i = 0; i < length; i++) //postfixexp의 길이만큼 반복
	{
		symbol = postfixExp[i]; //symbol에 postfixexp[i] 저장
		if(getToken(symbol) == operand) { //symbol이 1이라면
			evalPush(symbol - '0'); //evalPush함수 실행
		}
		else { //아니라면
			opr2 = evalPop(); //opr2에 evalpop함수의 리턴값 저장
			opr1 = evalPop(); //opr1에 evalpop함수의 리턴값 저장
			switch(getToken(symbol)) {
			    case plus: evalPush(opr1 + opr2); break; //opr1과 opr2를 더한 후 evalPush함수 실행
			    case minus: evalPush(opr1 - opr2); break; //opr1와 opr2를 뺀 후 evalPush함수 실행
			    case times: evalPush(opr1 * opr2); break; //opr1과 opr2를 곱한 후 evalPush함수 실행
			    case divide: evalPush(opr1 / opr2); break; //op1과 opr2를 나눈 후 evalPush함수 실행
			    default: break; //위의 case가 없다면 break
			}
		}
	}
	evalResult = evalPop(); //evalPop함수의 리턴값을 evalResult에 저장
}

