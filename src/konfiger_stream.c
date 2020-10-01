
#include <konfiger_stream.h>

enum konfiger_stat ks_init(KonfigerStream **out)
{
    KonfigerStream *ks;
    
    ks = (KonfigerStream *) malloc(sizeof(KonfigerStream)); 
    
    *out = ks;
    return KONFIGER_OK;
}