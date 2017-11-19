#include <linux/init.h>           
#include <linux/module.h>         
#include <linux/device.h>        
#include <linux/kernel.h>        
#include <linux/fs.h>             
#include <asm/uaccess.h>  
#include <linux/mutex.h>	
        
#define  DEVICE_NAME "JavadChar"    
#define  CLASS_NAME  "JavadClass"    
//static DEFINE_MUTEX(javadchar_mutex);

MODULE_LICENSE("GPL");           
MODULE_AUTHOR("Javad Malek Shahkoohi S224309");   
MODULE_DESCRIPTION("S224309 is the best student!....");  
MODULE_VERSION("0.1");          

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static char   message[256] = {0};           ///< Memory for the string that is passed from userspace
static short  size_of_message;              ///< Used to remember the size of the string stored
static int    numberOpens = 0;              ///< Counts the number of times the device is opened
static struct class*  JavadCharClass  = NULL; ///< The device-driver class struct pointer
static struct device* JavadCharDevice = NULL; ///< The device-driver device struct pointer

static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};


static int __init JavadChar_init(void){
   printk(KERN_INFO "JavadChar: Initializing the JavadChar LKM\n");

   // Try to dynamically allocate a major number for the device -- more difficult but worth it
   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "JavadChar failed to register a major number\n");
      return majorNumber;
   }
   printk(KERN_INFO "JavadChar: registered correctly with major number %d\n", majorNumber);

   // Register the device class
   JavadCharClass = class_create(THIS_MODULE, CLASS_NAME);

   printk(KERN_INFO "JavadChar: device class registered correctly\n");

   // Register the device driver
   JavadCharDevice = device_create(JavadCharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);

   printk(KERN_INFO "JavadChar: device class created correctly\n"); // Made it! device was initialized
  // mutex_init(&javadchar_mutex);       /// Initia
   return 0;
}

static void __exit JavadChar_exit(void){
	//mutex_destroy(&javadchar_mutex);
	device_destroy(JavadCharClass, MKDEV(majorNumber, 0));     // remove the device
	class_unregister(JavadCharClass);                          // unregister the device class
	class_destroy(JavadCharClass);                             // remove the device class
	unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
	printk(KERN_INFO "JavadChar: Goodbye from the LKM!\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
 /*if(!mutex_trylock(&javadchar_mutex)){    /// Try to acquire the mutex (i.e., put the lock on/down)
                                          /// returns 1 if successful and 0 if there is contention
      printk(KERN_ALERT "Javadchar: Device in use by another process");
      return -EBUSY;
   }*/
   numberOpens++;
   printk(KERN_INFO "JavadChar: Device has been opened %d time(s)\n", numberOpens);
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;
   // copy_to_user has the format ( * to, *from, size) 
   error_count = copy_to_user(buffer, message, size_of_message);

   if (error_count==0){           
      printk(KERN_INFO "JavadChar: Sent %d characters to the user\n", size_of_message);
      return (size_of_message=0);  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "JavadChar: Failed to send %d characters to the user\n", error_count);
      return -EFAULT;              
   }
}


static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
 copy_from_user(message,buffer,len);
 // sprintf(message, "%s(%d letters)", buffer, len);   // appending received string with its length
   size_of_message = strlen(message);                 // store the length of the stored message
   printk(KERN_INFO "JavadChar: Received %d characters from the user\n", len);
   return len;
}

static int dev_release(struct inode *inodep, struct file *filep){
  //mutex_unlock(&javadchar_mutex);
   printk(KERN_INFO "JavadChar: Device successfully closed\n");
   return 0;
}

module_init(JavadChar_init);
module_exit(JavadChar_exit);



