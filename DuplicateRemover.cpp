#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int ref_count = 0;
int del_count = 0;

void delete_files(char *ref_dir, char *target_dir, int perform_delete) {
    DIR *dir;
    struct dirent *entry;
    struct stat info, temp;
    char path[1024], target_path[1024];

    if (!(dir = opendir(ref_dir)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", ref_dir, entry->d_name);
        stat(path, &info);
        if (S_ISDIR(info.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(target_path, sizeof(target_path), "%s/%s", target_dir, entry->d_name);
            delete_files(path, target_path, perform_delete);
        } else {
            ref_count++;
            snprintf(path, sizeof(path), "%s/%s", target_dir, entry->d_name);
            if (stat(path, &temp) == 0) {
                del_count++;
                printf("%-30s %-30s\n", entry->d_name, path);
            } else {
                printf("%-30s %-30s\n", entry->d_name, "Not Found");
            }
            if(perform_delete){
            	remove(path);
			}
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    char ref_dir[100], target_dir[100];
    char confirm;
	
    printf("请输入参照文件夹的路径：");
    if(argc >= 2){
    	strcpy(ref_dir, argv[1]);
    	printf("%s\n", argv[1]);
	}else{
		scanf("%s", ref_dir);
	}

    printf("请输入目标文件夹的路径：");
    if(argc == 3){
    	strcpy(target_dir, argv[2]);
    	printf("%s\n", argv[2]);
	}else{
		scanf("%s", target_dir);
	}

    printf("%-30s %-30s\n", "参照文件夹", "目标文件夹");
    delete_files(ref_dir, target_dir, 0);

    printf("参照文件夹出现文件数目：%d   目标文件夹发现同名文件数目：%d\n", ref_count, del_count);
    printf("是否确认删除? (Y/N): ");
    scanf(" %c", &confirm);
    if (confirm == 'N' || confirm == 'n') {
        printf("操作被取消\n");
    } else if (confirm == 'Y' || confirm == 'y') {
        printf("开始删除文件...\n");
        delete_files(ref_dir, target_dir, 1);
        printf("文件已删除\n");
    }

    system("pause");

    return 0;
}

