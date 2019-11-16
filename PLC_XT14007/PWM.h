#ifndef PWM_H_
#define PWM_H_

#define X_AXIS_PULSE_ON()	MTUB.TSTR.BIT.CST1 = 1
#define Y_AXIS_PULSE_ON()	MTUB.TSTR.BIT.CST2= 1
#define Z_AXIS_PULSE_ON()	MTUB.TSTR.BIT.CST3= 1
#define U_AXIS_PULSE_ON()	MTUB.TSTR.BIT.CST4= 1

#define X_AXIS_PULSE_OFF()	MTUB.TSTR.BIT.CST1 = 0
#define Y_AXIS_PULSE_OFF()	MTUB.TSTR.BIT.CST2 = 0
#define Z_AXIS_PULSE_OFF()	MTUB.TSTR.BIT.CST3 = 0
#define U_AXIS_PULSE_OFF()	MTUB.TSTR.BIT.CST4 = 0

#define	DR_CW_X()			PORTA.DR.BIT.B5 = 0
#define	DR_CCW_X()			PORTA.DR.BIT.B5 = 1
#define	DR_CW_Y()			PORTA.DR.BIT.B7 = 0
#define	DR_CCW_Y()			PORTA.DR.BIT.B7 = 1
#define	DR_CW_Z()			PORTB.DR.BIT.B1 = 0
#define	DR_CCW_Z()			PORTB.DR.BIT.B1 = 1
#define	DR_CW_U()			PORTB.DR.BIT.B5 = 0
#define	DR_CCW_U()			PORTB.DR.BIT.B5 = 1

extern void MTU7_PWMInit(void);
extern void MTU8_PWMInit(void);
extern void MTU9_PWMInit(void);
extern void MTU10_PWMInit(void);
#endif
