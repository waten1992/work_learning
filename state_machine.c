#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum
{
  STOP = 0,
  RUNNING,
  PAUSE,
  MAX_STATE,
} CD_STATE;


typedef enum
{
  PRESS_RUNNING = 0,
  PRESS_PAUSE,
  PRESS_STOP,
  MAX_EVENT,
} CD_EVENT;

char state_to_str[3][100] = {"STOP", "RUNNING", "PAUSE"};


struct CD_STATE_MECHINE 
{
  int state;
  int event;
  void (*func)(unsigned char *);
};

void do_change_running(unsigned char * user_data);
void do_change_stop(unsigned char * user_data);
void do_change_pause(unsigned char * user_data);

struct CD_STATE_MECHINE state_mechine[] = {
  {RUNNING, PRESS_RUNNING, NULL},
  {RUNNING, PRESS_STOP, do_change_stop},
  {RUNNING, PRESS_PAUSE, do_change_pause},
  {PAUSE, PRESS_RUNNING, do_change_running},
  {PAUSE, PRESS_STOP, do_change_stop},
  {PAUSE, PRESS_PAUSE, NULL},
  {STOP, PRESS_RUNNING, do_change_running},
  {STOP, PRESS_STOP, NULL},
  {STOP, PRESS_PAUSE, do_change_pause},
  {-1, -1, NULL},
};


//全局变量，用来存储CD当前状态
int current_state = STOP;

void do_change_running(unsigned char * user_data)
{
  printf("CD Status from  %s to RUNING\n", state_to_str[current_state]);
  current_state = RUNNING;
}

void do_change_stop(unsigned char * user_data)
{
  printf("CD Status from  '%s' to STOP\n", state_to_str[current_state]);
  current_state = STOP;
}

void do_change_pause(unsigned char * user_data)
{
  printf("CD Status from  '%s' to pause\n", state_to_str[current_state]);
  current_state = PAUSE;
}

int dispather(current_state, event) 
{
  int i = 0;
  for(i = 0; state_mechine[i].state != -1; i++)
  {
    if (current_state == state_mechine[i].state && event == state_mechine[i].event)
    {
      void (*func)(unsigned char *);
      func = state_mechine[i].func;
      if (func != NULL)
      {
        func(NULL);
      }
      else
      {
        printf("state not change!\n");
      }
      break;
    }
  }
}


int main ()
{
  char ch = '0';

  printf ("请输入数字操作CD机(0:RUNNING, 1:PAUSE, 2:STOP):\n");
  while (1)
  {
    ch = getchar();
    if (ch == '\n')
    {
    } 
    else if ((ch < '0') || (ch > '3'))
    {
      printf ("非法输入，请重新输入!\n");
      continue;
    }
    else
    {
      int event = ch - '0';
      dispather(current_state, event);
      printf ("请输入数字操作CD机(0:RUNNING, 1:PAUSE, 2:STOP):\n");
    }
  }
  return 0;
}
