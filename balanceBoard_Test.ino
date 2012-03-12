

byte sendByte[22]={0xAA,0xA7,0xA1,0xB1,0x00,0x00,0x08,0x00,0xC1,0x01,0x00,0x02,0x00,0x03,0x00,0x04,0x00,0x7D,0x00,0x00,0x0D,0x0A};

unsigned int lfront;
unsigned int lback;
unsigned int rfront;
unsigned int rback;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(115200);
 
}

void loop() {

  analyze(1);
  analyze(2);

  sendByte[9]=(lfront<<8)>>8;
  sendByte[10]=lfront>>8;
  sendByte[11]=(lback<<8)>>8;
  sendByte[12]=lback>>8;
  sendByte[13]=(rfront<<8)>>8;
  sendByte[14]=rfront>>8;
  sendByte[15]=(rback<<8)>>8;
  sendByte[16]=rback>>8;
  Serial3.write(sendByte,22);
  /*
  Serial.println("------------");
  Serial.println(lfront);
  Serial.println(lback);
  Serial.println(rfront);
  Serial.println(rback);
  Serial.println("------------");
  */
  /*
		   if (Serial3.available()) {
   		   comingByte = Serial3.read();
   		   Serial.println(comingByte);
   		   Serial3.flush();
   		   }
   		 */
  delay(5);
}



/*分辨数据来自A通道还是B通道*/
char  getChannel(byte indentcode){
  char channel = '0';
  
 // Serial.print("Byte is  ");
  //Serial.println(channel);
  if((indentcode & B00000010) == B00000010)		channel = 'A';
  else		channel = 'B';
  //Serial.print("result is  ");
  //Serial.println(channel);
  return channel;
}



void analyze(byte numcom){
  unsigned int intdatalow;
  unsigned int intdatahigh;

  //byte bytedata[21]={0x00,0x00,0x00,0x00,0x01,0x12,0x34,0x2B,0x2B,0x0F,0x00,0x00,0x00,0x00,0x01,0x11,0x23,0x2B,0x2B};
  byte bytedata[21]={
    0x00  };
  char chardatalow[4]={
    0  };
  char chardatahigh[2]={
    0  };
  int i;
  if(numcom==1){

    if(Serial1.available()>=22){

      if(Serial1.read()==0x0F){

        for(i=0;i<21;i++){
          bytedata[i] = Serial1.read();
          // Serial.write(bytedata[i]);

        }
		getData(bytedata,1);
        Serial1.flush();
      }
    }
    //Serial1.flush();
  }
  else if(numcom==2){

    if(Serial2.available()>=21){

      if(Serial2.read()==0x0F){

        for(i=0;i<21;i++){
          bytedata[i] = Serial2.read();
          //Serial.write(bytedata[i]);

        }

        getData(bytedata,2);
        Serial2.flush();
      }
    }
  }
  //Serial2.flush();
}


/*
void getData(byte *bytedata ,byte numcom){
  unsigned int intdatalow;
  unsigned int intdatahigh;
  unsigned int data1;
  unsigned int data2;
  // 示例数据:  00 00 00 00 00 00 00 00 55 5A 0F 00 00 00 00 00 00 00 00 57 58
  

  //byte bytedata[19] = {0x00,0x00,0x00,0x00,0x01,0x12,0x34,0x2B,0x2B,0x0F,0x00,0x00,0x00,0x00,0x01,0x11,0x23,0x2B,0x2B};
  char chardatalow[4] = {0};
  char chardatahigh[4]= {0};


  if(bytedata[10] == 0x0F){
    
	intdatalow = (bytedata[6]<<8)+bytedata[7];
    sprintf(chardatalow, "%x", intdatalow);
    intdatalow=atoi(chardatalow);

    intdatahigh = bytedata[5];
    sprintf(chardatahigh,"%x",intdatahigh);
    intdatahigh = atoi(chardatahigh);
	data1= intdatahigh*10000+intdatalow;

    intdatalow = (bytedata[16]<<8)+bytedata[17];
    sprintf(chardatalow, "%x", intdatalow);
	intdatalow=atoi(chardatalow);

    intdatahigh = bytedata[15];
    sprintf(chardatahigh,"%x",intdatahigh);
    intdatahigh = atoi(chardatahigh);
    data2 = intdatahigh*10000+intdatalow;

    if(numcom ==1){
		if (getChannel(bytedata[8])=='A' && getChannel(bytedata[19])=='B'){
				rback = data1;
				rfront = data2;
		}else if(getChannel(bytedata[19])=='A' && getChannel(bytedata[8])=='B'){
			    rback = data2;
				rfront = data1;

		}
    }
    else if (numcom ==2){
		if (getChannel(bytedata[8])=='A' && getChannel(bytedata[19])=='B'){
				lfront = data2;
				lback = data1;
		}else if(getChannel(bytedata[19])=='A' && getChannel(bytedata[8])=='B'){
			    lfront = data1;
				lback = data2;

		}
    }
  }
}
*/


void getData(byte *bytedata ,byte numcom){
  unsigned int intdatalow;
  unsigned int intdatahigh;
  unsigned int intdatamiddle;
  unsigned int data1;
  unsigned int data2;
  // 示例数据:  00 00 00 00 00 00 00 00 55 5A 0F 00 00 00 00 00 00 00 00 57 58
  

  //byte bytedata[22] = {0x00,0x00,0x00,0x00,0x0,0x12,0x34,0x56,0x2B,0x5A,0x0F,0x00,0x00,0x00,0x00,0x0,0x65,0x43,0x21,0x2B,0x5A};
  char chardatalow[4] = {0};
  char chardatahigh[4]= {0};
  char chardatamiddle[4]= {0};
  for(int i =0;i<21;i++){
		Serial.print(bytedata[i],HEX);
		Serial.print(' ');
  }
  Serial.println("----");
  if(bytedata[10] == 0x0F){
    //Serial.println("Got it");
	

	intdatalow = bytedata[7];
    sprintf(chardatalow,"%x",intdatalow);
    intdatalow = atoi(chardatalow);
	//Serial.println(intdatalow);

	intdatamiddle = bytedata[6];
    sprintf(chardatamiddle,"%x",intdatamiddle);
    intdatamiddle = atoi(chardatamiddle);
	//Serial.println(intdatamiddle);

    intdatahigh = bytedata[5];
    sprintf(chardatahigh,"%x",intdatahigh);
    intdatahigh = atoi(chardatahigh);
	//Serial.println(intdatahigh);
	data1= intdatahigh*10000+100*intdatamiddle+intdatalow;

	//Serial.println("------------*");


   intdatalow = bytedata[18];
    sprintf(chardatalow,"%x",intdatalow);
    intdatalow = atoi(chardatalow);
	//Serial.println(intdatalow);

	intdatamiddle = bytedata[17];
    sprintf(chardatamiddle,"%x",intdatamiddle);
    intdatamiddle = atoi(chardatamiddle);
	//Serial.println(intdatamiddle);

    intdatahigh = bytedata[16];
    sprintf(chardatahigh,"%x",intdatahigh);
    intdatahigh = atoi(chardatahigh);
	//Serial.println(intdatahigh);
	data2= intdatahigh*10000+100*intdatamiddle+intdatalow;

	//Serial.println("------------");
	//Serial.println(data1);
	//Serial.println(data2);

    if(numcom ==1){
		if (getChannel(bytedata[8])=='A' && getChannel(bytedata[19])=='B'){
				rback = data1;
				rfront = data2;
		}else if(getChannel(bytedata[19])=='A' && getChannel(bytedata[8])=='B'){
			    rback = data2;
				rfront = data1;

		}
    }
    else if (numcom ==2){
		if (getChannel(bytedata[8])=='A' && getChannel(bytedata[19])=='B'){
				lfront = data2;
				lback = data1;
		}else if(getChannel(bytedata[19])=='A' && getChannel(bytedata[8])=='B'){
			    lfront = data1;
				lback = data2;

		}
    }
  }
}



/*两个ADC模块分别交替输出AB通道读数,在模块中已经设置,不需再发送命令
void setABcom(void){
  byte ABcom[3] = {
    0xA5,0x0F,0xAA    };
  Serial1.write(ABcom,3);
  delay(100);
  Serial2.write(ABcom,3);
}
*/




