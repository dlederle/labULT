#include <assert.h>

/* We want the extra information from these definitions */
#ifndef __USE_GNU
#define __USE_GNU
#endif /* __USE_GNU */
#include <ucontext.h>

#include "ULT.h"



Tid ULT_CreateThread(void (*fn)(void *), void *parg)
{
  assert(0); /* TBD */
  return ULT_FAILED;
}



Tid ULT_Yield(Tid wantTid)
{
  int i;
  if(wantTid == ULT_SELF) {
    wantTid = current.tid;    
  }
  if(wantTid == ULT_ANY) {
    for(i = 0;i < ULT_MAX_THREADS;i++) {
      if(blocks[i]) {
        wantTid = i; 
        break; 
      }
    }
    if(wantTid == ULT_ANY) {
      return ULT_NONE; 
    }
  }
  if(!blocks[wantTid]) {
    return ULT_INVALID; 
  }
  ucontext_t mycontext;
  int err = getcontext(&mycontext);
  assert(!err); /* TBD */

  mycontext.uc_mcontext.gregs[REG_EIP]++;
  current.context = mycontext;
  current.tid = wantTid; 
  setcontext(&(blocks[wantTid]->context)); 
  
    
 
  return wantTid;

}


Tid ULT_DestroyThread(Tid tid)
{
  assert(0); /* TBD */
  return ULT_FAILED;
}





