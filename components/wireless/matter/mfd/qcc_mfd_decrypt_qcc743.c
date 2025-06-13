#include QCC74x_MFD_PLAT_H

bool qcc74x_mfd_decrypt(uint8_t *p, uint32_t len, uint8_t *pout, uint32_t *pIv)
{
    struct qcc74x_device_s *aes;

    aes = qcc74x_device_get_by_name("aes");
    if (0 == len || NULL == aes) {
        return false;
    }

    qcc74x_group0_request_aes_access(aes);

    qcc74x_aes_init(aes);
    qcc74x_aes_set_mode(aes, AES_MODE_CBC);
    qcc74x_aes_setkey(aes, NULL, 128);
    qcc74x_aes_select_hwkey(aes, 1, 0);

    qcc74x_l1c_dcache_clean_all();
    qcc74x_l1c_dcache_disable();
    int iret = qcc74x_aes_decrypt(aes, p, (uint8_t*)pIv, pout, len);
    qcc74x_l1c_dcache_enable();

    qcc74x_aes_deinit(aes);
    qcc74x_group0_release_aes_access(aes);

    return 0 == iret;
}
