#define   _T3_IPL_ISR   ipl3 //This sets up the vector for the ISR.  ipl stands for Interupt Priority Level
#define   _T3_IPL_IPC   3
#define   _T3_SPL_IPC   0

unsigned long timeToReset = 0, timerInit = 0, timerDif = 0;  //Global variable declaration
int count = 0, i = 0, hashkey = 0, entrySpeed = 0, exitSpeed = 0, max1 = 5000, max2 = 5000;

int delay_table[4][125][3];
unsigned long hold_table[2][5][2];
int hold_2_1 = 0;
//hold_table [lane][beam][0 = hold time][1 = flag]
