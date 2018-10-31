#include <linux/init.h>
#include <linux/module.h>
#include<linux/fs.h>
#include "cryptctl_driver.h" 
//#include<stdio.h>
//#inc
static int encrypt_open(struct inode *, struct file *);
static int create_char_dev(unsigned int , const char* , const struct file_operations* );
static int destroy_char_dev(void);
static long char_dev_ctl(struct file *, unsigned int, unsigned long );
static int Major;
MODULE_LICENSE("Dual BSD/GPL");
static const  struct file_operations fops =
  {
    .owner = THIS_MODULE,
    .open  = encrypt_open,
    .unlocked_ioctl = char_dev_ctl, //(struct file * open_file, unsigned int request, unsigned long dev_info),
    //    .write = encrypt 
  };
//static int encrypt()
//{
  //encryption code
//}
static int encrypt_open(struct inode * file_data, struct file * open_file)
{
  return 0;
}
static long char_dev_ctl(struct file * open_file, unsigned int request, unsigned long dev_info)
{
  switch(request)
    {
    case CREATE_DEV_CODE:
      printk("ioctl LIVES!");
      create_char_dev(0,((const encryptctl_struct*)dev_info)->encrypt_name, &fops);
      create_char_dev(0,((const encryptctl_struct*)dev_info)->decrypt_name, &fops);
    case DESTROY_DEV_CODE:
      break;
      //    case DESTROY_DEV_CODE:
      // destroy_char_dev((const encryptctl_struct*)dev_info)->decrypt_name, fops);
    }
  return 0;
}

int init_module(void)
{
 Major =  create_char_dev(0,CRYPTCTL_NAME, &fops);
 if(Major<0)
   {
     printk("There was an error registering this device\n");
     return -1;
   }
 printk("I think the device should be registered now:%d\n", Major);
 return 0;
}
void cleanup_module(void)
{
  unregister_chrdev(Major, CRYPTCTL_NAME);
  printk("Device %d was unregustered.\nSee ya later alligator");
  return 0;
}
static int  create_char_dev(unsigned int major, const char* dev_name, const struct  file_operations* fops)
{
 Major =  register_chrdev(major,dev_name, fops);
 if(Major<0)
   {
     printk("There was an error registering this device. Please try again.\n");
     return Major;
   }
 return Major;
}
static int destroy_char_dev(void)
{
  return 0;
}

//module_init(char_dev_ctl);
//module_exit(hello_exit);
//printf("Hi Kernel\n");