/*
 * ultrasonic_radar.c
 *
 * Created: 01/03/2024 13:03:34
 *  Author: Eslam
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "LCD.h"
#include "std_macros.h"
#include "servo.h"
#include "ultrasonic.h"
#include "Button.h"

char mode=2;
signed short i=0,d=1,deg=0,distanc=0;
short c=0;
void select_mode(){
	LCD_clearscreen();
	LCD_vSend_string("SELECT MODE");
	LCD_movecursor(2,1);
	LCD_vSend_string("1-AUTO 2-MANUAL");
	while(1){
			if (READ_BIT(PIND,1)==0)
			{
				mode=2; //MANUAL
				break;
			}
		if (READ_BIT(PIND,0)==0)
		{
			mode=1; //AUTO
			break;
		}
	
	}
	
	return;
}

void display(char dis){
	LCD_clearscreen();
	LCD_vSend_string("OBJECT DETECTED:");
	LCD_movecursor(2,1);
	LCD_vSend_string("AT : (");
	signed short ii=i;
	if(ii<0)
	LCD_vSend_char('-'),ii=-ii;
	LCD_vSend_char(ii/10+48);
	LCD_vSend_char(ii%10+48);
	LCD_vSend_char(0xdf);	
	LCD_vSend_char(',');
	if (dis>=100)
	{
		LCD_vSend_char(dis/100+48);
		LCD_vSend_char((dis/10)%10+48);
		LCD_vSend_char(dis%10+48);
		LCD_vSend_string("CM)");
	}else
	{
		LCD_vSend_char(dis/10+48);
		LCD_vSend_char(dis%10+48);
		LCD_vSend_string("CM)");
	}
}





int main(void)
{
	LCD_vInit();
	LCD_vSend_string("  RADAR SYSTEM");
	servo_vmove_to(0);
	ADC_vinit(0);
	Buzzer_vInit('C',1);

	button_vInit('D',0);
	button_vInit('D',1);
	PORTD|=3;
	
	_delay_ms(2000);

	while(1)
	{
					Buzzer_vOff('C',1);		
		select_mode();
		_delay_ms(50);
		if (mode==1)
		{
		i=0,d=1,c=0,deg=0,distanc=0;
		LCD_clearscreen();
		LCD_vSend_string("  All Clear!");
			while(1)
			{
					if (i>=90 || i<=-90)
					{
						d=-d;
					}
					short dis=ultrasonic_distance();
					servo_vmove_to(i);
					c++;					
					Buzzer_vOff('C',1);
					if (dis<=120 && (distanc!=dis || i!=deg))
					{
						Buzzer_vOn('C',1);
						display(dis);
						c=0;
						distanc=dis;
						deg=i;
					}
					if(c>=180){
					c=0;
					LCD_clearscreen();
					LCD_vSend_string("  All Clear!");
					}
					
					if (READ_BIT(PIND,0)==0 || READ_BIT(PIND,1)==0){
						break;
					}
					i+=d;
			}
		}else if (mode==2) {
			i=0,d=1,c=0,deg=0,distanc=0;
			LCD_clearscreen();
			LCD_vSend_string("  All Clear");
			while(1){
			short ad=ADC_u16Read();
			
			double res =0.175781*ad-90;
			short dis=ultrasonic_distance();
			servo_vmove_to(res);
			_delay_ms(50);
			i=res;
			Buzzer_vOff('C',1);
			if (dis<=120)
			{
				Buzzer_vOn('C',1);
				display(dis);
				c=0;
				distanc=dis;
				deg=i;
			}
			if(c>=320)
			{
				LCD_clearscreen();
				LCD_vSend_string("  All Clear!");
				
				c=0;
			}
			if (READ_BIT(PIND,0)==0 || READ_BIT(PIND,1)==0){
				break;
			}
			c++;
		}			
		}
	}
}