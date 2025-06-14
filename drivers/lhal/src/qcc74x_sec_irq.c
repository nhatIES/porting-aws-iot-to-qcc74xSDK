#include "qcc74x_sec_irq.h"
#include "hardware/sec_eng_reg.h"

struct qcc74x_sec_irq_callback {
    void (*handler)(void *arg);
    void *arg;
};

#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
#define QCC74x_SEC_ENG_BASE ((uint32_t)0x40004000)
#elif defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
#define QCC74x_SEC_ENG_BASE ((uint32_t)0x20004000)
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
#define QCC74x_SEC_ENG_BASE ((uint32_t)0x20080000)
#endif

struct qcc74x_sec_irq_callback sec_eng_callback[6];

void sec_eng_isr(int irq, void *arg)
{
    uint32_t regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    if (regval & SEC_ENG_SE_AES_0_INT) {
        regval |= SEC_ENG_SE_AES_0_INT_CLR_1T;
        putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_AES_0_CTRL_OFFSET);
        if (sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_AES].handler) {
            sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_AES].handler(sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_AES].arg);
        }
    }

    regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_SHA_0_CTRL_OFFSET);
    if (regval & SEC_ENG_SE_SHA_0_INT) {
        regval |= SEC_ENG_SE_SHA_0_INT_CLR_1T;
        putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_SHA_0_CTRL_OFFSET);
        if (sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_SHA].handler) {
            sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_SHA].handler(sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_SHA].arg);
        }
    }

    regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_PKA_0_CTRL_0_OFFSET);
    if (regval & SEC_ENG_SE_PKA_0_INT) {
        regval |= SEC_ENG_SE_PKA_0_INT_CLR_1T;
        putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_PKA_0_CTRL_0_OFFSET);
        if (sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_PKA].handler) {
            sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_PKA].handler(sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_PKA].arg);
        }
    }

    regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    if (regval & SEC_ENG_SE_TRNG_0_INT) {
        regval |= SEC_ENG_SE_TRNG_0_INT_CLR_1T;
        putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
        if (sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_TRNG].handler) {
            sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_TRNG].handler(sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_TRNG].arg);
        }
    }

    regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_GMAC_0_CTRL_0_OFFSET);
    if (regval & SEC_ENG_SE_GMAC_0_INT) {
        regval |= SEC_ENG_SE_GMAC_0_INT_CLR_1T;
        putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_GMAC_0_CTRL_0_OFFSET);
        if (sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_GMAC].handler) {
            sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_GMAC].handler(sec_eng_callback[QCC74x_SEC_ENG_IRQ_TYPE_GMAC].arg);
        }
    }
}

void qcc74x_sec_int_mask(uint8_t sec_type, bool mask)
{
    uint32_t regval;

    switch (sec_type) {
        case QCC74x_SEC_ENG_IRQ_TYPE_AES:
            regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_AES_0_CTRL_OFFSET);
            if (mask) {
                regval |= SEC_ENG_SE_AES_0_INT_MASK;
            } else {
                regval &= ~SEC_ENG_SE_AES_0_INT_MASK;
            }
            putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_AES_0_CTRL_OFFSET);
            break;
        case QCC74x_SEC_ENG_IRQ_TYPE_SHA:
            regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_SHA_0_CTRL_OFFSET);
            if (mask) {
                regval |= SEC_ENG_SE_SHA_0_INT_MASK;
            } else {
                regval &= ~SEC_ENG_SE_SHA_0_INT_MASK;
            }
            putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_SHA_0_CTRL_OFFSET);
            break;
        case QCC74x_SEC_ENG_IRQ_TYPE_PKA:
            regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_PKA_0_CTRL_0_OFFSET);
            if (mask) {
                regval |= SEC_ENG_SE_PKA_0_INT_MASK;
            } else {
                regval &= ~SEC_ENG_SE_PKA_0_INT_MASK;
            }
            putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_PKA_0_CTRL_0_OFFSET);
            break;
        case QCC74x_SEC_ENG_IRQ_TYPE_TRNG:
            regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
            if (mask) {
                regval |= SEC_ENG_SE_TRNG_0_INT_MASK;
            } else {
                regval &= ~SEC_ENG_SE_TRNG_0_INT_MASK;
            }
            putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
            break;
        case QCC74x_SEC_ENG_IRQ_TYPE_GMAC:
            regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_GMAC_0_CTRL_0_OFFSET);
            if (mask) {
                regval |= SEC_ENG_SE_GMAC_0_INT_MASK;
            } else {
                regval &= ~SEC_ENG_SE_GMAC_0_INT_MASK;
            }
            putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_GMAC_0_CTRL_0_OFFSET);
            break;
        case QCC74x_SEC_ENG_IRQ_TYPE_CDET:
            regval = getreg32(QCC74x_SEC_ENG_BASE + SEC_ENG_SE_CDET_0_CTRL_0_OFFSET);
            if (mask) {
                regval |= SEC_ENG_SE_CDET_0_INT_MASK;
            } else {
                regval &= ~SEC_ENG_SE_CDET_0_INT_MASK;
            }
            putreg32(regval, QCC74x_SEC_ENG_BASE + SEC_ENG_SE_CDET_0_CTRL_0_OFFSET);
            break;

        default:
            break;
    }
}

void qcc74x_sec_irq_attach(uint8_t sec_type, void (*callback)(void *arg), void *arg)
{
    sec_eng_callback[sec_type].handler = callback;
    sec_eng_callback[sec_type].arg = arg;
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    qcc74x_irq_attach(25, sec_eng_isr, NULL);
    qcc74x_irq_attach(26, sec_eng_isr, NULL);
    qcc74x_irq_attach(27, sec_eng_isr, NULL);
    qcc74x_irq_attach(28, sec_eng_isr, NULL);
    qcc74x_irq_attach(29, sec_eng_isr, NULL);
    qcc74x_irq_attach(30, sec_eng_isr, NULL);
    qcc74x_irq_enable(25);
    qcc74x_irq_enable(26);
    qcc74x_irq_enable(27);
    qcc74x_irq_enable(28);
    qcc74x_irq_enable(29);
    qcc74x_irq_enable(30);
#elif (defined(QCC74x_undef) || defined(QCC74x_undef)) && (defined(CPU_M0) || defined(CPU_LP))
    qcc74x_irq_attach(25, sec_eng_isr, NULL);
    qcc74x_irq_attach(26, sec_eng_isr, NULL);
    qcc74x_irq_attach(27, sec_eng_isr, NULL);
    qcc74x_irq_attach(28, sec_eng_isr, NULL);
    qcc74x_irq_enable(25);
    qcc74x_irq_enable(26);
    qcc74x_irq_enable(27);
    qcc74x_irq_enable(28);
#elif defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    qcc74x_irq_attach(25, sec_eng_isr, NULL);
    qcc74x_irq_attach(26, sec_eng_isr, NULL);
    qcc74x_irq_attach(27, sec_eng_isr, NULL);
    qcc74x_irq_attach(28, sec_eng_isr, NULL);
    qcc74x_irq_enable(25);
    qcc74x_irq_enable(26);
    qcc74x_irq_enable(27);
    qcc74x_irq_enable(28);
#endif
    qcc74x_sec_int_mask(sec_type, false);
}

void qcc74x_sec_irq_detach(uint8_t sec_type)
{
    sec_eng_callback[sec_type].handler = NULL;
    sec_eng_callback[sec_type].arg = NULL;
    qcc74x_sec_int_mask(sec_type, true);
}
