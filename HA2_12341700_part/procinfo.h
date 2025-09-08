struct proc_info{
  int pid;
  int ppid;
  int sz;
  char state[16];
  char name[16];
};
