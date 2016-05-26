#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <artik_module.h>
#include <artik_platform.h>
static artik_adc_config config = { 0, "adc" };
artik_error adc_test_value()
{
    artik_adc_handle handle;
    artik_error ret = S_OK;
    artik_adc_module* adc = (artik_adc_module*)artik_get_api_module("adc");
    int i = 0;
    fprintf(stdout, "TEST: %s\n", __func__);
    ret = adc->request(&handle, &config);
    if (ret != S_OK) {
        fprintf(stderr, "TEST: %s - Failed to request adc (err=%d)\n", __func__, ret);
        return ret;
    }
    for (i=0; i<5; i++) {
        fprintf(stdout, "TEST: %s - Value = %d\n", __func__, adc->get_value(handle));
        usleep(1000*1000);
    }
    adc->release(handle);
    fprintf(stdout, "TEST: %s suceeded\n", __func__);
    return S_OK;
}
int main()
{
    artik_error ret = S_OK;
    ret = adc_test_value();
    return (ret == S_OK) ? 0 : -1;
}
