#include "disk_info.h"

/*
  You can use function traverse_directory_find_deleted() and check_occupied() to finish this function
*/
int locate_deleted_file(struct DiskInfo *disk_info/*file in disk*/, 
                        const char *recover_target/*user input*/, 
                        struct msdos_dir_entry *target_dir_entry, 
                        int cleanse) {

    char *dirc, *basec;
    int check;
    dirc = strdup(recover_target);
    basec = strdup(recover_target);
    char *recover_target_dirname = dirname(dirc);
    if(recover_target_dirname == NULL)
        die();

    char *recover_target_basename = basename(basec);
    if(recover_target_basename == NULL)
        die();

    if(traverse_directory_find_deleted(disk_info,recover_target_dirname,2,recover_target_basename,target_dir_entry))

        {
            if(cleanse==0 && check_occupied(disk_info, target_dir_entry)){
                     printf("%s: error - fail to recover\n", recover_target+1);
                 free(dirc);
                      free(basec);
                    exit(EXIT_FAILURE);}
        else  
            if(cleanse==1 && check_occupied(disk_info, target_dir_entry)){
                      printf("%s: error - fail to cleanse\n", recover_target+1); 
                      free(dirc);
                      free(basec);
                    exit(EXIT_FAILURE);
               }
        else
            if(cleanse==0 && !check_occupied(disk_info, target_dir_entry)){
                    printf("%s: recovered\n", recover_target + 1);
                    free(dirc);
                    free(basec);
                     return 1;
                }
        else
             if(cleanse==1 && (target_dir_entry->size==0 || check_occupied(disk_info, target_dir_entry))){
                printf("%s: error - fail to cleanse\n", recover_target + 1); 
                free(dirc);
                free(basec);
                return 1;
            }
        else{
                 free(dirc);
                 free(basec);
                 return 1;

            }


        } 
    
    free(dirc);
    free(basec);
    return 0;
}


/* 
You can reuse most of the codes in the copy_deleted_file() function.
*/
int cleanse_deleted_file(struct DiskInfo *disk_info, struct msdos_dir_entry dir_entry, const char *cleanse_target) {
    // Insert your code here
    
        uint32_t dir_first_cluster = get_dir_first_cluster(&dir_entry);
    
        uint32_t next_cluster_number = dir_first_cluster;
        uint32_t current_cluster_number;
        uint32_t file_size = dir_entry.size;

        char *buffer = malloc(disk_info->bpc);
        char before[1];
            if(file_size!=0)    printf("%s: cleansed\n", cleanse_target+1);
            current_cluster_number = next_cluster_number;
            off_t cluster_offset = get_cluster_offset(
                disk_info->root_entry_offset, current_cluster_number, disk_info->bpc);
            int a=0;

            while (file_size>a){

            fseek(disk_info->fp, cluster_offset+a, SEEK_SET);
            size_t ret = fread(buffer, 1, 1, disk_info->fp);
            fseek(disk_info->fp, cluster_offset+a, SEEK_SET);
            if(!strcmp(before,"\\") && !strcmp(buffer,"n")){
                fwrite("", sizeof(char), 1, disk_info->fp);
            }
            else{    
                fwrite("", sizeof(char), 1, disk_info->fp);
            }
            a++;
            strcpy(before,buffer);
            }
        free(buffer);   

       
    return 1;
}