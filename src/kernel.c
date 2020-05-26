void main()
{
	char* mem = (char*) 0xb8000;
	*mem = 'O';
	mem += 2;
	*mem = 'S';
	mem += 2;
	*mem = '8';
	mem += 2;
	*mem = ':';
	mem += 2;
	*mem = ' ';
	mem += 2;
	*mem = 'K';
	mem += 2;
	*mem = 'e';
	mem += 2;
	*mem = 'r';
	mem += 2;
	*mem = 'n';
	mem += 2;
	*mem = 'e';
	mem += 2;
	*mem = 'l';
}
