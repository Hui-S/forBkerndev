#include <system.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;
int seconds = 0;


void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r)
{
    int mask, tmp1, tmp2, zeroflag;
    const int maskinit = 100000000;
    /* Increment our 'tick count' */
    timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 100 == 0)
    {
        ++seconds;

        mask = maskinit;
        zeroflag = 0;
        tmp1 = seconds;
        while(mask != 0) {
            tmp2 = tmp1 / mask;
            if(tmp2 != 0) {
                putch(tmp2 + '0' - 0);
                if(!zeroflag)
                    zeroflag = 1;
            }
            else if(zeroflag) //zeroflag == tru && tmp2 == 0
                putch('0');

            tmp1 %= mask;
            mask /= 10;
        }
        puts(" second(s) has passed.\n");
    }
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}