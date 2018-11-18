#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"
#include "../include/emoneylib.h"
#include "../include/md5.h"

int initialization_transaction(int *account_state, int payment_amount)
{
  *account_state -= payment_amount;
  if (*account_state >= 0) {
    return 0;
  } else return 1;
}
