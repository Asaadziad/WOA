typedef enum {
   UPDATECALL_PLAYER,
} UpdateCall;

void updatecall_player() {
  
}

void (*updatecalls[1])() = {
[UPDATECALL_PLAYER] =  updatecall_player
};
