#include "TM4C123GH6PM.h"
#include "BlueTooth.h"
#include "Keypad.h"
#include "Lock.h"
#include "Reset Password.h"
#include "Init.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ROOMS 2 //Number of Rooms
#define PASS_LENGTH 4 //Length of Password
#define ROOM_NUMBER_LENGTH 2

int dstrcmp(char a[],char b [],int len){
	for (int i=0; i<len;i++){
		if (a[i] != b[i]) return 1;
	}
	return 0;
}

int main()
{
	char pass[PASS_LENGTH]=""; //Reference Password, from Bluetooth
	char s[PASS_LENGTH]=""; //Password, from Keypad
	int count=0; //Counter, for End of Password
	int kcount=0; //Counter, for End of Password
	char c; //Received Character 
	int found = 0; //Flag for Locating Room
	char room_id[ROOMS][ROOM_NUMBER_LENGTH] = {""}; //Room Number
	int room_number = 0; //Room Number in System
	char room_pass[ROOMS][PASS_LENGTH]={}; //Password Container for All Rooms
	int window = 0; //For Displaying The Message on PC screen
	int done = 0; //For Identifying When a Valid Response is made
	char prev_stat[ROOMS]; //Necessary for Cleaning Option
	char status[ROOMS]; //Room Status
	char temp[5]=""; //Container for Conversion
	int setup = 0;
	porTA_init();
	porTB_init();
	PortF(0xFF,0,0);
	BTInit();
	for (int i = 0; i<ROOMS;i++){
		prev_stat[i]='0';
		status[i]='0';
	}
	count=0;
	GPIOF->DATA |= 0x04;
	if((GPIO_PORTF_DATA_R & (1<<4)) == 0){
				close_the_lock();
	} //Lock Door
	while(1){
		if(window == 0 && setup == 0){
			BTSendString("Hello, Welcome to our Hotel System\nPress any key to Start Entering Room Numbers ......\n");
			window = 1;
		}
		else if (window == 0 && setup == 1){
			BTSendString("Hello, Welcome to our Hotel System\nPress any key to Start ......\n");
			window = 1;
		}
		if(BTGetChar()!='x' && setup == 0){
			BTSendString("Start Entering:\n");
			for (int i = 0; i < ROOMS; i++){
				for(int j = 0; j < ROOM_NUMBER_LENGTH; j++){
					do{
						c = BTGetChar();
					}while(c == 'x');
					room_id[i][j] = c;
					BTSendChar(c);
				}
				BTSendString("\n");
			}
			BTSendString("Setup Complete\nPress any key to show options\n");
			setup = 1;
		}
		else if(BTGetChar()!='x' && setup == 1){
		//input occurs when c!=x, from bluetooth or from keypad
		do{
			BTSendString("Rooms in Hotel: ");
			for(int i = 0; i < (ROOMS-1); i++){	
				for(int j = 0; j< (ROOM_NUMBER_LENGTH);j++){
					BTSendChar(room_id[i][j]);
				}
				BTSendString(",");
			}
			BTSendString(room_id[ROOMS-1]);
			BTSendString("\n");
			BTSendString("Choose the Room : ");
			char d[ROOM_NUMBER_LENGTH] = "";
			for(int i = 0; i<ROOM_NUMBER_LENGTH; i++){
					do{
						c = BTGetChar();
					}while(c == 'x');
				d[i] = c;
			}
			for(int i = 0; i<ROOMS; i++){
				if (dstrcmp(d,room_id[i],ROOM_NUMBER_LENGTH) == 0){
					found = 1;
					room_number = i;
					break;
				}
			}	
			if (found == 0){
				BTSendString("Room not Found, Try Again\n");
			}
		}while(found==0);
		found = 0; // Get Room Number from User
		if (status[room_number] == '0'){// Get Pass First from PC via Bluetooth
			done = 0;
			do{
				BTSendString("\nDo you wish to Reserve the Room, or Clean it?   (enter \"r\" or \"c\") : ");
				do{
					c = BTGetChar();
					if (c=='r'){
						BTSendString("\nEnter Room Pass (Numbers Only) : ");
						do{
							c = BTGetChar();
							switch (c){
								case('0'):if(count!=PASS_LENGTH){room_pass[room_number][count]='0';count++;}break;
								case('1'):if(count!=PASS_LENGTH){room_pass[room_number][count]='1';count++;}break;
								case('2'):if(count!=PASS_LENGTH){room_pass[room_number][count]='2';count++;}break;
								case('3'):if(count!=PASS_LENGTH){room_pass[room_number][count]='3';count++;}break;
								case('4'):if(count!=PASS_LENGTH){room_pass[room_number][count]='4';count++;}break;
								case('5'):if(count!=PASS_LENGTH){room_pass[room_number][count]='5';count++;}break;
								case('6'):if(count!=PASS_LENGTH){room_pass[room_number][count]='6';count++;}break;
								case('7'):if(count!=PASS_LENGTH){room_pass[room_number][count]='7';count++;}break;
								case('8'):if(count!=PASS_LENGTH){room_pass[room_number][count]='8';count++;}break;
								case('9'):if(count!=PASS_LENGTH){room_pass[room_number][count]='9';count++;}break;
							}
						}while(count!=PASS_LENGTH);
						status[room_number]='1';
						BTSendString("\nRoom reserved, Returning to Main Screen\n");
						count=0;
						done = 1;
					}
					else if (c=='c'){
						BTSendString("Room will be Cleaned shortly\nThank you for Choosing our Hotel");
						prev_stat[room_number]=status[room_number];
						status[room_number]='2';
						done = 1;
					}
				}while (c=='x');
					 if (done ==0){
						BTSendString("Response not Found, Please Try Again\n");
					 }						 
			}while(done == 0);
			window=0;
		}
		else if(status[room_number]=='1'){
			do{
				BTSendString("Do you want to Clean the Room or End the Reservation? (enter \"c\" or \"e\") : ");
				do{
					c = BTGetChar();
					if(c == 'c'){
						BTSendString("Room will be Cleaned, press enter on keypad to unlock ");
						prev_stat[room_number]=status[room_number];
						status[room_number]='2';
						done = 1;
					}
					else if(c == 'e'){
						BTSendString("Room will be Vacant Shortly\nThank you for Choosing our Hotel ");
						strcpy(room_pass[room_number],"");
						status[room_number]='0';
						close_the_lock();
						done = 1;
					}
				}while(c == 'x');
				if (done == 0){
						BTSendString("Response not Found, Please Try Again\n");
					 }	
			}while(done == 0);
				window=0;
			}
		else if(status[room_number]=='2'){
			done = 0;
			do{
				BTSendString("Room is Being Cleaned, Is the Cleaning Finished? (enter \"y\" or \"n\")");
				do{
					c = BTGetChar();
					if(c == 'y'){
						BTSendString("Room will be Relocked Shortly ");
						status[room_number]=prev_stat[room_number];
						prev_stat[room_number]='0';
						close_the_lock();
						done = 1;
					}
					else if (c=='n'){
						BTSendString("Waiting for cleaning to be Finished ");
						done = 1;
					}
				}while(c == 'x');
				if (done == 0){
						BTSendString("Response not Found, Please Try Again\n");
					 }
			}while(done==0);
			window=0;
		}
	}
		else if (getfromkeybad()!='x' && setup == 1){
			room_number=1;
			if(status[room_number] == '1'){
				c=getfromkeybad();
				if(c!='x') {
						switch(c){
							case('0'):if(kcount!=PASS_LENGTH){s[kcount]='0';kcount++;}break;
							case('1'):if(kcount!=PASS_LENGTH){s[kcount]='1';kcount++;}break;
							case('2'):if(kcount!=PASS_LENGTH){s[kcount]='2';kcount++;}break;
							case('3'):if(kcount!=PASS_LENGTH){s[kcount]='3';kcount++;}break;
							case('4'):if(kcount!=PASS_LENGTH){s[kcount]='4';kcount++;}break;
							case('5'):if(kcount!=PASS_LENGTH){s[kcount]='5';kcount++;}break;
							case('6'):if(kcount!=PASS_LENGTH){s[kcount]='6';kcount++;}break;
							case('7'):if(kcount!=PASS_LENGTH){s[kcount]='7';kcount++;}break;
							case('8'):if(kcount!=PASS_LENGTH){s[kcount]='8';kcount++;}break;
							case('9'):if(kcount!=PASS_LENGTH){s[kcount]='9';kcount++;}break;
							case('c'):strcpy(s,"");kcount=0;break; //clearing the string
							case('h'):if(kcount>0 && kcount<=PASS_LENGTH){s[kcount]=' ';kcount--;}break; //clearing the last bit
							case('e'):
								if(kcount == PASS_LENGTH && dstrcmp(s,room_pass[room_number],ROOM_NUMBER_LENGTH)==0)
								{
										open_the_lock();
										kcount = 0;
										strcpy(s,"");
								 //Open Door
								}
								else{
										close_the_lock();
										//Lock Door
									kcount = 0;
									strcpy(s,"");
								}
								break;
						}
				}
			while(c!='x'){c = getfromkeybad();} //won't take any input until it gets x;
			}
			else if(status[room_number] == '2'){
				do{
					c=getfromkeybad();
					if (c == 'e'){
						open_the_lock();
					}
				}while(c == 'x');
			}
		}
	}
}
