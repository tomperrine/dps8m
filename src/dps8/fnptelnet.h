void fnpTelnetInit (void);
void * ltnConnect (uv_tcp_t * client);
void ltnRaw (telnet_t * client);
void ltnDialout (telnet_t * client);
