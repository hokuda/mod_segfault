/* 
**  mod_test.c -- Apache sample test module
**  [Autogenerated via ``apxs -n test -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_test.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /test in as follows:
**
**    #   httpd.conf
**    LoadModule test_module modules/mod_test.so
**    <Location /test>
**    SetHandler test
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /test and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/test 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_test.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#include "stdio.h"
#include "http_log.h"

/* The sample content handler */
static int segfault_handler(request_rec *r)
{
    if (strcmp(r->handler, "segfault")) {
        return DECLINED;
    }

    char *p = 0;
    *p = 0;
    
    return OK;
}

static void segfault_register_hooks(apr_pool_t *p)
{
  fprintf(stderr, "hello segfault!!\n"); // go to journalctl
  ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, "_________________hello segfault___________________ [   %d    ]", 0);
  ap_hook_handler(segfault_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA segfault_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    segfault_register_hooks  /* register hooks                      */
};

