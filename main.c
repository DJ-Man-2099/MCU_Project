int main()
{
	int x=1;
	Portf_init();
	porTA_init();
	porTB_init();
	GPIOF->DATA = blue;
	Start_Timer();
	
	Setup();
	Clear();
	count=0;
	while(1)
	{
		c = getfromkeybad();
		//c_b = getfrombluetooth();
		//***********************************keypad
		//if(c!='x'){
			if (x==16) x=1;
			Send_Char_Pos(c,x,1);
			x++;
		//}
		if(c!='x')
		{
			switch (c)
			{
				case('0'):if(count!=4){s[count]='0';count++;}break;
				case('1'):if(count!=4){s[count]='1';count++;}break;
				case('2'):if(count!=4){s[count]='2';count++;}break;
				case('3'):if(count!=4){s[count]='3';count++;}break;
				case('4'):if(count!=4){s[count]='4';count++;}break;
				case('5'):if(count!=4){s[count]='5';count++;}break;
				case('6'):if(count!=4){s[count]='6';count++;}break;
				case('7'):if(count!=4){s[count]='7';count++;}break;
				case('8'):if(count!=4){s[count]='8';count++;}break;
				case('9'):if(count!=4){s[count]='9';count++;}break;
				case('c'):while(count!=-1){s[count]=' ';count--;}count++;break; //clearing the string
				case('h'):if(count>0){s[count]=' ';count--;}break; //clearing the last bit
				case('e'):
					if(count == 4)
					{
						count=0;
					while(count!=4)
					{
						if(s[count]!='0')
							iszero=0;
						count++;
					}
					count=0;
					if(!iszero)
					{
					while(count!=4)
					{
						pass[count]=s[count];
						count++;
					}
					count=0;
					enter_pass();
				  }
					iszero=1;
				}
					count=0;
					break;
			}
			while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();} //won't take any input until it gets x;  
		}
		
		/*if(c_b!='x')
		{
			switch (c)
			{
				case('0'):if(count_b!=4){s_b[count_b]='0';count_b++;}break;
				case('1'):if(count_b!=4){s_b[count_b]='1';count_b++;}break;
				case('2'):if(count_b!=4){s_b[count_b]='2';count_b++;}break;
				case('3'):if(count_b!=4){s_b[count_b]='3';count_b++;}break;
				case('4'):if(count_b!=4){s_b[count_b]='4';count_b++;}break;
				case('5'):if(count_b!=4){s_b[count_b]='5';count_b++;}break;
				case('6'):if(count_b!=4){s_b[count_b]='6';count_b++;}break;
				case('7'):if(count_b!=4){s_b[count_b]='7';count_b++;}break;
				case('8'):if(count_b!=4){s_b[count_b]='8';count_b++;}break;
				case('9'):if(count_b!=4){s_b[count_b]='9';count_b++;}break;
				case('c'):while(count_b!=-1){s_b[count_b]=' ';count_b--;}count_b++;break; //clearing the string
				case('h'):if(count_b>0){s[count_b]=' ';count_b--;}break; //clearing the last bit
				case('e'):
					if(count_b == 4)
					count_b=0;
					while(count_b!=4)
					{
						pass[count_b]=s[count_b];
						count_b++;
					}
					count_b=0;
					enter_pass();
					break;
			}
			while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();} //won't take any input until it gets x;  
		}*/
	}
}
