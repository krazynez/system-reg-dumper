#include <pspctrl.h>
#include <pspdebug.h>
#include <pspiofilemgr.h>
#include <pspkernel.h>
#include <pspsdk.h>
#include <stdio.h>


#define printf pspDebugScreenPrintf


void dump(const char *f1_file, const char *save_file) {
    SceUID reg = sceIoOpen(f1_file, PSP_O_RDONLY, 0);
    SceUID reg_size = sceIoLseek(reg, 0, PSP_SEEK_END);
    sceIoLseek(reg, 0, PSP_SEEK_SET);
    u8 reg_buf[reg_size];
    sceIoRead(reg, &reg_buf, reg_size);
    SceUID reg_save = sceIoOpen(save_file, PSP_O_WRONLY | PSP_O_TRUNC | PSP_O_CREAT, 0777);
    sceIoWrite(reg_save, reg_buf, reg_size);
	sceIoClose(reg);
	sceIoClose(reg_save);
}
	


PSP_MODULE_INFO("system dreg/ireg expoter", 0, 1, 0);
int main(int args, char *argv[]) {

	pspDebugScreenInit();
    SceUID dc_check = sceIoDopen("ms0:/TM/DCARK/registry");
	if(dc_check < 0) {
		pspDebugScreenClear();
		printf("\n\nYOU NEED TO INSTALL DCARK FIRST!!!\n");
		sceKernelDelayThread(3*1000*1000);
		sceKernelExitGame();
	}
	else 
		sceIoDclose(dc_check);

	printf("\nFYI: You can also just use the 'Boot ARK from Memory Stick'\nvia DCARK to create the files\n\n");

	printf("----------------------------------------------------------|\n");

	printf("| Press X to dump system.ireg and system.dreg from flash1 |\n");
	printf("| Press O to exit                                         |\n");

	printf("----------------------------------------------------------|\n\n");

	SceCtrlData pad;
	while(1) {
		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_CROSS) {
	        printf("Dumping system.dreg\n");
			dump("flash1:/registry/system.dreg", "ms0:/TM/DCARK/registry/system.dreg");
			printf("Saved system.dreg to ms0:/TM/DCARK/registry\n");
	        printf("Dumping system.ireg\n");
			dump("flash1:/registry/system.ireg", "ms0:/TM/DCARK/registry/system.ireg");
			printf("Saved system.ireg to ms0:/TM/DCARK/registry\n");
			sceKernelDelayThread(3*1000*1000);
			break;
		}
		else if(pad.Buttons & PSP_CTRL_CIRCLE) {
			break;
		}

	}
		
	sceKernelExitGame();
				
	return 0;
}

