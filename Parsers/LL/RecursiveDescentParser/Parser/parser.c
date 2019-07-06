#include "parser.h"

void parse_input(char* input_str)
{
	token_lexeme token;
	int result = 0;

	set_input_stream(input_str);

	token = get_next_token();
	result = stmt(token);

	// �����������, ��� ���������������� ���� ������ ���������, � ��� �� ����� �������� ��������� ������
	printf("Result: %d\n", result);

	return;
}

static int stmt(token_lexeme token)
{
	int result = 0;

	switch (token.token)
	{
	case LP:
	case NUM:
		// expr ����� ���������� � ������������� ������ ��� ����� 			
		result = expr(token);
	default:
		break;
	}

	return result;
}


static int expr(token_lexeme token)
{
	token_lexeme tmp_token = token;
	int ret = 0;

	switch (tmp_token.token)
	{
	case NUM:
	case LP:
		ret = term(tmp_token);

		tmp_token = get_next_token();

		switch (tmp_token.token)
		{
		case PLUS:
			tmp_token = get_next_token();
			ret += expr(tmp_token);
			break;
		case RP:
			// ���� ����� ����� ������������� ������, ���������� ��� ����� � ������
			set_token_index(get_token_index() - 1);
		default:
			break;
		}

		break;
	default:
		break;
	}

	return ret;
}

static int term(token_lexeme token)
{
	token_lexeme tmp_token = token;
	int ret = 0;

	switch (tmp_token.token)
	{
	case LP:
	case NUM:
		ret = fact(tmp_token);

		tmp_token = get_next_token();

		switch (tmp_token.token)
		{
		case STAR:
			tmp_token = get_next_token();
			ret *= term(tmp_token);
			break;
		case PLUS:
		case RP:
			// ���� ����� ����� ����� ��� ������������� ������, ���������� ��� ����� � ������
			set_token_index(get_token_index() - 1);
		default:
			break;
		}
	default:
		break;
	}

	return ret;
}

static int fact(token_lexeme token)
{
	int ret = 0;
	token_lexeme tmp_token = token;

	switch (tmp_token.token)
	{
	case NUM:
		ret = atoi(&tmp_token.lexeme);
		break;
	case LP:
		tmp_token = get_next_token();
		ret = expr(tmp_token);
		tmp_token = get_next_token();	// ��������� ������������� ������
		break;
	default:
		break;
	}

	return ret;
}
