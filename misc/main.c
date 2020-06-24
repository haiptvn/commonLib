#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define DEBUG

#ifdef DEBUG
#define PRINT(ftm, ...) printf(ftm, __VA_ARGS__)
#else
#define PRINT(ftm, ...) 
#endif

struct KeyValue
{
	const char* key;
	int key_len;
	char* value;
	int value_len;
} Pairs[20];
struct Simple_Parser
{
	struct KeyValue* const pst;
} SimpleParser_st = { 
	.pst = Pairs 
};

int GetValueByKey(const char* filename_pchr,
	uint8_t mode_u8, const char* key_pcchr, char* value_pchr)
{
	FILE* fp = fopen(filename_pchr, "a+");

	if (NULL == fp) { perror(""); return -1;}
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	printf("Size of file: %lu \n", filesize);
	char* read_buf = malloc(filesize + 1);

	size_t readbyte = fread(read_buf, 1, filesize, fp);
	if (readbyte != filesize)
	{
		printf("An error occured.\n");
	}
	fclose(fp);
	read_buf[filesize] = '\0';
	printf("READ:%s\n", read_buf);
	int j = 0;
	for (int i = 0; (i <= filesize) && (read_buf[i] != '\0'); i++)
	{
		if ('#' == read_buf[i])
		{
			SimpleParser_st.pst[j].key = &read_buf[i + 1];
			printf("key[%d]: %s\n", j, SimpleParser_st.pst[j].key);
		}
		else if ('=' == read_buf[i])
		{
			SimpleParser_st.pst[j].value = &read_buf[i + 1];
			SimpleParser_st.pst[j].key_len = &read_buf[i] - SimpleParser_st.pst[j].key;
			printf("value[%d]: %s\n", j, SimpleParser_st.pst[j].value);
			printf("key len[%d]: %d\n", j, SimpleParser_st.pst[j].key_len);
		}
		else if (';' == read_buf[i])
		{
			SimpleParser_st.pst[j].value_len = &read_buf[i] - SimpleParser_st.pst[j].value;
			printf("value len[%d]: %d\n",j, SimpleParser_st.pst[j].value_len);
			j++;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		if (SimpleParser_st.pst[i].key_len != 0)
		{
			printf("%.*s", SimpleParser_st.pst[i].key_len, SimpleParser_st.pst[i].key);
			printf("=>");
			printf("%.*s\n", SimpleParser_st.pst[i].value_len, SimpleParser_st.pst[i].value);
		}
		else
		{
			break;
		}
	}

	if (0u == mode_u8)
	{
		
		

	}

	return 0;
}


int main(int argc, char* agrs[])
{
	char buf[100] = { 0 };
	(void)GetValueByKey("file.txt", 0, "ecu_name", buf);

	return 0;
}