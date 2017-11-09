#include <system.h>

/* You will need to code these up yourself!  */
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
    /* Add code here to copy 'count' bytes of data from 'src' to
    *  'dest', finally return 'dest' */
    char * s = (char*) src, *d = (char*) dest;
    while(count--)
        *(d++) = *(s++);

    return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    /* Add code here to set 'count' bytes in 'dest' to 'val'.
    *  Again, return 'dest' */
    dest += count;
    while(count--)
        *(--dest) = val;

    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    /* Same as above, but this time, we're working with a 16-bit
    *  'val' and dest pointer. Your code can be an exact copy of
    *  the above, provided that your local variables if any, are
    *  unsigned short */
    dest += count;
    while(count--)
        *(--dest) = val;

    return dest;
}

int strlen(const char *str)
{
    /* This loops through character array 'str', returning how
    *  many characters it needs to check before it finds a 0.
    *  In simple words, it returns the length in bytes of a string */
    int i = 0;
    while(*str != '\0') {
        ++str;
        ++i;
    }

    return i;
}

void putint(int i) {
	int d, mask = 1000000000, zeroflag = 0;
	
	if(i == 0) {
		putch('0');
		return;
	}
	else if(i == -2147483648) {
		puts("-2147483648");
		return;
	}
	else if(i < 0) {
		i = -i;
		putch('-');
	}

	while(mask != 0) {
		d = i / mask;
		if(d != 0) {
			putch(d + '0' - 0);
			if(!zeroflag)
				zeroflag = 1;
		}
		else if(zeroflag) //zeroflag == true && d == 0
			putch('0');

		i %= mask;
		mask /= 10;
	}
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void main()
{
    /* You would add commands after here */
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    timer_phase(100);
    timer_install();
	keyboard_install();
    __asm__ __volatile__ ("sti");
    
    init_video();
    puts("Hello, world!\n");

    
    /* ...and leave this loop in. There is an endless loop in
    *  'start.asm' also, if you accidentally delete this next line */
    for (;;);
}
