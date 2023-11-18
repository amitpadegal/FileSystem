#include "fs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int inode_no = 0;
int disk_block_no = 0;

int validateName(char *name)
{
    const char *disallowedChars = "/\0.*?:'\"";
    while (*name)
    {
        if (strchr(disallowedChars, *name) != NULL)
        {
            return 1; // Found a disallowed character
        }
        name++;
    }

    return 0;
}

void splitPath(const char *path, char *dir, char *name)
{
    const char *slash = strrchr(path, '/'); // Last occurence of slash
    if (slash)
    {
        if (slash == path)
        {
            strcpy(dir, "/");
            strcpy(name, slash + 1);
        }
        else
        {
            strncpy(dir, path, slash - path);
            dir[slash - path] = '\0';
            strcpy(name, slash + 1);
        }
    }
    else
    {
        strcpy(dir, "");
        strcpy(name, path);
    }
}

INODE createInode(char *name, int permissions, int type)
{
    INODE newInode;
    strcpy(newInode.name, name);
    newInode.f_arr.permissions = permissions;
    newInode.f_arr.creation_time = time(NULL);
    newInode.f_arr.modification_time = newInode.f_arr.creation_time;
    newInode.file_type = type;
    newInode.inode_number = inode_no++;
    for (int i = 0; i < MAX_BLOCKS; i++)
    {
        newInode.block_pointers[i] = -1; // No content initially
    }
    return newInode;
}

DIRECTORY *makeDir(DIR_TREE *tobj, DIRECTORY *parent, char *name)
{
    DIRECTORY *newDir = malloc(sizeof(DIRECTORY));
    strcpy(newDir->name, name);
    newDir->files = NULL;
    newDir->no_directories = 0;
    newDir->no_files = 0;
    newDir->subdir = NULL;
    newDir->parentdir = parent;
    return newDir;
}

void initializeFS(FILE_SYSTEM *fs)
{
    fs->disk_block_table = NULL;
    fs->inode_table = NULL;
    fs->tobj.root = makeDir(&fs->tobj, NULL, "/");
    fs->tobj.current_dir = fs->tobj.root;
}

DIRECTORY *findDirectory(DIRECTORY *cur_directory, char *token)
{
    for (int i = 0; i < cur_directory->no_directories; i++)
    {
        if (strcmp(cur_directory->subdir[i].name, token) == 0)
        {
            return &cur_directory->subdir[i];
        }
    }
    return NULL;
}

void createDir(DIR_TREE *tobj, char *path, int permission)
{
    DIRECTORY *cur_dir;
    char dir[MAX_NAME_LENGTH * 10]; // Assuming depth of 10 i.e MAX_NAME_LENGTH/MAX_NAME_LENGTH 10 times
    char name[MAX_NAME_LENGTH];
    splitPath(path, dir, name);
    if (dir[0] == '/')
    {
        cur_dir = tobj->root;
    }
    else
    {
        cur_dir = tobj->current_dir;
    }
    if (strcmp(dir, "") != 0)
    {
        char *token = strtok(dir, "/");
        while (token != NULL)
        {
            DIRECTORY *dir = findDirectory(cur_dir, token);
            if (dir == NULL)
            {
                printf("Error : Path does not exist.\n");
                return;
            }
            cur_dir = dir;
            token = strtok(NULL, "/");
        }
    }
    if (findDirectory(cur_dir, name) != NULL)
    {
        printf("Error : Directory already exists.\n");
        return;
    }
    DIRECTORY *newDir = makeDir(tobj, cur_dir, name);
    cur_dir->subdir = realloc(cur_dir->subdir, ++(cur_dir->no_directories) * sizeof(DIRECTORY));
    cur_dir->subdir[cur_dir->no_directories - 1] = *newDir;
}

void searchDir(DIR_TREE *tobj, char *path)
{
    char dir_path[MAX_NAME_LENGTH * 10];
    strcpy(dir_path, path);
    DIRECTORY *cur_dir;
    if (path[0] == '/')
    {
        cur_dir = tobj->root;
    }
    else
    {
        cur_dir = tobj->current_dir;
    }
    if (strcmp(path, "") != 0)
    {
        char *token = strtok(dir_path, "/");
        while (token != NULL)
        {
            DIRECTORY *dir = findDirectory(cur_dir, token);
            if (dir == NULL)
            {
                printf("Error : Path does not exist\n");
                return;
            }
            cur_dir = dir;
            token = strtok(NULL, "/");
        }
    }
    if (cur_dir != NULL)
    {
        printf("Directory found at : %s\n", path);
    }
    else
    {
        printf("Directory not found at :%s\n", path);
    }
}
DIRECTORY *findDir(DIR_TREE *tobj, char *path)
{

    char dir_path[MAX_NAME_LENGTH * 10];
    strcpy(dir_path, path);
    DIRECTORY *cur_dir;
    if (path[0] == '/')
    {
        cur_dir = tobj->root;
    }
    else
    {
        cur_dir = tobj->current_dir;
    }
    if (strcmp(path, "") != 0)
    {
        char *token = strtok(dir_path, "/");
        while (token != NULL)
        {
            DIRECTORY *dir = findDirectory(cur_dir, token);
            if (dir == NULL)
            {
                return NULL;
            }
            cur_dir = dir;
            token = strtok(NULL, "/");
        }
    }
    return cur_dir;
}

void changeCurrentDir(DIR_TREE *tobj, char *path)
{
    DIRECTORY *newCurrentDir = findDir(tobj, path);
    if (newCurrentDir == NULL)
    {
        printf("Directory '%s' not found.\n", path);
        return;
    }
    tobj->current_dir = newCurrentDir;
    printf("Current directory changed to '%s'.\n", path);
}
void swapEntries(DIRECTORY *a, DIRECTORY *b)
{
    DIRECTORY temp = *a;
    *a = *b;
    *b = temp;
}

void sortDir(DIRECTORY *dir)
{
    int n = dir->no_directories;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(dir->subdir[j].name, dir->subdir[j + 1].name) > 0)
            {
                swapEntries(&dir->subdir[j], &dir->subdir[j + 1]);
            }
        }
    }
}

// Function to sort a directory by name given a path
void sortDirByName(DIR_TREE *tobj, char *path)
{
    // Find the directory given the path
    DIRECTORY *dir = findDir(tobj, path);

    // Check if the directory was found
    if (dir == NULL)
    {
        printf("Directory '%s' not found.\n", path);
        return;
    }
    // Sort the directory by name
    sortDir(dir);
}
DIRECTORY *copyDirRecursive(DIR_TREE *tobj, DIRECTORY *srcDir, DIRECTORY *destParentDir)
{
    // Create a new directory in the destination path
    DIRECTORY *newDir = makeDir(tobj, destParentDir, srcDir->name);

    // Copy the contents of the source directory to the new directory
    /* for(int i=0;i<srcDir->no_files;i++)
    {
        INODE* srcFile=&srcDir->files[i];
        INODE* newInode = &newDir->files[i];
        newInode->file_type=srcFile->file_type;
        newInode->block_pointers[0]=srcFile->block_pointers[0];
        if(srcFile->file_type==TYPE_REG)
        {
            newInode->content=malloc(MAX_BLOCK_SIZE*srcFile->block_pointers[0]);
            memcpy(newInode->content,srcFile->content,MAX_BLOCK_SIZE*srcFile->block_pointers[0]);
        }
    } */
    for (int i = 0; i < srcDir->no_files; i++)
    {
        INODE srcFile = srcDir->files[i];
        newDir->files = realloc(newDir->files, sizeof(INODE) * i + 1);
        newDir->no_files++;
        newDir->files[i] = srcDir->files[i];
    }

    // Recursively copy the contents of subdirectories
    if (srcDir->subdir != NULL)
    {
        // Initialize the subdirectory in the new directory
        /* newDir->subdir = malloc(sizeof(DIRECTORY));
        newDir->subdir->files = malloc(sizeof(INODE));
        newDir->subdir->parentdir = newDir;
        newDir->subdir->subdir = NULL;  */
        // Initialize the sub-subdirectory to NULL

        for (int i = 0; i < srcDir->no_directories; i++)
        {
            // Recursively copy subdirectories
            DIRECTORY *copiedSubdir = copyDirRecursive(tobj, &srcDir->subdir[i], &newDir->subdir[i]);
            // Add the copied subdirectory to the new directory
            newDir->subdir[i] = *copiedSubdir;
        }
    }

    return newDir;
}
void moveDir(DIR_TREE *tobj, char *pathSrc, char *pathDest)
{
    // Validate arguments
    if (tobj == NULL || tobj->root == NULL || pathSrc == NULL || pathDest == NULL)
    {
        printf("Invalid arguments.\n");
        return;
    }

    // Find the source directory
    DIRECTORY *srcDir = findDir(tobj, pathSrc);

    // If source directory not found, print an error and return
    if (srcDir == NULL)
    {
        printf("Source directory '%s' not found.\n", pathSrc);
        return;
    }

    // Find the destination directory
    DIRECTORY *destDir = findDir(tobj, pathDest);

    // If destination directory not found, print an error and return
    if (destDir == NULL)
    {
        printf("Destination directory '%s' not found.\n", pathDest);
        return;
    }

    // Check if destination directory already contains a directory with the same name
    for (int i = 0; i < destDir->no_directories; i++)
    {
        if (strcmp(destDir->subdir[i].name, srcDir->name) == 0)
        {
            printf("Error: Destination directory already contains a directory with the same name.\n");
            return;
        }
    }
    // Perform the directory copy (copy INODE and update parent directory)
    DIRECTORY *newDir = copyDirRecursive(tobj, srcDir, destDir);

    // Add the new directory to the destination directory
    destDir->subdir = realloc(destDir->subdir, ++(destDir->no_directories) * sizeof(DIRECTORY));
    destDir->subdir[destDir->no_directories - 1] = *newDir;

    // Perform the directory delete (remove INODE and update parent directory)
    deleteDir(tobj, pathSrc);
}

void copyDir(DIR_TREE *tobj, char *pathSrc, char *pathDest)
{
    // Validate arguments
    if (tobj == NULL || tobj->root == NULL || pathSrc == NULL || pathDest == NULL)
    {
        printf("Invalid arguments.\n");
        return;
    }

    // Find the source directory
    DIRECTORY *srcDir = findDir(tobj, pathSrc);
    printf("src dir : %s\n", srcDir->name);

    // If source directory not found, print an error and return
    if (srcDir == NULL)
    {
        printf("Source directory '%s' not found.\n", pathSrc);
        return;
    }

    // Find the destination directory
    DIRECTORY *destDir = findDir(tobj, pathDest);
    printf("dest dir : %s\n", destDir->name);

    // If destination directory not found, print an error and return
    if (destDir == NULL)
    {
        printf("Destination directory '%s' not found.\n", pathDest);
        return;
    }

    // Check if destination directory already contains a directory with the same name
    for (int i = 0; i < destDir->no_directories; i++)
    {
        if (strcmp(destDir->subdir[i].name, srcDir->name) == 0)
        {
            printf("Error: Destination directory already contains a directory with the same name.\n");
            return;
        }
    }

    // Perform the directory copy (copy INODE and update parent directory)
    DIRECTORY *newDir = copyDirRecursive(tobj, srcDir, destDir);

    // Add the new directory to the destination directory
    // destDir->subdir->files[destDir->subdir->files->block_pointers[0]] = *newDir->files;
    // destDir->subdir->files->block_pointers[0]++;

    destDir->subdir = realloc(destDir->subdir, ++(destDir->no_directories) * sizeof(DIRECTORY));
    destDir->subdir[destDir->no_directories - 1] = *newDir;

    printf("Directory '%s' copied to '%s'.\n", pathSrc, pathDest);
}

/* void deleteDir(DIR_TREE *tobj, char *path)
{
    DIRECTORY *currentDir = tobj->current_dir;

    // Check if the directory exists in the current directory
    int i;
    for (i = 0; i < currentDir->no_directories; ++i)
    {
        if (strcmp(currentDir->subdir[i].name, path) == 0)
        {
            // Found the directory to delete

            // Free memory associated with files and subdirectories
            free(currentDir->subdir[i].files);
            free(currentDir->subdir[i].subdir);

            // Remove the directory from the list
            for (int j = i; j < currentDir->no_directories - 1; ++j)
            {
                currentDir->subdir[j] = currentDir->subdir[j + 1];
            }

            // Update the number of directories
            currentDir->no_directories--;

            printf("Directory '%s' deleted successfully.\n", path);
            return;
        }
    }

    // If the directory is not found in the current directory, print an error message
    printf("Directory '%s' not found.\n", path);
} */

void deleteDirRecursive(FILE_SYSTEM *fs, DIRECTORY *dir);

void formatFS(FILE_SYSTEM *fs)
{
    // Free resources in the root directory
    deleteDirRecursive(fs, fs->tobj.root);

    // Reset the root directory
    fs->tobj.root->files = NULL;
    fs->tobj.root->no_directories = 0;
    fs->tobj.root->no_files = 0;
    fs->tobj.root->subdir = NULL;

    // Reset the current directory
    fs->tobj.current_dir = fs->tobj.root;

    // Free resources in the inode table and disk block table
    free(fs->inode_table);
    free(fs->disk_block_table);

    // Reset the inode table and disk block table
    fs->inode_table = NULL;
    fs->disk_block_table = NULL;

    inode_no = 0;
    disk_block_no = 0;

    printf("File system formatted successfully.\n");
}

void deleteDir(DIR_TREE *tobj, char *path)
{
    DIRECTORY *currentDir = tobj->current_dir;

    // Check if the directory exists in the current directory
    int i;
    for (i = 0; i < currentDir->no_directories; ++i)
    {
        if (strcmp(currentDir->subdir[i].name, path) == 0)
        {
            // Found the directory to delete

            // Free memory associated with files and subdirectories
            free(currentDir->subdir[i].files);
            free(currentDir->subdir[i].subdir);

            // Remove the directory from the list
            for (int j = i; j < currentDir->no_directories - 1; ++j)
            {
                currentDir->subdir[j] = currentDir->subdir[j + 1];
            }

            // Update the number of directories
            currentDir->no_directories--;

            printf("Directory '%s' deleted successfully.\n", path);
            return;
        }
    }

    // If the directory is not found in the current directory, print an error message
    printf("Directory '%s' not found.\n", path);
}

void deleteDirRecursive(FILE_SYSTEM *fs, DIRECTORY *dir)
{
    for (int i = 0; i < dir->no_files; ++i)
    {
        deleteFile(fs, dir->files[i].name);
    }

    for (int i = 0; i < dir->no_directories; ++i)
    {
        deleteDirRecursive(fs, &dir->subdir[i]);
    }

    // Free memory associated with files and subdirectories
    free(dir->files);
    free(dir->subdir);
}

void displayPath(DIR_TREE *tobj, char *name)
{
    DIRECTORY *cur_dir = tobj->current_dir;
    if (strcmp(name, "..") == 0)
    {
        if (cur_dir->parentdir != NULL)
        {
            tobj->current_dir = cur_dir->parentdir;
            printf("Current directory: %s\n", cur_dir->parentdir->name);
        }
        else
        {
            printf("Error: Already at the root directory.\n");
        }
    }
    else if (strcmp(name, ".") == 0)
    {
        printf("Current directory: %s\n", cur_dir->name);
    }
    else
    {
        DIRECTORY *dir = findDirectory(cur_dir, name);
        if (dir != NULL)
        {
            tobj->current_dir = dir;
            printf("Current directory: %s\n", dir->name);
        }
        else
        {
            printf("Error: Directory not found.\n");
        }
    }
}

void renameDir(DIR_TREE *tobj, char *newName)
{
    if (validateName(newName))
    {
        printf("Invalid name. Please do not include / \0 . : * etc\n");
    }
    else
    {
        if (tobj->current_dir->parentdir != NULL)
        {
            strcpy(tobj->current_dir->name, newName);
        }
        else
        {
            printf("Error: Cannot rename root directory.\n");
        }
    }
}

void displayDir(DIRECTORY *dir, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("  "); // Adjust spacing for visual hierarchy
    }
    printf("[%s] (Type: Directory)\n", dir->name);
    for (int i = 0; i < dir->no_files; i++)
    {
        if (dir->files[i].file_type != TYPE_EMPTY)
        {
            for (int i = 0; i < depth; i++)
            {
                printf("  "); // Adjust spacing for visual hierarchy
            }
            printf("  ");
            printf("[%s] (Type: File, Inode: %d)\n", dir->files[i].name, dir->files[i].inode_number);
        }
    }
    for (int i = 0; i < dir->no_directories; i++)
    {
        displayDir(&dir->subdir[i], depth + 1);
    }
}
void displayFileSystem(DIR_TREE *tobj)
{
    printf("File System Structure:\n");
    displayDir(tobj->root, 0);
}

INODE *findFile(DIRECTORY *cur_directory, char *token)
{
    for (int i = 0; i < cur_directory->no_files; i++)
    {
        if (strcmp(cur_directory->files[i].name, token) == 0)
        {
            return &cur_directory->files[i];
        }
    }
    return NULL;
}

void createFile(FILE_SYSTEM *fs, char *path, int permissions)
{
    DIRECTORY *cur_dir;
    char dir[MAX_NAME_LENGTH * 10]; // Assuming depth of 10 i.e MAX_NAME_LENGTH/MAX_NAME_LENGTH 10 times
    char name[MAX_NAME_LENGTH];
    splitPath(path, dir, name);
    if (dir[0] == '/')
    {
        cur_dir = fs->tobj.root;
    }
    else
    {
        cur_dir = fs->tobj.current_dir;
    }
    if (strcmp(dir, "") != 0)
    {
        char *token = strtok(dir, "/");
        while (token != NULL)
        {
            DIRECTORY *dir = findDirectory(cur_dir, token);
            if (dir == NULL)
            {
                printf("Error : Path does not exist.\n");
                return;
            }
            cur_dir = dir;
            token = strtok(NULL, "/");
        }
    }
    if (findFile(cur_dir, name) != NULL)
    {
        printf("Error : File already exists.\n");
        return;
    }
    INODE newFile = createInode(name, permissions, TYPE_REG);
    fs->inode_table = realloc(fs->inode_table, sizeof(INODE) * inode_no);
    fs->inode_table[inode_no - 1] = newFile;
    cur_dir->files = realloc(cur_dir->files, ++(cur_dir->no_files) * sizeof(INODE));
    cur_dir->files[cur_dir->no_files - 1] = newFile;
}
void readFile(FILE_SYSTEM *fs, char *path)
{

    DIRECTORY *cur_dir;
    char dir[MAX_NAME_LENGTH * 10]; // Assuming depth of 10 i.e MAX_NAME_LENGTH/MAX_NAME_LENGTH 10 times
    char name[MAX_NAME_LENGTH];
    splitPath(path, dir, name);
    if (dir[0] == '/')
    {
        cur_dir = fs->tobj.root;
    }
    else
    {
        cur_dir = fs->tobj.current_dir;
    }
    if (strcmp(dir, "") != 0)
    {
        char *token = strtok(dir, "/");
        while (token != NULL)
        {
            DIRECTORY *dir = findDirectory(cur_dir, token);
            if (dir == NULL)
            {
                printf("Error : Path does not exist.\n");
                return;
            }
            cur_dir = dir;
            token = strtok(NULL, "/");
        }
    }
    INODE *file = findFile(cur_dir, name);
    if (file != NULL)
    {
        printf("%s : \n", file->name);
        for (int i = 0; i < MAX_BLOCKS; i++)
        {
            if (file->block_pointers[i] == -1)
                break;
            printf("%s", fs->disk_block_table[file->block_pointers[i]].data);
        }
        printf("\n");
    }
    else
    {
        printf("No File found\n");
    }
}
void writeFile(FILE_SYSTEM *fs, char *path, char *content)
{
    if (strlen(content) > MAX_BLOCK_SIZE * MAX_BLOCKS)
    {
        printf("File too big\n");
    }
    else
    {
        int length = strlen(content);
        if (length)
        {
            DIRECTORY *cur_dir;
            char dir[MAX_NAME_LENGTH * 10]; // Assuming depth of 10 i.e MAX_NAME_LENGTH/MAX_NAME_LENGTH 10 times
            char name[MAX_NAME_LENGTH];
            splitPath(path, dir, name);
            if (dir[0] == '/')
            {
                cur_dir = fs->tobj.root;
            }
            else
            {
                cur_dir = fs->tobj.current_dir;
            }
            if (strcmp(dir, "") != 0)
            {
                char *token = strtok(dir, "/");
                while (token != NULL)
                {
                    DIRECTORY *dir = findDirectory(cur_dir, token);
                    if (dir == NULL)
                    {
                        printf("Error : Path does not exist.\n");
                        return;
                    }
                    cur_dir = dir;
                    token = strtok(NULL, "/");
                }
            }
            INODE *file = findFile(cur_dir, name);
            if (file != NULL)
            {
                int i = 0;
                while (length > 0)
                {
                    DISK_BLOCKS block;
                    strncpy(block.data, content, MAX_BLOCK_SIZE);
                    length -= MAX_BLOCK_SIZE;
                    content += MAX_BLOCK_SIZE;
                    file->block_pointers[i] = disk_block_no++;
                    fs->disk_block_table = realloc(fs->disk_block_table, disk_block_no * sizeof(DISK_BLOCKS));
                    fs->disk_block_table[disk_block_no - 1] = block;
                    i++;
                }
            }
            else
            {
                printf("No File found\n");
            }
        }
        else
        {
            printf("No content available\n");
        }
    }
}
void deleteFile(FILE_SYSTEM *fs, char *path)
{
    DIRECTORY *cur_dir;
    char dir[MAX_NAME_LENGTH * 10]; // Assuming depth of 10 i.e MAX_NAME_LENGTH/MAX_NAME_LENGTH 10 times
    char name[MAX_NAME_LENGTH];
    splitPath(path, dir, name);
    if (dir[0] == '/')
    {
        cur_dir = fs->tobj.root;
    }
    else
    {
        cur_dir = fs->tobj.current_dir;
    }
    if (strcmp(dir, "") != 0)
    {
        char *token = strtok(dir, "/");
        while (token != NULL)
        {
            DIRECTORY *dir = findDirectory(cur_dir, token);
            if (dir == NULL)
            {
                printf("Error : Path does not exist.\n");
                return;
            }
            cur_dir = dir;
            token = strtok(NULL, "/");
        }
    }
    if (findFile(cur_dir, name) == NULL)
    {
        printf("Error : File does not exist.\n");
        return;
    }
    else
    {
        // Logical deletion, Actual deletion is very time consuming and inefficient due to arrays, can be made better with linked lists but would still be O(n) complexity
        // ^ This process usually leads to disk fragmentation and is usually handled by a process separately, however we are not implementing that here
        int i;
        for (i = 0; i < cur_dir->no_files; i++)
        {
            if (strcmp(cur_dir->files[i].name, name) == 0)
            {
                break;
            }
        }
        for (int k = 0; k < MAX_BLOCKS; k++)
        {
            if (cur_dir->files[i].block_pointers[k] == -1)
                break;
            strcpy(fs->disk_block_table[cur_dir->files[i].block_pointers[k]].data, "");
        }
        fs->inode_table[cur_dir->files[i].inode_number].file_type = TYPE_EMPTY;
        cur_dir->files[i].file_type = TYPE_EMPTY;
        /* int j;
        for(j=i;j<cur_dir->no_files-1;j++)
        {
            cur_dir->files[j]=cur_dir->files[j+1];
        }
        free(&cur_dir->files[j]);
        cur_dir->no_files--;
        cur_dir->files=realloc(cur_dir->files,sizeof(INODE)*cur_dir->no_files); */
        // Costly so commented out
    }
}
