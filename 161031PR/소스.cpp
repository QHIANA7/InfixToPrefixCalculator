#include "std.h"


typedef struct StackTypeChar {
	char stack[MAX_STACK_SIZE];
	int top;
} StackTypeChar;

// ���� �ʱ�ȭ �Լ�
void init(StackTypeChar *s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackTypeChar *s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackTypeChar *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackTypeChar *s, char item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// �����Լ�
char pop(StackTypeChar *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// ��ũ�Լ�
char peek(StackTypeChar *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top];
}

// �������� �켱������ ��ȯ�Ѵ�.
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char exp[],char* postfix)
{
	int i = 0, cnt = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackTypeChar s;

	init(&s);					// ���� �ʱ�ȭ 
	for (i = 0; i<len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // ������
												// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				postfix[cnt] = pop(&s);
				cnt++;
			}
			push(&s, ch);
			break;
		case '(':	// ���� ��ȣ
			push(&s, ch);
			break;
		case ')':	// ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���
			while (top_op != '(') {
				postfix[cnt] = top_op;
				cnt++;
				top_op = pop(&s);
			}
			break;
		default:		// �ǿ�����
			postfix[cnt] = ch;
			cnt++;
			break;
		}
	}
	while (!is_empty(&s))	// ���ÿ� ����� �����ڵ� ���
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

// ���� �ʱ�ȭ �Լ�
void init_int(StackTypeInt *s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty_int(StackTypeInt *s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full_int(StackTypeInt *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push_int(StackTypeInt *s, int item)
{
	if (is_full_int(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// �����Լ�
int pop_int(StackTypeInt *s)
{
	if (is_empty_int(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// ��ũ�Լ�
int peek_int(StackTypeInt *s)
{
	if (is_empty_int(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top];
}
// ���Լ�


// ���� ǥ�� ���� ��� �Լ�
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
			value = ch - '0';	// �Է��� �ǿ������̸�
			push_int(&s, value);
		}
		else {	//�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop_int(&s);
			op1 = pop_int(&s);
			switch (ch) { //������ �����ϰ� ���ÿ� ���� 
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
	char form[100]; //���� ���� 100
	char postfix[100] = {}; //��ȯ�� ����ǥ��� �����


	printf("������ �Է��Ͻÿ�. (�� : (2+3)*4+9 )\n(��, �ǿ����ڴ� 1�� �ڸ� ���� �Է��� ��) >>");
	scanf_s("%s", &form, sizeof(form));

	infix_to_postfix(form, postfix);	//���� �Է��� ������ ����ǥ������� ��ȯ

	result = eval(postfix);	//����ǥ��� ��꿡 ��ȯ�� ����ǥ��� ����

	printf("����ǥ����� %s\n", &postfix);	//����ǥ��� ��ȯ ��� ���
	printf("������� %d\n", result);


	return 0;
}
