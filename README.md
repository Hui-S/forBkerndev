#forBkerndev#
<h5 align = "right">Nov. 3, 2017</h5>
This is an implementation following [Bran's kernel Development Tutorial](http://www.osdever.net/bkerndev/Docs/title.htm), coded for learning the basic concepts of developing an OS kernel on x86 platform. </br></br></br></br></br>
##Before Started##
You should check out [User:Alexander/Combining Bran's Kernel Development and the Barebones Tutorials](http://wiki.osdev.org/User:Alexander/Combining_Bran%27s_Kernel_Development_and_the_Barebones_Tutorials) first if you want to follow Bkerndev directly. The tutorial was written in 2005, the tools programmers used is much different from the ones nowadays. Read the content thoroughly to avoid the happening of some mistakes.</br></br></br></br></br>
##Toolset
This program is built on Ubuntu 16.04 LTS 32bit, with GCC 5.4.0, nasm 2.11.08 and GNU ld 2.26.1. Kernel runs on [Bochs](http://bochs.sourceforge.net/)  2.6.9.</br></br></br></br></br>
##Create a grub-based bootable hard-drive image##
**This part is basically a copy of [GRUB - OSDev Wiki](http://wiki.osdev.org/GRUB), with a little difference. You can visit the page and simply skip this section, if you wish to get more understanding about GRUB or make a bootable floppy image for instance. If you want to start your kernel running quickly, follow the shell commands below.**

###1. Create a new disk image
Create new disk image file
`$ dd if=/dev/zero of=disk.img bs=512 count=131072`  

###2.Create an DOS partition with bootable entry
1. Enter the following shell command:  
`$ fdisk disk.img`</br>  
2. Add new partition, starting at 1MB (2048th sector). This is more space than GRUB actually needs.   
Enter the following commands: `n`->`p`->`1`->`(Enter, use default)`->`(Enter, use default)`.  
Enter `a` to make it bootable.  
Enter `w` to wite the changes to the image.</br>  
3. Setup two loop devices. One will be used for writing GRUB and its additional codes to MBR, and the second will be used for mounting filesystem of your operating system.   
`$ sudo losetup /dev/loop0 disk.img`
`$ sudo losetup /dev/loop1 disk.img -o 1048576`  
-o option defines offset from start of the file. Number 1048576 is actually 1024^2 = 1MB and that's the start of your partition. </br>  
4. Format your partition You can simply use [any supported filesystem](http://www.gnu.org/software/grub/manual/grub.html#Features) like ext2 or FAT32. Here we use ext2:  
 `$ sudo mke2fs /dev/loop1`</br>  
 5. Mount your newly formatted partition 
 `$ sudo mount /dev/loop1 /mnt`  
 Note that if you tried to mount your first loop device which doesn't have any offset set, you would be requested to specify filesystem and even if you did it, you wouldn't get the expected result. </br>  
 6. Install GRUB using grub-install  
 `sudo grub-install --root-directory=/mnt --no-floppy --modules="normal part_msdos ext2 multiboot" /dev/loop0`  
 If you mistyped /dev/loop1 (pointing on your partition) instead of /dev/loop0 (pointing on your MBR), you would receive message that grub-install can't use 'embedding' (because there's no space for it) and that it would like to use 'block lists', which are not recomended.  
 Don't forget to flush the filesystem buffers when manipulating with files on mounted disk image. On a Unix-like system, this can be simply done by executing the sync program in your shell. </br></br></br></br></br>
##Compilation and Run##
Make sure the following directories are in existance: **bin** and **obj**. Then open the shell, switch to the current directory, type `make` or `make all` to compile. You can also use `make image` to copy your kernel into the image automatically after build, as long as the **hd**   directory exists.
In the original tutorial, the author wrote his script in ".bat" file and run it on Windows. Here, we transtated it into a makefile script to run on Linux.</br></br></br></br></br>
