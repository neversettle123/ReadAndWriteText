// text.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include"getopt.h"
#include<iomanip>
#include<algorithm>
#include<stdio.h>

using namespace std;

struct student
{
	int id;
	char name[20];
	int  Chinese;
	int Math;
	int English;
	int Physics;
	int Chemistry;
	int PE;
};

enum OPTION
{
	OT_NONE = 0,
	OT_EXIT = 1,
	OT_LOADFILE = 2,
	OT_SAVEFILE = 3,
	OT_MODIFY = 4,
	OT_PRINT = 5,
	OT_FIND = 6

};
struct CmdLine
{
	OPTION ot;
	union CmdLineData
	{
		struct LoadData
		{
			char * filepath;
		}ld;
		struct SaveData
		{
			char * filepath;
		}sd;
		struct ModifyData
		{
			int user_id;
			char name[20];
			int  Chinese;
			int  Math;
			int English;
			int Physics;
			int Chemistry;
			int PE;
		}md;
		struct FIND
		{
			int user_id;
		}fd;
	} cld;
};

void PrintUsage();
bool loadfile(char *);
bool savefile(char *);
void print();
bool selete(int);
void modify(int, char *, int, int, int, int, int, int);
CmdLine GetUserInput(char *, CmdLine &);

student * s_data = nullptr;
int s_data_num = 0;
int s_real_num = 0;


void disptchcmd(CmdLine & cl)
{
	switch (cl.ot)
	{
	case OT_NONE:
		break;
	case OT_EXIT:
		exit(EXIT_FAILURE);
		break;
	case OT_LOADFILE:
		loadfile(cl.cld.ld.filepath);
		break;
	case OT_SAVEFILE:
		savefile(cl.cld.sd.filepath);
		break;
	case OT_PRINT:
		print();
		break;
	case OT_FIND:
		selete(cl.cld.fd.user_id);
		break;
	case OT_MODIFY:
		modify(cl.cld.md.user_id, cl.cld.md.name,
			cl.cld.md.Chinese, cl.cld.md.Math, cl.cld.md.English,
			cl.cld.md.Physics, cl.cld.md.Chemistry, cl.cld.md.PE);
		break;

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	PrintUsage();
	while (true)
	{
		char yhInput[512];
		cin.getline(yhInput, 512);
		CmdLine cl;
		GetUserInput(yhInput, cl);
		disptchcmd(cl);
	}

	
	return 0;
}

void PrintUsage()
{
	cout << "--------------------\n";
	cout << "\twelcome\t\n ";
	cout << "--------------------\n";
	cout << "<-l>" << ": loadfile.\n";
	cout << "<-s>" << ": savefile.\n";
	cout << "<-p>" << ": print.\n";
	cout << "<-f>" << ": find.\n";
	cout << "<-m>" << ": modify.\n";
	cout << "<-e>" << ": exit.\n";
	cout << "The option: \n";
}

CmdLine  GetUserInput(char * a, CmdLine & cl)
{
	int argc = 0;
	char * argv[128];
	argv[argc++] = "Score.exe";
	char * token = strtok(a, " ");
	argv[argc++] = token;
	if (token)
	{
		token = strtok(NULL, " ");
		argv[argc++] = token;
	}
	int oc = 0;
	if ((oc = getopt(argc, argv, "l:s:pf:m:e")) != -1)
	{
		switch (oc)
		{
		case 'l':
			cl.ot = OT_LOADFILE;
			cout << "load: " << optarg << endl;
			cl.cld.ld.filepath = optarg;
			
			break;
		case 's':
			cl.ot = OT_SAVEFILE;
			cout << "save: " << optarg << endl;
			cl.cld.sd.filepath = optarg;
			
			break;
		case 'p':
			cl.ot = OT_PRINT;
			break;
		case 'f':
			cl.ot = OT_FIND;
			break;
		case 'm':
			cl.ot = OT_MODIFY;
			if (optind < argc)
			{
				cl.cld.md.user_id = atoi(argv[optind]);
				strcpy(cl.cld.md.name, argv[optind++]);
				cl.cld.md.Chinese = atoi(argv[optind++]);
				cl.cld.md.Math = atoi(argv[optind++]);
				cl.cld.md.English = atoi(argv[optind++]);
				cl.cld.md.Physics = atoi(argv[optind++]);
				cl.cld.md.Chemistry = atoi(argv[optind++]);
				cl.cld.md.PE = atoi(argv[optind++]);
			}
		case 'e':
			cl.ot = OT_EXIT;
			break;

		default:
			break;
		}
	}
	return cl;
}

bool realloc(int new_size)
{
	if (new_size > s_data_num)
	{
		student * new_data = new student[new_size];
		memcpy(new_data, s_data, sizeof(student)*s_data_num);
		delete[]s_data;
		s_data = new_data;
		s_data_num = new_size;
	}
	return true;
}

bool loadfile(char * a)
{
	FILE*fp = fopen(a, "r");
	if (!fp)
	{
		return false;
	}
	char line[1024];
	fgets(line, sizeof(line), fp);

	while (fgets(line, sizeof(line), fp))
	{
		if (s_real_num = s_data_num)
		{
			if (!realloc(max(s_data_num, 20) * 2))
			{
				return false;
			}
		}
		student *stu_data = &s_data[s_real_num];

		char * token;
		token = strtok(line, " ");
		if (!token)
		{
			continue;
		}
		stu_data->id = atoi(token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		strcpy(stu_data->name, token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		stu_data->Chinese = atoi(token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		stu_data->Math = atoi(token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		stu_data->English = atoi(token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		stu_data->Physics = atoi(token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		stu_data->Chemistry = atoi(token);

		token = strtok(NULL, " ");
		if (!token)
		{
			continue;
		}
		stu_data->PE = atoi(token);

		s_real_num++;
	}
}

bool savefile(char * a)
{
	FILE * fp = fopen(a, "w");
	if (!fp)
	{
		return false;
	}
	char * title = "  id name Chinese Math English Physics Chemicstry PE\n";
	char buffer[512];
	for (int i = 0; i < s_real_num; i++)
	{
		int len = sprintf(buffer, "%2d %2d %10s %2d %2d %2d %2d %2d %2d\n", i,
			s_data[i].id, s_data[i].name, s_data[i].Chinese, s_data[i].Math,
			s_data[i].English, s_data[i].Physics, s_data[i].Chemistry, s_data[i].PE);
		fwrite(buffer, len, 1, fp);
	}
	fclose(fp);
	return true;
}

void print()
{
	cout << "students' informatiom: \n";
	for (int i = 0; i < s_real_num; i++)
	{
		cout << setw(2) << i << ": " << s_data[i].id << setw(10) << s_data[i].name
			<< setw(7) << s_data[i].Chinese << setw(7)
			<< s_data[i].Math << setw(7) << s_data[i].English << setw(7) <<
			s_data[i].Physics << setw(7) << s_data[i].Chemistry
			<< setw(7) << s_data[i].PE << endl;
	}
}

bool selete(int user_id)
{
	for (int i = 0; i < s_real_num; i++)
	{
		if (s_data[i].id = user_id)
		{
			cout << "The student's informatiom is：\n";
			cout << setw(2) << i << ": " << s_data[i].id << setw(10) << s_data[i].name
				<< setw(5) << s_data[i].Chinese << setw(5)
				<< s_data[i].Math << setw(5) << s_data[i].English << setw(5) <<
				s_data[i].Physics << setw(5) << s_data[i].Chemistry
				<< setw(5) << s_data[i].PE << endl;
		}
	}
	return true;
}

void modify(int a1, char *a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	for (int i = 0; i < s_real_num; i++)
	{
		if (s_data[i].id = a1)
		{
			cout << "The student's informatiom is：\n";
			cout << setw(2) << i << ": " << s_data[i].id << setw(10) << s_data[i].name
				<< setw(5) << s_data[i].Chinese << setw(5)
				<< s_data[i].Math << setw(5) << s_data[i].English << setw(5) <<
				s_data[i].Physics << setw(5) << s_data[i].Chemistry
				<< setw(5) << s_data[i].PE << endl;
			cout << "Here are the new informations: \n";
			strcpy(s_data[i].name, a2);
			s_data[i].Chinese = a3;
			s_data[i].Math = a4;
			s_data[i].English = a5;
			s_data[i].Physics = a6;
			s_data[i].Chemistry = a7;
			s_data[i].PE = a8;
			cout << setw(2) << i << ": " << a1 << setw(7) << s_data[i].name << setw(7)
				<< s_data[i].Chinese << setw(7) << s_data[i].Math << setw(7) <<
				s_data[i].English << setw(7) << s_data[i].Physics << setw(7) <<
				s_data[i].Chemistry << setw(7) << s_data[i].PE << endl;
		}
	}
}



















