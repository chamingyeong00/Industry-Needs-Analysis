int main(int argc, char *argv[])
{
	int i,ch,temp[3];
	if(argc != 4)
	{
		printf("사용법 : %s [시작 단] [끝 단] [출력라인수]\n", argv[0]);
		printf("주의 : - 시작, 끝 단, 출력라인수는 1~99까지의 숫자만 넣으세요\n");
		printf("      - 시작 단이 끝 단 보다 크면 안됩니다\n");
		printf("예) %s 3 90 4\n",argv[0]);
		return 0;
	}
	for(i=1; i<3; i++) //시작, 끝단의 제한 
	{
		ch=atoi(argv[i]);
		temp[i]=ch;
	}
	if(temp[1] > temp[2]) //시작 단이 끝 단 보다 크지 않도록 제한
	temp[0]=atoi(argv[3]);
	googoo(temp[1], temp[2], temp[0]); //구구단
	return 0;
}
