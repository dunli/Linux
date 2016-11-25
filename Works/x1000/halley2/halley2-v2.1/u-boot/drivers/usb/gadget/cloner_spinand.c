#include<asm/arch-x1000/spi.h>
#include "../../spi/jz_spi.h"
#include <linux/mtd/mtd.h>
#include <ingenic_nand_mgr/nand_param.h>
#include "../../mtd/nand/jz_spinand.h"
extern struct jz_spinand_partition *get_partion_index(u32 startaddr,int *pt_index);
extern struct nand_param_from_burner nand_param_from_burner;
/*******************************************************************************
 * in burner init,we find spinand information from stage2_arg
 * and change it to struct nand_param_from_burner which uboot can use
 *for chip probe,but after chip probe the struct nand_param_from_burner
 *is changed,and para_num is changed to 1,and jz_spi_support_from_burner
 *pointer addr changed to the address which param we probe.
 * ******************************************************************************/
void get_burner_nandinfo(struct cloner *cloner,struct nand_param_from_burner *param)
{
	struct arguments *get_id=cloner->args;
	char *member_addr=(char *)(get_id+1);
	param->version=*(int *)member_addr;
	member_addr+=sizeof(param->version);
	param->flash_type=*(int *)member_addr;
	member_addr+=sizeof(param->flash_type);
        param->para_num=*(int *)member_addr;
	member_addr+=sizeof(param->para_num);
        param->addr=member_addr;
	member_addr+=param->para_num*sizeof(struct jz_spi_support_from_burner);
        param->partition_num=*(int *)member_addr;
	member_addr+=sizeof(param->partition_num);
        param->partition=member_addr;
}
int spinand_program(struct cloner *cloner)
{
	u32 length = cloner->cmd->write.length;
	u32 full_size = cloner->full_size;
	void *databuf = (void *)cloner->write_req->buf;
	u32 startaddr = cloner->cmd->write.partation + (cloner->cmd->write.offset);
	char command[128];
	volatile int pt_index;
	struct jz_spinand_partition *partation;
	int ret;

	static int pt_index_bak = -1;
	static char *part_name = NULL;

	partation = get_partion_index(startaddr,&pt_index);
	if(startaddr==0){
		add_information_to_spl(databuf);
	}
	if((!cloner->args->spi_erase) && (partation->manager_mode != UBI_MANAGER)){
		if(pt_index != pt_index_bak){/* erase part partation */
			pt_index_bak = pt_index;
			memset(command, 0 , 128);
			sprintf(command, "nand erase 0x%x 0x%x", partation->offset,partation->size);
			printf("%s\n", command);
			ret = run_command(command, 0);
			if (ret) goto out;
		}
	}

	memset(command, 0 , 128);

	if(partation->manager_mode == MTD_MODE){
		sprintf(command, "nand write.jffs2 0x%x 0x%x 0x%x", (unsigned)databuf, startaddr, length);
		printf("%s\n", command);
		ret = run_command(command, 0);
		if (ret) goto out;
		printf("...ok\n");
	}else if(partation->manager_mode == UBI_MANAGER){
		if(!(part_name == partation->name) && cloner->args->spi_erase){/* need change part */
			memset(command, 0, 128);
			sprintf(command, "ubi part %s", partation->name);
			printf("%s\n", command);
			ret = run_command(command, 0);
			memset(command, 0, X_COMMAND_LENGTH);
			sprintf(command, "ubi create %s",partation->name,partation->size);
			ret = run_command(command, 0);

			if (ret) {
				printf("error...\n");
				return ret;
			}
			part_name = partation->name;
		}

		if(cloner->full_size && !(cloner->args->spi_erase)){
			memset(command, 0, 128);
			sprintf(command, "ubi part %s", partation->name);
			printf("%s\n", command);
			ret = run_command(command, 0);
		}

		memset(command, 0, 128);
		static wlen = 0;
		wlen += length;
		if (full_size && (full_size <= length)) {
			length = full_size;
			sprintf(command, "ubi write 0x%x %s 0x%x", (unsigned)databuf, partation->name, length);
		} else if (full_size) {
			sprintf(command, "ubi write.part 0x%x %s 0x%x 0x%x",(unsigned)databuf, partation->name, length, full_size);
		} else {
			sprintf(command, "ubi write.part 0x%x %s 0x%x",(unsigned)databuf, partation->name, length);
		}


		ret = run_command(command, 0);
		if (ret) {
			printf("...error\n");
			return ret;
		}
	}
	if(cloner->full_size)
		cloner->full_size = 0;
	return 0;
out:
	printf("...error\n");
	return ret;

}
/****************************************************************************************
 * copy spinand information from burner to u-boot-with-spl.bin
 * char *databuf:u-boot-with-spl.bin date pointer
 * in function :
 * param is global variable of struct nand_param_from_burner this struct is information in spinand
 * **************************************************************************************/
void add_information_to_spl(char *databuf)
{
	int page_spl=0;
	int32_t nand_magic=0x6e616e64;
	char *member_addr=databuf;
	page_spl=((nand_param_from_burner.addr->page_num/32)<<16)|((nand_param_from_burner.addr->page_size/1024)<<24);//compatible
	*((int *)(databuf+8))=( *((int *)(databuf+8)))|page_spl;	//write pagesize to spl head
	member_addr+=CONFIG_SPIFLASH_PART_OFFSET;			//spinand parameter number addr
	memcpy((char *)member_addr,&nand_magic,sizeof(int32_t));
	member_addr+=sizeof(int32_t);					//spinand parameter magic  addr
	memcpy((char *)member_addr,&nand_param_from_burner.version,sizeof(nand_param_from_burner.version));
	member_addr+=sizeof(nand_param_from_burner.version);		//spinand parameter number addr
	memcpy((char *)member_addr,&nand_param_from_burner.flash_type,sizeof(nand_param_from_burner.flash_type));
	member_addr+=sizeof(nand_param_from_burner.flash_type);
	memcpy((char *)member_addr,&nand_param_from_burner.para_num,sizeof(nand_param_from_burner.para_num));
	member_addr+=sizeof(nand_param_from_burner.para_num);		//spinand parameter addr
	memcpy((char *)member_addr,nand_param_from_burner.addr,nand_param_from_burner.para_num*sizeof(struct jz_spi_support_from_burner));

	member_addr+=nand_param_from_burner.para_num*sizeof(struct jz_spi_support_from_burner);//spinand partation number addr
	memcpy(member_addr,&nand_param_from_burner.partition_num,sizeof(nand_param_from_burner.partition_num));
	member_addr+=sizeof(nand_param_from_burner.partition_num);		//partition addr
	memcpy(member_addr,nand_param_from_burner.partition,nand_param_from_burner.partition_num*sizeof(struct jz_spinand_partition));	//partition
}
