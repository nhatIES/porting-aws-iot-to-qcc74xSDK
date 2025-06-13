#include "qcc74x_irq.h"
#include "qcc74x_core.h"
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
#include <risc-v/e24/clic.h>
#else
#include <csi_core.h>
#endif

#if defined(QCC74x_undef)
#include "qcc74x_undef_irq.h"
#endif

#ifndef QCC74x_IOT_SDK
extern struct qcc74x_irq_info_s g_irqvector[];

static void irq_unexpected_isr(int irq, void *arg)
{
    printf("irq :%d unregistered\r\n", irq);
}
#endif
void qcc74x_irq_initialize(void)
{
#ifndef QCC74x_IOT_SDK
    int i;

    /* Point all interrupt vectors to the unexpected interrupt */
    for (i = 0; i < CONFIG_IRQ_NUM; i++) {
        g_irqvector[i].handler = irq_unexpected_isr;
        g_irqvector[i].arg = NULL;
    }
#endif
}

ATTR_TCM_SECTION uintptr_t qcc74x_irq_save(void)
{
#ifdef romapi_qcc74x_irq_save
    return romapi_qcc74x_irq_save();
#else
    uintptr_t oldstat;

    /* Read mstatus & clear machine interrupt enable (MIE) in mstatus */

    asm volatile("csrrc %0, mstatus, %1"
                 : "=r"(oldstat)
                 : "r"(MSTATUS_MIE));
    return oldstat;
#endif
}

ATTR_TCM_SECTION void qcc74x_irq_restore(uintptr_t flags)
{
#ifdef romapi_qcc74x_irq_restore
    romapi_qcc74x_irq_restore(flags);
#else
    /* Write flags to mstatus */

    asm volatile("csrw mstatus, %0"
                 : /* no output */
                 : "r"(flags));
#endif
}

#if (defined(QCC74x_undef) && defined(CPU_LP))
void qcc74x_undef_level2_irq_handler(int irq, void *arg0)
{
    irq_callback handler;
    void *arg;
    uint32_t irq_num;
    uint64_t level2_irq_state = 0;

    level2_irq_state = GLB_Get_NP2MINI_Interrupt_Status();

    for (uint32_t i = 0; i < QCC74x_undef_IRQ_LEVEL2_SIZE; i++) {
        if ((level2_irq_state >> i) & 0x1) {
            irq_num = QCC74x_undef_IRQ_LEVEL2_BASE + 1 + i;
            handler = g_irqvector[irq_num].handler;
            arg = g_irqvector[irq_num].arg;
            if ((handler)) {
                handler(irq_num, arg);
                GLB_Set_NP2MINI_Interrupt_Clear(irq_num);
            } else {
                qcc74x_lhal_assert_func(__FILE__, __LINE__, __FUNCTION__, "handler is NULL");
            }
        }
    }
}
#endif

int qcc74x_irq_attach(int irq, irq_callback isr, void *arg)
{
    if (irq >= CONFIG_IRQ_NUM) {
        return -EINVAL;
    }
#ifndef QCC74x_IOT_SDK
#if (defined(QCC74x_undef) && defined(CPU_LP))
    if (irq >= QCC74x_undef_IRQ_LEVEL2_BASE) {
        g_irqvector[QCC74x_undef_IRQ_LEVEL2_BASE].handler = qcc74x_undef_level2_irq_handler;
        g_irqvector[QCC74x_undef_IRQ_LEVEL2_BASE].arg = arg;
    }
#endif
    g_irqvector[irq].handler = isr;
    g_irqvector[irq].arg = arg;
#else
    extern void qcc74x_irq_register_with_ctx(int irqnum, void *handler, void *ctx);
    qcc74x_irq_register_with_ctx(irq, (void *)isr, arg);
#endif
    return 0;
}

int qcc74x_irq_detach(int irq)
{
    if (irq >= CONFIG_IRQ_NUM) {
        return -EINVAL;
    }
#ifndef QCC74x_IOT_SDK
    g_irqvector[irq].handler = irq_unexpected_isr;
    g_irqvector[irq].arg = NULL;
#endif
    return 0;
}

void qcc74x_irq_enable(int irq)
{
#ifdef romapi_qcc74x_irq_enable
    romapi_qcc74x_irq_enable(irq);
#else
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    putreg8(1, CLIC_HART0_BASE + CLIC_INTIE_OFFSET + irq);
#else
#if (defined(QCC74x_undef) || defined(QCC74x_undef)) && defined(CPU_D0)
    if (csi_vic_get_prio(irq) == 0) {
        csi_vic_set_prio(irq, 1);
    }
#endif
#if (defined(QCC74x_undef) && defined(CPU_LP))
    if (irq >= QCC74x_undef_IRQ_LEVEL2_BASE) {
        csi_vic_enable_irq(QCC74x_undef_IRQ_LEVEL2_BASE);
    } else {
        csi_vic_enable_irq(irq);
    }
#else
    csi_vic_enable_irq(irq);
#endif
#endif
#endif
}

void qcc74x_irq_disable(int irq)
{
#ifdef romapi_qcc74x_irq_disable
    romapi_qcc74x_irq_disable(irq);
#else
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    putreg8(0, CLIC_HART0_BASE + CLIC_INTIE_OFFSET + irq);
#else
#if (defined(QCC74x_undef) && defined(CPU_LP))
    if (irq >= QCC74x_undef_IRQ_LEVEL2_BASE) {
        csi_vic_disable_irq(QCC74x_undef_IRQ_LEVEL2_BASE);
    } else {
        csi_vic_disable_irq(irq);
    }
#else
    csi_vic_disable_irq(irq);
#endif
#endif
#endif
}

void qcc74x_irq_set_pending(int irq)
{
#ifdef romapi_qcc74x_irq_set_pending
    romapi_qcc74x_irq_set_pending(irq);
#else
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    putreg8(1, CLIC_HART0_BASE + CLIC_INTIP_OFFSET + irq);
#else
#if (defined(QCC74x_undef) && defined(CPU_LP))
    if (irq >= QCC74x_undef_IRQ_LEVEL2_BASE) {
        csi_vic_set_pending_irq(QCC74x_undef_IRQ_LEVEL2_BASE);
    } else {
        csi_vic_set_pending_irq(irq);
    }
#else
    csi_vic_set_pending_irq(irq);
#endif
#endif
#endif
}

void qcc74x_irq_clear_pending(int irq)
{
#ifdef romapi_qcc74x_irq_clear_pending
    romapi_qcc74x_irq_clear_pending(irq);
#else
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    putreg8(0, CLIC_HART0_BASE + CLIC_INTIP_OFFSET + irq);
#else
#if (defined(QCC74x_undef) && defined(CPU_LP))
    if (irq >= QCC74x_undef_IRQ_LEVEL2_BASE) {
        csi_vic_clear_pending_irq(QCC74x_undef_IRQ_LEVEL2_BASE);
    } else {
        csi_vic_clear_pending_irq(irq);
    }
#else
    csi_vic_clear_pending_irq(irq);
#endif
#endif
#endif
}

void qcc74x_irq_set_nlbits(uint8_t nlbits)
{
#ifdef romapi_qcc74x_irq_set_nlbits
    romapi_qcc74x_irq_set_nlbits(nlbits);
#else
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    uint8_t clicCfg = getreg8(CLIC_HART0_BASE + CLIC_CFG_OFFSET);
    putreg8((clicCfg & 0xe1) | ((nlbits & 0xf) << 1), CLIC_HART0_BASE + CLIC_CFG_OFFSET);
#else
#if !defined(CPU_D0)
    CLIC->CLICCFG = ((nlbits & 0xf) << 1) | 1;
#endif
#endif
#endif
}

void qcc74x_irq_set_priority(int irq, uint8_t preemptprio, uint8_t subprio)
{
    if (irq >= CONFIG_IRQ_NUM) {
        return;
    }
#ifdef romapi_qcc74x_irq_set_priority
    romapi_qcc74x_irq_set_priority(irq, preemptprio, subprio);
#else
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    uint8_t nlbits = getreg8(CLIC_HART0_BASE + CLIC_CFG_OFFSET) >> 1 & 0xf;
    uint8_t clicIntCfg = getreg8(CLIC_HART0_BASE + CLIC_INTCFG_OFFSET + irq);
    putreg8((clicIntCfg & 0xf) | (preemptprio << (8 - nlbits)) | ((subprio & (0xf >> nlbits)) << 4), CLIC_HART0_BASE + CLIC_INTCFG_OFFSET + irq);
#else
#if (defined(QCC74x_undef) && defined(CPU_LP))
    if (irq >= QCC74x_undef_IRQ_LEVEL2_BASE) {
        csi_vic_set_prio(QCC74x_undef_IRQ_LEVEL2_BASE, preemptprio);
    } else {
        csi_vic_set_prio(irq, preemptprio);
    }
#else
    csi_vic_set_prio(irq, preemptprio);
#endif
#endif
#endif
}
