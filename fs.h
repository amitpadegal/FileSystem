#include <time.h>

#define MAX_BLOCK_SIZE 4096 // Typically the disk block size if 4096 bytes (4KB) or 512 bytes (64 bytes)
#define MAX_NAME_LENGTH 255 // The maxmimum file or directory name size is specified to be 255 bytes
#define MAX_BLOCKS 12       // Typically each inode has 12 direct block pointers and some indirect block pointers

#define TYPE_EMPTY 0
#define TYPE_REG 1
#define TYPE_DIR 2

typedef struct file_attributes
{
    int permissions;          // 0700, 0777, etc . Check file permissions (rwx thing for more information) . 2nd number is owner permissions, 3rd number is group permissions, 4th number is universe permissions
    time_t creation_time;     // Time the file is created
    time_t modification_time; // Time the file is modified or opened
} FILE_ATTRIBUTES;

typedef struct
{
    char data[MAX_BLOCK_SIZE];
} DISK_BLOCKS; // Disk block is used to simulate the hard disk blocks onto which the data is written and is non-volatile

typedef struct
{
    char name[MAX_NAME_LENGTH];
    FILE_ATTRIBUTES f_arr;
    int file_type; // Set to 1 for regular file and 2 for directory
    int inode_number;
    int block_pointers[MAX_BLOCKS]; // direct blocks, a more mature FS would have single indirect, double indirect and triple indirect blocks to handle files of larger sizes
} INODE;

typedef struct directory
{
    char name[MAX_NAME_LENGTH];
    INODE *files;                // To house files in a directory , realloc when we need to add more files i.e array implementation
    struct directory *parentdir; // NOTE : This can be removed if necessary , this is used to support " cd .." kind of operations
    struct directory *subdir;    // To house subdirectories, realloc when we need to add more directories i.e an array implementation
    int no_directories;
    int no_files;
} DIRECTORY;

typedef struct directory_tree
{
    DIRECTORY *root;        // To hold the root directory of the file system
    DIRECTORY *current_dir; // To hold the current/present directory of the file system
} DIR_TREE;

/* typedef struct {
    int magic_number; // This is used to indicate the type of file system.
    int inode_blocks; // Number of inodes
    int disk_blocks; // Number of disk_blocks;

    int inode_region; // Address where inode blocks start
    int disk_block_region; // Address where disk blocks start
}SUPERBLOCK; */
// This part is not necessary but is an important part for a file system

typedef struct fs
{
    INODE *inode_table; // This houses all the inodes i.e files or directories present in the entire File system. Once we have an inode number we can access it in constant time for repeated operations
    DIR_TREE tobj;
    DISK_BLOCKS *disk_block_table; // This houses all the disk_blocks i.e places on the disk where the content is written to
} FILE_SYSTEM;

void initializeFS(FILE_SYSTEM *fs); // func 1
void createFile(FILE_SYSTEM *fs, char *path, int permissions); // func 2
void readFile(FILE_SYSTEM *fs, char *path); // func 3
void writeFile(FILE_SYSTEM *fs, char *path, char *content); // func 4
void deleteFile(FILE_SYSTEM *fs, char *path); // func 5
void createDir(DIR_TREE *tobj, char *path, int permissions); // func 6
void deleteDir(DIR_TREE *tobj, char *path); // func 7
void formatFS(FILE_SYSTEM *fs); // func 8
void sortDirByName(DIR_TREE *tobj, char *path); // func 9
void searchDir(DIR_TREE *tobj, char *path);// func 10
void copyDir(DIR_TREE *tobj, char *pathSrc, char *pathDest);// func 11
void renameDir(DIR_TREE *tobj, char *newName);// func 13
void changeCurrentDir(DIR_TREE *tobj, char *path);// func 14
void displayFileSystem(DIR_TREE *tobj);// func 15
// void moveDir(DIR_TREE *tobj, char *pathSrc, char *pathDest);// func 12
// void displayPath(DIR_TREE *tobj, char *name);