int static j = 20;

int fact(int n)
{
	if(n == 1)
		return 1;
	else
	{
		if( n != j )
		{
			return n*fact(n-1);
		}
		else
		{
			return n*fact(n-2);
		}
	}
}


int main(void)
{
	int i = 5;	
	fact(i);
	j = 10;
	fact(i);

	return 0;
}
