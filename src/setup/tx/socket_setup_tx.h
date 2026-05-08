#include "config/proto_hdr.h"
#include "setup/socket_options.h"

typedef struct {
    Socket sock;
    struct sockaddr_in rx_addr;
    const char* data;
} Tx;


int tx_init(Tx *tx, const char *ip, uint32_t port);

int tx_connect(Tx *tx);

int tx_send(Tx *tx);

int tx_close(Tx *tx);

// Suggestion:
//  make choose what arguments functions should handle
//
//  Examples:
//      1.
//          tx_send(Tx *tx, char* data)
//              * More flexible
//              * Easier to understand
//      2.  tx_send(Tx *tx) "now"
//              * More secure
//              * Harder to understand
