#include "std.h"


typedef struct StackTypeChar {
	char stack[MAX_STACK_SIZE];
	int top;
} StackTypeChar;

// 스택 초기화 함수
void init(StackTypeChar *s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackTypeChar *s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackTypeChar *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackTypeChar *s, char item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제함수
char pop(StackTypeChar *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// 피크함수
char peek(StackTypeChar *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top];
}

// 연산자의 우선순위를 반환한다.
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[],char* postfix)
{
	int i = 0, cnt = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackTypeChar s;

	init(&s);					// 스택 초기화 
	for (i = 0; i<len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // 연산자
												// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				postfix[cnt] = pop(&s);
				cnt++;
			}
			push(&s, ch);
			break;
		case '(':	// 왼쪽 괄호
			push(&s, ch);
			break;
		case ')':	// 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력
			while (top_op != '(') {
				postfix[cnt] = top_op;
				cnt++;
				top_op = pop(&s);
			}
			break;
		default:		// 피연산자
			postfix[cnt] = ch;
			cnt++;
			break;
		}
	}
	while (!is_empty(&s))	// 스택에 저장된 연산자들 출력
	{
		postfix[cnt] = pop(&s);
		cnt++;
	}
}
//===================================================================================================================================
typedef struct StackTypeI {
	int stack[MAX_STACK_SIZE];
	int top;
} StackTypeInt;

// 스택 초기화 함수
void init_int(StackTypeInt *s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty_int(StackTypeInt *s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full_int(StackTypeInt *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push_int(StackTypeInt *s, int item)
{
	if (is_full_int(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제함수
int pop_int(StackTypeInt *s)
{
	if (is_empty_int(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// 피크함수
int peek_int(StackTypeInt *s)
{
	if (is_empty_int(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top];
}
// 주함수


// 후위 표기 수식 계산 함수
int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackTypeInt s;

	init_int(&s);
	for (i = 0; i<len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';	// 입력이 피연산자이면
			push_int(&s, value);
		}
		else {	//연산자이면 피연산자를 스택에서 제거
			op2 = pop_int(&s);
			op1 = pop_int(&s);
			switch (ch) { //연산을 수행하고 스택에 저장 
			case '+': push_int(&s, op1 + op2); break;
			case '-': push_int(&s, op1 - op2); break;
			case '*': push_int(&s, op1*op2); break;
			case '/': push_int(&s, op1 / op2); break;
			}
		}
	}
	return pop_int(&s);
}



int main()
{
	int result = 0;
	char form[100]; //수식 길이 100
	char postfix[100] = {}; //변환된 후위표기식 저장소


	printf("수식을 입력하시오. (예 : (2+3)*4+9 )\n(단, 피연산자는 1의 자리 수만 입력할 것) >>");
	scanf_s("%s", &form, sizeof(form));

	infix_to_postfix(form, postfix);	//직접 입려한 수식을 후위표기식으로 변환

	result = eval(postfix);	//후위표기식 계산에 변환된 후위표기식 대입

	printf("후위표기식은 %s\n", &postfix);	//후위표기식 변환 결과 출력
	printf("결과값은 %d\n", result);


	return 0;
}
