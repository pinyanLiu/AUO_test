#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <algorithm>
#include "SQLFunction.hpp"

using namespace std;
MYSQL *mysql_con = mysql_init(NULL);
MYSQL_RES *mysql_result;
MYSQL_ROW mysql_row;
char sql_buffer[2000] = {'\0'};
int row_totalNum, col_totalNum, error;

int fetch_row_value() {

	sent_query();
	mysql_result = mysql_store_result(mysql_con);
	if ((mysql_row = mysql_fetch_row(mysql_result)) != NULL) {

		row_totalNum = mysql_num_rows(mysql_result);
		col_totalNum = mysql_num_fields(mysql_result);
		error = 0;
	}
	else
		error = -1;

	mysql_free_result(mysql_result);
	memset(sql_buffer, 0, sizeof(sql_buffer));
	return error;
}

void sent_query() { mysql_query(mysql_con, sql_buffer); }

int turn_int(int col_num) {	

	if (mysql_row[col_num] != NULL)
		return atoi(mysql_row[col_num]); 
	else
		return -999;		
}

float turn_float(int col_num) { 
	
	if (mysql_row[col_num] != NULL)
		return atof(mysql_row[col_num]); 
	else
		return -999;
}

float turn_value_to_float(int col_num) {
	
	if (fetch_row_value() != -1) {

		float result = turn_float(col_num);
		return result;
	}
	else
		return -404;
}

int turn_value_to_int(int col_num) {

	if (fetch_row_value() != -1) {
		
		int result = turn_int(col_num);
		return result;
	}
	else
		return -404;
}

void messagePrint(int lineNum, const char *message, char contentSize, float content, char tabInHeader) {

	// tap 'Y' or 'N' means yes or no
	if (tabInHeader == 'Y')
		printf("\t");
	// tap 'I' or 'F' means int or float, otherwise no contents be showed.
	switch (contentSize)
	{
	case 'I':
		printf("LINE %d: %s%d\n", lineNum, message, (int)content);
		break;
	case 'F':
		printf("LINE %d: %s%f\n", lineNum, message, content);
		break;
	default:
		printf("LINE %d: %s\n", lineNum, message);
	}
}

void functionPrint(const char* functionName) {

	printf("\nFunction: %s\n", functionName);
}

int find_variableName_position(vector<string> variableNameArray, string target)
{
	auto it = find(variableNameArray.begin(), variableNameArray.end(), target);

	// If element was found
	if (it != variableNameArray.end())
		return (it - variableNameArray.begin());
	else
		return -1;
}

int *demand_response_info(int dr_mode)
{
	functionPrint(__func__);

	int *result = new int[5];
	snprintf(sql_buffer, sizeof(sql_buffer), "SELECT * FROM `demand_response` WHERE mode = %d", dr_mode);
	fetch_row_value();
	for (int i = 0; i < 5; i++)
	{
		result[i] = turn_int(i + 1);
	}

	messagePrint(__LINE__, "dr start time: ", 'I', result[0], 'Y');
	messagePrint(__LINE__, "dr end time: ", 'I', result[1], 'Y');
	messagePrint(__LINE__, "dr min decrease power: ", 'I', result[2], 'Y');
	messagePrint(__LINE__, "dr min feedback price: ", 'I', result[3], 'Y');
	messagePrint(__LINE__, "dr customer base line: ", 'I', result[4], 'Y');
	return result;
}

int flag_receive(string table_name, string table_variable_name) {

	snprintf(sql_buffer, sizeof(sql_buffer), "SELECT flag FROM `%s` WHERE variable_name = '%s' ", table_name.c_str(), table_variable_name.c_str());
	int flag = turn_value_to_int(0);
	return flag;
}

int value_receive(string table_name, string condition_col_name, string condition_col_target) {

	snprintf(sql_buffer, sizeof(sql_buffer), "SELECT value FROM `%s` WHERE `%s` = '%s' ", table_name.c_str(), condition_col_name.c_str(), condition_col_target.c_str());
	int reuslt = turn_value_to_int(0);
	return reuslt;
}

int value_receive(string table_name, string condition_col_name, int condition_col_number) {

	snprintf(sql_buffer, sizeof(sql_buffer), "SELECT value FROM `%s` WHERE `%s` = %d ", table_name.c_str(), condition_col_name.c_str(), condition_col_number);
	int reuslt = turn_value_to_int(0);
	return reuslt;
}

float value_receive(string table_name, string condition_col_name, string condition_col_target, char target_dataType) {

	snprintf(sql_buffer, sizeof(sql_buffer), "SELECT value FROM `%s` WHERE `%s` = '%s' ", table_name.c_str(), condition_col_name.c_str(), condition_col_target.c_str());
	float reuslt = turn_value_to_float(0);
	return reuslt;
}

float value_receive(string table_name, string condition_col_name, int condition_col_number, char target_dataType) {

	snprintf(sql_buffer, sizeof(sql_buffer), "SELECT value FROM `%s` WHERE `%s` = %d ", table_name.c_str(), condition_col_name.c_str(), condition_col_number);
	float reuslt = turn_value_to_float(0);
	return reuslt;
}